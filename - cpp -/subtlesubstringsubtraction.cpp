#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1673A

//if the string length is even, then alice will take everything.
//if the string length is odd, then alice will take everything except for the minimum of the 
//two characters on the ends. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int sum = 0;
        for(int i = 0; i < s.size(); i++){
            sum += s[i] - 'a' + 1;
        }
        int a = 0;
        int b = 0;
        if(s.size() % 2 == 0){
            a = sum;
        }
        else{
            a = sum - min(s[0] - 'a' + 1, s[s.size() - 1] - 'a' + 1);
            b = min(s[0] - 'a' + 1, s[s.size() - 1] - 'a' + 1);
        }
        cout << (a > b? "Alice " : "Bob ") << abs(a - b) << endl;
    }
    
    return 0;
}
