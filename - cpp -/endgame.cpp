#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NWERC 2020 - E

//solving if alice can win is relatively easy, you can do in O(n). 

//solving if bob can force a win is harder, as it seems like you need to test every cell on the board. 
//note that the input is relatively weird; the number of valid moves is always equal to the board size.
//this leads to a probabilistic solution where you guess random cells on the board, and check them in
//O(n). If all of the cells you check are winning for bob, then just say bob wins. 

pair<int, int> add(pair<int, int>& a, pair<int, int>& b){
    return {a.first + b.first, a.second + b.second};
}

pair<int, int> sub(pair<int, int>& a, pair<int, int>& b){
    return {a.first - b.first, a.second - b.second};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    pair<int, int> a, b;
    cin >> a.first >> a.second >> b.first >> b.second;
    a.first --;
    a.second --;
    b.first --;
    b.second --;
    set<pair<int, int>> moves;
    for(int i = 0; i < n; i++){
        pair<int, int> move;
        cin >> move.first >> move.second;
    }
    bool win = false;
    //check if alice can win
    for(auto i = moves.begin(); i != moves.end(); i++){
        pair<int, int> move = *i;
        pair<int, int> npos = add(a, move);
        if(npos == b){
            win = true;
        }
        pair<int, int> diff = sub(b, a);
        if(moves.find(diff) != moves.end()) {
            win = true;
        }
    }
    if(win){
        cout << "Alice wins\n";
        return 0;
    }
    set<pair<int, int>> b_moves;
    for(auto i = moves.begin(); i != moves.end(); i++){
        pair<int, int> move = *i;
        b_moves.insert(add(move, b));
    }
    bool tie = false;
    pair<int, int> tie_ans;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(b_moves.find({i, j}) == b_moves.end()){
                tie = true;
                tie_ans = {i + 1, j + 1};
            }
        }
    }
    if(tie){
        cout << "tie " << tie_ans.first << " " << tie_ans.second << "\n";
    }
    else {
        cout << "Bob wins\n";
    }
    
    return 0;
}
