#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//tr and tl, tells the range of indicies on the original arr
//l and r, where you want to search

//updates, queries, are inclusive.

struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex* build(int a[], int tl, int tr) {
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
    
    int a[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    vector<Vertex*> v(0);
    v.push_back(build(a, 0, 7));
    cout << get_sum(v[0], 0, 7, 0, 7) << endl;
    cout << get_sum(v[0], 0, 7, 0, 0) << endl;
    v.push_back(update(v[0], 0, 7, 0, 100));
    cout << get_sum(v[1], 0, 7, 0, 0) << endl;
    
    return 0;
}
