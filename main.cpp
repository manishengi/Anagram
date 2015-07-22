#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>

#define ASCII_BASE 65
using namespace std;
const int PRIME_FACTORS[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};


struct keyComparator
{
    bool operator () (const unsigned long long first, const unsigned long long second) const
    {
        return (first > second);
    }
};

multimap<unsigned long long, string, keyComparator> AnagramsMap;




bool checkFileExistence(const string& filename)
{
    ifstream f(filename.c_str());
    return f.is_open();
}

void getFile(string filename, ifstream& file)
{
    const bool file_exists = checkFileExistence(filename);
    if (!file_exists) {
        cout<<"\n unable to open file";
    }
    file.open(filename.c_str());
}

int getPrimeFactorForCharacter ( char alphabet )
{
    return PRIME_FACTORS[alphabet-ASCII_BASE];

}

unsigned long long computeHashForEachWord ( string word )
{
    unsigned long long primeValueForWord = 1;

    for (int index = 0; index < word.size(); index++ )
    {
           primeValueForWord *= getPrimeFactorForCharacter( word[index] );
    }

    //cout<< "\n word  "<< word <<" value "<<primeValueForWord  << endl;
    return primeValueForWord;
}
void hashEachWord( unsigned long long hashkey, string word)
{
    AnagramsMap.insert(pair<unsigned long long,string> (hashkey,word));
    //cout << "the count of anagrams is " << AnagramsMap.count (hashkey) << endl;
}


void printAnagrams()
{

    pair<multimap<unsigned long long , string>::iterator, multimap<unsigned long long, string>::iterator> valueIterator;


    for ( multimap<unsigned long long, string, keyComparator>::iterator it = AnagramsMap.begin();
         it != AnagramsMap.end();)
    {
        valueIterator = AnagramsMap.equal_range((*it).first);

        int noOfValuesforKey = AnagramsMap.count((*it).first);

        if(noOfValuesforKey == 1)
        {
            it++;
            continue;
        }

        for (multimap<unsigned long long, string>::iterator iterate = valueIterator.first;
                iterate != valueIterator.second;
                ++iterate)
        {
            cout <<  " " << (*iterate).second ;
        }
        cout << endl;

        for(int dummyIncrementor = 0; dummyIncrementor < noOfValuesforKey; dummyIncrementor++)
        {
            it++;
        }
    }
}



int main()
{
    ifstream file;
    string word;
    getFile("scrabble.txt", file);
    if (file.is_open()) {

        while (getline (file,word))
        {
            unsigned long long hashkey = computeHashForEachWord(word);
            //cout << "the hashkey" << hashkey << endl;
            hashEachWord (hashkey, word);
        }
    }

    printAnagrams();

}
