#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 04 G

//if you imagine the players not going one by one to pick their players, but all at the same time, 
//you'll notice that the ghost legs seem to swap adjacent players. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> legs(0);
    for(int i = 0; i < k; i++){
        int a, b;
        cin >> a >> b;
        legs.push_back({b, a});
        //cout << a << " " << b << "\n";
    }
    sort(legs.begin(), legs.end());
    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        ans[i] = i;
    }
    //cout << "HERE\n";
    for(int i = k - 1; i >= 0; i--) {
        int next = legs[i].second;
        //cout << next << "\n";
        int tmp = ans[next];
        ans[next] = ans[next + 1];
        ans[next + 1] = tmp;
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
