#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//University of Alberta Programming Contest 2023 D

//first, if there is a topic where there is only left or right experts, then you know you must interview a left
//or right expert for that topic. 

//then, all other topics must have both left and right experts. First, you can try to balance the amount of left
//and right experts, then alternate between left and right. 

//if there are any extra experts, you can use one of them to balance. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t, n;
    cin >> t >> n;
    vector<pair<bool, bool>> a(t, {false, false});
    int eLeft = 0;
    int eRight = 0;
    for(int i = 0; i < n; i++){
        int next;
        string s;
        cin >> next >> s;
        next --;
        if(s == "L"){
            if(!a[next].first) {
                a[next].first = true;
            }
            else {
                eLeft ++;
            }
        }
        else {
            if(!a[next].second) {
                a[next].second = true;
            }
            else {
                eRight ++;
            }
        }
    }
    int ans = 0;
    bool isValid = true;
    int altCnt = 0;
    int lCnt = 0;
    int rCnt = 0;
    for(int i = 0; i < t; i++){
        if(!a[i].first && !a[i].second) {
            isValid = false;
        }
        else if(a[i].first && a[i].second) {
            altCnt ++;
        }
        else if(a[i].first) {
            ans ++;
            lCnt ++;
        }
        else {
            ans ++;
            rCnt ++;
        }
    }
    if(!isValid) {
        cout << "-1\n";
        return 0;
    }
    //balance
    if(lCnt < rCnt) {
        int diff = min(rCnt - lCnt, altCnt);
        altCnt -= diff;
        lCnt += diff;
        ans += diff;
    }
    else if(rCnt < lCnt) {
        int diff = min(lCnt - rCnt, altCnt);
        altCnt -= diff;
        rCnt += diff;
        ans += diff;
    }
    if(lCnt < rCnt) {
        int diff = min(rCnt - lCnt, eLeft);
        lCnt += diff;
        ans += diff;
        eLeft -= diff;
    }
    else if(rCnt < lCnt) {
        int diff = min(lCnt - rCnt, eRight);
        rCnt += diff;
        ans += diff;
        eRight -= diff;
    }
    if(rCnt != lCnt) {
        isValid = false;
    }
    //alternate
    ans += altCnt + (altCnt % 2);
    cout << (isValid? ans : -1) << "\n";
    
    return 0;
}
