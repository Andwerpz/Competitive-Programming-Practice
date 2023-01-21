#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 01 D

//implementation stuff. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s1, s2;
    cin >> s1 >> s2;
    int curHr, curMin, curSec;
    int tgtHr, tgtMin, tgtSec;
    curHr = (s1[0] - '0') * 10 + (s1[1] - '0');
    curMin = (s1[3] - '0') * 10 + (s1[4] - '0');
    curSec = (s1[6] - '0') * 10 + (s1[7] - '0');
    tgtHr = (s2[0] - '0') * 10 + (s2[1] - '0');
    tgtMin = (s2[3] - '0') * 10 + (s2[4] - '0');
    tgtSec = (s2[6] - '0') * 10 + (s2[7] - '0');
    int ansHr, ansMin, ansSec;
    ansSec = tgtSec - curSec;
    if(ansSec < 0) {
        ansSec += 60;
        curMin ++;
    }
    ansMin = tgtMin - curMin;
    if(ansMin < 0){
        ansMin += 60;
        curHr ++;
    }
    ansHr = tgtHr - curHr;
    if(ansHr < 0){
        ansHr += 24;
    }
    if(ansHr == ansMin && ansMin == ansSec && ansSec == 0){
        ansHr = 24;
    }
    string ans = "";
    ans += ansHr < 10? "0" : "";
    ans += to_string(ansHr) + ":";
    ans += ansMin < 10? "0" : "";
    ans += to_string(ansMin) + ":";
    ans += ansSec < 10? "0" : "";
    ans += to_string(ansSec) + "\n";
    cout << ans;
    
    return 0;
}
