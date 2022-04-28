#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 61E

//first, compress the strengths of the soldiers into a range from 0 - (n - 1)

//use two segment trees. One to keep track of occurrences of numbers, 
//and one to keep track of for each person, how many people they are greater than.

//when you reach the ith person with strength 'a', update the 'a'th position in the first tree to be 1, 
//and update the 'a'th position in the second tree to be equal to the range sum of first tree from
//(a + 1) - (n - 1). this represents how many people there are in the prefix that have id greater than 'a'. 

//next, just update ans with range sum of second tree from (a + 1) - (n - 1). As the second tree represents
//the number of pairs ending at each number, taking the range sum will make it represent the number of triples ending at
//each number. 

vector<ll> tree(1e6 * 2);
vector<ll> tree2(1e6 * 2);

void modify(vector<ll>& t, int i, ll val, int n){
    i += n;
    t[i] = val;
    for(; i > 1; i /= 2){
        t[i / 2] = t[i] + t[i + (i % 2 == 0? 1 : -1)];
    }
}

ll query(vector<ll>& t, int l, int r, int n){
    ll ans = 0;
    for(l += n, r += n; l < r; l /= 2, r /= 2){
        if(l % 2 == 1) {ans += t[l++];}
        if(r % 2 == 1) {ans += t[--r];}
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<int, int>> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i].first;
        nums[i].second = i;
    }
    sort(nums.begin(), nums.end(), [] (pair<int, int>& a, pair<int, int>& b) {return a.first < b.first;});
    for(int i = 0; i < n; i++){
        nums[i].first = i;
    }
    sort(nums.begin(), nums.end(), [] (pair<int, int>& a, pair<int, int>& b) {return a.second < b.second;});
    ll ans = 0;
    for(int i = 0; i < n; i++){
        int str = nums[i].first;
        ll s1 = query(tree, str + 1, n, n);
        ll s2 = query(tree2, str + 1, n, n);
        modify(tree, str, 1, n);
        modify(tree2, str, s1, n);
        ans += s2;
    }
    cout << ans << endl;
    
    return 0;
}
