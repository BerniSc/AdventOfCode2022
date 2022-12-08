#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

static string data;

vector<vector<string>> lines;

vector<string> singleVectorLines;

int sumPoints = 0;
int sumPointsPartTwo = 0;

void printLines(const vector<vector<string>> &vec) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << endl;
            singleVectorLines.push_back(vec[i][j]);
        }
        cout << singleVectorLines.size() << endl;
        cout << endl;
    }    
}

void evaluateResults(char *oponent, char *player, int &pointCounter) {
    //WINNING OPTIONS
    if(*oponent == 'A' && *player == 'Y') {
        pointCounter += 6;
    } else if(*oponent == 'B' && *player == 'Z') {
        pointCounter += 6;
    } else if(*oponent == 'C' && *player == 'X') {
        pointCounter += 6;
    }
    //DRAW OPTIONS
    if(*oponent == 'A' && *player == 'X') {
        pointCounter += 3;
    } else if(*oponent == 'B' && *player == 'Y') {
        pointCounter += 3;
    } else if(*oponent == 'C' && *player == 'Z') {
        pointCounter += 3;
    }
    //EVALUATE POINTS FOR CHOICE
    if(*player == 'X') pointCounter += 1;
    if(*player == 'Y') pointCounter += 2;
    if(*player == 'Z') pointCounter += 3;
};

void processDataPartTwo(vector<string> &vecSingle) {
    for(int i = 0; i < vecSingle.size(); i++) {
        string dummy = vecSingle[i];
        char* dataAsPointer = &dummy[0];
        char* oponent = strtok(dataAsPointer, " ");
        char* player = strtok(NULL, " ");

        char playerChoice;

        if(*player == 'X') {
            if(*oponent == 'A') playerChoice = 'Z';
            if(*oponent == 'B') playerChoice = 'X';
            if(*oponent == 'C') playerChoice = 'Y';
        } else if(*player == 'Y') {
            if(*oponent == 'A') playerChoice = 'X';
            if(*oponent == 'B') playerChoice = 'Y';
            if(*oponent == 'C') playerChoice = 'Z';
        } else if(*player == 'Z') {
            if(*oponent == 'A') playerChoice = 'Y';
            if(*oponent == 'B') playerChoice = 'Z';
            if(*oponent == 'C') playerChoice = 'X';
        }
        evaluateResults(oponent, &playerChoice, sumPointsPartTwo);
    }
}

void processData(vector<string> &vecSingle) {
    for(int i = 0; i < vecSingle.size(); i++) {
        string dummy = vecSingle[i];
        char* dataAsPointer = &dummy[0];
        char* oponent = strtok(dataAsPointer, " ");
        //cout << oponent << "        ";
        char* player = strtok(NULL, " ");
        //cout << player << endl;
        evaluateResults(oponent, player, sumPoints);
    }
}

int main() {
    ifstream myfile;
    
    myfile.open("data.txt");
    
    vector<string> paragraph;
    
    if(myfile.is_open()) {
        while(myfile) {
            if(myfile.eof()) data = "";
            getline(myfile, data);
            if(data != "") {
                paragraph.push_back(data);
            } else {
                lines.push_back(paragraph);
                paragraph.clear();
            }
        }
    }
    printLines(lines);
    processData(singleVectorLines);
    processDataPartTwo(singleVectorLines);
    cout << "Lösung für Aufgabe 1: " << sumPoints << endl;
    cout << "Lösung für Aufgabe 2: " << sumPointsPartTwo << endl;

    return 0;
}