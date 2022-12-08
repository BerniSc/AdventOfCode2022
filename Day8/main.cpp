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

vector<string>& seperateStringTwoParts(string toSeperate, const char *seperator) {
    static vector<string> result;
    char* dataAsPointer = &toSeperate[0];
    char* part1 = strtok(dataAsPointer, seperator);
    result.push_back(part1);
    char* part2 = strtok(NULL, seperator);
    result.push_back(part2);
    
    return result;
}

void processDataPart2(const vector<string> &vecSingle, int &visibleTrees) {
    //Zeilen Addieren
    visibleTrees += 2*vecSingle.size();
    //Spalten addieren
    visibleTrees += 2*vecSingle[0].size();
    //Ecken abziehen
    visibleTrees -= 4;

    int scenicScore = 1;
    int bestScenicScore = 1;

    for(int i = 1; i < vecSingle.size() - 1; i++) {
        for(int j = 1; j < vecSingle[0].size() -1; j++) {
            scenicScore = 1;
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
    visibleTrees = bestScenicScore;
}

void processData(const vector<string> &vecSingle, int &visibleTrees) {
    //Zeilen Addieren
    visibleTrees += 2*vecSingle.size();
    //Spalten addieren
    visibleTrees += 2*vecSingle[0].size();
    //Ecken abziehen
    visibleTrees -= 4;

    bool erkannt = false;
    bool sichtbar = true;

    for(int i = 1; i < vecSingle.size() - 1; i++) {
        //cout << "schleife1     " << i << "," << vecSingle.size() - 1 << endl;
        for(int j = 1; j < vecSingle[0].size() -1; j++) {
            erkannt = false;
            sichtbar = true;
            //cout << "schleife2     " << j << "," << vecSingle[0].size() - 1 << endl;
            //Oben
            for(int x = 0; x < i; x++) {
                //WENN Baum kleiner als vergleichsbaum, dann nicht sichtbar
                if(vecSingle[i][j] <= vecSingle[x][j]) {
                    sichtbar = false;
                    break;
                }
            }
            //cout << "Oben sichtbar: (" << i << "," << j <<") " << sichtbar << endl; 
            if(sichtbar && !erkannt) {
                visibleTrees++;
                erkannt = true;
                cout << "Oben sichtbar: (" << i << "," << j << ")" << endl;
            }
            sichtbar = true;
            //Unten
            for(int x = i+1; x < vecSingle.size(); x++) {
            //Baum Größer als Vergleichsbaum
                if(vecSingle[i][j] <= vecSingle[x][j]) {
                    sichtbar = false;
                    break;
                }
            }
            //cout << "Unten sichtbar: (" << i << "," << j <<") " << sichtbar << endl; 
            if(sichtbar && !erkannt) {
                visibleTrees++;
                erkannt = true;
                cout << "Unten sichtbar: (" << i << "," << j << ")" << endl;
            }
            sichtbar = true;
            for(int y = 0; y < j; y++) {
            //LINKS
            //Wenn Baum Kleiner als Vergleichsbaum, dann nicht sichtbar
                if(vecSingle[i][j] <= vecSingle[i][y]) {
                    sichtbar = false;
                    break;
                }
            }
            //cout << "Links sichtbar: (" << i << "," << j <<") " << sichtbar << endl; 
            if(sichtbar && !erkannt) {
                visibleTrees++;
                erkannt = true;
                cout << "Links sichtbar: (" << i << "," << j << ")" << endl;
            }
            //RECHTS
            sichtbar = true;
            for(int y = j+1; y < vecSingle[0].size(); y++) {
            //Baum Größer als Vergleichsbaum
                if(vecSingle[i][j] <= vecSingle[i][y]) {
                    sichtbar = false;
                }
            }
            //cout << "Rechts sichtbar: (" << i << "," << j <<") " << sichtbar << endl; 
            if(sichtbar && !erkannt) {
                visibleTrees++;
                erkannt = true;
                cout << "Rechts sichtbar: (" << i << "," << j << ")" << endl;
            }
        }
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
    processData(singleLinesBernhard, sumBernhard);
    processDataPart2(singleLinesBernhard, sumBernhardPart2);

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
    processData(singleLinesJasmina, sumJasmina);
    processDataPart2(singleLinesJasmina, sumJasminaPart2);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}