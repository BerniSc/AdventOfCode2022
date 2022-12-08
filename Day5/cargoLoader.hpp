#include "vector"

using namespace std;


void inputCargoB(vector<vector<char>> &cargo){
    vector<char> row;
    //ROW 1 von UNten
    row.push_back('F');
    row.push_back('D');
    row.push_back('B');
    row.push_back('Z');
    row.push_back('T');
    row.push_back('J');
    row.push_back('R');
    row.push_back('N');
    cargo.push_back(row);

    row.clear();

    //ROW 2
    row.push_back('R');
    row.push_back('S');
    row.push_back('N');
    row.push_back('J');
    row.push_back('H');
    cargo.push_back(row);

    row.clear();

    //ROW 3
    row.push_back('C');
    row.push_back('R');
    row.push_back('N');
    row.push_back('J');
    row.push_back('G');
    row.push_back('Z');
    row.push_back('F');
    row.push_back('Q');
    cargo.push_back(row);

    row.clear();

    //ROW 4
    row.push_back('F');
    row.push_back('V');
    row.push_back('N');
    row.push_back('G');
    row.push_back('R');
    row.push_back('T');
    row.push_back('Q');
    cargo.push_back(row);

    row.clear();

    //ROW 5
    row.push_back('L');
    row.push_back('T');
    row.push_back('Q');
    row.push_back('F');
    cargo.push_back(row);

    row.clear();

    //ROW 6
    row.push_back('Q');
    row.push_back('C');
    row.push_back('W');
    row.push_back('Z');
    row.push_back('B');
    row.push_back('R');
    row.push_back('G');
    row.push_back('N');
    cargo.push_back(row);

    row.clear();

    //ROW 7
    row.push_back('F');
    row.push_back('C');
    row.push_back('L');
    row.push_back('S');
    row.push_back('N');
    row.push_back('H');
    row.push_back('M');
    cargo.push_back(row);
    
    row.clear();

    //ROW 8
    row.push_back('D');
    row.push_back('N');
    row.push_back('Q');
    row.push_back('M');
    row.push_back('T');
    row.push_back('J');
    cargo.push_back(row);

    row.clear();

    //ROW 9
    row.push_back('P');
    row.push_back('G');
    row.push_back('S');
    cargo.push_back(row);
}

void inputCargoJ(vector<vector<char>> &cargo){
    vector<char> row;
    //ROW 1 von UNten
    row.push_back('D');
    row.push_back('T');
    row.push_back('R');
    row.push_back('B');
    row.push_back('J');
    row.push_back('L');
    row.push_back('W');
    row.push_back('G');
    cargo.push_back(row);

    row.clear();

    //ROW 2
    row.push_back('S');
    row.push_back('W');
    row.push_back('C');
    cargo.push_back(row);

    row.clear();

    //ROW 3
    row.push_back('R');
    row.push_back('Z');
    row.push_back('T');
    row.push_back('M');
    cargo.push_back(row);

    row.clear();

    //ROW 4
    row.push_back('D');
    row.push_back('T');
    row.push_back('C');
    row.push_back('H');
    row.push_back('S');
    row.push_back('P');
    row.push_back('V');
    cargo.push_back(row);

    row.clear();

    //ROW 5
    row.push_back('G');
    row.push_back('P');
    row.push_back('T');
    row.push_back('L');
    row.push_back('D');
    row.push_back('Z');
    cargo.push_back(row);

    row.clear();

    //ROW 6
    row.push_back('F');
    row.push_back('B');
    row.push_back('R');
    row.push_back('Z');
    row.push_back('J');
    row.push_back('Q');
    row.push_back('C');
    row.push_back('D');
    cargo.push_back(row);

    row.clear();

    //ROW 7
    row.push_back('S');
    row.push_back('B');
    row.push_back('D');
    row.push_back('J');
    row.push_back('M');
    row.push_back('F');
    row.push_back('T');
    row.push_back('R');
    cargo.push_back(row);
    
    row.clear();

    //ROW 8
    row.push_back('L');
    row.push_back('H');
    row.push_back('R');
    row.push_back('B');
    row.push_back('T');
    row.push_back('V');
    row.push_back('M');
    cargo.push_back(row);

    row.clear();

    //ROW 9
    row.push_back('Q');
    row.push_back('P');
    row.push_back('D');
    row.push_back('S');
    row.push_back('V');
    cargo.push_back(row);
}

void inputCargoE(vector<vector<char>> &cargo) {
    vector<char> row;
    //ROW 1 von UNten
    row.push_back('Z');
    row.push_back('N');
    cargo.push_back(row);

    row.clear();

    //ROW 2
    row.push_back('M');
    row.push_back('C');
    row.push_back('D');
    cargo.push_back(row);

    row.clear();

    //ROW 3
    row.push_back('P');
    cargo.push_back(row);  
}