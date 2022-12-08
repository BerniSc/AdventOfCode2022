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

#include "cargoLoader.hpp"

using namespace std;

static string data;

vector<vector<string>> linesBernhard;
vector<vector<string>> linesJasmina;

vector<string> singleLinesJasmina;
vector<string> singleLinesBernhard;

vector<vector<char>> jasminaCargo;
vector<vector<char>> bernhardCargo;
vector<vector<char>> bspCargo;

static int sumBernhard = 0;
static int sumJasmina = 0;

static int sumBernhardPart2 = 0;
static int sumJasminaPart2 = 0;

static const bool debugMode = false;

void printLines(const vector<vector<string>> &vec, vector<string> &singleLines) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            if(debugMode) cout << vec[i][j] << endl;
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
vector<string>& seperateStringThreeParts(string toSeperate, const char *seperator) {
    static vector<string> result;
    result.clear();
    char* dataAsPointer = &toSeperate[0];
    char* part1 = strtok(dataAsPointer, seperator);
    result.push_back(part1);
    char* part2 = strtok(NULL, seperator);
    result.push_back(part2);
    char* part3 = strtok(NULL, seperator);
    result.push_back(part3);

    return result;
}

void processDataPart2(const vector<string> &vecSingle, vector<vector<char>> &cargo) {
    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> seperated = seperateStringThreeParts(vecSingle[i], "movefromto");
        vector<char> save;
        for(int j = 0; j < stoi(seperated[0]); j++) {
            save.push_back(cargo[stoi(seperated[1])-1].back());
            cargo[stoi(seperated[1])-1].pop_back();
        }
        int d = save.size();
        for(int j = 0; j < d; j++) {
            cargo[stoi(seperated[2])-1].push_back(save.back());
            save.pop_back();
        }
        save.clear();
        seperated.clear();
    }
}

void processData(const vector<string> &vecSingle, vector<vector<char>> &cargo) {
    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> seperated = seperateStringThreeParts(vecSingle[i], "movefromto");
        char save = ' ';
        for(int j = 0; j < stoi(seperated[0]); j++) {
            save = cargo[stoi(seperated[1])-1].back();
            cargo[stoi(seperated[1])-1].pop_back();
            cargo[stoi(seperated[2])-1].push_back(save);
        }
    seperated.clear();
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
    inputCargoB(bernhardCargo);
    printLines(linesBernhard, singleLinesBernhard);
    //processData(singleLinesBernhard, bernhardCargo);
    processDataPart2(singleLinesBernhard, bernhardCargo);
    cout << endl;
    for(int i = 0; i < bernhardCargo.size(); i++) {
        cout << "CargoB: " << bernhardCargo[i].back() << endl;
    }

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
    inputCargoJ(jasminaCargo);
    printLines(linesJasmina, singleLinesJasmina);
    //processData(singleLinesJasmina, jasminaCargo);
    processDataPart2(singleLinesJasmina, jasminaCargo);
    cout << endl;
    for(int i = 0; i < jasminaCargo.size(); i++) {
        cout << "CargoJ: " << jasminaCargo[i].back() << endl;
    }
    
    return 0;
}