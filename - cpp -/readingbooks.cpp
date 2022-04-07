
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1631

//if there is a book that takes longer to read than all other books combined, then the time taken is 
//going to be double the length of that book.

//else, the ans is the sum of all lengths of books.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> nums(n);
    ll sum = 0;
    ll max = 0;
    for(int i = 0; i < n; i++){
        cin >> nums[i];
        max = std::max(max, (ll) nums[i]);
        sum += nums[i];
    }
    cout << std::max(max * 2, sum) << endl;
    
    return 0;
}
