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
#include <set>

using namespace std;
using std::cout;

static string data;

static vector<vector<string>> linesBernhard;
static vector<vector<string>> linesJasmina;

static int sumBernhard = 0;
static int sumJasmina = 5;

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

void calculateTail(const int &xHead, const int &yHead, int &xTail, int &yTail) {
    int xAbst = abs(xTail - xHead);
    int yAbst = abs(yTail - yHead);
    //Wenn nicht direkt anliegt
    if(xAbst > 1 || yAbst > 1) {
        //Wenn nicht gleiche Spalte
        if(xTail != xHead) {
            //Addieren von -1 / +1 je nach richtung
            xTail += (xHead - xTail) / abs(xHead - xTail);
        }
        //Wenn nicht gleiche Zeile
        if(yTail != yHead) {
            //Addieren von -1 / +1 je nach richtung
            yTail += (yHead - yTail) / abs(yHead - yTail);
        }
        //Kombiniert deckt damit auch Diagonal ab -> Nur "Start" wenn abstand GRÖßER 1
        //Versucht dementsprechend wieder näher an Head zu kommen
    }
}

void calculateTailAlt(const int &xHead, const int &yHead, int &xTail, int &yTail) {
    int xAbst = abs(xTail - xHead);
    int yAbst = abs(yTail - yHead);
    bool diagDirect = false;
    if(xAbst == 1 && yAbst == 1) diagDirect = true;
    //Gleiche Spalte
    if(xHead == xTail && yAbst > 1) {
        //Hoch oder Runter
        if(yHead > yTail) {
            yTail++;
        } else
        if(yHead < yTail) {
            yTail--;
        }
    //Nur entweder gleiche Zeile oder gleiche Spalte oder diagonal
    } else 
    //Gleiche Zeile
    if(yHead == yTail && xAbst > 1) {
        //Rechts oder Links
        if(xHead > xTail) {
            xTail++;
        } else
        if(xHead < xTail) {
            xTail--;
        }
    //Nur entweder gleiche Zeile oder gleiche Spalte oder diagonal
    } else 
    //Diagonal
    if(xAbst >= 1 && yAbst >= 1 && !diagDirect) {
        //Tail genau 2 über Head
        if(yTail == yHead + 2) {
            xTail = xHead;
            yTail = yHead + 1;
        } else
        //Tail genau 2 rechts von Head
        if(xTail == xHead + 2) {
            yTail = yHead;
            xTail = xHead + 1;
        } else
        //Tail genau 2 unterhalb von Head
        if(yTail == yHead - 2) {
            xTail = xHead;
            yTail = yHead - 1;
        } else
        //Tail genau 2 links von Head
        if(xTail == xHead - 2) {
            yTail = yHead;
            xTail = xHead - 1;
        }
    }
}

void processDataPart2(const vector<string> &vecSingle, int &saveVar) {
    //Start Positionen
    //Kopf
    int xHeadAkt = 0, yHeadAkt = 0;
    //Tail
    int xTailAkt = 0, yTailAkt = 0;
    //Initialisierung der Zwischenknoten mit 0 als Startpunkt
    int knotsXAkt[8] = {0};
    int knotsYAkt[8] = {0};
    //Set an von Tail besuchten Koordinaten des Tails
    set<string> visitedFields;
    // Jede Zeile durchgehen
    for(int i = 0; i < vecSingle.size(); i++) {
        //Jede Zeile in Anweisungen zerteilen
        vector<string> parts = seperateString(vecSingle[i], " ");
        if(parts[0] == "U") {
            for(int i = 0; i < stoi(parts[1]); i++) {
                //Kopf bewegen
                yHeadAkt++;
                //ersten Knoten relativ zum Kopf bewegen
                calculateTail(xHeadAkt, yHeadAkt, knotsXAkt[0], knotsYAkt[0]);
                //Alle Knoten relativ zu ihren Vorgängerknoten bewegen
                for(int j = 1; j < 8; j++) {
                    calculateTail(knotsXAkt[j-1], knotsYAkt[j-1], knotsXAkt[j], knotsYAkt[j]);
                } 
                //Tail relativ zu letztem Knote bewegen
                calculateTail(knotsXAkt[7], knotsYAkt[7], xTailAkt, yTailAkt);
                //Tail Position in Set inserten
                visitedFields.insert(to_string(xTailAkt) + to_string(yTailAkt));
            }
        }
        //Kommentare siehe "U"
        if(parts[0] == "D") {
            for(int i = 0; i < stoi(parts[1]); i++) {
                yHeadAkt--;
                calculateTail(xHeadAkt, yHeadAkt, knotsXAkt[0], knotsYAkt[0]);
                for(int j = 1; j < 8; j++) {
                    calculateTail(knotsXAkt[j-1], knotsYAkt[j-1], knotsXAkt[j], knotsYAkt[j]);
                } 
                calculateTail(knotsXAkt[7], knotsYAkt[7], xTailAkt, yTailAkt);
                visitedFields.insert(to_string(xTailAkt) + to_string(yTailAkt));
            }
        }
        //Kommentare siehe "U"
        if(parts[0] == "R") {
            for(int i = 0; i < stoi(parts[1]); i++) {
                xHeadAkt++;
                calculateTail(xHeadAkt, yHeadAkt, knotsXAkt[0], knotsYAkt[0]);
                for(int j = 1; j < 8; j++) {
                    calculateTail(knotsXAkt[j-1], knotsYAkt[j-1], knotsXAkt[j], knotsYAkt[j]);
                } 
                calculateTail(knotsXAkt[7], knotsYAkt[7], xTailAkt, yTailAkt);
                visitedFields.insert(to_string(xTailAkt) + to_string(yTailAkt));
            }
        }
        //Kommentare siehe "U"
        if(parts[0] == "L") {
            for(int i = 0; i < stoi(parts[1]); i++) {
                xHeadAkt--;
                calculateTail(xHeadAkt, yHeadAkt, knotsXAkt[0], knotsYAkt[0]);
                for(int j = 1; j < 8; j++) {
                    calculateTail(knotsXAkt[j-1], knotsYAkt[j-1], knotsXAkt[j], knotsYAkt[j]);
                } 
                calculateTail(knotsXAkt[7], knotsYAkt[7], xTailAkt, yTailAkt);
                visitedFields.insert(to_string(xTailAkt) + to_string(yTailAkt));
            }
        }
    }
    saveVar += visitedFields.size();
    cout << "Head: (" << xHeadAkt << "," << yHeadAkt << ")" << endl;
    cout << "Tail: (" << xTailAkt << "," << yTailAkt << ")" << endl;
    cout << "Number of visited Places: " << saveVar << endl;

}

void processData(const vector<string> &vecSingle, int &saveVar) {
    //Start Positionen
    int xHeadAkt = 0, yHeadAkt = 0;
    int xTailAkt = 0, yTailAkt = 0;
    //Set an von Tail besuchten Koordinaten
    set<string> visitedFields;
    // Jede Zeile durchgehen
    for(int i = 0; i < vecSingle.size(); i++) {
        vector<string> parts = seperateString(vecSingle[i], " ");
        if(parts[0] == "U") {
            //cout << "Up" << stoi(parts[1]) << endl;
            for(int i = 0; i < stoi(parts[1]); i++) {
                yHeadAkt++;
                calculateTail(xHeadAkt, yHeadAkt, xTailAkt, yTailAkt);
                visitedFields.insert(to_string(xTailAkt) + to_string(yTailAkt));
            }
        }
        if(parts[0] == "D") {
            //cout << "Down" << endl;
            for(int i = 0; i < stoi(parts[1]); i++) {
                yHeadAkt--;
                calculateTail(xHeadAkt, yHeadAkt, xTailAkt, yTailAkt);
                visitedFields.insert(to_string(xTailAkt) + to_string(yTailAkt));
            }
        }
        if(parts[0] == "R") {
            //cout << "Right" << endl;
            for(int i = 0; i < stoi(parts[1]); i++) {
                xHeadAkt++;
                calculateTail(xHeadAkt, yHeadAkt, xTailAkt, yTailAkt);
                visitedFields.insert(to_string(xTailAkt) + to_string(yTailAkt));
            }
        }
        if(parts[0] == "L") {
            //cout << "Left" << endl;
            for(int i = 0; i < stoi(parts[1]); i++) {
                xHeadAkt--;
                calculateTail(xHeadAkt, yHeadAkt, xTailAkt, yTailAkt);
                visitedFields.insert(to_string(xTailAkt) + to_string(yTailAkt));
            }
        }
        //cout << to_string(xTailAkt) + to_string(yTailAkt) << endl;
    }
    saveVar += visitedFields.size();
    cout << "Head: (" << xHeadAkt << "," << yHeadAkt << ")" << endl;
    cout << "Tail: (" << xTailAkt << "," << yTailAkt << ")" << endl;
    cout << "Number of visited Places: " << saveVar << endl;

}

int main() {
    readInData("bernhard.txt", linesBernhard);
    //printLines(linesBernhard);
    processData(split2DimVec(linesBernhard), sumBernhard);
    processDataPart2(split2DimVec(linesBernhard), sumBernhardPart2);

    readInData("jasmina.txt", linesJasmina);
    //printLines(linesJasmina);
    processData(split2DimVec(linesJasmina), sumJasmina);
    processDataPart2(split2DimVec(linesJasmina), sumJasminaPart2);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}