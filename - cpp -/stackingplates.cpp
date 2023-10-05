#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2012 - K

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int cases = 1;

    int n; cin >> n;
    while(!cin.eof()) {
        vector<vector<int>> stacks(n);
        multiset<int> ms;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        for(int i = 0; i < n; i++) {
            int h; cin >> h;
            for(int j = 0; j < h; j++) {
                int num; cin >> num;
                stacks[i].push_back(num);
                ms.insert(num);
            }
            reverse(stacks[i].begin(),stacks[i].end());
            for(int j = 0; j < h; j++) {
                if(j == 0) {
                    pq.push({stacks[i][j],0,i});
                } else {
                    pq.push({stacks[i][j],stacks[i][j-1],i});
                }
            }
        }
        ll ops = 0;
        int stacks_left = n;
        while(stacks_left != 1) {
            vector<int> v = pq.top();
            cout << v[0] << " " << v[1] << " " << v[2] << "\n";
            pq.pop();
            ms.erase(ms.find(v[0]));
            if(v[1] == 0) { //there is no plate below here
                ops++;
                stacks_left--;
            } else if(v[1] <= *ms.begin()) { //case the plate below it is next lowest

            } else {
                ops += 2;
            }
        }

        cout << "Case " << cases++ << ": " << ops << "\n";
        cin >> n;
    }
    
    return 0;
}
