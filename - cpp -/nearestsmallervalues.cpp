
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1645

//the idea with this problem is to use a stack. 

//maintain a stack, s and the array of numbers, n. 

//when you get to n[i], pop numbers from the stack until s.top() < n[i] || s.size() == 0. 

//if s.size() == 0, then there is no smaller number to n[i] left. If s.top() < n[i], then s.top() is the 
//closest smaller number to n[i] left. After that, add n[i] to the stack. 

//this works since if n[i + 1] > n[i], then it will stop on n[i], and if it is less than n[i], then 
//it will continue past, finding the next smaller number. 

//you can think of s as a sort of updating pfx min array. Notice that when you pop a number from s, the 
//next number will always be smaller than the current one. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    stack<int> s;
    stack<int> id;
    for(int i = 0; i < n; i++){
        int ans = 0;
        int next = nums[i];
        while(s.size() != 0){
            if(s.top() < next){
                ans = id.top();
                break;
            }
            else{
                s.pop();
                id.pop();
            }
        }
        cout << ans << " ";
        s.push(next);
        id.push(i + 1);
    }
    cout << endl;
    
    return 0;
}
