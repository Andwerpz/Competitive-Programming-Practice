#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 01 B

//another brute force. 

//since there are only 2 dice, you can just figure out how many ways there are to make each sum

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    map<int, int> mp;
    int most = 0;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++) {
            if(mp.find(j + i) == mp.end()) {
                mp.insert({j + i, 0});
            }
            mp.find(j + i) -> second ++;
            most = max(most, mp.find(j + i) -> second);
        }
    }
    for(auto i = mp.begin(); i != mp.end(); i++){
        if(i -> second == most) {
            cout << i -> first << "\n";
        }
    }
    
    return 0;
}
