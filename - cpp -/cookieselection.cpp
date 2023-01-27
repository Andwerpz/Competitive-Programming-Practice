#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 02 D

//you can use two multisets to keep track of the upper half and bottom half of the sizes of cookies. 
//every time they want you to query a cookie, you just have to return the middle cookie, which is the edge of
//one of the sets. 

//it's best if you always keep the 'middle' cookie in one set, and just balance it afterwards. 

void insert(map<int, int>& m, int i) {
    if(m.find(i) == m.end()){
        m.insert({i, 0});
    }
    m.find(i) -> second ++;
}

void remove(map<int, int>& m, int i) {
    m.find(i) -> second --;
    if(m.find(i) -> second == 0){
        m.erase(i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<int, int> l;
    map<int, int> r;
    int lCnt = 0;
    int rCnt = 0;
    while(!cin.eof()) {
        string s;
        cin >> s;
        if(s[0] == '#') {
            //send one out
            int rbot = r.begin() -> first;
            cout << rbot << endl;
            remove(r, rbot);
            rCnt --;
        }
        else {
            int next = 0;
            for(int i = 0; i < s.size(); i++){
                next *= 10;
                int dig = s[i] - '0';
                next += dig;
            }
            if(rCnt + lCnt == 0 || next >= r.begin() -> first) {
                insert(r, next);
                rCnt ++;
            }
            else {
                insert(l, next);
                lCnt ++;
            }
        }
        //balance
        while(lCnt > rCnt) {
            int ltop = l.rbegin() -> first;
            remove(l, ltop);
            insert(r, ltop);
            lCnt --;
            rCnt ++;
        }
        while(rCnt - 1 > lCnt) {
            int rbot = r.begin() -> first;
            remove(r, rbot);
            insert(l, rbot);
            lCnt ++;
            rCnt --;
        }
    }
    
    return 0;
}
