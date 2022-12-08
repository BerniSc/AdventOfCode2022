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

using std::cout;
using std::vector;
using std::string;
using std::ifstream;
using std::getline;
using std::endl;

static string data;

struct Folder;

vector<vector<string>> linesBernhard;
vector<vector<string>> linesJasmina;

vector<string> singleLinesJasmina;
vector<string> singleLinesBernhard;

static int sumBernhard = 0;
static int sumJasmina = 0;

static Folder *deleB;
int sizeB = 48381165;

static Folder *deleJ;

static int sumBernhardPart2 = 0;
static int sumJasminaPart2 = 0;

struct Folder;

struct Node {
    string name;
    int size;

    Folder* parent;

    Node() = default;
    Node(string name) : name(name), size(0) {};
    Node(string name, Folder *parent) : name(name), parent(parent), size(0) {
        cout << "init site:" << size << endl;
    };
};

struct File : Node {

    File() = default;
    File(string name) : Node(name) {};
};

struct Folder : Node {
    vector<Folder*> content;

    Folder() = default;
    Folder(string name) : Node(name) {};
    Folder(string name, Folder *parent) : Node(name, parent) {};
};


void printLines(const vector<vector<string>> &vec, vector<string> &singleLines) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << endl;
            singleLines.push_back(vec[i][j]);
        }
        cout << endl;
    }    
}

vector<string>& seperateStringThreeParts(string toSeperate, const char *seperator) {
    static vector<string> result;
    result.clear();
    char* dataAsPointer = &toSeperate[0];
    char* part1 = strtok(dataAsPointer, seperator);
    result.push_back(part1);
    char* part2 = strtok(NULL, seperator);
    result.push_back(part2);

    if(part1[0] == '$' && part2[0] != 'l') {
        char* part3 = strtok(NULL, seperator);
        result.push_back(part3);
    }
    
    return result;
}

int processDataFurtherPart2(Folder *folder, int occupied) {
    for(auto f : folder->content) {
        processDataFurtherPart2(f, occupied);
    }
    if((folder->size >= (30000000 - (70000000 - occupied)))){
        cout << "! War da" << endl;
        if((folder->size < sizeB)) {
            cout << "Folder site " << folder->size << " " << deleB->size << endl;
            sizeB = folder->size;
        } 
    } 
    return -1;
}

int processDataFurther(Folder *folder, int &sizeVar) {
    for(auto f : folder->content) {
        folder->size += processDataFurther(f, sizeVar);
    }
    if(folder->size <= 100000) sizeVar += folder->size;
    return folder->size;
}

void processData(const vector<string> &vecSingle, int &sizeVar, int &sizeVar2, Folder *dele) {
    Folder *root = new Folder("root");
    Folder *current = new Folder();

    current = root;

    dele = root;

    for(int i = 1; i < vecSingle.size(); i++) {
        vector<string> data;
        if(vecSingle[i][0] == '$') {
            cout  << "Befehl ";
            data = seperateStringThreeParts(vecSingle[i], " ");
            if(data[1] == "cd") {
                cout << endl << "DATA " << data[2] << endl;
                if(data[2][0] == '.') {
                    cout << "Went Up" << endl;
                    current = current->parent;
                } else {
                    for(auto c : current->content) {
                        if(c->name == data[2]) {
                            current = c;
                            cout << "NAME DES PARENT: " << current->parent->name << endl;;
                        } 
                    }
                }
                //current = current->content.
            } else if(data[1] == "ls") {
                //WEG DAMIT
            }
            cout << data[1] << endl;
        } else {
            data = seperateStringThreeParts(vecSingle[i], " ");
            
            if(data[0] == "dir") {
                //cout << "Data:: " << data[1] << endl;
                current->content.push_back(new Folder(data[1], current));
            } else {
                current->size += stoi(data[0]);
            }
            cout << data[0] << endl;
        }
    }
    int i = processDataFurther(root, sizeVar);
    int j = processDataFurtherPart2(root, i);
    sizeVar2 = dele->size;
    cout << "Size: " << i << endl;
    cout << "Size2: " <<  sizeB << endl;
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
    deleB = new Folder("deleB");
    deleB->size = 48381166;
    printLines(linesBernhard, singleLinesBernhard);
    processData(singleLinesBernhard, sumBernhard, sumBernhardPart2, deleB);

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

    //printLines(linesJasmina, singleLinesJasmina);
    //processData(singleLinesJasmina);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}