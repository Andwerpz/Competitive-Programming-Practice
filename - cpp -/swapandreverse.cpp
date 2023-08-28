#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1864B

//using only the type 1 operation, we can sort all the even and odd indexed characters relative to each other. 

//if k is odd, then it only will swap even characters with other even characters, and odd characters with other odd characters, 
//which means if k is odd, it can't improve the sort. 

//but if k is even, it can swap even characters with odd characters, which means that we can just sort everything. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        if(k % 2 == 0){
            sort(s.begin(), s.end());
            cout << s << "\n";
            continue;
        }
        vector<char> even(0);
        vector<char> odd(0);
        for(int i = 0; i < n; i++){
            if(i % 2 == 0){
                even.push_back(s[i]);
            }
            else {
                odd.push_back(s[i]);
            }
        }
        sort(even.begin(), even.end());
        sort(odd.begin(), odd.end());
        for(int i = 0; i < n; i++){
            if(i % 2 == 0){
                cout << even[i / 2];
            }
            else {
                cout << odd[i / 2];
            }
        }
        cout << "\n";
    }
    
    return 0;
}
