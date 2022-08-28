#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Meta Hacker Cup 2022 B1

//if r or c == 1, and there is a tree present in the painting, then it is impossible
//to give all trees 2 friends. 

//else, just make all tiles trees. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin("second_friend_input.txt");
    ofstream fout("second_friend_output.txt");
    
    int t;
    fin >> t;
    int caseNum = 1;
    while(t-- > 0){
        int r, c;
        fin >> r >> c;
        vector<vector<char>> g(r, vector<char>(c));
        int tCnt = 0;
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                fin >> g[i][j];
                tCnt += g[i][j] == '^'? 1 : 0;
            }
        }
        if(r == 1 || c == 1) {
            if(tCnt == 0){
                fout << "Case #" << caseNum << ": Possible\n";
                for(int i = 0; i < r; i++){
                    for(int j = 0; j < c; j++){
                        fout << ".";
                    }
                    fout << "\n";
                }
            }
            else{
                fout << "Case #" << caseNum << ": Impossible\n";
            }
        }
        else{
            fout << "Case #" << caseNum << ": Possible\n";
            for(int i = 0; i < r; i++){
                for(int j = 0; j < c; j++){
                    fout << "^";
                }
                fout << "\n";
            }
        }
        caseNum ++;
    }
    
    return 0;
}
