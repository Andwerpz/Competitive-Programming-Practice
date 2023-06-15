#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1841C

//'ranom' is anagram for 'roman'. nice. 

//for each digit in the number, try replacing with all other digits. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    vector<int> val = {1, 10, 100, 1000, 10000};
    while(t--) {
        string s;
        cin >> s;
        int n = s.size();
        vector<int> sfx(n + 1, 0);
        vector<int> sfxCnt(5, 0);
        vector<int> a(n, 0);
        for(int i = 0; i < n; i++){
            a[i] = s[i] - 'A';
        }
        for(int i = n - 1; i >= 0; i--){
            bool neg = false;
            for(int j = a[i] + 1; j < 5; j++){
                if(sfxCnt[j] != 0){
                    neg = true;
                    break;
                }
            }
            sfx[i] = (neg? -1 : 1) * val[a[i]] + sfx[i + 1];
            sfxCnt[a[i]] ++;
        }
        vector<int> pfxnCnt(5, 0);
        vector<int> pfxpCnt(5, 0);
        int ans = sfx[0];
        // cout << "SFX : \n";
        // for(int i = 0; i < n; i++){
        //     cout << sfx[i] << " ";
        // }
        // cout << "\n";
        for(int i = 0; i < n; i++){
            sfxCnt[a[i]] --;
            for(int j = 0; j < 5; j++){
                //try letter j. 
                int curAns = sfx[i + 1];
                //for each letter in the pfx, see what it's contribution is given that this letter is j. 
                int maxSfx = 0;
                for(int k = 0; k < 5; k++){
                    if(sfxCnt[k] != 0){
                        maxSfx = k;
                    }
                }
                for(int k = 0; k < 5; k++) {
                    curAns -= pfxnCnt[k] * val[k];
                    if(k >= max(maxSfx, j)) {
                        curAns += pfxpCnt[k] * val[k];
                    }
                    else {
                        curAns -= pfxpCnt[k] * val[k];
                    }
                }
                bool neg = false;
                for(int k = j + 1; k < 5; k++){
                    if(sfxCnt[k] != 0) {
                        neg = true;
                        break;
                    }
                }
                curAns += (neg? -1 : 1) * val[j];
                ans = max(ans, curAns);
            }
            pfxpCnt[a[i]] ++;
            for(int j = 0; j < a[i]; j++) {
                pfxnCnt[j] += pfxpCnt[j];
                pfxpCnt[j] = 0;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
