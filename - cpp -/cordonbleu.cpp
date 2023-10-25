#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Kattis - cordonbleu

//we can convert this problem into the job matching problem if we consider that there are 
//n - 1 couriers just waiting at the restaurant. 

//now, we are forced to use at least one courier that isn't originally at the restaurant, 
//and if it is optimal to use a courier starting from the restaurant, we have the n - 1 couriers
//waiting there. 

template <class T> 
bool ckmin(T &a, const T &b) { return b < a ? a = b, 1 : 0; }

template <class T>
vector<T> hungarian(const vector<vector<T>> &C) {
    const int J = (int)size(C), W = (int)size(C[0]);
    assert(J <= W);
    // job[w] = job assigned to w-th worker, or -1 if no job assigned
    // note: a W-th worker was added for convenience
    vector<int> job(W + 1, -1);
    vector<T> ys(J), yt(W + 1);  // potentials
    // -yt[W] will equal the sum of all deltas
    vector<T> answers;
    const T inf = numeric_limits<T>::max();
    for (int j_cur = 0; j_cur < J; ++j_cur) {  // assign j_cur-th job
        int w_cur = W;
        job[w_cur] = j_cur;
        // min reduced cost over edges from Z to worker w
        vector<T> min_to(W + 1, inf);
        vector<int> prv(W + 1, -1);  // previous worker on alternating path
        vector<bool> in_Z(W + 1);    // whether worker is in Z
        while (job[w_cur] != -1) {   // runs at most j_cur + 1 times
            in_Z[w_cur] = true;
            const int j = job[w_cur];
            T delta = inf;
            int w_next;
            for (int w = 0; w < W; ++w) {
                if (!in_Z[w]) {
                    if (ckmin(min_to[w], C[j][w] - ys[j] - yt[w]))
                        prv[w] = w_cur;
                    if (ckmin(delta, min_to[w])) w_next = w;
                }
            }
            // delta will always be non-negative,
            // except possibly during the first time this loop runs
            // if any entries of C[j_cur] are negative
            for (int w = 0; w <= W; ++w) {
                if (in_Z[w]) ys[job[w]] += delta, yt[w] -= delta;
                else min_to[w] -= delta;
            }
            w_cur = w_next;
        }
        // update assignments along alternating path
        for (int w; w_cur != -1; w_cur = w) job[w_cur] = job[w = prv[w_cur]];
        answers.push_back(-yt[W]);
    }
    return answers;
}

int dist(pair<int, int>& a, pair<int, int>& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> bottles(n);
    vector<pair<int, int>> couriers(m);
    for(int i = 0; i < n; i++){
        cin >> bottles[i].first >> bottles[i].second;
    }
    for(int i = 0; i < m; i++){
        cin >> couriers[i].first >> couriers[i].second;
    }
    pair<int, int> restaurant;
    cin >> restaurant.first >> restaurant.second;
    vector<vector<int>> cost(n, vector<int>(m + n - 1));
    for(int i = 0; i < n; i++){
        //home -> bottle -> restaurant
        for(int j = 0; j < m; j++){
            cost[i][j] = dist(couriers[j], bottles[i]) + dist(bottles[i], restaurant);
        }
        //restaurant -> bottle -> restaurant
        for(int j = 0; j < n - 1; j++){
            cost[i][m + j] = dist(restaurant, bottles[i]) * 2;
        }
    }
    cout << hungarian<int>(cost)[n - 1] << "\n";

    return 0;
}
