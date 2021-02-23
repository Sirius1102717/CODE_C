#include<bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <ios>
#include <utility>
using namespace std;

const int DIVISOR = 4099;
const int MAX_CODES = 4096;
const int BYTE_SIZE = 8;
const int EXCESS = 4;
const int ALPHA = 256;
const int MASK1 = 255;
const int MASK2 = 15;


template<class K, class E>
pair<const K, E> *find(const K &theKey) const
{
    return table[hash(theKey) % DIVISOR].find(theKey);
}


typedef pair<const long , int> pairType;

int leftOver;
bool bitsLeftOver = false;
ifstream in;
ofstream out;


void setFiles(int argc, char *argv[])
{
    char outputFile[50], inputFile[54];
    if (argc >= 2)
        strcpy(inputFile, argv[1]);
    else {
        cout << "Enter name of file to compress" << "\n";
        cin >> inputFile;
    }

    in.open(inputFile , ios::binary);
    if (in.fail()) {
        cerr << "Cannot open " << inputFile << "\n";
        exit(1);
    }
    strcpy(outputFile, inputFile);
    strcat(outputFile, ".zzz");
    out.open(outputFile, ios::binary);
}

void output(long pcode)
{
    int c, d;
    if (bitsLeftOver) {
        d = int(pcode & MASK1);
        c = int((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
        out.put(c);
        out.put(d);
        bitsLeftOver = false;
    } else {
        leftOver = pcode &MASK2;
        c = int(pcode >> EXCESS);
        out.put(c);
        bitsLeftOver = true;
    }
}

void compress()
{
    hashChains<long, int> h(DIVISOR);
    for (int i = 0; i < ALPHA; i++)
        h.insert(pairType(i, 0));
    int codesUsed = ALPHA;


    int c = in.get();
    if ( c != EOF) {
        long pcode = c;
        while ((c = in.get()) != EOF) {
            long theKey = (pcode << BYTE_SIZE) + c;
            pairType *thePair = h.find(theKey);
            if (theKey == nullptr) {
                output(pcode);
                if (codesUsed < MAX_CODES) 
                    h.insert(pairType((pcode << BYTE_SIZE) | c, codesUsed));
                pcode = c;
            } else {
                pcode = thePair->second;
            }
        }

        output(pcode);
        out.put(leftOver << EXCESS);
    }
    
    out.close();
    in.close();
}

int main(int argc, char *argv[])
{
    setFiles(argc,  argv);
    compress();
}