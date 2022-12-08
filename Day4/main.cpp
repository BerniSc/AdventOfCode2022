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

void evenFurtherProcessingPart2(string _elve1_1, string _elve1_2, string _elve2_1, string _elve2_2, int &sum) {
    int elve1_1 = stoi(_elve1_1);
    int elve1_2 = stoi(_elve1_2);
    int elve2_1 = stoi(_elve2_1);
    int elve2_2 = stoi(_elve2_2);

    if(((elve1_2 - elve2_1) >= 0) && elve1_1 <= elve2_2) {
        sum += 1;
        return;
    }
}

void evenFurtherProcessing(string _elve1_1, string _elve1_2, string _elve2_1, string _elve2_2, int &sum) {
    int elve1_1 = stoi(_elve1_1);
    int elve1_2 = stoi(_elve1_2);
    int elve2_1 = stoi(_elve2_1);
    int elve2_2 = stoi(_elve2_2);

    if(elve1_1 >= elve2_1 && elve1_2 <= elve2_2) {
        sum += 1;
        return;
    }

    if(elve1_1 <= elve2_1 && elve1_2 >= elve2_2) sum += 1;
}

void furtherProcessing(string arg1, string arg2, const char* seperator1, const char* seperator2, int &sum, int &sum2) {
        char* dataAsPointer1 = &arg1[0];
        char* elve1_1 = strtok(dataAsPointer1, seperator1);
        char* elve1_2 = strtok(NULL, seperator2);
        //cout << "Test: " << elve1_1 << "    " << elve1_2 << endl;

        char* dataAsPointer2 = &arg2[0];
        char* elve2_1 = strtok(dataAsPointer2, seperator1);
        char* elve2_2 = strtok(NULL, seperator2);
        //cout << "Test: " << elve2_1 << "    " << elve2_2 << endl;

        evenFurtherProcessing(elve1_1, elve1_2, elve2_1, elve2_2, sum);
        evenFurtherProcessingPart2(elve1_1, elve1_2, elve2_1, elve2_2, sum2);
        
}

void processData(const vector<string> &vecSingle, int &sum, int &sum2) {
    for(int i = 0; i < vecSingle.size(); i++) {
        string dummy = vecSingle[i];
        char* dataAsPointer = &dummy[0];
        char* elve1 = strtok(dataAsPointer, ",");
        //cout << "Elve1: " << elve1 << endl;
        char* elve2 = strtok(NULL, ",");
        //cout << "Elve2: " << elve2 << endl;
        furtherProcessing(elve1, elve2, "-", "-", sum, sum2);
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
    processData(singleLinesBernhard, sumBernhard, sumBernhardPart2);

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
    processData(singleLinesJasmina, sumJasmina, sumJasminaPart2);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}