#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 06 C

//instead of 'R' and 'B', make 'R' = 1 and 'B' = -1. Then the problem is simply find the subarray with
//the largest absolute value. 

//for each prefix, figure out the minimum and maximum prefixes that it contains. Then, the maximum absolute value subarray that ends
//at index i must begin at the minimum or maximum prefix contained by prefix of length i. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int min = 0;
    int max = 0;
    int ans = 0;
    int sum = 0;
    int minInd = -1;
    int maxInd = -1;
    int l = 0;
    int r = 0;
    for(int i = 0; i < s.size(); i++){
        sum += s[i] == 'R'? 1 : -1;
        if(sum < min) {
            minInd = i;
            min = sum;
        }
        if(sum > max){
            maxInd = i;
            max = sum;
        }
        if(ans < abs(sum - min)) {
            ans = abs(sum - min);
            l = minInd + 1;
            r = i;
        }
        if(ans < abs(sum - max)) {
            ans = abs(sum - max);
            l = maxInd + 1;
            r = i;
        }
    }
    cout << l + 1 << " " << r + 1 << "\n";
    
    return 0;
}
