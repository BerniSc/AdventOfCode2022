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
#include <cmath>

#define int long long

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

int SNAFU_to_dec(string snafu) {
    int length = snafu.length();
    int start = pow(5, length-1);
    
    int result = 0;
    for(int i = 0; i <= length; i++) {
        if(snafu[i] == '=') {
            result += start*(-2);
        } else if(snafu[i] == '-'){
            result += start*(-1);
        } else {
            result += start*(snafu[i] - 48);
        }
        start /= 5;
    }
    return result;
}

string dec_to_snafu_helper_positive(int &length, int &dec, int &dummy) {
    if(dummy < dec) {
        dec -= 2*pow(5, length);
        cout << dec << endl;
        cout << 2*pow(5, length-1) << endl;
        if(2*pow(5, length-1) > dec && length >= 1) {
            return "0";
        }
        return "2";
    } else {
        dec -= pow(5, length);
        cout << dec << endl;
        if(2*pow(5, length-1) >= dec) {
            return "0";
        }
        return "1";
    }
}

string dec_to_snafu_helper_negative(int &length, int &dec, int &dummy) {
    if(dummy < dec) {
        dec -= 2*pow(5, length);
        cout << dec << endl;
        if(2*pow(5, length-1) >= dec) {
            return "0";
        }
        return "=";
    } else {
        dec -= pow(5, length);
        cout << dec << endl;
        if(2*pow(5, length-1) >= dec) {
            return "0";
        }
        return "-";
    }
}

int dec_to_snafu_helper_1_2(int &length, int &dec) {
    int dummy = pow(5, length-1);
    for(int i = (length - 2); i >= 0; i--) {
        dummy += 2 * pow(5, i);
    }  
    length--;
    return dummy;
}

string dec_to_SNAFU(int dec) {
    //Höchste 5er Potenz suchen die noch geht -> Länge
    int length = 0;
    int actualSum = 0;
    int original = dec;

    while(dec >= actualSum) {
        actualSum += 2 * pow(5, length);
        length++;
    }

    string s = "";

    int dummy = dec_to_snafu_helper_1_2(length, dec);
    s = dec_to_snafu_helper_positive(length, dec, dummy);

    for(int i = length; i > 0; i--) {
        if(dec > 0) {
            //positiv
            cout << "pos" << endl;
            dummy = dec_to_snafu_helper_1_2(length, dec);
            s += dec_to_snafu_helper_positive(length, dec, dummy);
        } else {
            //negativ
            cout << "neg" << endl;
            dec = abs(dec);
            dummy = dec_to_snafu_helper_1_2(length, dec);
            s += dec_to_snafu_helper_negative(length, dec, dummy);
            dec *= (-1);
        }
    }

    cout << s << endl;
}

string dec_to_SNAFU_idea_2(int dec) {
    //Determine length
    int length = 0;
    int actualSum = 0;
    
    while(dec >= actualSum) {
        actualSum += 2 * pow(5, length);
        length++;
    }

    //convert number to char
    static const char snafu[] = {'=', '-', '0', '1', '2'}; 

    char stringSnafu[length + 1] = {0};
    stringSnafu[length] = '\0';

    int position = (length - 1);

    while(dec > 0) {
        int value = dec % 5;
        if(value >= 3) value -= 5;
        stringSnafu[position--] = snafu[value+2];
        dec -= value;
        dec /= 5;
    }

    std::string s = stringSnafu;
    return s;
}

void processData(const vector<string> &vecSingle, int &saveVar) {
    for(int i = 0; i < vecSingle.size(); i++) {
        int dec = SNAFU_to_dec(vecSingle[i]);
        //string snafu = dec_to_SNAFU_idea_2(dec);
        //cout << dec << "            ";
        //cout << snafu << endl;
        saveVar += dec;
    }
    cout << saveVar << endl;
    cout << dec_to_SNAFU_idea_2(saveVar) << endl;
}

signed main() {
    cout << dec_to_SNAFU_idea_2(7475) << endl;
    cout << SNAFU_to_dec("11-00") << endl;

    return -100;

    readInData("bernhard.txt", linesBernhard);
    //printLines(linesBernhard);
    processData(split2DimVec(linesBernhard), sumBernhard);

    readInData("jasmina.txt", linesJasmina);
    //printLines(linesJasmina);
    processData(split2DimVec(linesJasmina), sumJasmina);
    
    cout << endl << "Bernhard: " << sumBernhard <<  "   " << sumBernhardPart2 << endl;
    cout << "Jasmina: " << sumJasmina << "  " << sumJasminaPart2 << endl;

    return 0;
}