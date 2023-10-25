#include <bits/stdc++.h>
typedef long long ll;
// typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2016 L

//if we know the sequence in which to reformat the drives, we can directly compute the answer. 

//the problem is that the sequence is not obvious. 

//note that we should probably reformat all of the drives that increase our extra storage first. These drives
//should be done in ascending order based off of the initial amount of memory required. 

//for the drives that decrease storage, we should order them in descending order of the amount of memory the
//drive will become after the reformatting. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<ll,ll>> decreases(0);
    vector<pair<ll,ll>> increases(0);
    for(int i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        if(b > a) {
            increases.push_back({a,b});
        } else {
            decreases.push_back({a,b});
        }
    }

    ll total_extra = 0;
    ll curr_extra = 0;

    sort(increases.begin(),increases.end());

    for(int i = 0; i < increases.size(); i++) {
        if(curr_extra < increases[i].first) {
            ll add = increases[i].first - curr_extra;
            total_extra += add;
            curr_extra += add;
        }
        curr_extra -= increases[i].first;
        curr_extra += increases[i].second;
    }

    sort(decreases.begin(),decreases.end(), [] (const pair<ll,ll> &lhs, const pair<ll,ll> &rhs) -> bool {
        if(lhs.second == rhs.second) {
            return lhs.first > rhs.first;
        } else {
            return    lhs.second > rhs.second;
        }
        
    });

    for(int i = 0; i < decreases.size(); i++) {
        if(curr_extra < decreases[i].first) {
            ll add = decreases[i].first - curr_extra;
            total_extra += add;
            curr_extra += add;
        }
        curr_extra -= decreases[i].first;
        curr_extra += decreases[i].second;
    }
    
    cout << total_extra << "\n";

    return 0;
}
