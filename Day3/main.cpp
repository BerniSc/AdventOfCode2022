/******************************************************************************
                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

static string data;

vector<vector<string>> lines;

vector<string> links, rechts;

static int score = 0;
static int score2 = 0;

void printLines(const vector<vector<string>> &vec) {
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < vec[i].size(); j++) {
            cout << vec[i][j] << endl;
            string l = vec[i][j].substr(0, vec[i][j].length()/2);
            string r = vec[i][j].substr(vec[i][j].length()/2);
            links.push_back(l);
            rechts.push_back(r);
        }
        cout << endl;
    }    
}

void evaluateData(int &score, const char &doppelt) {
    //GROSSBUCHSTABEN
    if(doppelt >= 65 && doppelt <= 90) {
        //65-27 = 38
        score += (doppelt - 38);
    //kleinbuchstaben
    } else if(doppelt >= 97 && doppelt <= 122) {
        //97-1 = 96
        score += (doppelt - 96);
    }
}

void processData(vector<string> &vecl, vector<string> &vecr) {
    char doppelt = ' ';
    for(int z = 0; z < vecl.size(); z++) {
        int length = vecl[z].size();
        bool detected = false;
        for(int i = 0; i < length; i++) {
            for(int j = 0; j < length; j++) {
                if(vecl[z][i] == vecr[z][j] && !detected) {
                    detected = !detected;
                    //cout << " l: " << vecl[z][i] << " r: " << vecr[z][j] << endl;
                    evaluateData(score, vecl[z][i]);
                }
            }
        }
    }
}

void processDataPartTwo(vector<vector<string>> &lines) {
    vector<string> paragraph;
    for(int i = 0; i < lines.size(); i++) {
        paragraph = lines[i];
        for(int j = 0; j < paragraph.size(); j+=3) {
            bool detected = false;
            for(int a = 0; a < paragraph[j+0].size(); a++) {
                for(int b = 0; b < paragraph[j+1].size(); b++) {
                    for(int c = 0; c < paragraph[j+2].size(); c++) {
                        if(paragraph[j][a] == paragraph[j+1][b] && paragraph[j][a] == paragraph[j+2][c] && !detected) {
                            detected = true;
                            //cout << " l: " << vecl[z][i] << " r: " << vecr[z][j] << endl;
                            //cout << paragraph[j][a] << endl;
                            evaluateData(score2, paragraph[j][a]);
                        }
                    }
                }
            }
        }   
    }   
}

int main() {
    ifstream myfile;
    
    //myfile.open("data.txt");
    myfile.open("data.jasmina");
    
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
    processData(links, rechts);
    processDataPartTwo(lines);



    cout << "Score:     " << score << endl;
    cout << "Score 2:   " << score2 << endl;

    return 0;
}
