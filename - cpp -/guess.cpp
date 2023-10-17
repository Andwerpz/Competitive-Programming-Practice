#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - guess

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int low = 1;
    int high = 1000;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        cout << mid << endl;
        string s;
        cin >> s;
        if(s == "correct") {
            break;
        }
        else if(s == "lower") {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }
    
    return 0;
}
