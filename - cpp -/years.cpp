#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1424G

//classic sweep line problem. 

//sort start and endpoints and keep running total of people alive. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<pair<int, int>> a(n * 2, {0, 0});
    for(int i = 0; i < n; i++){
        cin >> a[i * 2].first >> a[i * 2 + 1].first;
        a[i * 2].second = 1;
        a[i * 2 + 1].second = -1;
    }
    int maxP = 0;
    int year = 0;
    int sum = 0;
    sort(a.begin(), a.end());
    for(int i = 0; i < n * 2; i++){
        sum += a[i].second;
        if(sum > maxP){
            maxP = sum;
            year = a[i].first;
        }
    }
    cout << year << " " << maxP << "\n";
    
    return 0;
}
