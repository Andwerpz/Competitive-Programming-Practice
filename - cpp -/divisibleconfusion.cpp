
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1604C

//lets go down the array, from i = 1 to i = n. For the first number, the possible i values are 1, so the only possible divisor is 2. 
//given that a[1] % 2 != 0, lets look at the second number. The possible i values of the second number are 1 and 2; we can remove it first,
//or we can remove it after we removed the first number. 

//The possible i values for the third number are 1 - 3, and for the fourth number, 1 - 4. So for each number, we just check whether there is a
//number that it is not divisible by within that range. We can check all the numbers, since usually, numbers do not have too many divisors, and
//the ones that do are much greater than 10^9. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    int counter = 0;
    string output = "";
    while(t-- > 0){
        counter ++;
        int n;
        cin >> n;
        vector<int> nums(n);
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        bool isValid = true;
        for(int i = 0; i < n; i++){
            int next = nums[i];
            for(int j = i + 2; j >= 2; j--){
                if(next % j != 0){
                    break;
                }
                if(j == 2){
                    isValid = false;
                    goto outer;
                }
            }
        }
        outer: ;
        cout << (isValid? "YES\n" : "NO\n");
    }

    return 0;
}
