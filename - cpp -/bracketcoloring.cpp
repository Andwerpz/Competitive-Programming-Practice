#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1837D

//assertion 1: if the number of forward brackets, '(', is equal to the number of back brackets, ')', then there is always a valid coloring. 
//assertion 2: if there is a valid coloring, then the maximum amount of colors is 2. 

//first, we can see that if the number of '(' is not equal to the number of ')', then there is no valid coloring, since any 
//beautiful sequence must have a balanced amount of brackets. 

//to prove assertion 2, we can see that if we interlace two regular bracket sequences, we always get another regular bracket sequence. 
//for example: '(())' and '()()' can be interlaced to form '((()))()', which is regular. 
//notice that this works for reversed regular bracket sequences as well. 

//proving assertion 1 is left as an exercise to the reader :3

//to prove assertion 1, lets take an arbitrary bracket string, s. s has an equal amount of forwards and backwards brackets. 
//going from left to right, for each forward bracket in s, try to greedily pair it up to the closest unpaired backwards bracket that is to the right of it. 
//After pairing up as many brackets as you can, notice that the sequence of paired brackets is a regular bracket sequence, and the sequence of unpaired
//brackets (if there are any), is a reverse regular sequence of brackets. 

vector<int> solve(string s, int n) {
    vector<int> ans(n, 2);
    stack<int> st;
    for(int i = 0; i < n; i++){
        if(s[i] == '(') {
            st.push(i);
        }
        else {
            if(st.size() != 0){
                int l = st.top();
                st.pop();
                ans[l] = 1;
                ans[i] = 1;
            }
        }
    }
    bool all2 = true;
    int cnt = 1;
    for(int i = 0; i < n; i++){
        cnt = max(cnt, ans[i]);
        all2 &= ans[i] == 2;
    }
    if(all2){
        cnt = 1;
        for(int i = 0; i < n; i++){
            ans[i] = 1;
        }
    }
    ans.push_back(cnt);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int a = 0;
        int b = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '(') {
                a ++;
            }
            else {
                b ++;
            }
        }
        if(a != b) {
            cout << "-1\n";
            continue;
        }
        vector<int> ans1 = solve(s, n);
        reverse(s.begin(), s.end());
        vector<int> ans2 = solve(s, n);
        vector<int> ans = ans1[n] <= ans2[n]? ans1 : ans2;
        cout << ans[n] << "\n";
        for(int i = 0; i < n; i++){
            cout << ans[i] << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
