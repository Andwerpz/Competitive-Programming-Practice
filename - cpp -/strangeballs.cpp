#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC 2022 Week 1 E

//Stack based problem. Notice that the balls not at the top of the stack can never disappear. 

//So, we just have to keep track of the amount of balls at the top of the stack. We can group balls
//based on their types, so the type of the ball doesn't factor into time complexity. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int ans = 0;
    stack<pair<int, int>> s;    //type, amt
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int type;
        cin >> type;
        if(s.size() == 0 || s.top().first != type){
            s.push({type, 0});
        }
        s.top().second ++;
        ans ++;
        if(s.top().second == type){
            ans -= type;
            s.pop();
        }
        cout << ans << "\n";
    }
    
    return 0;
}
