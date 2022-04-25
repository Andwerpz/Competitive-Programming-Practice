
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1668B

//notice that the number of empty chairs between two people is going to be equal to the maximum between their
//two preferences. Thus, we want to minimize the amount of times we have to put two people with unequal preferences
//next to each other, as putting two people with unequal preferences next to each other means unecessary empty chairs.

//to do this, we can just sort it. Answering the question is easy, we can just iterate through the array and see how many
//chairs our current configuration will take, and compare that value to m. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        vector<int> nums(n, 0);
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        sort(nums.begin(), nums.end(), [] (int a, int b) {return a < b;});
        ll sum = 0;
        sum += n;
        for(int i = 0; i < n; i++){
            sum += max(nums[i], nums[(i + 1) % n]);
        }
        cout << (sum <= m? "YES\n" : "NO\n");
    }
    
    return 0;
}
