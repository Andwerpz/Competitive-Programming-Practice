#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1837C

//first, figure out how to compute the minimum amount of arbitrary subarray reversals to sort an arbitrary binary string. 
//consider that we are trying to move all of the '1's to the right side. 
//then for each continuous subarray of '1's, we want to make it 'touch' the next subarray of '1's directly to it's right. 
//thus the answer is simply the number of segments made of '1's, excluding the segment of '1's touching the right edge. 

//for example, the binary string '1101011' would take 2 reversals. 

//so, this means that we want to minimize the amount of segments of '1's. To do this, we can just go from right to left, and make 
//s[i] = s[i + 1]. 

//if s[n - 1] == '?', then we can just set it to '1'. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int n = s.size();
        if(s[n - 1] == '?') {
            s[n - 1] = '1';
        }
        for(int i = n - 2; i >= 0; i--){
            if(s[i] == '?') {
                s[i] = s[i + 1];
            }
        }
        cout << s << "\n";
    }
    
    return 0;
}
