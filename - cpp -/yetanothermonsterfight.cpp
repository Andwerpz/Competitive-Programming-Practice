#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1901D

//when we consider the worst case, we can analyze it independently for each element in the array. 

//let's say that we start at index i. The worst case for some index j, where j < i is the case
//where all the elements greater than i are struck first, then after that all the elements less than
//i are struck. Similar reasoning for j > i. 

//then, for every starting index, we just need to find the 'worst' element for that starting index, 
//and that will determine the required starting power. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> l(n), r(n);
    l[0] = a[0];
    for(int i = 1; i < n; i++){
        l[i] = max(a[i], l[i - 1] + 1);
    }
    r[n - 1] = a[n - 1];
    for(int i = n - 2; i >= 0; i--){
        r[i] = max(a[i], r[i + 1] + 1);
    }
    int ans = min(r[0], l[n - 1]);
    for(int i = 1; i < n - 1; i++){
        int l_ans = max({a[i], l[i - 1] + 1, r[i + 1] + 1 + i});
        int r_ans = max({a[i], r[i + 1] + 1, l[i - 1] + 1 + (n - (i + 1))});
        ans = min(ans, max(l_ans, r_ans));
    }
    cout << ans << "\n";
    
    return 0;
}
