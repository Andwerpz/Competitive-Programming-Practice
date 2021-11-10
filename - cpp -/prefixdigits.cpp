
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//DMOJ - pdigit

//my idea was to try to bring k up to the same magnitude as n, and then iterate up k, and see if n had the same starting digits as k.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        ll n, k;
        cin >> n >> k;
        int nZero = 0;
        int kZero = 0;
        bool isValid = true;
        string s = to_string(n);
        for(int i = s.length() - 1; i >= 0; i--){
            if(s[i] != '0'){
                break;
            }
            nZero ++;
        }
        s = to_string(k);
        for(int i = s.length() - 1; i >= 0; i--){
            if(s[i] != '0'){
                break;
            }
            kZero ++;
        }
        if(nZero < kZero){
            isValid = false;
        }
        else{
            if(nZero > kZero){
                while(kZero != nZero - 1){
                    k *= 10;
                    kZero ++;
                }
            }
            isValid = false;
            string nString = to_string(n);
            ll kTemp = k;
            for(int i = 0; i < 100; i++){
                string kString = to_string(kTemp);
                int pointer = kString.length() - 1;
                bool curValid = true;
                //cout << kString << " " << nString << endl;
                for(int j = nString.length() - 1; j >= 0; j--){
                    if(pointer == -1){
                        break;
                    }
                    if(kString[pointer] != nString[j]){
                        curValid = false;
                        break;
                    }
                    pointer --;
                }
                if(curValid){
                    isValid = true;
                    break;
                }
                kTemp += k;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }

    return 0;
}



