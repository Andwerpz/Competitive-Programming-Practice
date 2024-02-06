#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//NWERC 2020 - F

//only adjacent robots can collide with each other, so keep track of all gaps between adjacent robots.
//for each gap, compute the time at which the gap will become 0, and store all these times in a 
//min-priority queue. 

//when two robots collide, it then makes two robots that weren't adjacent, adjacent. Keep track of the
//new gap. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<lld,lld>> v(n);
    for(int i = 0; i < n; i++){
        ld vel, d;
        cin >> vel >> d;
        v[i].first = vel;
        v[i].second = d;
    }
    priority_queue<pair<lld,pair<int,int>>, vector<pair<lld,pair<int,int>>>, greater<pair<lld,pair<int,int>>>> pq;
    set<int> uncrashed;
    for(int i = 0; i < n; i++) {
        uncrashed.insert(i);
    }
    for(int i = 0; i < n - 1; i++) {
        if(v[i].second > v[i+1].second) {
            lld time = (v[i].first - v[i+1].first) / (v[i+1].second - v[i].second);
            // cout << "i : " << i << " time : " << time << '\n';
            pq.push({time, {i, i + 1}});
        }
    }
    while(pq.size()) {
        pair<lld,pair<int,int>> p = pq.top();
        pq.pop();
        if(uncrashed.find(p.second.second) == uncrashed.end() || uncrashed.find(p.second.first) == uncrashed.end()) continue;

        uncrashed.erase(p.second.first);
        uncrashed.erase(p.second.second);

        if(uncrashed.lower_bound(p.second.second) != uncrashed.end() && uncrashed.lower_bound(p.second.first) != uncrashed.begin()) {
            int loidx = (*--uncrashed.lower_bound(p.second.first));
            int hiidx = (*uncrashed.lower_bound(p.second.second));
            if(v[loidx].second > v[hiidx].second) {
                lld time = (v[loidx].first - v[hiidx].first) / (v[hiidx].second - v[loidx].second);
                // cout << "time : " << time << '\n';
                pq.push({time, {loidx, hiidx}});
            }
        }
    }
    cout << uncrashed.size() << '\n';
    for(int i = 0; i < n; i++) {
        if(uncrashed.count(i)) {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';

    return 0;
}
