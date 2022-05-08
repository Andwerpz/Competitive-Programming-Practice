#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1678C

//for each i, you can calculate how many numbers before and after it are less than it. 
//store these two values in a pfx and sfx array. 

//from these arrays, we know that the number of valid positions of a, given c is pfx[c], same for b and d,
//except you use the sfx array. 

//if we iterate through all pairs of b and c, for a given pair, the number of tuples is pfx[c] * sfx[b]. 

//the problem is that a has to come before b, and d has to come after c. We might overcount if we use
//the above method. To fix this, we can subtract, before multiplying, the amount of elements between b and c
//that are less than nums[b] and nums[c] respectively. 

//to do this, we can keep a segment tree to query. Since the numbers are a permutation, we can just store 
//5000 positions, and do range queries from 0 - nums[b] or 0 - nums[c] and subtract the sum from their respective
//values before multiplying. 

vector<int> t(10002);
int tSize = 5001;

void reset(){
    for(int i = 0; i < t.size(); i++){
        t[i] = 0;
    }
}

int query(int l, int r) {
    int ans = 0;
    for(l += tSize, r += tSize; l < r; l /= 2, r /= 2){
        if(l % 2 == 1) {ans += t[l++];}
        if(r % 2 == 1) {ans += t[--r];}
    }
    return ans;
}

void modify(int i, int val){
    i += tSize;
    for (t[i] = val; i > 1; i /= 2) {
        t[i / 2] = t[i] + t[i + (i % 2 == 0? 1 : -1)];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> nums(n);
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        vector<int> pfxLess(n);
        vector<int> sfxLess(n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if(nums[j] < nums[i]){
                    pfxLess[i] ++;
                }
            }
            for(int j = i + 1; j < n; j++){
                if(nums[j] < nums[i]){
                    sfxLess[i] ++;
                }
            }
        }
        ll ans = 0;
        for(int b = 0; b < n; b++){
            int bSub = 0;
            reset();
            modify(nums[b], 1);
            for(int c = b + 1; c < n; c++){
                modify(nums[c], 1);
                if(nums[c] < nums[b]){
                    bSub ++;
                }
                ans += (pfxLess[c] - query(0, nums[c])) * (sfxLess[b] - bSub);
            }
        }
        cout << ans << endl;
    }
    
    return 0;
}
