
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces edu - Binary Search Step 2 D

//just binary search the amount of time it takes. Calculating how many balloons each assistant can fill can be done in
//O(n) time, so final time complexity is O(n * log(n))

vector<ll> t, z, y, ans;
ll m, minTime;
int n;

bool isValid(ll time){
    ll balloonsInflated = 0;
    vector<ll> curAns(n);
    for(int i = 0; i < n; i++){
        ll amt = z[i];
        ll cycleTime = z[i] * t[i] + y[i];
        ll remainder = time % cycleTime;
        ll cycleAmt = time / cycleTime;
        ll curInflated = cycleAmt * amt + min(remainder / t[i], z[i]);
        curInflated = min(curInflated, m - balloonsInflated);
        balloonsInflated += curInflated;
        curAns[i] = curInflated;
    }
    if(balloonsInflated >= m){
        if(minTime > time){
            //cout << time << endl;
            ans = curAns;
        }
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> m >> n;
    t = vector<ll>(n);
    z = vector<ll>(n);
    y = vector<ll>(n);
    ans = vector<ll>(n);
    for(int i = 0; i < n; i++){
        cin >> t[i] >> z[i] >> y[i];
    }
    ll low = 0;
    ll high = 1500000ll * 1100ll + 100ll;
    minTime = high;
    ll mid = low + (high - low) / 2;
    while(low <= high){
        if(isValid(mid)){
            minTime = min(mid, minTime);
            high = mid - 1;
        }
        else{
            low = mid + 1;
        }
        mid = low + (high - low) / 2;
    }
    cout << minTime << endl;
    for(ll i : ans){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
