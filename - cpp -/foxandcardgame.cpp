#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 388C

//according to the editorial, under optimal play, each player will get at least floor(s / 2) cards from each stack, where 
//s is the size of the stack. The remaining cards will be taken in an alternating fashion in order of greatest to lowest. 

//lets consider the situation where all the stacks are initially even sized. If you go second, you can easily force the situation where
//both players get exactly half of each stack. If one stack deviates from this, we notice that it will either benefit one person or the other, 
//so both players have incentive to stick to only taking half of each stack. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(0);
    ll ans_a = 0;
    ll ans_b = 0;
    for(int i = 0; i < n; i++){
        int s;
        cin >> s;
        vector<int> c(s);
        for(int j = 0; j < s; j++){
            cin >> c[j];
        }
        int ptr = 0;
        for(int i = 0; i < s / 2; i++){
            ans_a += c[ptr++];
        }
        if(s % 2 == 1){
            a.push_back(c[ptr++]);
        }
        for(int i = 0; i < s / 2; i++){
            ans_b += c[ptr++];
        }
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    for(int i = 0; i < a.size(); i++){
        if(i % 2 == 0){
            ans_a += a[i];
        }
        else {
            ans_b += a[i];
        }
    }
    cout << ans_a << " " << ans_b << "\n";
    
    return 0;
}
