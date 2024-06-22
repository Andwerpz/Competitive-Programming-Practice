#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//AtCoder - ARC179C

//it turns out that the only safe numbers to add are the minimum and maximum. 

//so, first sort the array, and add them. Then, find where to put the newly generated number via binary search. 
//rinse and repeat until the size of the array is 1. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        a[i] = i + 1;
    }
    sort(a.begin(), a.end(), [](int a, int b) -> bool {
        cout << "? " << a << " " << b << endl;
        int ans;
        cin >> ans;
        return ans;
    });
    while(a.size() > 2){
        cout << "+ " << a[0] << " " << a[a.size() - 1] << endl;
        int p;
        cin >> p;
        a.erase(a.begin());
        a.erase(a.begin() + (a.size() - 1));
        int low = 0;
        int high = a.size() - 1;
        int ind = a.size();
        while(low <= high) {
            int mid = low + (high - low) / 2;
            cout << "? " << p << " " << a[mid] << endl;
            int ans;
            cin >> ans;
            if(ans) {
                ind = min(ind, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
        }
        a.insert(a.begin() + ind, p);
    }
    cout << "+ " << a[0] << " " << a[1] << endl;
    cout << "!" << endl;
    
    return 0;
}