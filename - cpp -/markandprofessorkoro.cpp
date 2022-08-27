#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1705E

//lazy prop seg tree and naive binary search is too slow. Try to integrate bsearch into
//the tree ds to make it faster. 

const int N = 2e5 + 100;  //+100 since there might be duplicate a[i]
int t[2 * N];
int h = sizeof(int) * 8 - __builtin_clz(N); //height of tree
int d[N];   //lazy tree
int upd[N]; //to support assigning 0

void calc(int p, int k) {   //accounting for length of segment 
    if (!upd[p]) {
        t[p] = t[p * 2] + t[p * 2 + 1];
    }
    else {
        t[p] = d[p] * k;
    }
}

void apply(int p, int value, int k) {
    t[p] = value * k;
    if (p < N) {
        d[p] = value;
        upd[p] = true;
    }
}

void build(int l, int r) {
    l += N, r += N - 1;
    int k = 2; 
    for (; l > 1; k *= 2) {
        l /= 2, r /= 2;
        for (int i = r; i >= l; i--) {
            calc(i, k);
        }
    }
}

void push(int l, int r) {
    l += N, r += N - 1;
    int s = h, k = 1 << (h - 1);
    for (; s > 0; s--, k /= 2) {
        for (int i = l >> s; i <= r >> s; i++) {
            if (upd[i]) {
                apply(i * 2, d[i], k);
                apply(i * 2 + 1, d[i], k);
                d[i] = 0;
                upd[i] = false;
            }
        }
    }
}

void modify(int l, int r, int value) {
    push(l, l + 1);
    push(r - 1, r);
    int l0 = l, r0 = r, k = 1;
    for (l += N, r += N; l < r; l /= 2, r /= 2, k *= 2) {
        if (l % 2 == 1) apply(l++, value, k);
        if (r % 2 == 1) apply(--r, value, k);
    }
    build(l0, l0 + 1);
    build(r0 - 1, r0);
}

int query(int l, int r) {
    push(l, l + 1);
    push(r - 1, r);
    int res = 0;
    for (l += N, r += N; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) res += t[l++];
        if (r % 2 == 1) res += t[--r];
    }
    return res;
}

void add(int i){    //adds a 1 at position i
    int low = i;
    int high = N;
    int mid = low + (high - low) / 2;
    int ans = low;
    while(low <= high){
        if(query(i, mid) == mid - i){
            ans = max(ans, mid);
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
        mid = low + (high - low) / 2;
    }
    modify(i, ans, 0);
    modify(ans, ans + 1, 1);
}

void sub(int i){    //removes a 1 from position i
    int low = i + 1;
    int high = N;
    int mid = low + (high - low) / 2;
    int ans = high;
    while(low <= high){
        if(query(i, mid) >= 1){
            ans = min(ans, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    modify(ans - 1, ans, 0);
    modify(i, ans - 1, 1);
}

int findMax(){  //find maximum position of 1
    int low = 0;
    int high = N - 1;
    int mid = low + (high - low) / 2;
    int ans = low;
    while(low <= high){
        if(query(mid, N) >= 1){
            ans = max(ans, mid);
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
        mid = low + (high - low) / 2;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        add(a[i]);
    }
    for(int i = 0; i < q; i++){
        int k, l;
        cin >> k >> l;
        sub(a[--k]);
        add(l);
        a[k] = l;
        cout << findMax() << "\n";
    }
    
    return 0;
}
