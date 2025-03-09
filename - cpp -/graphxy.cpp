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

//AtCoder - ARC89E

//Observe that any path from S to T is going to have a weight of form c_1 * X + c_2 * Y + c_3. 
//The minimum weight is simply the minimum out of all these expressions. 

//What are the limits on c_1, c_2, and c_3? Due to limits on d_{x, y} being within 1 to 100, c_1, c_2, and c_3
//shouldn't be larger than 100, as if they are, then this path will never be the minimum length path. 
//Also, they can't be negative, so 0 <= c_1, c_2, c_3 <= 100.

//Actually, given some c_1 and c_2, there should only be 1 relevant c_3. This is because changing c_3 
//only really vertically shifts the plane, and the only plane that matters is the one with minimum c_3. 
//Since there are only around 10^4 (c_1, c_2) pairs, we can just brute force find all minimum c_3 for these pairs. 

//Once we have the expressions, how do we create a graph? Naively, we can just create a seperate path for
//each expression, but then we'll run into the 300 node limit. Realize that it's all the edges with single
//'X' and 'Y' labels that are really consuming all the nodes. 

//Instead, we can create the graph like this: Each path will have some amount of 'X's in the beginning, one 
//constant edge, and then a bunch of 'Y's at the back. From S, we'll have a chain of 100-ish 'X' edges chained
//together going outwards, and from T, we'll have 100-ish 'Y' edges chained together going into it. 
//Then, the constant edges will be placed going from the 'X' chain to the 'Y' chain, at appropriate distances 
//from S and T respectively. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int A, B;
    cin >> A >> B;
    vvi d(A + 1, vi(B + 1));
    for(int i = 1; i <= A; i++){
        for(int j = 1; j <= B; j++){
            cin >> d[i][j];
        }
    }
    set<array<int, 3>> es;  //{cx, cy, cnst}
    vvi cv(A + 1, vi(B + 1, 0));
    for(int cx = 0; cx <= 100; cx++){
        for(int cy = 0; cy <= 100; cy++){
            int cnst = -1e9;
            for(int i = 1; i <= A; i++){
                for(int j = 1; j <= B; j++){
                    int val = cx * i + cy * j;
                    cnst = max(cnst, d[i][j] - val);
                }
            }
            if(cnst < 0 || cnst > 100) continue;
            for(int i = 1; i <= A; i++){
                for(int j = 1; j <= B; j++){
                    int val = cx * i + cy * j + cnst;
                    cv[i][j] += val == d[i][j];
                }
            }
            es.insert({cx, cy, cnst});
        }
    }
    bool is_valid = true;
    for(int i = 1; i <= A; i++){
        for(int j = 1; j <= B; j++){
            if(!cv[i][j]) is_valid = false;
        }
    }
    if(!is_valid) {
        cout << "Impossible\n";
        return 0;
    }
    cout << "Possible\n";
    int S = 0, T = 1, N = 202, M = 0;
    vector<vector<pii>> c(N);   //-1 is X, -2 is Y
    vi xid(100), yid(100);
    xid[0] = S, yid[0] = T;
    int prev = S;
    for(int i = 2; i <= 101; i++){
        c[prev].push_back({i, -1});
        xid[i - 1] = i;
        prev = i;
        M ++;
    }
    prev = T;
    for(int i = 102; i <= 201; i++){
        c[i].push_back({prev, -2});
        yid[i - 101] = i;
        prev = i;
        M ++;
    }
    for(auto i = es.begin(); i != es.end(); i++){
        int cx = (*i)[0], cy = (*i)[1], cnst = (*i)[2];
        c[xid[cx]].push_back({yid[cy], cnst});
        M ++;
    }
    cout << N << " " << M << "\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < c[i].size(); j++){
            string out = c[i][j].second == -1? "X" : (c[i][j].second == -2? "Y" : to_string(c[i][j].second));
            cout << i + 1 << " " << c[i][j].first + 1 << " " << out << "\n";
        }
    }
    cout << S + 1 << " " << T + 1 << "\n";
    
    return 0;
}