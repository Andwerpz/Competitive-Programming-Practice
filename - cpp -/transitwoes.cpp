#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 02 H

//just simulate the situation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int s, t, n;
    cin >> s >> t >> n;
    vector<int> d(n + 1);
    for(int i = 0; i < n + 1; i++){
        cin >> d[i];
    }
    vector<int> b(n);
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    vector<int> c(n);
    for(int i = 0; i < n; i++){
        cin >> c[i];
    }
    int ptr = 0;
    ptr += d[0];
    for(int i = 0; i < n; i++){
        //wait until the bus arrives
        ptr += (c[i] - (ptr % c[i])) % c[i];
        //get on and ride the bus
        ptr += b[i];
        //walk to the next bus
        ptr += d[i + 1];
    }
    cout << (ptr <= t? "yes" : "no") << "\n";
    
    return 0;
}
