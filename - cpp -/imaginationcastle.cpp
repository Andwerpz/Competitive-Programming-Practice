#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//COMPFEST 15 I

//we say a tile is a W if the castle is on the tile, and the person currently moving is guaranteed to win
//given optimal play. Otherwise, if the person is guaranteed to lose, we call such a tile an L. 

//we have two different types of L tiles, induced and strong. Strong Ls are special tiles; they are always
//Ls regardless of other tiles. Induced Ls only exist if all the possible moves from the tile locations
//are W tiles. This means that no matter where you move from an induced L, you are always giving your
//opponent a win. 

//finally, notice that there can only be 1 induced L on a row or column. This limits the total amount of L
//tiles to around n. 

//to solve this problem, we can just try to see if there is an induced L on the starting tile. To do this, 
//we start from the bottom row, and work our way up, keeping track of induced L positions on each row. 
//To quickly compute the induced L position on each row, if there is one, we can keep track of what columns
//don't already have an L on them. The induced L is always going to be on the rightmost column. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> special(n, vector<int>(0));
    for(int i = 0; i < k; i++){
        int r, c;
        cin >> r >> c;
        r --;
        c --;
        special[r].push_back(c);
    }
    set<int> not_v;
    for(int i = 0; i < m; i++){
        not_v.insert(i);
    }
    set<int> l;
    //simulate
    for(int i = n - 1; i >= 0; i--){
        set<int> next;
        //special tiles
        for(int j = 0; j < special[i].size(); j++){
            next.insert(special[i][j]);
            not_v.erase(special[i][j]);
        }
        //induced L
        if(not_v.size() != 0){
            int last = *not_v.rbegin();
            if(next.size() == 0 || last > *next.rbegin()) {
                not_v.erase(last);
                next.insert(last);
            }
        }
        l = next;
    }
    cout << (l.find(0) == l.end()? "Chaneka" : "Bhinneka") << "\n";
    
    return 0;
}
