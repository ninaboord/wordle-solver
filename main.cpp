#include <iostream>
#include "lexicon.h"
#include "vector.h"
#include <string.h>
using namespace std;

// given placement of letters and letters that are contained in the word but NOT in that place
// return/print list of words that this word could be
// enter into console e.g. LO___ then ___RE

Vector<char> greenLetters =  {' ', 'o', ' ', ' ', 'y'};
Vector<Vector<char>> yellowLetters =  {{' ', ' ', ' ', 'h', ' '}, {' ', ' ', ' ', ' ', ' '}};
Set<char> grayLetters = {'s', 'a', 'r', 'e', 'n', 'i', 'g', 'u', 'c', 'k'};

bool containsChar(const string& word, const char ch){
    for (char character: word){
        if (character == ch){
            return true;
        }
    }
    return false;
}

bool matchesGreen(const Vector<char>& greenLetters, const string& word){
    int index = 0;
    while (index < 5 && (greenLetters[index] == ' ' || greenLetters[index] == word[index])){
       index++;
    }
    return index == 5;
}

bool matchesYellow(const Vector<Vector<char>>& yellowLetters, const string& word){
       int i = 0;
       int lines = 0;
        for (Vector<char> yellows: yellowLetters){
            for (char ch: yellows){
                if ((ch == ' ' || containsChar(word, ch)) && i < 5){
                    i++;
                }
                if (i == 5){ // first vector matches
                    lines++; // add one to counter
                    i = 0; // reset counter
                }
            }
            for (int index = 0; index < 5; index++){
               if (word[index] == yellows[index]){
                   return false;
               }
            }
    }
  return lines == yellowLetters.size();
        }

bool matchesGray(const Set<char> grayLetters, const string& word){
    for(char ch: grayLetters){
        if (containsChar(word, ch)){
            return false;
        }
    }
    return true;
}

Set<string> findWordle(const Vector<char>& greenLetters, const Vector<Vector<char>>& yellowLetters, Lexicon& fiveLetterWords){
    Set<string> possibleWords;
    for (string word: fiveLetterWords){
        if (matchesGreen(greenLetters, word) && matchesYellow(yellowLetters, word) && matchesGray(grayLetters, word)){
            possibleWords += word;
        }
    }
    return possibleWords;
}



int main()
{
    Lexicon english("EnglishWords.txt");
    Lexicon fiveLetterWords;
    for (string word: english){
        if (word.length() == 5){
            fiveLetterWords += word;
        }
    }
    string letters;
    cout << "possible words: " << endl << findWordle(greenLetters, yellowLetters, fiveLetterWords) << endl;
    return 0;
};
