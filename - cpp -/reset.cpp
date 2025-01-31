#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;

//2022 ICPC NAC - I

//given fixed amount of resets, how to determine if it's possible
// - on the resets before the final one, want to just focus on researching. 
// - greedily research the tasks that will reduce the sum the most. 
// - on the final reset, if we can still research, we should do so, otherwise just do tasks.

//is there any situation in which we would want to save some studying for the last reset?
//on the last reset, any studying we do comes at the cost of 1 second. Ideally, we don't have to do any studying during the 
//last reset. 

//are we getting any false positives?

//req = lower bound of total effort for all tot + 1 days
//last = lower bound of effort for last day
//req and last are computed assuming we research every task the maximum amount of times (tot + 1)
//if req > c * (tot + 1) or last > c, then it's definitely impossible. Obviously, we can't decrease the effective 
//time any more, since we've already researched to the maximum. 

//how to prove in the other case that it's always possible?
//lets split our tasks into 'easy' and 'hard' tasks. Easy tasks are ones that can be researched in tot or less days, and 
//hard ones have to be researched on the tot + 1th day. 
//we can see that it's easy to schedule all the 'easy' tasks, as no easy task has more than tot required times to research. 
//we can even throw in the first tot tasks for each of the 'hard' tasks in the first tot days, leaving each hard task with
//1 second needing scheduling on the last day. 
//Next, all the hard tasks need to be scheduled on the last day, sharing space with the leftover time that 
//couldn't be researched away. This is where the second constraint comes in, guaranteeing that we can fit everything into 
//the last day. 

//next, why didn't my old solution manage to construct something?
//my old solution greedily filled up the initial tot days with the largest decreases and in some testcases it would leave
//some task that had to be researched twice on the last day. 
//try this testcase:
//3 2
//4 4
//4 4
//6 3

bool is_valid(ll n, ll c, vector<array<ll, 2>>& a, lll tot) {
    // priority_queue<array<lll, 3>> q; //{d, t, ind}
    // for(int i = 0; i < a.size(); i++){
    //     q.push({a[i][0], a[i][1], i});
    // }
    // priority_queue<array<lll, 3>> fq;
    // vector<lll> amt(n, 0);
    // lll totamt = tot * (lll) c;
    // lll sum = 0;
    // for(int i = 0; i < n; i++) sum += a[i][1];
    // //before last reset
    // while(q.size() != 0){
    //     array<lll, 3> next = q.top();
    //     q.pop();
    //     lll d = next[0], t = next[1], ind = next[2];
    //     if(amt[ind] == tot || totamt == 0) {    //can't study this anymore
    //         fq.push({d, t, ind});
    //         continue;
    //     }
    //     lll camt = t / d;
    //     camt = min(camt, tot - amt[ind]);
    //     camt = min(camt, totamt);
    //     totamt -= camt;
    //     t -= camt * d;
    //     sum -= camt * d;
    //     amt[ind] += camt;
    //     if(t != 0) q.push({min(d, t), t, ind}); //remainder
    // }
    // //last reset
    // while(fq.size() != 0){
    //     array<lll, 3> next = fq.top();
    //     fq.pop();
    //     lll d = next[0], t = next[1], ind = next[2];
    //     if(d > 0) sum += 1, sum -= d;
    // }
    // return sum <= c;
    
    lll req = 0, last = 0;
    for(int i = 0; i < n; i++){
        lll t = a[i][1], d = a[i][0];
        lll amt = min(tot + 1, (t + d - 1) / d);
        req += amt;
        req += max((lll) 0, t - amt * d);
        if(amt == tot + 1) last += max((lll) 0, t - amt * d) + 1;
    }
    return req <= c * (tot + 1) && last <= c;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, c;
    cin >> n >> c;
    vector<array<ll, 2>> a; //{d, t}
    for(int i = 0; i < n; i++){
        ll t, d;
        cin >> t >> d;
        a.push_back({min(d, t), t});
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    lll low = 0, high = 1e18, ans = high;
    while(low <= high) {
        lll mid = low + (high - low) / 2;
        if(is_valid(n, c, a, mid)) ans = mid, high = mid - 1;
        else low = mid + 1;
    }
    cout << ((ll)ans) << "\n";

    return 0;
}