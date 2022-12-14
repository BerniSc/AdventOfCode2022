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
#include <algorithm>

using namespace std;

static string inputData;

static vector<vector<string>> linesBernhard;
static vector<vector<string>> linesJasmina;

static int sumBernhard = 0;
static int sumJasmina = 0;

static int sumBernhardPart2 = 0;
static int sumJasminaPart2 = 0;

void printLines(const vector<vector<string>> &vec) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << endl;
        }
        cout << endl;
    }    
}

void readInData(const string& fileName, vector<vector<string>> &dataDestination) {
    ifstream myFile;
    myFile.open(fileName);

    vector<string> paragraph;
    if(myFile.is_open()) {
        while(myFile) {
            if(myFile.eof()) inputData = "";
            getline(myFile, inputData);
            if(inputData != "") {
                paragraph.push_back(inputData);
            } else {
                dataDestination.push_back(paragraph);
                paragraph.clear();
            }
        }
    }
}

vector<string> split2DimVec(const vector<vector<string>> &vec) {
    vector<string> dummy;
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            dummy.push_back(vec[i][j]);
        }
    }  
    return dummy;
}

vector<string>& seperateString(string toSeperate, const char *seperator) {
    static vector<string> result;
    result.clear();
    char* dataAsPointer = &toSeperate[0];
    char* token = strtok(dataAsPointer, seperator);
    result.push_back(token);
    
    while(token != NULL) {
        token = strtok(NULL, seperator);
        if(token != NULL) result.push_back(token);
    }
    
    return result;
}

bool compareData(vector<char> &links, vector<char> &rechts) {
    //if(links[0].size() < rechts[0].size()) return false;
    char *str1 = &links[0][0];
    char *str2 = &rechts[0][0];
    if(strcmp(str1, str2) > 1) cout << "false" << endl;
}

void processData(const vector<vector<string>> &vec, int &saveVar) {
    vector<char> rechts, links;
    for(int z = 0; z < vec.size(); z++) {     
        //Oberes Pair (Links)
        int openedCounterLinks = 0, openedCounterRechts = 0;
        int maxVal = max(vec[z][0].size(), vec[z][1].size());
            for(int x = 0; x < maxVal; x++) {
                if(vec[z][0][x] == '[' || vec[z][1][x] == '[') {
                    rechts.push_back('[');
                    links.push_back('[');
                    if(vec[z][0][x] != '[' && vec[z][1][x] == '[') openedCounterLinks++;
                    if(vec[z][0][x] == '[' && vec[z][1][x] != '[') openedCounterRechts++;
                } 

                if(openedCounterLinks && (vec[z][0][x] == ',')) {
                    openedCounterLinks--;
                    links.push_back(']');
                    links.push_back(',');
                } else {
                    if(vec[z][0][x] != '[') {
                        links.push_back(vec[z][0][x]);
                    } 
                }
                if(openedCounterRechts && vec[z][1][x] == ',') {
                    openedCounterRechts--;
                    rechts.push_back(']');
                    rechts.push_back(',');
                } else {
                    if(vec[z][1][x] != '[') {
                        rechts.push_back(vec[z][1][x]);
                    }
                }
            }
            if(openedCounterLinks) links.push_back(']');
            if(openedCounterRechts) rechts.push_back(']');
            compareData(links, rechts);
            links.clear();
            rechts.clear();
            //Unteres Pair (rechts)
            //cout << endl;
            links.push_back('\n');
            rechts.push_back('\n');
    }

    for(auto l : links) {
        cout << l;
    }
    cout << endl;
    for(auto r : rechts) {
        cout << r;
    }
}

int main() {
    readInData("bernhard.txt", linesBernhard);

    printLines(linesBernhard);
    processData(linesBernhard, sumBernhard);

    readInData("jasmina.txt", linesJasmina);
    //printLines(linesJasmina);
    processData(linesJasmina, sumJasmina);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}