
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1569B

//the people who just want to not lose a game can just tie every game they play in. 

//the people who want to win a game, on the other hand, must win at least one game. Then they can just tie every other game.

//make sure that the people of type 2 only win games against other people of type 2. This means that you can just have them in a big loop. person 1 beats 2, 2 beats 3 and so on

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int numOne = 0;
        int numTwo = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '1'){
                numOne ++;
            }
            else{
                numTwo ++;
            }
        }
        if(numTwo == 0 || numTwo >= 3){
            cout << "YES\n";
            vector<vector<char>> ans(n);
            vector<int> twos;
            for(int i = 0; i < n; i++){
                if(s[i] == '2'){
                    twos.push_back(i);
                }
                ans[i] = vector<char>(n, 0);
            }
            for(int i = 0; i < twos.size(); i++){
                int cur = twos[i];
                int next = twos[(i + 1) % twos.size()];
                ans[cur][next] = '+';
                ans[next][cur] = '-';
            }
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(ans[i][j] == 0){
                        if(i == j){
                            ans[i][j] = 'X';
                        }
                        else{
                            ans[i][j] = '=';
                        }
                    }
                    cout << ans[i][j];
                }
                cout << endl;
            }
        }
        else{
            cout << "NO\n";
        }
    }

    return 0;
}



