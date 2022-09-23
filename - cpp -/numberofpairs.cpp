#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set 2B

//for each number, find out how many pairs you can make with it. 

//to avoid duplicate pairs, you can only make pairs with greater numbers that the one in question. 

//1: sort the array
//for each number a[i]:
//2: find the upper and lower bound of numbers that you can form pairs with a[i]. This can be done with binary search
//3: if the lower bound is less than i + 1, set lower bound to i + 1. This will make it so you don't make any duplicate pairs
//4: ans += upperBound - lowerBound;

int find(vector<int>& a, int l, int r, int val, int ind){
    //maximum value less than r;
    int low = 0;
    int high = a.size() - 1;
    int mid = low + (high - low) / 2;
    int rBound = 0;
    while(low <= high){
        if(val + a[mid] <= r){
            rBound = max(rBound, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
        mid = low + (high - low) / 2;
    }
    int lBound = a.size();
    low = 0;
    high = a.size() - 1;
    mid = low + (high - low) / 2;
    while(low <= high){
        if(val + a[mid] >= l){
            lBound = min(lBound, mid);
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    int ans = rBound - max(ind + 1, lBound) + 1;
    ans = max(ans, 0);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, l, r;
        cin >> n >> l >> r;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        ll ans = 0;
        for(int i = 0; i < n; i++){
            ans += find(a, l, r, a[i], i);
        }
        cout << ans << "\n";
    }
    
    return 0;
}
