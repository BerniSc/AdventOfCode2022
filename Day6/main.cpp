/******************************************************************************
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

static string data;

vector<vector<string>> linesBernhard;
vector<vector<string>> linesJasmina;

vector<string> singleLinesJasmina;
vector<string> singleLinesBernhard;

char memory[4] = {' ', ' ', ' ', ' '};
char memory2[14] = {' ', ' ', ' ', ' ',' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' '};

static int sumBernhard = 0;
static int sumJasmina = 0;

static int sumBernhardPart2 = 0;
static int sumJasminaPart2 = 0;

void printLines(const vector<vector<string>> &vec, vector<string> &singleLines) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << endl;
            singleLines.push_back(vec[i][j]);
        }
        cout << endl;
    }    
}

vector<string>& seperateStringTwoParts(string toSeperate, const char *seperator) {
    static vector<string> result;
    result.clear();
    char* dataAsPointer = &toSeperate[0];
    char* part1 = strtok(dataAsPointer, seperator);
    result.push_back(part1);
    char* part2 = strtok(NULL, seperator);
    result.push_back(part2);
    
    return result;
}

bool checkIfInSet(char set[], int iterations) {
    for(int i = 0; i < iterations; i++) {
        for(int j = 0; j < iterations; j++) {
            if(set[i] == set[j] && i != j) {
                return true;
            }
        }
    }
    return false;
}

void processData(const vector<string> &vecSingle, char memory[], int &sum, int size) {
    cout << endl;
    for(int i = 0; i < size; i++) {
        memory[i] = vecSingle[0][i];
    }
    for(int i = size; i < vecSingle[0].size(); i++) {
        char dummy = vecSingle[0][i];
        if(!checkIfInSet(memory, size)) {
            sum = i;
            break;
        }
        memory[i%size] = dummy;
    }
}

void processDataPart2Jasmina(string s) {
    int counter = 0;
    for(int i = 0; i <= s.size()-14; i++) {
        counter = 0;
        for(int j = 0; j < 14; j++) {
            for(int k = 0; k < 14; k++) {
                if(!(j != k && s[j+i] == s[i+k])) {
                    counter++;
                    //cout << k+j << "als Lösung "<< endl;
                }
            }
        }
        if(counter==196) {
            cout << "LÖsung Jasmina " << i+14;
            break;
        }
    }
}

int main() {
    ifstream myfileB, myfileJ;
    
    myfileB.open("bernhard.txt");
    
    vector<string> paragraph;
    
    if(myfileB.is_open()) {
        while(myfileB) {
            if(myfileB.eof()) data = "";
            getline(myfileB, data);
            if(data != "") {
                paragraph.push_back(data);
            } else {
                linesBernhard.push_back(paragraph);
                paragraph.clear();
            }
        }
    }
    printLines(linesBernhard, singleLinesBernhard);
    processData(singleLinesBernhard, memory ,sumBernhard, 4);
    processData(singleLinesBernhard, memory2, sumBernhardPart2, 14);
    //processDataPart2Jasmina(singleLinesBernhard[0]);

    myfileJ.open("jasmina.txt");
    
    if(myfileJ.is_open()) {
        while(myfileJ) {
            if(myfileJ.eof()) data = "";
            getline(myfileJ, data);
            if(data != "") {
                paragraph.push_back(data);
            } else {
                linesJasmina.push_back(paragraph);
                paragraph.clear();
            }
        }
    }

    printLines(linesJasmina, singleLinesJasmina);
    processData(singleLinesJasmina, memory, sumJasmina, 4);
    processData(singleLinesJasmina, memory2, sumJasminaPart2, 14);
    //processDataPart2Jasmina(singleLinesJasmina[0]);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}