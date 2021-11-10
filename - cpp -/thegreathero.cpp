
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1480B

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        ll a, b, n;
        cin >> a >> b >> n;
        vector<int> health(n);
        vector<int> attack(n);
        for(int i = 0; i < n; i++){
            cin >> attack[i];
        }
        for(int i = 0; i < n; i++){
            cin >> health[i];
        }
        bool isValid = false;
        ll maxAttack = 0;
        for(int i = 0; i < n; i++){
            ll curHealth = health[i];
            ll curAttack = attack[i];
            ll numAttacks = curHealth / a + (curHealth % a == 0? 0 : 1);
            b -= numAttacks * curAttack;
            maxAttack = max(maxAttack, curAttack);
        }
        if(b + maxAttack > 0){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }

    return 0;
}



