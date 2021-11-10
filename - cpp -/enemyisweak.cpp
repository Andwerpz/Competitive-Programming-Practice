
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 61E

//use two segment trees. One to keep track of occurrences of numbers, and one to keep track of for each person, how many people they are greater than.

using namespace std;

void insert(vector<vector<ll>> &tree, int index, ll val){
    for(int i = 0; i < tree.size(); i++){
        tree[i][index] += val;
        //cout << tree[i][index] << " " << i << " " << index << endl;
        index /= 2;
    }
}

ll getSum(vector<vector<ll>> &tree, int l, int r){
    ll ans = 0;
    for(int i = l; i <= r; i += 0){
        int index = i;
        int increment = 1;
        int layer = 0;
        while(true){
            int temp = index;
            index /= 2;
            increment *= 2;
            layer ++;
            int low = index * increment;
            int high = low + increment;
            if(low < l || high > r){
                index = temp;
                increment /= 2;
                layer --;
                break;
            }
        }
        i += increment;
        ans += tree[layer][index];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int treeLayers = (int) ceil((double)log(n) / (double)log(2)) + 1;
    int pointer = pow(2, treeLayers);
    vector<vector<ll>> tree(treeLayers);
    vector<vector<ll>> tree2(treeLayers);
    //cout << treeLayers << endl;
    vector<pair<ll, ll>> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i].first;
        nums[i].second = i;
    }
    pointer /= 2;
    for(int i = 0; i < treeLayers; i++){
        //cout << pointer << " ";
        tree[i] = vector<ll>(pointer);
        tree2[i] = vector<ll>(pointer);
        pointer /= 2;
    }
    //cout << endl;
    sort(nums.begin(), nums.end(), [&](pair<ll, ll> a, pair<ll, ll> b) -> bool {return a.first < b.first;});
    for(int i = 0; i < n; i++){
        nums[i].first = i;
    }
    sort(nums.begin(), nums.end(), [&](pair<ll, ll> a, pair<ll, ll> b) -> bool {return a.second < b.second;});
    // for(int i = 0; i < nums.size(); i++){
    //     //cout << nums[i].first << " " << nums[i].second << endl;
    // }
    //cout << endl;
    // for(int j = 0; j < tree.size(); j++){
    //     for(int k = 0; k < tree[j].size(); k++){
    //         cout << tree[j][k] << " ";
    //     }
    //     cout << endl;
    // }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ll next = nums[i].first;
        ll firstSum = getSum(tree, next, n - 1);
        ans += getSum(tree2, next, n - 1);
        insert(tree, next, 1);
        insert(tree2, next, firstSum);
    }
    cout << ans << endl;

    return 0;
}



