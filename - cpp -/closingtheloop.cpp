#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 06 B

//greedily use the longest string segments that you can. There is only one solution

int solve(vector<int>& a, vector<int>& b) {
    int sum = 0;
    int knots = 0;
    if(a.size() == 0 || b.size() == 0){
        return 0;
    }
    for(int i = 0; i < min(a.size(), b.size()); i++){
        sum += a[i];
        knots ++;
        sum += b[i];
        knots ++;
    }
    return sum - knots;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    for(int j = 0; j < n; j++){
        int cnt;
        cin >> cnt;
        vector<int> a(0);
        vector<int> b(0);
        for(int i = 0; i < cnt; i++){
            string s;
            cin >> s;
            int val = stoi(s.substr(0, s.size() - 1));
            if(s[s.size() - 1] == 'R'){
                a.push_back(val);
            }
            else {
                b.push_back(val);
            }
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        cout << "Case #" << j + 1 << ": " << max(solve(a, b), solve(b, a)) << "\n";
    }
    
    return 0;
}
