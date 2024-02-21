#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//NCPC 2019 - E

//just simulate it

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    getline(cin, line);
    int r = 0;
    for(int i = 0; i < line.size(); i++){
        r += line[i] == ' ';
    }
    int n;
    cin >> n;
    vector<string> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int ptr = 0;
    vector<vector<string>> teams(2, vector<string>(0));
    //cout << "GOT" << endl;
    for(int i = 0; i < n; i++){
        //cout << "I : " << i << endl;
        for(int j = 0; j < r; j++){
            ptr = (ptr + 1) % a.size();
        }
        teams[i % 2].push_back(a[ptr]);
        a.erase(a.begin() + ptr);
        if(i == n - 1){
            break;
        }
        ptr = ptr % a.size();
    }
    for(int i = 0; i < 2; i++){
        cout << teams[i].size() << "\n";
        for(int j = 0; j < teams[i].size(); j++){
            cout << teams[i][j] << "\n";
        }
    }
    
    return 0;
}
