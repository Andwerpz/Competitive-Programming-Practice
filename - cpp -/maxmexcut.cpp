
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1566C

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string s1;
        string s2;
        cin >> s1 >> s2;
        int ans = 0;
        bool seen0 = false;
        bool seen1 = false;
        for(int i = 0; i < n; i++){
            if(s1[i] != s2[i]){
                if(seen0){
                    ans ++;
                }
                ans += 2;
                seen0 = false;
                seen1 = false;
            }
            else if(s1[i] == '1' && s2[i] == '1'){
                if(seen0){
                    ans += 2;
                    seen1 = false;
                    seen0 = false;
                }
                else{
                    seen1 = true;
                }
            }
            else{
                if(seen1){
                    ans += 2;
                    seen0 = false;
                    seen1 = false;
                }
                else if(seen0){
                    ans ++;
                }
                else{
                    seen0 = true;
                }
            }
        }
        if(seen0){
            ans ++;
        }
        cout << ans << endl;
    }

    return 0;
}



