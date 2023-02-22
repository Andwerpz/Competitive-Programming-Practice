#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1795C

//consider a different problem, where each tea gets drunk by each taster, so taster 1 goes and drinks from all the teas
//then taster 2 drinks from all of them, etc... . It's pretty apparent that we can just use a min priority queue to solve
//this; keep track of the sum of tea that is drank from each cup, while the sum is greater than the top of the queue, 
//pop the queue and take away from the current tasters answer. 

//the idea for this problem is similar, except taster i doesn't get to drink from teas i - n. Instead of initially putting everything
//into the queue, we put the ith tea in when we compute the answer for the ith taster. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<ll> a(n, 0);
        vector<ll> b(n, 0);
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        priority_queue<ll> tea;
        ll sub = 0;
        for(int i = 0; i < n; i++){
            ll ans = 0;
            tea.push(-(b[i] + sub));
            ans = (ll) tea.size() * a[i];
            sub += a[i];
            while(tea.size() != 0 && -tea.top() <= sub){
                //cout << "finish " << -tea.top() << "\n";
                ans += -tea.top() - sub;
                tea.pop();
            }
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
