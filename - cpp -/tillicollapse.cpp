#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 786C

struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex* build(vector<int>& a, int tl, int tr) {
    if (tl == tr)
        return new Vertex(a[tl]);
    int tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm+1, tr));
}

int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

int kth_one(Vertex* v, int tl, int tr, int l, int r, int k){
    //cout << "START SEARCH" << endl;
    int pfxSum = get_sum(v, tl, tr, 0, l - 1);
    l = tl;
    r = tr;
    k += pfxSum;
    while(l != r){
        int mid = (l + r) / 2;
        //cout << l << " " << r << " " << mid << endl;
        if(v -> l -> sum >= k){
            v = v -> l;
            r = mid;
        }
        else{
            k -= v -> l -> sum;
            v = v -> r;
            l = mid + 1;
        }
        //cout << "BASE" << endl;
    }
    return r;
}

Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new Vertex(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos, new_val));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    vector<int> b(n);
    map<int, int> m;
    vector<int> a(n);
    for(int i = n - 1; i >= 0; i--){
        if(m.find(nums[i]) != m.end()){
            b[i] = m.find(nums[i]) -> second;
            m.find(nums[i]) -> second = i;
        }
        else{
            b[i] = 1e9;
            m.insert({nums[i], i});
        }
    }
    set<int> s;
    for(int i = 0; i < n; i++){
        if(s.find(nums[i]) == s.end()){
            a[i] = 1;
            s.insert(nums[i]);
        }
    }
    vector<Vertex*> v(0);
    v.push_back(build(a, 0, n - 1));
    for(int i = 1; i < n; i++){
        if(b[i - 1] != 1e9){
            v.push_back(update(v[i - 1], 0, n - 1, b[i - 1], 1));
        }
        else{
            v.push_back(v[i - 1]);
        }   
    }
    for(int k = 1; k <= n; k++){
        int ans = 0;
        int left = 0;
        //cout << "START K: " << k << endl;
        while(true){
            ans ++;
            int sum = get_sum(v[left], 0, n - 1, left, n - 1);
            //cout << "LEFT: " << left << " " << sum << endl;
            if(sum <= k){
                break;
            }
            int index = kth_one(v[left], 0, n - 1, left, n - 1, k + 1);
            //cout << "FOUND: " << index << endl;
            left = index;
            if(left == n){
                break;
            }
        }
        cout << ans << " ";
    }
    cout << endl;
    
    return 0;
}