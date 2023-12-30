#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2021 - L

//we can write a function that takes in an offset, and gives the spiral distance. 

//then, for each position in the grid, find all of the spiral distances to the 'X' characters, and sort them in 
//ascending order. 

//the soonest time a person can uniquely determine their position is the first time at which their sequence of 'X'
//visiting times is unique from all other sequences. We can use a trie to efficiently compute this for each
//sequence. 

struct Trie {
    struct TrieNode {
        map<int, TrieNode*> c;
        int subt_size = 0;
    };

    TrieNode head;

    Trie() {
        this->head = TrieNode();
    }

    void insert(vector<int>& a){
        TrieNode* ptr = &head;
        ptr->subt_size ++;
        for(int i = 0; i < a.size(); i++){
            int ch = a[i];
            if(ptr->c.find(ch) == ptr->c.end()) {
                ptr->c[ch] = new TrieNode();
            }
            ptr = ptr->c[ch];
            ptr->subt_size ++;
        }
    }

    //outputs the minimum number of moves before we know where we are
    int query(vector<int>& a) {
        TrieNode* ptr = &head;
        int ans = 0;
        for(int i = 0; i < a.size(); i++){
            int ch = a[i];
            if(ptr->subt_size == 1){
                return ans;
            }
            //if this is the last one, and the size of the last one is just 1
            //we can stop after going past the second to last one
            if(ptr->c.rbegin() -> first == ch && ptr->c.begin() -> first != ch) {
                auto c_ptr = ptr->c.end();
                c_ptr --;
                c_ptr --;
                TrieNode* next = ptr->c[ch];
                if(next->subt_size == 1) {
                    return c_ptr -> first;
                }
            }
            //we need to traverse to the next node
            ptr = ptr->c[ch];
            ans = ch;
        }
        return ans;
    }
};

int dist(int dy, int dx) {
    dy *= -1;
    //cerr << "dx : " << dx << " dy : " << dy << endl;
    if(dx <= 0 && dx + dy <= 0 && dx - dy <= 0) {
        int startnum = ((-dx) * 2+ 1) * ((-dx) * 2 + 1) + dx * 2;
        int diff = dy-dx;
        return startnum + diff;
    }
    if(dy > 0 && dy > abs(dx)) {
        int startnum = (dy * 2) * (dy * 2) + dy * -4 + 2;
        int diff = dy + dx - 1;
        return startnum + diff;
    }
    if(dx > 0 && dy - dx <= 0 && dy + dx > 0) {
        int startnum = (dx * 2) * (dx * 2) - dx * 2 + 1;
        int diff = dx - dy;
        return startnum + diff;
    }
    if(dy < 0 && dx - dy > 0 && dx + dy <= 0) {
        int startnum = ((-dy) * 2) * ((-dy * 2)) + 1;
        int diff = -dx - dy;
        return startnum + diff;
    }
    cerr << "Joshua is bad at math\n";
    return -1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n;
    cin >> m >> n;
    vector<string> g(n);
    for(int i = 0; i < n; i++){
        cin >> g[i];
    }
    vector<pair<int, int>> x_loc(0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(g[i][j] == 'X') {
                x_loc.push_back({i, j});
            }
        }
    }
    Trie trie;
    vector<vector<int>> dists(0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            vector<int> a(0);
            for(int k = 0; k < x_loc.size(); k++){
                int dst = dist(x_loc[k].first - i, x_loc[k].second - j) - 1;
                //cout << "DST : " << dst << "\n";
                a.push_back(dst);
            }
            sort(a.begin(), a.end());
            // for(int k = 0; k < a.size(); k++){
            //     cout << a[k] << " ";
            // }
            // cout << "\n";
            dists.push_back(a);
            trie.insert(a);
        }
    }
    int max_steps = -1;
    vector<pair<int, int>> max_coords(0);
    ld step_sum = 0;
    for(int i = 0; i < dists.size(); i++){
        // for(int j = 0; j < dists[i].size(); j++){
        //     cout << dists[i][j] << " ";
        // }
        // cout << "\n";
        int steps = trie.query(dists[i]);
        //cout << "STEPS : " << steps << "\n";
        // cout << steps << " ";
        // if(i % m == m - 1){
        //     cout << "\n";
        // }
        if(steps > max_steps) {
            max_coords.clear();
            max_steps = steps;
        }
        if(steps == max_steps) {
            max_coords.push_back({n - (i / m), (i % m) + 1});
        }
        step_sum += steps;
    }
    sort(max_coords.begin(), max_coords.end());
    step_sum /= (ld) (n * m);
    cout << fixed << setprecision(10) << step_sum << "\n";
    cout << max_steps << "\n";
    for(int i = 0; i < max_coords.size(); i++){
        cout << "(" << max_coords[i].second << "," << max_coords[i].first << ") ";
    }
    cout << "\n";
    
    return 0;
}
