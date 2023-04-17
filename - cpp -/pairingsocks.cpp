#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 10 F

//if you can pair all the socks, you can always do it in one pass. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    stack<int> a;
    stack<int> b;
    for(int i = 0; i < 2 * n; i++){
        int next;
        cin >> next;
        a.push(next);
    }
    int ans = 0;
    while(a.size() != 0){
        b.push(a.top());
        a.pop();
        ans ++;
        while(a.size() != 0 && b.size() != 0 && a.top() == b.top()) {
            ans ++;
            a.pop();
            b.pop();
        }
    }
    if(a.size() + b.size() == 0){
        cout << ans << "\n";
    }
    else {
        cout << "impossible\n";
    }
    
    return 0;
}
