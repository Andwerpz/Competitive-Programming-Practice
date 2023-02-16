#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//NCNA 2018 Regional I

//this is the general form of the classic wolf, sheep, cabbage problem. 

//if w = 0, then either s or c has to be less than k, or s = c = k. 
//similar reasoning for c = 0. 

//if s, c, k > 0, then if s <= k and w + c <= k * 2, then it's valid
//similarly, w + c <= k and s <= k * 2 is also valid. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll w, s, c, k;
    cin >> w >> s >> c >> k;
    bool isValid = false;
    if(w == 0){
        if((s == k && c == k) || s < k || c < k){
            isValid = true;
        }
    }
    if(c == 0){
        if((s == k && w == k) || s < k || w < k){
            isValid = true;
        }
    }
    if(s == 0){
        isValid = true;
    }
    if(s <= k && w + c <= k * 2){
        isValid = true;
    }
    if(s <= 2 * k && w + c <= k){
        isValid = true;
    }
    if(s < k || w + c < k){
        isValid = true;
    }
    if(k == 0){
        isValid = false;
    }
    cout << (isValid? "YES\n" : "NO\n");
    
    return 0;
}
