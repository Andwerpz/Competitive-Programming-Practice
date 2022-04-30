#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 1673C

//generate all palindromes of with length 5 digits or less. 

//since there are only around 1000 of them, you can do dp over the range 0 - 1e4 * 4 to figure
//out for each n, how many ways there are to construct.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    //generate all palindromes up to 5 digits long
    vector<string> ps(0);
    set<int> p;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 10; j++){
            if(i == 0){
                ps.push_back(to_string(j));
            }
            else if(i == 1){
                ps.push_back(to_string(j) + to_string(j));
            }
            else{
                vector<string> a(0);
                for(string k : ps){
                    a.push_back(to_string(j) + k + to_string(j));
                }
                for(string k : a){
                    if(k.size() > 5){
                        continue;
                    }
                    ps.push_back(k);
                }
            }
        }
    }
    for(string i : ps){
        if(i[0] == '0'){
            continue;
        }
        p.insert(stoi(i));
    }
    //build dp array
    vector<ll> dp(4 * 1e4 + 1);
    dp[0] = 1;
    ll mod = 1e9 + 7;
    for(int i : p){
        if(i > 4 * 1e4){
            break;
        }
        for(int j = 0; j <= dp.size() - 1 - i; j++){
            dp[j + i] += dp[j];
            if(dp[j + i] >= mod){
                dp[j + i] -= mod;
            }
        }
    }
    while(t-- > 0){
        int n;
        cin >> n;
        cout << dp[n] << endl;
    }
    
    return 0;
}
