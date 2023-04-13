#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1814C

//you can solve this problem with greedy approach

//figure out the first n times the robots will finish searching a box, and sort in ascending order. 
//sort the ball types in descending order by amount of times requested, then assign the most requested ball to 
//the earliest time, second most requested ball to the second earliest time, and so on. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, s1, s2;
        cin >> n >> s1 >> s2;
        vector<pair<int, int>> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].first;
            a[i].second = i + 1;
        }
        vector<int> l1(0);
        vector<int> l2(0);
        int p1 = 0;
        int p2 = 0;
        sort(a.begin(), a.end());
        for(int i = 0; i < n; i++){
            if(p1 + s1 <= p2 + s2) {
                l1.push_back(a[n - i - 1].second);
                p1 += s1;
            }
            else {
                l2.push_back(a[n - i - 1].second);
                p2 += s2;
            }
        }
        cout << l1.size() << " ";
        for(int i = 0; i < l1.size(); i++){
            cout << l1[i] << " \n"[i == l1.size() - 1];
        }
        cout << l2.size() << " ";
        for(int i = 0; i < l2.size(); i++){
            cout << l2[i] << " \n"[i == l2.size() - 1];
        }
    }
    
    return 0;
}
