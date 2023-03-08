#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1794A

//notice that there always are exactly two strings of each length i. 

//if the string is a palindrome, then any suffix of length i should be equal to the prefix of length i
//once reversed. 

//so, you can just make sure that this property is true for all the strings. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        map<int, string> m;
        bool isValid = true;
        for(int i = 0; i < (n - 1) * 2; i++){
            string s;
            cin >> s;
            if(m.find(s.size()) == m.end()) {
                m.insert({s.size(), s});
            }
            else {
                string a = m.find(s.size()) -> second;
                reverse(a.begin(), a.end());
                if(a != s){
                    isValid = false;
                }
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
