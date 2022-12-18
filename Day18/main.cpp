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

void processDataPartTwo(const vector<string> &vecSingle, int &saveVar, int size) {
    bool grid[size][size][size];

    for(int z = 0; z < size; z++) {
        for(int y = 0; y < size; y++) {
            for(int x = 0; x < size; x++) {
                grid[z][y][x] = false;
            }
        }
    }

    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> seperatedLine = seperateString(vecSingle[i], ",");
        int x = stoi(seperatedLine[0]);
        int y = stoi(seperatedLine[1]);
        int z = stoi(seperatedLine[2]);
        
        grid[z][y][x] = true;
    }

    /*
    for(int z = 0; z < size; z++) {
        cout << "+#################+" << "EBENE " << z << endl;
        for(int y = 0; y < size; y++) {
            for(int x = 0; x < size; x++) {
                cout << grid[z][y][x];
            }
            cout << '\n';
        }
    }
    */

    int visibleCounter = 0;

    for(int z = 0; z < size; z++) {
        for(int y = 0; y < size; y++) {
            for(int x = 0; x < size; x++) {
                //Wenn äußerste z Ebene
                if((z == 0 || z == size-1) && grid[z][y][x]) {
                    //Bounds -> kein davor/danach
                    visibleCounter++;
                    if(z > 0 && grid[z-1][y][x] == false && grid[z][y][x]) visibleCounter++;
                    if(z < (size-1) && grid[z+1][y][x] == false && grid[z][y][x]) visibleCounter++;
                } else {
                    //Davor ein Block in z
                    if(grid[z-1][y][x] == false && grid[z][y][x]) visibleCounter++;
                    //Danach ein Block in z
                    if(grid[z+1][y][x] == false && grid[z][y][x]) visibleCounter++;
                }
                if((y == 0 || y == size-1) && grid[z][y][x]) {
                    visibleCounter++;
                    if(y > 0 && grid[z][y-1][x] == false && grid[z][y][x]) visibleCounter++;
                    if(y < (size-1) && grid[z][y+1][x] == false && grid[z][y][x]) visibleCounter++;
                } else {
                    //Davor ein Block in y
                    if(grid[z][y-1][x] == false && grid[z][y][x]) visibleCounter++;
                    //Danach ein Block in y
                    if(grid[z][y+1][x] == false && grid[z][y][x]) visibleCounter++;
                }
                if((x == 0 || x == size-1) && grid[z][y][x]) {
                    visibleCounter++;
                    if(x > 0 && grid[z][y][x-1] == false && grid[z][y][x]) visibleCounter++;
                    if(x < (size-1) && grid[z][y][x+1] == false && grid[z][y][x]) visibleCounter++;
                } else {
                    //Davor ein Block in x
                    if(grid[z][y][x-1] == false && grid[z][y][x]) visibleCounter++;
                    //Danach ein Block in x
                    if(grid[z][y][x+1] == false && grid[z][y][x]) visibleCounter++;
                }
            }
        }
    }
    saveVar = visibleCounter;
}

void processData(const vector<string> &vecSingle, int &saveVar, int size) {
    bool grid[size][size][size];

    for(int z = 0; z < size; z++) {
        for(int y = 0; y < size; y++) {
            for(int x = 0; x < size; x++) {
                grid[z][y][x] = false;
            }
        }
    }

    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> seperatedLine = seperateString(vecSingle[i], ",");
        int x = stoi(seperatedLine[0]);
        int y = stoi(seperatedLine[1]);
        int z = stoi(seperatedLine[2]);
        
        grid[z][y][x] = true;
    }

    /*
    for(int z = 0; z < size; z++) {
        cout << "+#################+" << "EBENE " << z << endl;
        for(int y = 0; y < size; y++) {
            for(int x = 0; x < size; x++) {
                cout << grid[z][y][x];
            }
            cout << '\n';
        }
    }
    */

    int visibleCounter = 0;

    for(int z = 0; z < size; z++) {
        for(int y = 0; y < size; y++) {
            for(int x = 0; x < size; x++) {
                //Wenn äußerste z Ebene
                if((z == 0 || z == size-1) && grid[z][y][x]) {
                    //Bounds -> kein davor/danach
                    visibleCounter++;
                    if(z > 0 && grid[z-1][y][x] == false && grid[z][y][x]) visibleCounter++;
                    if(z < (size-1) && grid[z+1][y][x] == false && grid[z][y][x]) visibleCounter++;
                } else {
                    //Davor ein Block in z
                    if(grid[z-1][y][x] == false && grid[z][y][x]) visibleCounter++;
                    //Danach ein Block in z
                    if(grid[z+1][y][x] == false && grid[z][y][x]) visibleCounter++;
                }
                if((y == 0 || y == size-1) && grid[z][y][x]) {
                    visibleCounter++;
                    if(y > 0 && grid[z][y-1][x] == false && grid[z][y][x]) visibleCounter++;
                    if(y < (size-1) && grid[z][y+1][x] == false && grid[z][y][x]) visibleCounter++;
                } else {
                    //Davor ein Block in y
                    if(grid[z][y-1][x] == false && grid[z][y][x]) visibleCounter++;
                    //Danach ein Block in y
                    if(grid[z][y+1][x] == false && grid[z][y][x]) visibleCounter++;
                }
                if((x == 0 || x == size-1) && grid[z][y][x]) {
                    visibleCounter++;
                    if(x > 0 && grid[z][y][x-1] == false && grid[z][y][x]) visibleCounter++;
                    if(x < (size-1) && grid[z][y][x+1] == false && grid[z][y][x]) visibleCounter++;
                } else {
                    //Davor ein Block in x
                    if(grid[z][y][x-1] == false && grid[z][y][x]) visibleCounter++;
                    //Danach ein Block in x
                    if(grid[z][y][x+1] == false && grid[z][y][x]) visibleCounter++;
                }
            }
        }
    }
    saveVar = visibleCounter;
}

int main() {
    readInData("bernhard.txt", linesBernhard);

    printLines(linesBernhard);
    processData(split2DimVec(linesBernhard), sumBernhard, 22);
    processDataPartTwo(split2DimVec(linesBernhard), sumBernhardPart2, 22);

    //readInData("jasmina.txt", linesJasmina);
    //printLines(linesJasmina);
    //processData(split2DimVec(linesJasmina), sumJasmina, 22);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}