#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC NAQ 2023 - F

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string str; cin >> str;

    int vowels = 0, y = 0;
    for(char c : str) {
        switch(c) {
            case 'a' : vowels++; break;
            case 'e' : vowels++; break;
            case 'i' : vowels++; break;
            case 'o' : vowels++; break;
            case 'u' : vowels++; break;
            case 'y' : y++; break;
        }
    }
    cout << vowels << " " << vowels + y << '\n';
    return 0;
}
