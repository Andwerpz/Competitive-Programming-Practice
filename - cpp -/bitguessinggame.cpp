#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1780D

//since a given n only has maximum 30 bits, and you are given 30 queries, it's reasonable to assume
//the intended solution wants you to figure out n bit by bit. 

//going from the most significant bit to the least doesn't work, because you risk querying and x which
//is bigger than n. You'd first have to find what the most significant bit is, and you wouldn't have enough moves. 

//the only way you can get information is by going from the least significant bit. The best way to get information is
//to set x equal to a power of two, thus when n - x, you subtract 1 bit. 

//notice that if x is one bit, then subtracting n from x will always turn one bit in n to 0. That bit is always the least significant
//bit that is more significant than the x bit. Looking at the difference between 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int cnt;
        cin >> cnt;
        int n = 0;
        int p = 1;
        int pcnt = cnt;
        for(int i = 0; i < cnt; i++){
            int ncnt;
            cout << "- " << p << endl;
            cin >> ncnt;
            int diff = ncnt - pcnt + 1;
            pcnt = ncnt;
            for(int i = 0; i < diff; i++){
                p *= 2;
            }
            n |= p;
            p *= 2;
        }
        cout << "! " << n << endl;
    }
    
    return 0;
}
