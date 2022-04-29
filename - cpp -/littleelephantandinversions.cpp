#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 220E

//we can do a two pointer algorithm to solve this problem. 

//for each i, what is the minimum j that is required to get less than k inversions. 

//if we increase j, then the number of inversions will always go down. Increasing i will always make 
//the number of inversions go up. 

//To calculate the transitions, we can make use of 2 seg trees, 1 for the left side and one for the right side. 
//these seg trees will record the number of occurrences for each number. Since a_i can be up to 10^9, we need to 
//condense the values into a smaller range. Since there are only 10^5 values in total, we can condense it into a range
//from 0 - 10^5.

//when incrementing i, you add to inv, the current number of inversions, leftTree.sum(a_i + 1, inf) + rightTree.sum(0, a_i).
//when incrementing j, you subtract from inv, leftTree.sum(a_i + 1, inf) + rightTree.sum(0, a_i).

//for each i, you add to ans n - j, since for that i, j can be any value that is higher or equal to the cur j. 

int n;
int tSize = 1e5;
vector<int> tl(1e5 * 2 + 100);
vector<int> tr(1e5 * 2 + 100);

void increment(int i, int inc, vector<int>& t){
    i += tSize;
    t[i] += inc;
    for(i /= 2; i > 0; i /= 2){
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

int query(int l, int r, vector<int>& t){
    int ans = 0;
    for(l += tSize, r += tSize; l < r; l /= 2, r /= 2){
        if(l % 2 == 1){ans += t[l++];}
        if(r % 2 == 1){ans += t[--r];}
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll k;
    cin >> n >> k;
    vector<pair<int, int>> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i].first;
        nums[i].second = i;
    }
    //condense the numbers into a range from 0 - 1e5
    sort(nums.begin(), nums.end(), [] (pair<int, int>& a, pair<int, int>& b) {return a.first < b.first;});
    int ptr = 0;
    for(int i = 0; i < n; i++){
        int temp = nums[i].first;
        nums[i].first = ptr;
        if(i != n - 1 && temp != nums[i + 1].first){
            ptr ++;
        }
    }
    sort(nums.begin(), nums.end(), [] (pair<int, int>& a, pair<int, int>& b) {return a.second < b.second;});
    //for each i, what is the minimum j that we require
    ll ans = 0;
    ll curInv = 0;
    int j = 0;
    for(int i = 0; i < n; i++){
        increment(nums[i].first, 1, tr);
        curInv += query(nums[i].first + 1, tSize, tr);
    }
    for(int i = 0; i < n - 1; i++){
        if(j == i){
            increment(nums[i].first, 1, tl);
            increment(nums[i].first, -1, tr);
            j++;
        }
        else{
            increment(nums[i].first, 1, tl);
            curInv += query(nums[i].first + 1, tSize, tl) + query(0, nums[i].first, tr);
        }
        while(j != n && curInv > k){
            curInv -= query(nums[j].first + 1, tSize, tl) + query(0, nums[j].first, tr);
            increment(nums[j].first, -1, tr);
            j++;
        }
        if(curInv <= k){
           ans += n - j; 
        }
    }
    cout << ans << endl;
    
    return 0;
}
