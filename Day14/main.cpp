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
    int xMin = 1000, xMax = 0;
    int yMin = 1000, yMax = 0;
    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> seperatedData = seperateString(vecSingle[i], "->");
        for(int j = 0; j < seperatedData.size() - 1; j++) {
            vector<string> seperatedSecond = seperateString(seperatedData[j], ",");
            xMax = max(xMax, stoi(seperatedSecond[0]));
            yMax = max(yMax, stoi(seperatedSecond[1]));
            xMin = min(xMin, stoi(seperatedSecond[0]));
            yMin = min(yMin, stoi(seperatedSecond[1]));
        }
    }

    //int width = 16;
    int width = xMax - xMin + 42;
    //int height = 16;
    int height = yMax + 2;

    vector<vector<char>> cave;
    for(int y = 0; y < height; y++) {
        vector<char> caveRow;
        cave.push_back(caveRow);
        for(int x = 0; x < width; x++) {
            cave[y].push_back('.');
        }
    }

    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> seperatedData = seperateString(vecSingle[i], "->");
        for(int j = 0; j < seperatedData.size() - 1; j++) {
            vector<string> seperatedTwoOne = seperateString(seperatedData[j], ",");
            vector<string> seperatedTwoTwo = seperateString(seperatedData[j+1], ",");

            int xOne = stoi(seperatedTwoOne[0]) - 500;
            int xTwo = stoi(seperatedTwoTwo[0]) - 500;

            xOne += (width/2);
            xTwo += (width/2);

            int yOne = stoi(seperatedTwoOne[1]);
            int yTwo = stoi(seperatedTwoTwo[1]);
            
            cave[yOne][xOne] = '#';
            cave[yTwo][xTwo] = '#';

            //If Same Row
            if(yOne == yTwo) {
                while(xTwo < xOne) {
                    xTwo++;
                    cave[yTwo][xTwo] = '#';
                }

                while(xTwo > xOne) {
                    xOne++;
                    cave[yOne][xOne] = '#';
                }
            }
            //If Same Collumn
            if(xOne == xTwo) {
                while(yOne < yTwo) {
                    yOne++;
                    cave[yOne][xOne] = '#';
                }
                while(yOne > yTwo) {
                    yTwo++;
                    cave[yTwo][xTwo] = '#';
                }
            }
        }
    }

    int fallenSandCounter = 0;
    
    int minJ = 9;

    for(int i = 0; i < 1000; i++) {
        int xSand = width/2;
        int ySand = 1;
        bool kill = false;
        for(int j = 0; j < height-1; j++) {
            //Wenn Feld darunter frei
            if(cave[ySand+1][xSand] == '.') {
                ySand = j;
                if(j >= minJ) kill = true;
            } else if(cave[ySand+1][xSand-1] == '.' && xSand-1 > 0) {
                ySand = j;
                xSand -= 1;
                if(j >= minJ) kill = true;
            } else if(cave[ySand+1][xSand+1] == '.' && xSand+1 < width) {
                ySand = j;
                xSand += 1;
                if(j >= minJ) kill = true;
            } else {
                if(xSand-1 < 0 || xSand+1 > width) {
                    kill = true;
                    cout << "TERMINATED" << endl;
                }
                if(j == 0) {
                    cout << "EEEEEnde " << fallenSandCounter << endl;
                    kill = true;
                }
                break;
            }
            //cout << ySand << "  " << xSand << endl;
        }
        if(!kill) {
            fallenSandCounter++;
            cave[ySand][xSand] = 'o';
        }
    }

    cout << fallenSandCounter << endl;

    
    for(auto c : cave) {
        for(auto r : c) {
            cout << r;
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