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
            if(myFile.eof()) data = "";
            getline(myFile, data);
            if(data != "") {
                paragraph.push_back(data);
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

void drawData(const int &data, const int &cycle) {
    char toDraw = '.';
    if(data == cycle%40 || data-1 == cycle%40 || data+1 == cycle%40) toDraw = '#';
    cout << toDraw;
    if(!((cycle+1) % 40)) cout << endl;
}

void processDataPart2(const vector<string> &vecSingle, int &saveVar) {
    int x = 1;
    int cycle = 1;
    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> data = seperateString(vecSingle[i], " ");
        if(data[0] == "addx") {
            //cout << endl << x -1 << " " << x << " " << x+1 << "        " << cycle;
            drawData(x, cycle-1);
            cycle++;
            //cout << endl << x -1 << " " << x << " " << x+1 << "        " << cycle;
            drawData(x, cycle-1);
            cycle++;
            x += stoi(data[1]);
        } else {
            //cout << endl << x -1 << " " << x << " " << x+1 << "        " << cycle;
            drawData(x, cycle-1);
            cycle++;
        }
    }
}

void processData(const vector<string> &vecSingle, int &saveVar) {
    int x = 1;
    int cycle = 1;
    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> data = seperateString(vecSingle[i], " ");
        if(data[0] == "addx") {
            cycle++;
        
            if(cycle == 20 || (cycle+20)%40 == 0) {
                cout << "   " << cycle << " " << x;
                saveVar += cycle * x;
            }
            cycle++;
            x += stoi(data[1]);
        } else {
            cycle++;
        }
        if(cycle == 20 || (cycle+20)%40 == 0) {
            cout << "   " << cycle << " " << x;
           saveVar += cycle * x;
        }
    }
}

int main() {
    readInData("bernhard.txt", linesBernhard);

    //printLines(linesBernhard);
    split2DimVec(linesBernhard);
    //processData(split2DimVec(linesBernhard), sumBernhard);
    processDataPart2(split2DimVec(linesBernhard), sumBernhardPart2);

    readInData("jasmina.txt", linesJasmina);
    printLines(linesJasmina);
    processData(split2DimVec(linesJasmina), sumJasmina);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}