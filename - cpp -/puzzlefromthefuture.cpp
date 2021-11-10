
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1474A

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string s;
        cin >> s;
        string ans = "";
        char prev = 0;
        for(int i = 0; i < n; i++){
            if(i == 0){
                if(s[0] == '1'){
                    ans += '2';
                }
                else{
                    ans += '1';
                }
            }
            else{
                if(prev == '2'){
                    ans += '1';
                }
                else if(prev == '1'){
                    if(s[i] == '1'){
                        ans += '2';
                    }
                    else{
                        ans += '0';
                    }
                }
                else {
                    if(s[i] == '1'){
                        ans += '2';
                    }
                    else{
                        ans += '1';
                    }
                }
            }
            prev = ans[ans.size() - 1];
        }
        string realAns = "";
        for(int i = 0; i < ans.size(); i++){
            if(s[i] == '1'){
                if(ans[i] == '2'){
                    realAns += '1';
                }
                else if(ans[i] == '1'){
                    realAns += '0';
                }
            }
            else{
                if(ans[i] == '1'){
                    realAns += '1';
                }
                else{
                    realAns += '0';
                }
            }
        }
        cout << realAns << endl;
    }

    return 0;
}



