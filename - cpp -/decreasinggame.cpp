#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1839E

//essentially what the operation is doing is we're subtracting the smaller element from the bigger element, and
//then removing the smaller element. 

//In order for the first player to win, they want 1 non-zero element at the end, and the second player wants 
//0 non-zero elements. Note that for the second player to win, the last valid move must be with two equal elements, 
//as that's the only way to remove both of them in one move. 

//Actually, if we can partition the array into two equal parts, then we can just play as the second player and always
//win. This is true because as the second player, we can select an element from the opposite part that the first 
//player selects, keeping the sum between the two parts equal. And since every operation is guaranteed to remove
//an element, eventually the game will get to the state where there are only 2 equal non-zero elements remaining. 

//If it's impossible to partition the array into two equal parts, then the first player always wins. There actually
//isn't any strategy, you can just pick a random non-zero element and always win. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    bool p2_win = false;
    set<int> p2_set;
    int sum = 0;
    for(int i = 0; i < a.size(); i++){
        sum += a[i];
    }
    if(sum % 2 == 0){
        //0 = unv, 1 = don't take prev, 2 = take prev
        vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));
        dp[0][0] = -1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= sum; j++){
                if(dp[i][j] == 0){
                    continue;
                }
                dp[i + 1][j] = 1;
                if(j + a[i] <= sum) {
                    dp[i + 1][j + a[i]] = 2;
                }
            }
        }
        if(dp[n][sum / 2] != 0){
            int ptr = sum / 2;
            for(int i = n; i > 0; i--){
                if(dp[i][ptr] == 1){
                    continue;
                }
                ptr -= a[i - 1];
                p2_set.insert(i - 1);
            }
            p2_win = true;
        }
    }
    if(p2_win) {
        cout << "Second" << endl;
        set<int> aset, bset;
        for(int i = 0; i < n; i++){
            if(p2_set.count(i)) {
                aset.insert(i);
            }
            else {
                bset.insert(i);
            }
        }
        while(true) {
            int i;
            cin >> i;
            if(i == 0){
                break;
            }
            i --;
            int j = -1;
            if(aset.count(i)) {
                j = *bset.begin();
                int mn = min(a[i], a[j]);
                a[i] -= mn, a[j] -= mn;
                if(a[i] == 0){
                    aset.erase(i);
                }
                if(a[j] == 0){
                    bset.erase(j);
                }
            }
            else {
                j = *aset.begin();
                int mn = min(a[i], a[j]);
                a[i] -= mn, a[j] -= mn;
                if(a[i] == 0){
                    bset.erase(i);
                }
                if(a[j] == 0){
                    aset.erase(j);
                }
            }
            cout << j + 1 << endl;
        }
    }
    else {
        cout << "First" << endl;
        while(true){
            int _i = -1;
            for(int i = 0; i < n; i++){
                if(a[i] != 0){
                    _i = i;
                    break;
                }
            }
            cout << _i + 1 << endl;
            int j;
            cin >> j;
            if(j == 0){
                break;
            }
            j --;
            int mn = min(a[_i], a[j]);
            a[_i] -= mn, a[j] -= mn;
        }
    }
    
    return 0;
}