#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 356A

//we can use a segment tree to simulate the tournament.

//in order to do this, we need a segment tree that supports range assignment and single element queries. 

//to do this, we can just make some modifications to a range increment single element query segment tree. 
//since assignment operations aren't commtative, the one thing that we need to save alongside any operation
//is the priority of the assignment. 

//in this case, i made it so lower priority took precedent over higher priority. 

//to simulate it, we iterate over the rounds of the tournament, making range assignments. Since knights beaten
//in earlier rounds don't participate in later rounds, i made it so that earlier rounds
//have lower priority over later rounds. 

vector<pair<int, int>> t(1e6, {1e6, 0});   //priority, val
int n;

int query(int i){
    i += n;
    int ans = t[i].second;
    int priority = t[i].first;
    for(; i > 0; i /= 2) {
        if(t[i].first < priority){
            priority = t[i].first;
            ans = t[i].second;
        }
    }
    return ans;
}

void modify(int l, int r, int val, int priority){
    for(l += n, r += n; l < r; l /= 2, r /= 2){
        if(l % 2 == 1) {
            if(t[l].first > priority){
                t[l].first = priority;
                t[l].second = val;
            }
            l ++;
        }
        if(r % 2 == 1){
            r --;
            if(t[r].first > priority){
                t[r].first = priority;
                t[r].second = val;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        modify(l, x - 1, x, i);
        modify(x, r, x, i);
    }
    for(int i = 0; i < n; i++){
        cout << query(i) << " ";
    }
    cout << endl;
    
    return 0;
}
