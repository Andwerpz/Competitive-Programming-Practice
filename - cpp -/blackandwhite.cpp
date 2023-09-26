#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ACPC Weekly Problem Set 3 Fall 2023 I
//i also think i saw this in a pset related to icpc?

//do dp across all the possible subsets of children remaining. 
//for each, find the expected number of rounds played given that this is the starting state. 

vector<ld> dp((1 << 20), -1);
vector<ld> p;

ld solve(int state) {
    if(dp[state] != -1){
        return dp[state];
    }
    vector<int> c(0);
    {
        int tmp = state;
        int ind = 0;
        while(tmp != 0){
            if(tmp & 1) {
                c.push_back(ind);
            }
            ind ++;
            tmp /= 2;
        }
    }
    if(c.size() == 2) {
        dp[state] = 0;
        return 0;
    }
    ld p_sum = 1;
    ld c_sum = 1;
    for(int i = 0; i < c.size(); i++){
        p_sum *= p[c[i]];
        c_sum *= (1.0 - p[c[i]]);
    }
    ld t_prob = 0;
    ld ans = 0;
    for(int i = 0; i < c.size(); i++){
        {   
            //out is white
            ld prob = (p_sum / p[c[i]]) * (1.0 - p[c[i]]);
            t_prob += prob;
            ans += solve(state ^ (1 << c[i])) * prob;
        }
        {
            //out is black
            ld prob = (c_sum / (1.0 - p[c[i]])) * p[c[i]];
            t_prob += prob;
            ans += solve(state ^ (1 << c[i])) * prob;
        }
    }
    ans /= t_prob;
    ans += 1.0 / t_prob;
    dp[state] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    p = vector<ld>(n);
    for(int i = 0; i < n; i++){
        cin >> p[i];
    }
    cout << fixed << setprecision(10) << solve((1 << n) - 1) << "\n";
    
    return 0;
}
