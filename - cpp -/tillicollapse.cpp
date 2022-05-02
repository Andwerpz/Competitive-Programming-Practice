#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 786C

//supposed to use a persistent seg tree instead of a mergesort tree to get rid of extra log factor.

vector<vector<int>> t(1e5 * 2, vector<int>(0));
int n;

void combine(const vector<int>& a, const vector<int>& b, vector<int>& dest){
    int pa = 0;
    int pb = 0;
    dest = vector<int>(a.size() + b.size());
    int c = 0;
    while(pa != a.size() || pb != b.size()){
        if(pb == b.size() || (pa != a.size() && a[pa] <= b[pb])){
            dest[c] = a[pa];
            pa ++;
        }
        else{
            dest[c] = b[pb];
            pb ++;
        }
        c ++;
    }
}

int amtGEQ(vector<int>& a, int x){ 
    int low = 0;
    int high = a.size() - 1;
    int mid = low + (high - low) / 2;
    int ans = 0;
    while(low <= high){
        if(a[mid] >= x){
            ans = max(ans, (int) (a.size() - mid));
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    return ans;
}

int query(int l, int r, int x){
    int ans = 0;
    for(l += n, r += n; l < r; l /= 2, r /= 2){
        if(l % 2 == 1) {ans += amtGEQ(t[l++], x);}
        if(r % 2 == 1) {ans += amtGEQ(t[--r], x);}
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    map<int, int> m;
    for(int i = n - 1; i >= 0; i--){
        if(m.find(nums[i]) == m.end()){
            t[i + n].push_back(1e9);
            m.insert({nums[i], i});
        }
        else{
            t[i + n].push_back(m.find(nums[i]) -> second);
            m.find(nums[i]) -> second = i;
        }
    }
    for(int i = n - 1; i > 0; i--){
        combine(t[i * 2], t[i * 2 + 1], t[i]);
    }
    //cout << "Q: " << query(1, 4, 4) << endl;
    for(int i = 1; i <= n; i++){
        //cout << "I : " << i << endl;
        int ans = 0;
        int left = 0;
        while(true){
            //cout << "LEFT: " << left << endl;
            ans ++;
            int low = left;
            int high = n; 
            int mid = low + (high - low) / 2;
            int index = low;
            while(low <= high){
                if(query(left, mid, mid) <= i){
                    index = max(index, mid);
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
                mid = low + (high - low) / 2;
            }
            left = index;
            if(left >= n){
                break;
            }
        }
        cout << ans << " ";
    }
    cout << endl;
    
    return 0;
}
