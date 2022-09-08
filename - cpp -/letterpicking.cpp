#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1728D

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        vector<vector<int>> a(0);   //1 : A wins, 0 : tie, -1 : B wins
        int n = s.size();
        for(int i = n - 1; i > 0; i--){
            int layer = n - i - 1;
            a.push_back(vector<int>(i, 0));
            if(i == n - 1){ //final move
                for(int j = 0; j < n - 1; j++){ 
                    a[layer][j] = s[j] == s[j + 1]? 0 : 1;
                }
                continue;
            }
            else if(i == n - 2){    //chance for bob to win

            }
            else if(a.size() % 2 == 0){  //bob's turn
                for(int j = 0; j < i; j++){
                    a[layer][j] = min(a[layer - 1][j], a[layer - 1][j + 1]);
                }
                continue;
            }
            else if(a.size() % 2 == 1){ //alice's turn
                for(int j = 0; j < i; j++){
                    a[layer][j] = max(a[layer - 1][j], a[layer - 1][j + 1]);
                }
            }
        }
        cout << (a[a.size() - 1][0] == 1? "Alice\n" : "Draw\n");
    }
    
    return 0;
}
