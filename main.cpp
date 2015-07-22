#include <iostream>
#include <fstream>
#include <string>
#define ASCII_BASE 65
using namespace std;
const int PRIME_FACTORS[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

multimap<unsigned long long,string> AnagramsMap;


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
    unsigned long long primeValueforWord = 1;

    for (int index = 0; index < word.size(); index++ )
    {
           primeValueforWord *= getPrimeFactorForCharacter( word[index] );
    }

    cout<< "\n word  "<< word <<" value "<<primeValueforWord;
}
void hashEachWord( unsigned long long hashkey, string word)
{
    AnagramsMap.insert(pair<unsigned long long,string> (hashkey,word));

}
int main()
{
    ifstream file;
    string word;
    getFile("a.txt.txt", file);
    if (file.is_open()) {

        while (getline (file,word))
        {
           // cout << word << "\n";
            unsigned long long hashkey = computeHashForEachWord(word);
            hashEachWord (hashkey, word);

        }
    }

}