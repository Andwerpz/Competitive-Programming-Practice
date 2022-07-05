#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1698C

//notice that if the array has 3 positive or 3 negative numbers, it can never be 3-sum closed. 
//this is because we can always just pick the 3 largest or 3 smallest numbers in the array and
//have the sum be a number that isn't present in the array. 

//thus, the only cases where 'a' can be 3-sum closed is where the amount of positive and negative numbers
//repsectively remain under 3. 

//If you have more than 3 zeroes in 'a', then you can get rid of all the extras. 

//in the end, the maximum size of a is 7, so you can just do a brute force search to test. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        set<int> a;
        vector<int> nums(0);
        int pos = 0;
        int neg = 0;
        int zero = 0;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            a.insert(next);
            if(next > 0){
                nums.push_back(next);
                pos ++;
            }
            else if(next < 0){
                nums.push_back(next);
                neg ++;
            }
            else{
                zero ++;
                if(zero <= 3){
                    nums.push_back(next);
                }
            }
        }
        if(pos >= 3 || neg >= 3){
            cout << "NO\n";
            continue;
        }
        bool isValid = true;
        for(int i = 0; i < nums.size(); i++){
            for(int j = i + 1; j < nums.size(); j++){
                for(int k = j + 1; k < nums.size(); k++){
                    if(a.find(nums[i] + nums[j] + nums[k]) == a.end()){
                        isValid = false;
                    }
                }
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}
