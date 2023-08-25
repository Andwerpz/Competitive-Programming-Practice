#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1789D

//nice ad-hoc problem. 

//denote lowest_bit(a) as the leftmost (most significant) bit in a, and highest_bit(a) as the rightmost (least significant) bit in a. 

//first, it is impossible to convert a into b if only a or only b has all 0s. 

//next, if both a and b are all 0s, then the answer is trivially 0. 

//otherwise, the first step is to make sure that highest_bit(a) >= lowest_bit(b). 
//we can do this in one operation. 

//next, we want to erase all '1' bits in a that are to the left of lowest_bit(b). We can use highest_bit(a) as a 'brush'
//to erase all of these bits. 

//next, if lowest_bit(a) > lowest_bit(b), then we want to make it so that lowest_bit(a) = lowest_bit(b). 

//finally, we want to set all the remaining bits to the left of lowest_bit(a) equal to their corresponding bits in b. 
//once again, we can use lowest_bit(a) as a 'brush' to do so. 

int lowest_bit(vector<bool>& a) {
    for(int i = 0; i < a.size(); i++){
        if(a[i]) {
            return i;
        }
    }
    return a.size();
}

int highest_bit(vector<bool>& a) {
    for(int i = a.size() - 1; i >= 0; i--){
        if(a[i]){
            return i;
        }
    }
    return -1;
}

//shift is the amount of left shift
void apply_op(vector<bool>& a, int shift, vector<int>& ans) {
    ans.push_back(shift);
    vector<bool> b(a.size(), false);
    for(int i = 0; i < a.size(); i++){
        int nind = i - shift;
        if(0 <= nind && nind < a.size()) {
            b[nind] = a[i];
        }
    }
    for(int i = 0; i < a.size(); i++){
        a[i] = a[i] ^ b[i];
    }
    // for(int i = 0; i < a.size(); i++){
    //     cout << a[i];
    // }
    // cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<bool> a(n);
        vector<bool> b(n);
        for(int i = 0; i < n; i++){
            char c;
            cin >> c;
            a[i] = c == '1';
        }
        for(int i = 0; i < n; i++){
            char c;
            cin >> c;
            b[i] = c == '1';
        }
        if((lowest_bit(a) == n) ^ (lowest_bit(b) == n)) {
            cout << "-1\n";
            continue;
        }
        if(lowest_bit(a) == n && lowest_bit(b) == n) {
            cout << "0\n";
            continue;
        }
        vector<int> ans(0);
        if(highest_bit(a) < lowest_bit(b)) {
            //move the highest bit in a to be equal to the lowest bit in b
            apply_op(a, highest_bit(a) - lowest_bit(b), ans);
        }
        //erase all bits in a lower than the lowest bit in b
        for(int i = lowest_bit(b) - 1; i >= 0; i--){
            if(a[i]) {
                apply_op(a, highest_bit(a) - i, ans);
            }
        }
        //make lowest bits equal
        if(lowest_bit(a) != lowest_bit(b)) {
            apply_op(a, lowest_bit(a) - lowest_bit(b), ans);
        }
        //make the rest of the string equal using lowest_bit(a)
        for(int i = lowest_bit(b) + 1; i < n; i++){
            if(a[i] != b[i]) {
                apply_op(a, lowest_bit(a) - i, ans);
            }
        }
        cout << ans.size() << "\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
