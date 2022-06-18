#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1689D

//my approach was to find the minimum point and distance combo in which all the black cells are contained 
//through relaxing the area. 

//i could have just found the area directly, but whatever. 

//top left, top right, bottom right, bottom left
bool shrink(vector<string> &g, int r, int c, int d) {
    //top left
    int pr = r;
    int pc = c - d;
    for(int i = 0; i <= d; i++){
        //cout << pr << " " << pc << "\n";
        if(!(pr < 0 || pr >= g.size() || pc < 0 || pc >= g[0].size())){
            if(g[pr][pc] == 'B') {
                return false;
            }
        }
        if(i != d){
            pr --;
            pc ++;
        }
    }
    //top right
    for(int i = 0; i <= d; i++){
        //cout << pr << " " << pc << "\n";
        if(!(pr < 0 || pr >= g.size() || pc < 0 || pc >= g[0].size())){
            if(g[pr][pc] == 'B') {
                return false;
            }
        }
        if(i != d){
            pr ++;
            pc ++;
        }
    }
    //bottom right
    for(int i = 0; i <= d; i++){
        //cout << pr << " " << pc << "\n";
        if(!(pr < 0 || pr >= g.size() || pc < 0 || pc >= g[0].size())){
            if(g[pr][pc] == 'B') {
                return false;
            }
        }
        if(i != d){
            pr ++;
            pc --;
        }
    }
    //bottom left
    for(int i = 0; i <= d; i++){
        //cout << pr << " " << pc << "\n";
        if(!(pr < 0 || pr >= g.size() || pc < 0 || pc >= g[0].size())){
            if(g[pr][pc] == 'B') {
                return false;
            }
        }
        if(i != d){
            pr --;
            pc --;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<string> g(n);
        for(int i = 0; i < n; i++){
            cin >> g[i];
        }
        int r = n / 2;
        int c = m / 2;
        int d = (n + m) / 2 + 1;
        int dr[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
        int dc[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
        while(d != 0){
            bool isValid = false;
            for(int i = 0; i < 9; i++){
                if(dr[i] == 0 && dc[i] == 0){
                    if(shrink(g, r + dr[i], c + dc[i], d)){
                        isValid = true;
                        r += dr[i];
                        c += dc[i];
                        d --;
                        break;
                    }
                }
                else if(dr[i] == 0 || dc[i] == 0){
                    if(shrink(g, r + dr[i], c + dc[i], d) && shrink(g, r + dr[i], c + dc[i], d + 1)){
                        isValid = true;
                        r += dr[i];
                        c += dc[i];
                        d --;
                        break;
                    }
                }
                else{
                    if(shrink(g, r + dr[i], c + dc[i], d) && shrink(g, r + dr[i], c + dc[i], d + 1) && shrink(g, r + dr[i], c + dc[i], d + 2)){
                        isValid = true;
                        r += dr[i];
                        c += dc[i];
                        d --;
                        break;
                    }
                }
            }
            if(!isValid){
                break;
            }
        }
        cout << (r + 1) << " " << (c + 1) << "\n";
    }
    
    return 0;
}
