#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1674F

//keep a prefix of cells that you know will end up in the final arrangement after you have 
//re-organized the desktop. Any cell that starts in one of these cells we can call not-moving. 

//notice that the answer for any given desktop is going to be total cells minus not-moving cells. 
//so, when updating, if you can just update those two values, then you can compute the answer. 

//The key thing to notice is that when updating, you only need to check the values of at most 2 cells, 
//the cell you update, and the not-moving cell that changes state due to the update. 

//you also might have to consider the difference between updating a not-moving cell, and updating a
//moving cell. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> g(n, vector<int>(m));
    vector<int> cols(m);
    int total = 0;
    int amtNotMove = 0;
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < m; j++){
            if(s[j] == '*'){
                g[i][j] = 1;
                cols[j] ++;
                total ++;
            }
        }
    }
    int counter = 0;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(g[j][i] == 1){
                amtNotMove ++;
            }
            counter ++;
            if(counter == total){
                goto outer;
            }
        }
    }
    outer : ;
    while(q-- > 0){
        int r, c;
        cin >> r >> c;
        r--;
        c--;
        bool adding = g[r][c] == 0;
        //figure out which cell is changing
        int uc = total / n; //we're calculating the next cell. 
        int ur = total % n;
        if(!adding){
            ur --;
            if(ur == -1){
                ur = n - 1;
                uc --;
            }
            else if(ur == n){
                ur = 0;
                uc ++;
            }
        }
        //modify grid
        g[r][c] = adding? 1 : 0;
        total += adding? 1 : -1;
        if(r == ur && c == uc){ //change is modify
            amtNotMove += adding? 1 : -1;
        }
        else { //other cases
            if(c < uc || (c == uc && r < ur)){  //icon just placed or removed affects count
                amtNotMove += adding? 1 : -1;
            }
            //if adding to total affects any already existing icons
            if(adding && g[ur][uc] == 1){
                amtNotMove ++;
            }
            else if(!adding && g[ur][uc] == 1){
                amtNotMove --;
            }
        }
        cout << (total - amtNotMove) << endl;

        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j < m; j++){
        //         if(i == ur && j == uc){
        //             cout << "#";
        //         }
        //         else{
        //             cout << ".";
        //         }
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        // for(int i = 0; i < n; i++){
        //     for(int j = 0; j < m; j++){
        //         cout << (g[i][j] == 1? '#' : '.');
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
    
    return 0;
}
