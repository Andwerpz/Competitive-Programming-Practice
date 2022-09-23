#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Atcoder ABC215F

//oh my god... this one took way too many attempts

//if you sort by x value, then for each point, you can binary search for the maximum distance to any other point. 

//my solution involves a range max and min segtree for the y values. To check if a distance d is possible, first find
//the left and right bounds, where a_x[i] - a_x[left] < d and a_x[right] - a_x[i] < d. The idea is to then find the 
//largest difference y value outside of these bounds. If the largest difference is greater than or equal to d, then 
//d is valid. 

const int N = 5e5;
int tMin[N * 2];
int tMax[N * 2];

void modifyMin(int index, int value, int n){
    index += n;
    tMin[index] = value;
    for(index /= 2; index > 0; index /= 2){
        tMin[index] = std::min(tMin[index * 2], tMin[index * 2 + 1]);
    }
}

void modifyMax(int index, int value, int n){
    index += n;
    tMax[index] = value;
    for(index /= 2; index > 0; index /= 2){
        tMax[index] = std::max(tMax[index * 2], tMax[index * 2 + 1]);
    }
}

int queryMin(int l, int r, int n) {   //min over range [l, r)
    int res = 2e9;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res = std::min(res, tMin[l]);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res = std::min(res, tMin[r]);
        }
    }
    return res;
}

int queryMax(int l, int r, int n) {   //max over range [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res = std::max(res, tMax[l]);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res = std::max(res, tMax[r]);
        }
    }
    return res;
}

bool isValid(vector<pair<int, int>>& a, int d, int index){
    int lBound = index;
    int rBound = index;
    int low = 0;
    int high = index;
    int mid = low + (high - low) / 2;
    while(low <= high){
        if(a[index].first - a[mid].first < d){
            lBound = min(lBound, mid);
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    low = index;
    high = a.size() - 1;
    mid = low + (high - low) / 2;
    while(low <= high){
        if(a[mid].first - a[index].first < d){
            rBound = max(rBound, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
        mid = low + (high - low) / 2;
    }
    int maxYDiff = max(a[index].second - queryMin(0, lBound, a.size()), queryMax(rBound + 1, a.size(), a.size()) - a[index].second);
    int maxYDiff2 = max(queryMax(0, lBound, a.size()) - a[index].second, a[index].second - queryMin(rBound + 1, a.size(), a.size()));
    return max(maxYDiff, maxYDiff2) >= d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end(), [](pair<int, int> a, pair<int, int> b) {return a.first == b.first? a.second < b.second : a.first < b.first;});
    for(int i = 0; i < n; i++){
        modifyMin(i, a[i].second, n);
        modifyMax(i, a[i].second, n);
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int low = 0;
        int high = 2e9;
        int mid = low + (high - low) / 2;
        while(low <= high){
            if(isValid(a, mid, i)){
                ans = std::max(ans, mid);
                low = mid + 1;
            }   
            else {
                high = mid - 1;
            }
            mid = low + (high - low) / 2;
        }
    }
    cout << ans << "\n";
    
    return 0;
}
