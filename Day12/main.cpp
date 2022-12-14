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
#include <iomanip>
#include <algorithm>

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

int dijkstra(vector<pair<int, int>> &queue, vector<string> &grid, const pair<int, int> &end) {
    //Initialize DistanceMap
    vector<vector<int>> distanceMap;
    for(int i = 0; i < grid.size(); i++) {
        vector<int> row;
        row.clear();
        for(int j = 0; j < grid[0].size(); j++) {
            row.push_back(-1);
        }
        distanceMap.push_back(row);
    }
    cout << "D1 " << distanceMap.size() << "       " << grid.size() << endl;
    cout << "D2 " << distanceMap[0].size() << "    " << grid[0].size() << endl;
    
    distanceMap[queue[0].second][queue[0].first] = 0;

    while(queue.size()) {
        int x = queue.back().second, y = queue.back().first;
        queue.pop_back();
        //Drunter
        int dy = 1, dx = 0;
        if(min(y + dy, x + dx) >= 0 && y + dy < grid.size() && x + dx < grid[0].size() && distanceMap[y+dy][x+dx] == -1 && ((grid[y][x] + 1) >= grid[y+dy][x+dx])) {
            distanceMap[y+dy][x+dx] = distanceMap[y][x] + 1;
            queue.insert(queue.begin(), pair<int, int>(y + dy, x + dx));
        }
        //Drüber
        dy = -1, dx = 0;
        if(min(y + dy, x + dx) >= 0 && (y + dy) < grid.size() && (x + dx) < grid[0].size() && distanceMap[y+dy][x+dx] == -1 && (grid[y][x] + 1) >= grid[y+dy][x+dx]) {
            distanceMap[y+dy][x+dx] = distanceMap[y][x] + 1;
            queue.insert(queue.begin(), pair<int, int>(y + dy, x + dx));
        }
        //Rechts
        dy = 0, dx = 1;
        if(min(y + dy, x + dx) >= 0 && y + dy < grid.size() && x + dx < grid[0].size() && distanceMap[y+dy][x+dx] == -1 && (grid[y][x] + 1) >= grid[y+dy][x+dx]) {
            distanceMap[y+dy][x+dx] = distanceMap[y][x] + 1;
            queue.insert(queue.begin(), pair<int, int>(y + dy, x + dx));
        }
        //Links
        dy = 0; dx = -1;
        if(min(y + dy, x + dx) >= 0 && y + dy < grid.size() && x + dx < grid[0].size() && distanceMap[y+dy][x+dx] == -1 && (grid[y][x] + 1) >= grid[y+dy][x+dx]) {
            distanceMap[y+dy][x+dx] = distanceMap[y][x] + 1;
            queue.insert(queue.begin(), pair<int, int>(y + dy, x + dx));
        }
    }
    cout.precision(2);
    for(int i = 0; i < distanceMap.size(); i++) {
        for(int j = 0; j < distanceMap[0].size(); j++) {
            //cout << setw(2) << distanceMap[i][j] << " ";
        }
        //cout << endl;
    }

    return distanceMap[end.second][end.first];
}

void processDataPart2(vector<string> vecSingle, int &saveVar) {
    pair<int, int> start;
    pair<int, int> end;

    vector<pair<int, int>> queuePart2;
    for(int i = 0; i < vecSingle.size(); i++) {
        for(int j = 0; j < vecSingle[0].size(); j++) {
            if(vecSingle[i][j] == 'S') {
                start.first = j;
                start.second = i;
            }
            if(vecSingle[i][j] == 'E') {
                end.first = j;
                end.second = i;
            }

            if(vecSingle[i][j] == 'a') {
                pair<int, int> back;
                back.first = j;
                back.second = i;
                queuePart2.push_back(back);
            }
            //cout << start.first << start.second << "    " << end.first<< end.second << endl;
        }
    }
    cout << start.first << start.second << "    " << end.first << end.second << endl;
    vecSingle[end.second][end.first] = 'z' + 1;
    vecSingle[start.second][start.first] = 'a' - 1;
    int minVal = 10000;
    vector<pair<int, int>> queue;
    for(int i = 0; i < queuePart2.size(); i++) {
        queue.clear();
        queue.push_back(queuePart2[i]);
        int dummy = dijkstra(queue, vecSingle, end);
        cout << dummy << endl;
        minVal = std::min(minVal, dummy);
    }
    saveVar = minVal;
}

void processData(vector<string> vecSingle, int &saveVar) {
    pair<int, int> start;
    pair<int, int> end;
    for(int i = 0; i < vecSingle.size(); i++) {
        for(int j = 0; j < vecSingle[0].size(); j++) {
            if(vecSingle[i][j] == 'S') {
                start.first = j;
                start.second = i;
            }
            if(vecSingle[i][j] == 'E') {
                end.first = j;
                end.second = i;
            }
            //cout << start.first << start.second << "    " << end.first<< end.second << endl;
        }
    }
    cout << start.first << start.second << "    " << end.first<< end.second << endl;
    vecSingle[end.second][end.first] = 'z' + 1;
    vecSingle[start.second][start.first] = 'a' - 1;
    vector<pair<int, int>> queue;
    queue.push_back(start);
    saveVar = dijkstra(queue, vecSingle, end);
}

int main() {
    readInData("bernhard.txt", linesBernhard);

    printLines(linesBernhard);
    split2DimVec(linesBernhard);
    processData(split2DimVec(linesBernhard), sumBernhard);
    processDataPart2(split2DimVec(linesBernhard), sumBernhardPart2);

    //readInData("jasmina.txt", linesJasmina);
    //printLines(linesJasmina);
    //processData(split2DimVec(linesJasmina), sumJasmina);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}