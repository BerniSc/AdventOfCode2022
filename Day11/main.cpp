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
#include <numeric>

//vlt etwas unelegant, aber genervt -> long long nötig weil schlimmstenfalls (kgV-1)^2 für teil 2 -> int raus 
#define int long long

using namespace std;

static string dataLine;

static vector<vector<string>> linesBernhard;
static vector<vector<string>> linesJasmina;
static vector<vector<string>> linesDominik;

static int sumBernhard = 0;
static int sumJasmina = 0;
static int sumDominik = 0;

static unsigned int sumBernhardPart2 = 0;
static unsigned int sumJasminaPart2 = 0;
static unsigned int sumDominikPart2 = 0;

vector<string>& seperateString(string toSeperate, const char *seperator);

struct Monkey {
    const int monkeyNumber;
    vector<int> items;
    string operation;
    int test;
    unsigned int inspectionCounter;

    int nextMonkeyTrue;
    int nextMonkeyFalse;

    static int kgV;

    Monkey(int monkeyNumber, string operation, int test, int nextMonkeyTrue, int nextMonkeyFalse) : monkeyNumber(monkeyNumber), operation(operation), test(test), nextMonkeyTrue(nextMonkeyTrue), nextMonkeyFalse(nextMonkeyFalse), inspectionCounter(0) {

    }

    void operate() {
        vector<string> data = seperateString(operation, "Operation: w=ld");  
        inspectionCounter += items.size();
        for(int i = 0; i < items.size(); i++) {
            if(data.size() == 1) {
                items[i] *= items[i];
            } else {
                if(data[0] == "*") items[i] *= stoi(data[1]);
                if(data[0] == "+") items[i] += stoi(data[1]);
            }
        }
    }

    void operate2() {
        vector<string> data = seperateString(operation, "Operation: w=ld");  
        inspectionCounter += items.size();
        for(int i = 0; i < items.size(); i++) {
            if(data.size() == 1) {
                items[i] *= items[i];
            } else {
                if(data[0] == "*") items[i] *= stoi(data[1]);
                if(data[0] == "+") items[i] += stoi(data[1]);
            }
            items[i] %= (kgV);
        }
    }

    void addItems(int item) {
        items.push_back(item);
    }

    void clearItems() {
        items.clear();
    }

    ~Monkey() = default;
};

int Monkey::kgV = 1;

void printLines(const vector<vector<string>> &vec) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << endl;
        }
        cout << "------------------------------------------" << endl;
    }    
}

void readInData(const string& fileName, vector<vector<string>> &dataDestination) {
    ifstream myFile;
    myFile.open(fileName);

    vector<string> paragraph;
    if(myFile.is_open()) {
        while(myFile) {
            if(myFile.eof()) dataLine = "";
            getline(myFile, dataLine);
            if(dataLine != "") {
                paragraph.push_back(dataLine);
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

void processDataPart2(const vector<vector<string>> &vec, unsigned int &saveVar) {
    vector<Monkey*> monkeys;
    //VERARBEITEN UND SPEICHERN IN MONKEY
    for(int i = 0; i < vec.size(); i++) {
        vector<string> data = seperateString(vec[i][3], "Test: divbly");
        int test = stoi(data[0]);
        Monkey::kgV = lcm(Monkey::kgV, test);
        data = seperateString(vec[i][4], "If true: throw to monkey");
        int nextMonkeyTrue = stoi(data[0]);
        data = seperateString(vec[i][5], "If false: throw to monkey");
        int nextMonkeyFalse = stoi(data[0]);
        monkeys.push_back(new Monkey(i, vec.at(i)[2], test, nextMonkeyTrue, nextMonkeyFalse));
        data = seperateString(vec[i][1], "Starting items: ,");
        for(int j = 0; j < data.size(); j++) {
            monkeys[i]->addItems(stoi(data[j]));
        }
    }
    
    //AN MONKEY OPERATION DURCHFÜHREN
    for(int i = 0; i < 10000; i++) {
        for(auto m : monkeys) {
            m->operate2();
            for(int j = 0; j < m->items.size(); j++) {
                if((m->items[j]) % m->test) {
                    monkeys[m->nextMonkeyFalse]->addItems((m->items[j]));
                } else {
                    monkeys[m->nextMonkeyTrue]->addItems((m->items[j]));
                }
            }
            m->clearItems();
        }
    }
    //BEIDEN MAXIMALWERTE SUCHEN
    int max1 = 0, max2 = 0, temp;
    for(auto m : monkeys) {
        cout << "Monkey" << m->monkeyNumber << " " << m->inspectionCounter << endl;
        if(m->inspectionCounter > max1) {
            temp = max1;
            max1 = m->inspectionCounter;
            max2 = temp;
        //Falls erstes element größtes ist
        } else if(m->inspectionCounter > max2 && m->inspectionCounter < max1) {
            max2 = m->inspectionCounter;
        }
        delete m;
    }
    cout << max1 << "    " << max2 << endl;
    //ERGBENIS SETZEN
    saveVar = max1 * max2;
}

void processData(const vector<vector<string>> &vec, int &saveVar) {
    vector<Monkey*> monkeys;
    //VERARBEITEN UND SPEICHERN IN MONKEY
    for(int i = 0; i < vec.size(); i++) {
        vector<string> data = seperateString(vec[i][3], "Test: divbly");
        int test = stoi(data[0]);
        data = seperateString(vec[i][4], "If true: throw to monkey");
        int nextMonkeyTrue = stoi(data[0]);
        data = seperateString(vec[i][5], "If false: throw to monkey");
        int nextMonkeyFalse = stoi(data[0]);
        monkeys.push_back(new Monkey(i, vec.at(i)[2], test, nextMonkeyTrue, nextMonkeyFalse));
        data = seperateString(vec[i][1], "Starting items: ,");
        for(int j = 0; j < data.size(); j++) {
            monkeys[i]->addItems(stoi(data[j]));
        }
    }

    //AN MONKEY OPERATION DURCHFÜHREN
    for(int i = 0; i < 20; i++) {
        for(auto m : monkeys) {
            m->operate();
            for(int j = 0; j < m->items.size(); j++) {
                if((m->items[j]/3) % m->test) {
                    monkeys[m->nextMonkeyFalse]->addItems((m->items[j]/3));
                } else {
                    monkeys[m->nextMonkeyTrue]->addItems((m->items[j])/3);
                }
            }
            m->clearItems();
        }
    }
  
    //BEIDEN MAXIMALWERTE SUCHEN
    int max1 = 0, max2 = 0, temp;
    for(auto m : monkeys) {
        if(m->inspectionCounter > max1) {
            temp = max1;
            max1 = m->inspectionCounter;
            max2 = temp;
        //Falls erstes element größtes ist
        } else if(m->inspectionCounter > max2 && m->inspectionCounter < max1) {
            max2 = m->inspectionCounter;
        }
        delete m;
    }
    //ERGBENIS SETZEN
    saveVar = max1 * max2;
}

signed main() {
    readInData("bernhard.txt", linesBernhard);

    //printLines(linesBernhard);
    processData(linesBernhard, sumBernhard);
    processDataPart2(linesBernhard, sumBernhardPart2);

    readInData("dominik.txt", linesDominik);
    
    processData(linesDominik, sumDominik);
    processDataPart2(linesDominik, sumDominikPart2);

    readInData("jasmina.txt", linesJasmina);
    //printLines(linesJasmina);
    //processData(linesJasmina, sumJasmina);
    //processDataPart2(linesJasmina, sumJasminaPart2);
    
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;
    cout << "Dominik: " << sumDominik << "  " << sumDominikPart2 << endl;

    return 0;
}
