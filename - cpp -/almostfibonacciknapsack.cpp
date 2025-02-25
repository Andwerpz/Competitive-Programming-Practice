#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Topcoder - 14178

//brute force with heuristics. 

//notice that although x is pretty large, the number of elements in the sequence that are smaller than x are no more than
//around 100. This is because each element almost doubles compared to the previous element. We don't ever need to 
//consider elements greater than x, so we just need to check if x can be made using the first 100 or so elements. 

//Consider a brute force recursive approach where we either take or leave elements to try to make x. Without any 
//optimizations, this will run in O(2^n) time where n is the number of elements that we're considering, however we
//can add some heuristics to make this run significantly faster. 

//First, we'll make sure the current sum never exceeds x. Second, we'll make sure that it's possible to make the sum
//greater than or equal to x by adding all the remaining elements to the sum. If both of these are not met, then it's
//impossible to eventually make the sum equal to x, and we should back out. 

//This is actually enough heuristics to make the solution fast enough. 

bool solve(int ind, ll sum, ll x, vl& s, vl& sfx, stack<int>& st){
    if(sum == x) return true;
    if(ind == s.size() || sum > x || sum + sfx[ind] < x) return false;
    st.push(ind);
    if(solve(ind + 1, sum + s[ind], x, s, sfx, st)) return true;
    st.pop();
    return solve(ind + 1, sum, x, s, sfx, st); 
}

class AlmostFibonacciKnapsack {
public:
    vector<int> getIndices(ll x) {
        vl s = {2, 3};
        while(*s.rbegin() < x) s.push_back(s[s.size() - 1] + s[s.size() - 2] - 1);
        reverse(s.begin(), s.end());
        stack<int> st;
        vl sfx(s.size() + 1, 0);
        for(int i = s.size() - 1; i >= 0; i--) sfx[i] = sfx[i + 1] + s[i];
        solve(0, 0, x, s, sfx, st);
        vi ans;
        if(st.size() != 0) {
            while(st.size() != 0) ans.push_back(s.size() - st.top()), st.pop();
            reverse(ans.begin(), ans.end());
        }
        else ans = {-1};
        return ans;
    }
};

int main() {
    long long arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = AlmostFibonacciKnapsack();
    vector<int> ret = c.getIndices(arg0);
    for (auto& item : ret) { cout << item << "\n"; }
}