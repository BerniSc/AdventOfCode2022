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

void processData(const vector<string> &vecSingle, int &saveVar) {
    int minX = 100000, maxX = 0;
    int minY = 100000, maxY = 0;

    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> data = seperateString(vecSingle[i], "Sensor at closest beacon is x= y= : ,");
        minX = min(minX, stoi(data[0]));
        minX = min(minX, stoi(data[2]));
        maxX = max(maxX, stoi(data[0]));
        maxX = max(maxX, stoi(data[2]));
        
        minY = min(minY, stoi(data[1]));
        minY = min(minY, stoi(data[3]));
        maxY = max(maxY, stoi(data[1]));
        maxY = max(maxY, stoi(data[3]));
    }

    cout << maxX << "," << maxY << "    " << minX << "," << minY << endl;

    vector<vector<char>> sensorMap;
    for(int y = 0; y < (maxY - minY); y++) {
        vector<char> row;
        sensorMap.push_back(row);
        for(int x = 0; x < (maxX - minX); x++) {
            sensorMap[y].push_back('.');
        }
    }

    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> data = seperateString(vecSingle[i], "Sensor at closest beacon is x= y= : ,");
        int x1 = stoi(data[0]);
        int y1 = stoi(data[1]);
        int x2 = stoi(data[2]);
        int y2 = stoi(data[3]);

        sensorMap[y1-minY][x1-minX] = 'S';
        cout << y2-minY << "            " << x2-minX << endl;
        sensorMap[y2-minY][x2-minX] = 'B';
    }

    for(auto s : sensorMap) {
        for(auto v : s) {
            cout << v;
        }
        cout << endl;
    }

}

int main() {
    readInData("bernhard.txt", linesBernhard);

    printLines(linesBernhard);
    split2DimVec(linesBernhard);
    processData(split2DimVec(linesBernhard), sumBernhard);

    //readInData("jasmina.txt", linesJasmina);
    //printLines(linesJasmina);
    //processData(split2DimVec(linesJasmina), sumJasmina);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}