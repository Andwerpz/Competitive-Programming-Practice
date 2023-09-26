#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1870D

//i solved this using a greedy strategy, i couldn't prove that this is correct. 

//the intuition is that we want to first maximize the number of purchases, regardless of what we purchase. 
//this means finding the minimum cost element, and buying as many as we can. 
//next, we want to try to push our purchases as far right as we can, buy selling some of the stuff we bought before
//and buying stuff to the right, given that we can make a 1 to 1 trade, with our leftover coins facilitating. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int k;
        cin >> k;
        map<pair<int, int>, int> m; //{cost, -index} -> amount
        for(int i = 0; i < n; i++){
            int cost = a[i];
            //for anything above this price, sell it. 
            while(m.size() != 0 && m.rbegin() -> first.first >= cost) {
                pair<int, int> pi = m.rbegin() -> first;
                int amt = m.rbegin() -> second;
                k += amt * pi.first;
                m.erase(pi);
            }
            //if we can still perform a 1 to 1 sell to buy, then do it.
            while(m.size() != 0){
                pair<int, int> pi = m.rbegin() -> first;
                int amt = m.rbegin() -> second;
                int ureq = cost - pi.first;
                int sellamt = (k % cost) / ureq;
                sellamt = min(amt, sellamt);
                k += pi.first * sellamt;
                m[pi] -= sellamt;
                if(m[pi] == 0){
                    m.erase(pi);
                }
                else {
                    break;
                }
            }
            //buy everything we can
            int buyamt = k / cost;
            k -= buyamt * cost;
            m.insert({{cost, -i}, buyamt});
        }
        //write to answer. 
        vector<int> ans(n, 0);
        for(auto i = m.begin(); i != m.end(); i++){
            int ind = -i -> first.second;
            int amt = i -> second;
            ans[ind] = amt;
        }
        for(int i = n - 2; i >= 0; i--){
            ans[i] += ans[i + 1];
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
