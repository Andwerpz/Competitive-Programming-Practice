#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef array<int, 2> pii;
typedef array<ll, 2> pll;
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

//2022-2023 Winter Petrozavodsk Camp Day 4 - J

//some nim grundy 

//for each squirrel, we only care about the number of empty spaces directly in front of it. 
//consider k = 1. Each move, we take some amount of squares from one squirrel and transfer it to the
//squirrel directly behind it. 

//We can arrive at this winning strategy: If we consider pairs of adjacent squirrels
//(we start the pairs from the last squirrel, if n is odd then pretend there is a squirrel at the front with 
//0 spaces remaining), then if the second player can maintain that the second squirrel in every pair has 0 spaces,
//then they can always win. Whenever the first player makes a move, it has to be on the first squirrel in the 
//pair, then the first player can easily maintain the invariant by moving the second squirrel forwards. 

//then to achieve this invariant, the two players have to play a normal nim game over all the second squirrels in 
//each pair. 

//Now, unfix k. Observe that now instead of transferring the spaces to the direct next squirrel, we transfer to the
//kth next squirrel. For a given k, squirrel i can interact with squirrel j iff i % k == j % k, therefore we
//can say that there are k different games which we can compute the grundy number for seperately. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int m, n, k;
    cin >> m >> n >> k;
    vi a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    vi d(n);
    d[0] = a[0] - 1;
    for(int i = 1; i < n; i++) d[i] = a[i] - a[i - 1] - 1;
    vvi b(k);
    int g = 0;
    for(int i = 0; i < k; i++){
        vi b;
        for(int j = i; j < n; j += k) {
            b.push_back(d[j]);
        }
        if(b.size() % 2) b.insert(b.begin(), 0);
        for(int j = 1; j < b.size(); j += 2) {
            g ^= b[j];
        }
    }
    cout << (g? "Twinkle" : "Nova") << "\n";
    
    return 0;
}