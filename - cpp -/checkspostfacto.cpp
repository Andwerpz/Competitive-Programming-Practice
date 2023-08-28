#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

vector<bool> isCapture;
vector<vector<int>> moves;

vector<int> genMoves() {

}

vector<int> genCaptures() {

}

bool solve(int ind, vector<char>& startPos) {
    vector<char> board = startPos;
    if(!isCapture) {
        //just have to make sure that there are no capture moves available.
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    char c;
    int n;
    cin >> c >> n;
    isCapture = vector<bool>(n, false);
    moves = vector<vector<int>>(n, vector<int>(0));
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        int cell = 0;
        for(int j = 0; j < s.size(); j++){
            if(s[j] == '-' || s[j] == 'x') {
                if(s[j] == 'x'){
                    isCapture[i] = true;
                }
                moves[i].push_back(cell);
                cell = 0;
            }
            else {
                cell *= 10;
                cell += s[j] - '0';
            }
        }
        moves[i].push_back(cell);
    }
    vector<char> startPos(33, '.');
    solve(0, startPos);
    
    return 0;
}
