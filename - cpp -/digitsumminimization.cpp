#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC130C

//note that the digit sum will never go up; it will only stay the same or go down. 
//when it does go down, it means that a carry has happened, so you want to maximize carrys. 

//we can choose the least significant digits to add up to some value >= 10, then we want to maximize the number
//of '9 carrys' that come afterwards. We can find the maximum amount using binary search. 

pair<vector<int>, vector<int>> gen_ans(vector<int> a_dig, vector<int> b_dig, int ten_a, int ten_b, int nr_carry) {
    vector<int> a_ans(0);
    vector<int> b_ans(0);
    a_dig[ten_a] --;
    b_dig[ten_b] --;
    int a_ptr = 9;
    int b_ptr = 9;
    for(int i = 0; i < nr_carry; i++){
        while(a_ptr >= 0 && a_dig[a_ptr] == 0){
            a_ptr --;
        }
        while(b_ptr >= 0 && b_dig[b_ptr] == 0){
            b_ptr --;
        }
        if(a_ptr != -1){
            a_dig[a_ptr] --;
            a_ans.push_back(a_ptr);
        }
        if(b_ptr != -1){
            b_dig[b_ptr] --;
            b_ans.push_back(b_ptr);
        }
    }
    reverse(b_ans.begin(), b_ans.end());
    a_ans.push_back(ten_a);
    b_ans.push_back(ten_b);
    reverse(a_ans.begin(), a_ans.end());
    reverse(b_ans.begin(), b_ans.end());
    for(int i = 0; i < 10; i++){
        while(a_dig[i] != 0){
            a_dig[i] --;
            a_ans.push_back(i);
        }
        while(b_dig[i] != 0){
            b_dig[i] --;
            b_ans.push_back(i);
        }
    }
    reverse(a_ans.begin(), a_ans.end());
    reverse(b_ans.begin(), b_ans.end());
    //cout << "TEN : " << ten_a << " " << ten_b << "\n";
    return {a_ans, b_ans};
}

bool is_valid(vector<int> a_dig, vector<int> b_dig, int val) {
    vector<int> a(val, 0);
    vector<int> b(val, 0);
    int a_ptr = 9;
    int b_ptr = 9;
    for(int i = 0; i < val; i++){
        while(a_ptr >= 1 && a_dig[a_ptr] == 0){
            a_ptr --;
        }
        while(b_ptr >= 1 && b_dig[b_ptr] == 0){
            b_ptr --;
        }
        if(a_ptr == 0 && b_ptr == 0) {
            return false;
        }
        a_dig[a_ptr] --;
        b_dig[b_ptr] --;
        a[i] = a_ptr;
        b[i] = b_ptr;
    }
    reverse(b.begin(), b.end());
    for(int i = 0; i < val; i++){
        if(a[i] + b[i] < 9) {
            return false;
        }
    }
    return true;
}

int solve(int ten_a, int ten_b, vector<int> a_dig, vector<int> b_dig) {
    if(ten_a + ten_b < 10) {
        return 0;
    }
    if(a_dig[ten_a] == 0 || b_dig[ten_b] == 0){
        return 0;
    }
    a_dig[ten_a] --;
    b_dig[ten_b] --;
    int low = 0;
    int high = 1e6;
    int ans = low;
    while(low <= high) {
        int mid = low + (high - low) / 2;
        if(is_valid(a_dig, b_dig, mid)) {
            ans = max(ans, mid);
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s_a, s_b;
    cin >> s_a >> s_b;
    bool swap_ans = false;
    if(s_a.size() < s_b.size()) {
        swap_ans = true;
        swap(s_a, s_b);
    }
    vector<int> a_dig(10, 0);
    vector<int> b_dig(10, 0);
    for(int i = 0; i < s_a.size(); i++){
        a_dig[s_a[i] - '0'] ++;
    }
    for(int i = 0; i < s_b.size(); i++){
        b_dig[s_b[i] - '0'] ++;
    }
    int ten_a = -1;
    int ten_b = -1;
    int max_carry = 0;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            int next_carry = solve(i, j, a_dig, b_dig);
            if(next_carry > max_carry) {
                ten_a = i;
                ten_b = j;
                max_carry = next_carry;
            }
        }
    }
    if(max_carry == 0){
        if(swap_ans) {
            swap(s_a, s_b);
        }
        cout << s_a << "\n" << s_b << "\n";
        return 0;
    }
    //cout << "MAX CARRY : " << max_carry << "\n";
    pair<vector<int>, vector<int>> ans = gen_ans(a_dig, b_dig, ten_a, ten_b, max_carry);
    if(swap_ans) {
        swap(ans.first, ans.second);
    }
    for(int i = 0; i < ans.first.size(); i++){
        cout << ans.first[i];
    }
    cout << "\n";
    for(int i = 0; i < ans.second.size(); i++){
        cout << ans.second[i];
    }
    cout << "\n";
    
    return 0;
}
