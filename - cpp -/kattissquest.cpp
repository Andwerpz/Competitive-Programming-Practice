#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 02 C

//note that there can be multiple of one type of quest. so make sure to handle that. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    auto cmp = [](vector<int> a, vector<int> b) {
        if(a[0] == b[0]) {
            if(a[1] == b[1]){
                return a[2] < b[2];
            }
            return a[1] < b[1];
        }
        return a[0] < b[0];
    };
    set<vector<int>, decltype(cmp)> s(cmp);
    for(int i = 0; i < n; i++){
        string type;
        cin >> type;
        if(type == "add") {
            int e, g;
            cin >> e >> g;
            vector<int> next(3, 0);
            next[0] = e;
            next[1] = g;
            next[2] = i;
            s.insert(next);
        }
        else if(type == "query") {
            int x;
            ll sum = 0;
            cin >> x;
            vector<int> vec(3, 0);
            vec[0] = x;
            vec[1] = 1e7;
            vec[2] = 1e7;
            while(s.lower_bound(vec) != s.begin()) {
                vector<int> next = *(--s.lower_bound(vec));
                s.erase(next);
                sum += (ll) next[1];
                vec[0] -= next[0];
                //cout << "ERASE : " << next.first << " " << next.second << endl;
            }
            cout << sum << "\n";
        }
    }
    
    return 0;
}
