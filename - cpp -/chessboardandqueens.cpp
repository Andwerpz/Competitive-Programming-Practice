
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//CSES - Chessboard and Queens

//do an exaustive recursive search, but with one caveat, only put one queen on each row. So for each recursion, you only need to check for 1 row, not over the entire
//board. 

//this also fixes the problem where you'll get multiple solutions that have queens placed in the same place, just placed in a different order.

using namespace std;

ll getAns(vector<string> grid, int numLeft);

ll getAns(vector<string> grid, int numLeft){
    //cout << numLeft << endl;
    ll ans = 0;
    for(int i = numLeft - 1; i <= numLeft - 1; i++){
        for(int j = 0; j < grid.size(); j++){
            if(grid[i][j] == '.'){
                if(numLeft == 1){
                    ans ++;
                }
                else{
                    vector<string> nextGrid(8);
                    for(int k = 0; k < 8; k++){
                        nextGrid[k] = "        ";
                        for(int l = 0; l < 8; l++){
                            nextGrid[k][l] = grid[k][l];
                            if(k == i){
                                nextGrid[k][l] = '*';
                            }
                            else if(j == l){
                                nextGrid[k][l] = '*';
                            }
                            else if(abs(i - k) == abs(j - l)){
                                nextGrid[k][l] = '*';
                            }
                            //cout << nextGrid[k][l];
                        }
                        //cout << endl;
                    }
                    //cout << endl;
                    //cout << numLeft << endl;
                    ans += getAns(nextGrid, numLeft - 1);
                }
            }
        }
    }
    return ans;
}

int main() {

    vector<string> grid(8);
    for(int i = 0; i < 8; i++){
        cin >> grid[i];
    }
    cout << getAns(grid, 8);

    return 0;
}



