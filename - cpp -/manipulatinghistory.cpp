#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1688C

//for a char to appear in the string, it must have a counterpart, some substring that added it
//originally. This means each time the letter appears, it has to appear twice, meaning it appears an even
//amount of times. 

//If a letter appears an odd amount of times, then it has to be the initial char. This works because 
//the length of the initial string is always 1. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        int n;
        cin >> n;
        vector<int> a(26);
        for(int i = 0; i < n * 2 + 1; i++){
            string s;
            cin >> s;
            for(char c : s) {
                a[c - 'a'] ++;
            }
        }
        for(int i = 0; i < a.size(); i++){
            if(a[i] % 2 == 1){
                char ch = ('a' + i);
                cout << ch << "\n";
                break;
            }
        }
    }
    
    return 0;
}
