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
using std::cout;

static string inputData;

static vector<vector<string>> linesBernhard;
static vector<vector<string>> linesJasmina;

static int sumBernhard = 0;
static int sumJasmina = 0;

static int sumBernhardPart2 = 0;
static int sumJasminaPart2 = 0;

struct field;

struct field {
    int height;
    int oben;
    int unten;
    int rechts;
    int links;

    field() = default;

    field(int height) : height(height) {

    }
};

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

void processData(vector<string> vecSingle, int &saveVar) {
    for(int i = 0; i < vecSingle.size(); i++) {
        for(int j = 0; j < vecSingle[0].size(); j++) {
            field f(vecSingle[i][j]-96);
            if(i > 0) {
                f.oben = vecSingle[i-1][j];
            } else {
                f.oben = -1;
            }

            if()

            //Oben
            for(int x = i-1; x >= 0; x--) {
                //Reihe durchgehen bis nicht mehr sichtbar
                if(vecSingle[i][j] <= vecSingle[x][j] || x == 0) {
                    scenicScore *= (i-x);
                    break;
                }
            }
            //Unten
            for(int x = i+1; x < vecSingle.size(); x++) {
            //Reihe durchgehen bis nicht mehr sichtbar
                if(vecSingle[i][j] <= vecSingle[x][j] || x == vecSingle.size()-1) {
                    scenicScore *= (x-i);
                    break;
                }
            }
            //LINKS
            for(int y = j-1; y >= 0; y--) {
            //Reihe durchgehen bis nicht mehr sichtbar
                if(vecSingle[i][j] <= vecSingle[i][y] || y == 0) {
                    scenicScore *= (j-y);
                    break;
                }
            }
            //RECHTS
            for(int y = j+1; y < vecSingle[0].size(); y++) {
            //Reihe durchgehen bis nicht mehr sichtbar
                if(vecSingle[i][j] <= vecSingle[i][y] || (y == vecSingle[0].size()-1)) {
                    scenicScore *= (y-j);
                    break;
                }
            }
            if(scenicScore >= bestScenicScore) bestScenicScore = scenicScore;
        }
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