#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 06 G

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        int sum = 0;
        int m = 0;
        int mInd = -1;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            sum += a[i];
            if(a[i] > m){
                m = a[i];
                mInd = i + 1;
            }
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        if(a[0] == a[1]){
            cout << "no winner\n";
            continue;
        }
        else if(sum - a[0] >= a[0]){
            cout << "minority winner " << mInd << "\n";
            continue;
        }
        else {
            cout << "majority winner " << mInd << "\n";
            continue;
        }
    }
    
    return 0;
}
