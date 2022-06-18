#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1694A

//just have to alternate between 0 and 1

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int a, b;
        cin >> a >> b;
        char prev = a >= b? '1' : '0';
        vector<char> ans(0);
        while(a > 0 || b > 0){
            if(a == 0){
                ans.push_back('1');
                b--;
            }
            else if(b == 0){
                ans.push_back('0');
                a--;
            }
            else{
                char next = prev == '0'? '1' : '0';
                ans.push_back(next);
                prev = next;
                if(next == '0'){
                    a--;
                }
                else{
                    b--;
                }
            }
        }
        for(char c : ans){
            cout << c;
        }
        cout << endl;
    }
    
    return 0;
}
