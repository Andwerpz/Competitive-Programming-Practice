
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1562D1

//of course the title of the problem can't be a hint, that's cheating!!

//for each queried segment, we can find the sum of the rods on the segment using pfx sums. If the sum is 0, then the answer is 0 rods removed.
//but if the sum is not zero, we need to find a way to get it to 0.

//first, notice that when you remove a rod in the middle of a sequence, all of the rods that come after have their values reversed.

//we can use this to efficiently change the value of the sequence. If the sum of a sequence is x, x != 0, then there must be a point in the sequence where everything before it 
//is equal to zero and everything after it is equal to x. So it also follows that there must be a point in the sequence where everything before it is x / 2, and everything after
//is x / 2. If we flip at this point, then we should make the sequence equal to zero. 

//but not quite!, when we flip, we also remove a value. So this means that if we flip in the middle of the sequence, we can only change the overall value of the sequence by an
//odd number. So if the overall value is odd, then the number of removals = 1. If it isn't odd, then we can make it odd by just removing one pipe from either end.

//so if the value is even, then the answer is 2.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, q;
        cin >> n >> q;
        vector<int> pfx(n);
        string s;
        cin >> s;
        char add = '+';
        for(int i = 0; i < n; i++){
            if(s[i] == add){
                pfx[i] ++;
            }
            else{
                pfx[i] --;
            }
            add = (add == '+'? '-' : '+');
            if(i != 0){
                pfx[i] += pfx[i - 1];
            }
        }
        for(int i = 0; i < q; i++){
            int l, r;
            cin >> l >> r;
            l --; r --;
            int sum = pfx[r] - (l == 0? 0 : pfx[l - 1]);
            if(sum == 0){
                cout << "0\n";
            }
            else if(abs(sum) % 2 == 1){
                cout << "1\n";
            }
            else{
                cout << "2\n";
            }
        }
    }

    return 0;
}



