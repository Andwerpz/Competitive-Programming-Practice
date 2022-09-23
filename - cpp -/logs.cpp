#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problem Set 2C

//if given a maximum length log l, the most efficient way to split the log so that the maximum length segment is less than
//or equal to l in length is to just lop off length l pieces from the end of the log, until you can't anymore. The amount
//of steps taken in the procdure is just floor(a / l), where a is the length of the log.  

//So for a given l, to make all the logs shorter than or equal to l, you just take the sum of moves when you do the above 
//procedure on all the logs. 

//You can binary search across all possible lengths to find the minimal length. 

bool isValid(vector<double>& a, double val, int k) {
    for(double d : a){
        k -= (int) (d / val);
        if(k < 0){
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<double> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    double low = 0;
    double high = 1e9;
    double mid = low + (high - low) / 2;
    while(high - low > 0.0001) {
        if(isValid(a, mid, k)){
            high = mid;
        }
        else {
            low = mid;
        }
        mid = low + (high - low) / 2;
    }
    cout << (int) (low + 1) << "\n";
    
    return 0;
}
