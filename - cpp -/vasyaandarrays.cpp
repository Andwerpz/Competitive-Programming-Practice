
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1036D

//solve in java, somehow this c++ solution doesn't pass.

//use 
//ios_base::sync_with_stdio(false);
//cin.tie(NULL);
//to make input much faster

using namespace std;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    //vector<int> a(n);
    int* a;
    a = new int[n];
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int m;
    cin >> m;
    //vector<int> b(m);
    int* b;
    b = new int[m];
    for(int i = 0; i < m; i++){
        cin >> b[i];
    }
    ll aSum = 0;
    ll bSum = 0;
    int aPointer = 0;
    int bPointer = 0;
    int ans = 0;
    for(int i = 0; i < n; i++){
        aSum += (ll)a[i];
    }
    for(int i = 0; i < m; i++){
        bSum += (ll)b[i];
    }
    //cout << "YES\n";
    if(aSum != bSum){
        cout << "-1\n";
    }
    else{
        aSum = 0;
        bSum = 0;
        while(true){
            //cout << aSum << " " << bSum << endl;;
            if(aSum <= bSum){
                aSum += (ll)a[aPointer];
                aPointer ++;
            }
            else {
                bSum += (ll)b[bPointer];
                bPointer ++;
            }
            if(aSum == bSum){
                ans ++;
                //cout << "YES\n";
            }
            if(aPointer == n && bPointer == m){
                break;
            }
        }
        cout << ans << endl;
    }
    

    return 0;
}



