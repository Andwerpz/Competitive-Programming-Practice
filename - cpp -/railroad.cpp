#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 02 F

//you want an odd amount of outgoing exits from the junction. The problem implies that since you have an unlimited
//amount of curved and straight and bridge rails, you can connect any two exits. 

//therefore, if the number of 'Y' junctions is odd, then there will always be a leftover exit. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b;
    cin >> a >> b;
    cout << (b % 2 == 0? "possible" : "impossible") << endl;
    
    return 0;
}
