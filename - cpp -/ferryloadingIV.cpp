#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 05 A

//just simulate the problem

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int l, m;
        cin >> l >> m;
        queue<int> left;
        queue<int> right;
        l *= 100;
        for(int i = 0; i < m; i++){
            int length;
            string which;
            cin >> length >> which;
            if(which == "left"){
                left.push(length);
            }
            else {
                right.push(length);
            }
        }
        bool onLeft = true;
        int ans = 0;
        while(left.size() + right.size() != 0){
            int sum = 0;
            ans ++;
            if(onLeft){
                while(left.size() != 0 && sum + left.front() <= l){
                    sum += left.front();
                    left.pop();
                }
                onLeft = false;
            }
            else {
                while(right.size() != 0 && sum + right.front() <= l) {
                    sum += right.front();
                    right.pop();
                }
                onLeft = true;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}
