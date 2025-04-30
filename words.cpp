
#include <iostream>
#include <string>
#include <unistd.h>
#include "MyVector.h"


using namespace std;


struct WordInfo {
    string text;
    int count;

    // default constructor
    WordInfo() : text(""), count(0) {}

    // constructor[paramterised]
    WordInfo(const string& t) : text(t), count(1) {}
};


int findWord(const MyVector<string>& vec, const string& word) {
    for (size_t i = 0; i< vec.size();++i) {
        if (vec[i] == word) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int main(int argc, char** argv)
{
    enum {
        total,
        unique,
        iterative
    } mode  = total;

    // CLI controler
    for (int c; (c = getopt(argc, argv, "tui")) != -1;) {
        switch (c) {

            case 't':
                mode = total;
                break;

            case 'u':
                mode = unique;
                break;

            case 'i':
                mode = iterative;
                break;

            default:
                break;
        }
    }
    argc -= optind;
    argv += optind;

    string word;
    int count = 0;

    //  unique vectors -- iterative mode
     MyVector<string> uniqueWords;
     MyVector<WordInfo> wordInfos;

    while (cin >> word) {
        count += 1;
        if (mode == unique || mode == iterative)
            {
            int index = findWord(uniqueWords, word);
            if (index == -1) {
                uniqueWords.push_back(word);
                WordInfo wi(word);
                wordInfos.push_back(wi);
            } else {
                wordInfos[index].count += 1;
            }
        }
    }
// MODES
    switch (mode) {

        case total:
            cout << "Total: " << count << '\n';
            break;


        case unique:
            cout << "Unique: " << uniqueWords.size() << '\n';
            break;


        case iterative:
            // insertion sort algo
            for (size_t i = 1; i < wordInfos.size(); ++i) {
                 WordInfo key = wordInfos[i];
                 int j = static_cast<int>(i) - 1;

                while (j >= 0 && wordInfos[j].text > key.text) {
                    wordInfos[j + 1] = wordInfos[j];
                    j--;
                }
                 wordInfos[j + 1] = key;
            }
            for (size_t i = 0; i < wordInfos.size(); ++i) {
                cout << wordInfos[i].text << ": " << wordInfos[i].count << '\n';
            }
            break;
     }

     return 0;
}
