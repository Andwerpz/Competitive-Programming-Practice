#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 3C

//use a map to keep track of how many times you've seen each username. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    map<string, int> m;
    for(int i = 0; i < n; i++){
        string next;
        cin >> next;
        if(m.find(next) == m.end()){
            m.insert({next, 1});
            cout << "OK\n";
        }
        else{
            cout << next << (m.find(next) -> second) << "\n";
            m.find(next) -> second ++;
        }
    }
    
    return 0;
}
