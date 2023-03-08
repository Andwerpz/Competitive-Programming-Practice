#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 07 B

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    set<char> v;
    v.insert('a');
    v.insert('e');
    v.insert('i');
    v.insert('o');
    v.insert('u');
    v.insert('y');
    while(n != 0){
        string ans = "";
        int cnt = 0;
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            if(cnt == 0){
                ans = s;
            }
            int curCnt = 0;
            for(int j = 1; j < s.size(); j++){
                if(s[j - 1] == s[j] && v.find(s[j]) != v.end()) {
                    curCnt ++;
                }
            }
            if(curCnt > cnt){
                ans = s;
                cnt = curCnt;
            }
        }
        cout << ans << "\n";
        cin >> n;
    }
    
    return 0;
}
