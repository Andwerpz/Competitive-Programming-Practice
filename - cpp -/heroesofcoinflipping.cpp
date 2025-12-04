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

//2020-2021 ICPC NERC (NEERC) - H

//observe that a game A is not exciting iff we've seen another game B, where B is an ancestor of A and
//the winner of A is present in B. 

//first, lets solve it if n = 2^k
//lets consider every game we watch in chronological order. Before we watch a game, we can find its closest
//ancestor that we've watched. Then, if there are D intermediate games between the current one and its 
//closest ancestor, then the probability that the winner of this game gets to the ancestor is (1/2)^D. 
//so we can directly compute the probability of each game being exciting. 

//of course, if a game doesn't have an ancestor that we've watched, then the game is always exciting. 

//next, lets solve it if n = 0
//since we don't know the order in which the games are watched, this seems relatively hard. However, since
//the only thing that matters is D, we can just iterate across D, and the extra thing we need to do is 
//compute the probability for some D to occur. 

//suppose we want to compute the probability that D = 0. This means that we watch the very next game before
//the child. This has probability 1/2 of happening. 
//next, compute probability of D = 1. So we want to compute the probability of both the parent being after and
//grandparent being before the child. Parent has 1/2 probability to be after child, and conditioned on the
//parent being after the child, the grandparent actually has 1/3 probability to be before the child. 
//once you observe that it isn't just powers of 1/2, you can probably derive the rule pretty easily.
//hint : think about how you would build the permutation. 

//finally, let's look at how to solve the original problem. 
//getting the EV of the first N nodes is relatively easy, we can just solve it like the N = 2^K case. 
//the rest of the nodes are more tricky, but at this point it's just an exercise in implementation. 
//hint : figure out how to compute the contribution of a subtree of not-given nodes in O(k) time, then you
// can observe that there are actually only O(nk) subtrees that you need to compute. 

struct node {
    node *parent;
    node *left, *right;
    bool is_given;

    node() {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        is_given = false;
    }

    node(node *_parent) {
        parent = _parent;
        left = nullptr;
        right = nullptr;
        is_given = false;
    }

    node* add(int s, int m) {
        if(s == 0) {
            assert(m == 0);
            assert(!this->is_given);
            is_given = true;
            return this;
        }
        if(m < (1 << (s - 1))) {
            if(left == nullptr) left = new node(this);
            return left->add(s - 1, m);
        }
        else {
            if(right == nullptr) right = new node(this);
            return right->add(s - 1, m - (1 << (s - 1)));
        }
    }
};

vd pd, cpd, term, lsum;
node *root;

ld solve_slow(node *cur, int depth, int d, bool given_above, int k) {
    if(depth == k) return 0;
    ld ans = 0;
    if(!cur->is_given) {
        //compute ev for this node
        if(given_above) {
            ans += lsum[d] + cpd[d] * (1.0 - 1.0 / (ld) (1 << d));
            // cout << "TERM : " << term[d] << "\n";
        }
        else {
            ans += lsum[depth] + cpd[depth];
        }
        // cout << "PROB : " << depth << " " << (d * given_above) << " " << ans << "\n";
    }
    else {
        d = -1;
        given_above = true;
    }
    if(cur->left == nullptr) cur->left = new node(cur);
    if(cur->right == nullptr) cur->right = new node(cur);
    ans += solve_slow(cur->left, depth + 1, d + 1, given_above, k);
    ans += solve_slow(cur->right, depth + 1, d + 1, given_above, k);
    return ans;
}

ld solve(node *cur, int depth, int d, bool given_above, int k) {
    ld ans = 0;

    if(!cur->is_given) {
        //compute ev for this node
        if(given_above) {
            ans += lsum[d] + cpd[d] * (1.0 - 1.0 / (ld) (1 << d));
        }
        else {
            ans += lsum[depth] + cpd[depth];
        }
    }
    else {
        d = -1;
        given_above = true;
    }
    if(cur->left != nullptr) ans += solve(cur->left, depth + 1, d + 1, given_above, k);
    else {
        if(given_above) {
            for(int i = depth + 1; i < k; i++) {
                int ind = d + 1 + (i - depth - 1);
                // cout << "IND : " << ind << "\n";
                ans += (lsum[ind] + cpd[ind] * (1.0 - 1.0 / (ld) (1 << ind))) * (1 << (i - depth - 1));
            }
            // cout << "GIVEN ABOVE : " << ans << "\n";
        }
        else {
            for(int i = depth + 1; i < k; i++) {
                ans += (lsum[i] + cpd[i]) * (1 << (i - depth - 1));
            }
        }
    }
    if(cur->right != nullptr) ans += solve(cur->right, depth + 1, d + 1, given_above, k);
    else {
        if(given_above) {
            for(int i = depth + 1; i < k; i++) {
                int ind = d + 1 + (i - depth - 1);
                // cout << "IND : " << ind << "\n";
                ans += (lsum[ind] + cpd[ind] * (1.0 - 1.0 / (ld) (1 << ind))) * (1 << (i - depth - 1));
            }
        }
        else {
            for(int i = depth + 1; i < k; i++) {
                ans += (lsum[i] + cpd[i]) * (1 << (i - depth - 1));
            }
        }
    }

    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k;
    cin >> k >> n;

    pd = vd(k + 1);
    for(int i = 0; i <= k; i++) {
        pd[i] = 1.0;
        for(int j = 0; j < i; j++) {
            pd[i] *= (ld) (j + 1) / (ld) (j + 2);
        }
        pd[i] *= (ld) (1.0) / (ld) (i + 2);
    }
    cpd = vd(k + 1);
    for(int i = 0; i <= k; i++) {
        cpd[i] = 1.0;
        for(int j = 0; j < i; j++) {
            cpd[i] *= (ld) (j + 1) / (ld) (j + 2); 
        }
    }
    term = vd(k + 1);
    for(int i = 0; i <= k; i++) {
        term[i] = pd[i] * (1.0 - (ld) 1.0 / (ld) (1 << i));
    }
    lsum = vd(k + 1);
    for(int i = 0; i <= k; i++) {
        lsum[i] = 0.0;
        for(int j = 0; j < i; j++) {
            lsum[i] += term[j];
        }
    }

    // if(n == 0) {
    //     ld ans = 0;
    //     for(int i = 0; i < k; i++) {
    //         ans += (lsum[i] + cpd[i]) * (1 << i);
    //     }
    //     cout << fixed << setprecision(10) << ans << "\n";
    //     return 0;
    // }

    ld ans = 0;
    root = new node();
    for(int i = 0; i < n; i++) {
        int s, m;
        cin >> s >> m;
        s = k - s;
        m --;
        // cout << "ADD : " << s << " " << m << "\n";
        node *x = root->add(s, m);
        
        //get ev for this one
        int d = 0;
        while(true) {
            x = x->parent;
            if(x == nullptr) break;
            if(x->is_given) break;
            d ++;
        }
        // cout << "GIVEN : " << (x == nullptr) << "\n";
        if(x == nullptr) ans += 1.0;
        else ans += 1.0 - (ld) 1.0 / (ld) (1 << d);
    }
    // cout << "INIT ANS : " << ans << "\n";

    ans += solve(root, 0, 0, false, k);
    // ans += solve_slow(root, 0, 0, false, k);
    cout << fixed << setprecision(10) << ans << "\n";
    
    return 0;
}