#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//USACO Silver December 2015

//The solution is to always play the lowest card that can beat the next card the opponent puts out. 
//If you can't beat the opponent's card, then put out your lowest card.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("highcard.in", "r", stdin);
    freopen("highcard.out", "w", stdout);
    
    int n;
    cin >> n;
    set<int> bcards;
    for(int i = 1; i <= n * 2; i++){
        bcards.insert(i);
    }
    vector<int> ecards(0);
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        bcards.erase(next);
        ecards.push_back(next);
    }
    int ans = 0;
    for(int i = 0; i < n; i++){
        auto next = bcards.upper_bound(ecards[i]);
        if(next != bcards.end()){
            bcards.erase(next);
            ans ++;
        }
        else{
            bcards.erase(bcards.begin());
        }
    }
    cout << ans << endl;
    
    return 0;
}
