
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1352C

//figuring out the kth number in the sequence is hard, but given a number, a, you can figure out it's position in the sequence relatively easily. 

//just subtract from a, (a / n), rounded down. 

//one edge case when binary searching, if you land on a number b, that is divisible by n, then it will have the same position as b - 1, when you do b - (b / k). 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        ll n, k;
        cin >> k >> n;
        ll ans = 0;
        ll low = 1;
        ll high = 10000000000;
        ll mid = low + (high - low) / 2;
        while(low <= high){
            ll amtDivisible = mid / k;
            if(mid - amtDivisible == n){
                if(mid % k == 0){
                    mid --;
                }
                cout << mid << endl;
                break;
            }
            else if(mid - amtDivisible > n){
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
    }

    return 0;
}



