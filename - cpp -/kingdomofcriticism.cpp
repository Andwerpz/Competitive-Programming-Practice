#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1725K

//we can handle each query in amortized O(log(n)) time. 

//we'll keep a map from height to the set of buildings that are that height. Handling type 1 operations are pretty
//easy, we'll just move the corresponding entry from the original height to w. 

//type 3 queries are slightly harder, but easy as well. We just merge all sets in range [l, r] to either l - 1 or
//r + 1, depending on which side they are on. Note that the complexity this operation is actually amortized O(log(n)), 
//as it requires one operation to 'unmerge' some building from a set.

//now for type 2 queries, we need to know which set some building k is in. To handle these, we can maintain
//a pointer for each building to the set that contains them. 

map<int, pair<set<int>, int>*> m;
vector<pair<set<int>, int>*> a;

void rm_mp(int k) {
    int height = a[k]->second;
    m[height]->first.erase(k);
    a[k] = nullptr;
}

void ins_mp(int k, int h) {
    if(m.find(h) == m.end()) {
        m[h] = new pair<set<int>, int>(set<int>(), h);
    }
    m[h]->first.insert(k);
    a[k] = m[h];
}

//merge h0 into h1
void merge_gp(int h0, int h1) {
    if(!m.count(h0)) {
        m[h0] = new pair<set<int>, int>(set<int>(), h0);
    }
    if(!m.count(h1)) {
        m[h1] = new pair<set<int>, int>(set<int>(), h1);
    }
    int fh = h1;
    pair<set<int>, int>* p0 = m[h0];
    pair<set<int>, int>* p1 = m[h1];
    m.erase(h0);
    m.erase(h1);
    if(p1->first.size() < p0->first.size()) {
        swap(p0, p1);
    }
    for(auto i = p0->first.begin(); i != p0->first.end(); i++){
        p1->first.insert(*i);
        a[*i] = p1;
    }
    p1->second = fh;
    m[fh] = p1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    a = vector<pair<set<int>, int>*>(n, nullptr);
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        ins_mp(i, next);
    }
    int q;
    cin >> q;
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int k, w;
            cin >> k >> w;
            k --;
            rm_mp(k);
            ins_mp(k, w);
        }
        else if(type == 2){
            int k;
            cin >> k;
            k --;
            cout << a[k]->second << "\n";
        }
        else if(type == 3){
            int l, r;
            cin >> l >> r;
            int mid = (l + r) / 2;
            while(true) {
                auto ptr = m.lower_bound(l);
                if(ptr == m.end() || ptr->first > r) {
                    break;
                }
                int h = ptr->first;
                if(h <= mid) {
                    merge_gp(h, l - 1);
                }
                else {
                    merge_gp(h, r + 1);
                }
            }
        }
    }
    
    return 0;
}