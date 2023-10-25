#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//AtCoder - ARC138B

//any 01 sequence generated using the moves provided must have the following form: 
//a binary string of length 'a' of alternating '0' and '1' characters starting with '0', concatenated with 
//an arbitrary binary string of length 'b'. The total number of 'sections' of the second binary string
//must be less than 'a'. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    if(a[0] == 1) {
        cout << "No\n";
        return 0;
    }
    vector<int> nr_seg(n);
    nr_seg[n - 1] = a[n - 1];
    for(int i = n - 2; i >= 0; i--){
        nr_seg[i] = nr_seg[i + 1];
        if(a[i] != a[i + 1]) {
            nr_seg[i] ++;
        }
    }
    bool is_valid = true;
    for(int i = 1; i < n; i++){
        if(a[i] != a[i - 1]) {
            continue;
        }
        int nr_flips = i;
        int nr_req = nr_seg[i];
        if(nr_req > nr_flips) {
            is_valid = false;
        }
        break;
    }
    cout << (is_valid? "Yes\n" : "No\n");
    
    return 0;
}
