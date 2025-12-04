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

//Codeforces - 2155D

//Since we don't know the value of A, our solution needs to be able to solve regardless of what value it is. 

//consider A = N / 2, we have exactly 2N queries. It seems like the best way to solve it given A = N / 2 is
//to query N / 2 disjoint pairs. If at this point the flaslight hasn't turned on, we know that each disjoint pair
//has at most 1 working battery, then we can start pairing up all the pairs. 

//actually, this works in general. Start with N disjoint groups. At every step, pick the smallest 2 groups 
//and try every pairwise pair between the two groups. If the flashlight doesn't turn on, merge the two groups
//and keep going. Since we know that there can be at most 1 battery in any group, due to pidgeonhole principle
//our search will end when there are A groups and we pick the smallest 2 groups to merge. 

//proving this stays under the query limit is an exercise for the reader :3

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        queue<vi> q;
        for(int i = 1; i <= n; i++) q.push({i});
        while(true) {
            assert(q.size() >= 2);
            vi a = q.front();
            q.pop();
            vi b = q.front();
            q.pop();
            bool done = false;
            for(int u : a) for(int v : b) {
                cout << u << " " << v << endl;
                int ret;
                cin >> ret;
                if(ret == -1) return 0;
                if(ret == 1) {
                    done = true;
                    break;
                }
            }
            if(done) break;
            vi c;
            for(int x : a) c.push_back(x);
            for(int x : b) c.push_back(x);
            q.push(c);
        }
    }
    
    return 0;
}