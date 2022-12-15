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

void processDataPartTwo(const vector<string> &vecSingle, int &saveVar) {
    int minX = 100'000, maxX = 0;
    int minY = 100'000, maxY = 0;

    //int desiredRowInt = 10;
    int desiredRowInt = 3'999'000;
    //int desiredRowInt = 10;

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

    cout << maxX << "," << maxY << "    " << minX << "," << minY << endl;
    bool desiredRowRow[maxX-minX];
    for(; desiredRowInt < 4'000'000; desiredRowInt++) {

    for(long long y = 0; y < 1; y++) {
        for(long long i = 0; i < (maxX-minX); i++) {
            desiredRowRow[i] = false;
        }
    }
    for(auto s : sensors) {
        if(s->ownY > desiredRowInt) {
            //Hoch
            if((s->ownY - s->getDistance()) <= desiredRowInt) {
                int dif = abs((s->ownY - s->getDistance()) - desiredRowInt);
                for(int i = 0; i < (2 * dif); i++) {
                    if(((s->ownX-dif)+i-minX-1) > 0 && ((s->ownX-dif)+i-minX-1) < 4'000'000) {
                    desiredRowRow[(s->ownX-dif)+i-minX-1] = true;
                    }
                }
            } 
        } else {
            //Runter
            if((s->ownY + s->getDistance()) >= desiredRowInt) {
                int dif = (s->ownY + s->getDistance()) - desiredRowInt;
                for(int i = 0; i < (2 * dif); i++) {
                    if(((s->ownX-dif)+i-minX-1) > 0 && ((s->ownX-dif)+i-minX-1) < 4'000'000) {
                    desiredRowRow[(s->ownX-dif)+i-minX-1] = true;
                    }
                }
            }
        }
    }
    }
    for(int i = 0; i < (maxX-minX); i++) {
        if(desiredRowRow[i] == false) {
            cout << "POOOOOIIIINT" << i << "  " << desiredRowInt << endl;
            break;;
        }
    }
}

void processData(const vector<string> &vecSingle, int &saveVar) {
    int minX = 100'000, maxX = 0;
    int minY = 100'000, maxY = 0;

    //int desiredRowInt = 10;
    int desiredRowInt = 2'000'000;
    int rowOffset = 2'000'000;
    //1'000'000;
    //int desiredRowInt = 10;

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

    char desiredRowRow[maxX-minX+rowOffset];
    for(long long i = 0; i < (maxX-minX+rowOffset); i++) {
        desiredRowRow[i] = '.';
    }

    cout << maxX << "," << maxY << "    " << minX << "," << minY << endl;

    for(auto s : sensors) {
        cout << s->getDistance() << endl;
        if(s->ownY > desiredRowInt) {
            //Hoch
            if((s->ownY - s->getDistance()) <= desiredRowInt) {
                int dif = abs((s->ownY - s->getDistance()) - desiredRowInt);
                for(int i = 0; i < (2 * dif); i++) {
                    desiredRowRow[(s->ownX-dif)+i-minX-1+rowOffset/2] = 'X';
                }
            } 
        } else {
            //Runter
            if((s->ownY + s->getDistance()) >= desiredRowInt) {
                int dif = (s->ownY + s->getDistance()) - desiredRowInt;
                for(int i = 0; i < (2 * dif); i++) {
                    desiredRowRow[(s->ownX-dif)+i-minX-1+rowOffset/2] = 'X';
                }
            }
        }
    }

    
    for(long long i = 0; i < (maxX-minX+rowOffset); i++) {
        //if(!(i%5)) cout << "    ";
        //cout << desiredRowRow[i];
        if(desiredRowRow[i] == 'X') saveVar++;
    }
    //cout << endl;


}

int main() {
    readInData("bernhard.txt", linesBernhard);

    //printLines(linesBernhard);
    //split2DimVec(linesBernhard);
    //processData(split2DimVec(linesBernhard), sumBernhard);
    processDataPartTwo(split2DimVec(linesBernhard), sumBernhardPart2);

    readInData("jasmina.txt", linesJasmina);
    //printLines(linesJasmina);
    //processData(split2DimVec(linesJasmina), sumJasmina);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}