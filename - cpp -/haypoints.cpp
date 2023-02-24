#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 06 E

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cin >> m >> n;
    map<string, int> mp;
    for(int i = 0; i < m; i++){
        string a;
        cin >> a;
        int val;
        cin >> val;
        mp.insert({a, val});
    }
    while(n-- > 0){
        ll sum = 0;
        string a;
        cin >> a;
        while(a != "."){
            if(mp.find(a) != mp.end()){
                sum += mp.find(a) -> second;
            }
            cin >> a;
        }
        cout << sum << "\n";
    }
    
    return 0;
}
