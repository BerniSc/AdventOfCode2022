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

struct Sensor {
    int ownX, ownY;
    int beaconX, beaconY;

    Sensor(int x, int y, int bX, int bY) : ownX(x), ownY(y), beaconX(bX), beaconY(bY) {

    }

    int getDistance() {
        return (abs(ownX - beaconX) + abs(ownY - beaconY));
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

void processData(const vector<string> &vecSingle, int &saveVar) {
    int minX = 100000, maxX = 0;
    int minY = 100000, maxY = 0;

    //int desiredRow = 2000000;
    int desiredRowInt = 10;

    vector<Sensor*> sensors;

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

        sensors.push_back(new Sensor(stoi(data[0]), stoi(data[1]), stoi(data[2]), stoi(data[3])));
    }

    char desiredRowRow[maxX-minX];
    for(int i = 0; i < (maxX-minX); i++) {
        desiredRowRow[i] = '.';
    }

    for(auto s : sensors) {
        if(s->ownY > desiredRowInt) {
            //Hoch
            if((s->ownY - s->getDistance()) <= desiredRowInt) {
                int dif = abs((s->ownY - s->getDistance()) - desiredRowInt);
                for(int i = 0; i <= 2 * dif; i++) {
                    desiredRowRow[(s->ownX-dif)+i-minX-1] = 'X';
                    //cout << s->ownX << " | " << s->ownY << " -> " << s->getDistance() << endl;
                }
                //cout << "Sensor" << endl;
            } 
        } else {
            //Runter
            if((s->ownY + s->getDistance()) >= desiredRowInt) {
                int dif = (s->ownY + s->getDistance()) - desiredRowInt;
                for(int i = 0; i <= 2 * dif; i++) {
                    if(s->ownY==7 && s->ownX==8);
                    desiredRowRow[(s->ownX-dif)+i-minX-1] = 'X';
                }
                //cout << "Sensor" << endl;
            }
        }
    }

    
    for(int i = 0; i < (maxX-minX); i++) {
        if(!(i%5)) cout << "    ";
        //cout << desiredRowRow[i];
        if(desiredRowRow[i] == 'X') saveVar++;
    }
    //cout << endl;

    cout << maxX << "," << maxY << "    " << minX << "," << minY << endl;

}

int main() {
    readInData("bernhard.txt", linesBernhard);

    //printLines(linesBernhard);
    //split2DimVec(linesBernhard);
    processData(split2DimVec(linesBernhard), sumBernhard);

    readInData("jasmina.txt", linesJasmina);
    //printLines(linesJasmina);
    processData(split2DimVec(linesJasmina), sumJasmina);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}