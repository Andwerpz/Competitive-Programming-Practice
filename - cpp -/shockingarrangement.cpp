#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1798D

//we want to make the maximum subarray sum smaller than the range of the array, or the difference between the highest
//and lowest number. 

//notice that if all of the prefix sums are within the range of the array, then the maximum subarray sum will be good. 

//so we just greedily choose positive numbers when the prefix sum is negative, and vice versa. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> pos(0);
        vector<int> neg(0);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(next < 0){
                neg.push_back(next);
            }
            else if(next > 0) {
                pos.push_back(next);
            }
        }
        if(pos.size() == 0){
            cout << "No\n";
            continue;
        }
        cout << "Yes\n";
        int sum = 0;
        int pptr = 0;
        int nptr = 0;
        for(int i = 0; i < n; i++){
            int next = 0;
            if(sum < 0) {
                next = pos[pptr++];
            }
            else if(sum > 0){
                next = neg[nptr++];
            }
            else if(pptr != pos.size()){
                next = pos[pptr++];
            }
            cout << next << " ";
            sum += next;
        }
        cout << "\n";
    }
    
    return 0;
}
