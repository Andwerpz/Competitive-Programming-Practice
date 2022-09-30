#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 3E

//for each number, count how many times it appears in the list. If x appears greater than or equal to x times, then
//just remove until you have x appearances. Else, you have to remove all of x. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    map<int, int> m;
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        if(m.find(next) == m.end()){
            m.insert({next, 0});
        }
        m.find(next) -> second ++;
    }
    ll ans = 0;
    for(auto i = m.begin(); i != m.end(); i++){
        int val = i -> first;
        int amt = i -> second;
        if(amt >= val){
            ans += amt - val;
        }
        else{
            ans += amt;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
