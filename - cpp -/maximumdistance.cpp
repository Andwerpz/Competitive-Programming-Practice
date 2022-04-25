
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 102951A

//just iterate through all pairs of points.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> x(n, 0);
    vector<int> y(n, 0);
    for(int i = 0; i < n; i++){
        cin >> x[i];
    }
    for(int i = 0; i < n; i++){
        cin >> y[i];
    }
    int max = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            max = std::max(max,(int) (pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2)));
        }
    }
    cout << max << endl;
    
    return 0;
}
