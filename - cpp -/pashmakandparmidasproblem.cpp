#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 459D

//my solution is pretty jank. 2979 / 3000 ms

//we can calculate for each i, how many j exist that satisfies the condition in log(n) time

//to do this, we can save 2 seg trees, both supporting range sum and single element modification. 

//one seg tree will store for each i, how many unique numbers have i elements in the array
//other seg tree will store the same info, except each value is multiplied by their respective i. 

//now we iterate through the array, 'a' = f(0, i, arr[i]).

//We can use the first seg tree to calculate the j's that have the amount of numbers greater or equal to 'a'. 
//use the second seg tree to get the sum of j's that have amount of numbers less than 'a'. 

//do this for all i. Before getting the sum, you must update the trees since j > i, and when you increment i,
//you 'lose' numbers from the j side. 

vector<int> tCnt(1e6 * 2 + 100);    //how many unique numbers have i members
vector<int> tScore(1e6 * 2 + 100);  //how many unique numbers have i members times i
int tSize = 1e6 + 1;

ll query(int l, int r, vector<int>& t){
    ll ans = 0;
    for(l += tSize, r += tSize; l < r; l /= 2, r /= 2){
        if(l % 2 == 1){ans += t[l++];}
        if(r % 2 == 1){ans += t[--r];}
    }
    return ans;
}

void increment(int i, int val, vector<int>& t){
    i += tSize;
    t[i] += val;
    for(i /= 2; i > 0; i /= 2){
        t[i] = t[i * 2] + t[i * 2 + 1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> nums(n);
    map<int, int> amt;
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        if(amt.find(nums[i]) == amt.end()){
            amt.insert({nums[i], 1});
        }
        else{
            amt.find(nums[i]) -> second ++;
        }
    }
    for(pair<int, int> i : amt){
        //cout << i.first << " " << i.second << endl;
        increment(i.second, 1, tCnt);
        increment(i.second, i.second, tScore);
        //cout << query(i.second, i.second + 1, tCnt) << " " << tCnt[i.second + tSize] << endl;
    }
    ll ans = 0;
    map<int, int> cAmt;
    for(int i = 0; i < n; i++){
        if(cAmt.find(nums[i]) == cAmt.end()){
            cAmt.insert({nums[i], 1});
        }
        else{
            cAmt.find(nums[i]) -> second ++;
        }
        int curAmt = cAmt.find(nums[i]) -> second;
        int jAmt = amt.find(nums[i]) -> second - curAmt;
        //cout << nums[i] << " : " << curAmt << " " << jAmt << endl;
        //upd trees
        increment(jAmt + 1, -1, tCnt);
        increment(jAmt, 1, tCnt);
        increment(jAmt + 1, -(jAmt + 1), tScore);
        increment(jAmt, jAmt, tScore);
        //calc ans increment
        ans += query(0, curAmt, tScore) + query(curAmt, 1e6, tCnt) * (curAmt - 1);
    }
    cout << ans << endl;

    return 0;
}
