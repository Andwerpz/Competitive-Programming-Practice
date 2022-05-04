#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1029D

//since the lengths of the numbers are max 10 digits long, we can save 10 maps, each storing how many of each
//of the possible remainders of all numbers after multiplying them by 10^1, 10^2, ... 10^10. 

//the maps save remainders of the second part of the concatenated number. 

//now, we can how many concatenated numbers we can make using each number as a first number using the maps. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll k;
    cin >> n >> k;
    vector<map<int, int>> m(11);
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        ll rem = nums[i] % k;
        for(int j = 1; j <= 10; j++){
            rem = (rem * 10) % k;
            //cout << "INSERT: " << j << " " << rem << endl;
            if(m[j].find((int) rem) != m[j].end()){
                m[j].find((int) rem) -> second ++;
            }
            else{
                m[j].insert({(int) rem, 1});
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < n; i++){
        int rem = nums[i] % k;
        int length = (int) (log10(nums[i])) + 1;
        int left = (k - rem) % k;
        //cout << nums[i] << " " << length << " " << rem << endl;
        if(m[length].find(left) != m[length].end()){
            ans += m[length].find(left) -> second;
        }
        if(((ll) rem * (ll) pow(10, length)) % k == left){
            //cout << nums[i] << endl;
            ans --;
        }
    }
    cout << ans << endl;
    
    return 0;
}
