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

//AtCoder - AGC8D

//Intuitively, I believe there is a greedy solution. Perhaps we can start building the array one element at
//a time while satisfying the most 'urgent' requirement first. Sort the requirements in order of increasing 
//index, and satisfy them in that order while building the array. 

//We can maintain a pointer to the current element in the array, and just greedily append elements to satisfy
//the closest requirement to the right. At any moment, if we fail to satisfy the closest requirement, we can 
//simply say 'No'. 

//One more thing: not only do we have to worry about satisfying requirements, we also have to make sure they
//stay satisfied. Thus, after satisfying all requirements, we'll go back in order and place the remaining 
//elements. All remaining elements must be placed after their corresponding requirement, or else it also
//becomes invalid. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<pii> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i;
        a[i].first --;
    }
    sort(a.begin(), a.end());
    vi ans(n * n, -1);
    for(int i = 0; i < n; i++){
        ans[a[i].first] = a[i].second;
    }
    int ptr = 0;
    bool is_valid = true;
    for(int i = 0; i < n; i++){ //place stuff before required
        for(int j = 0; j < a[i].second; j++){
            while(ans[ptr] != -1) ptr ++;
            if(ptr >= a[i].first) is_valid = false;
            ans[ptr] = a[i].second;
        }
    }
    for(int i = 0; i < n; i++){ //place stuff after required
        for(int j = a[i].second + 1; j < n; j++){
            while(ans[ptr] != -1) ptr ++;
            if(ptr < a[i].first) is_valid = false;
            ans[ptr] = a[i].second;
        }
    }
    if(!is_valid) {
        cout << "No\n";
        return 0;
    }
    cout << "Yes\n";
    for(int x : ans) cout << x + 1 << " ";
    cout << "\n";

    return 0;
}