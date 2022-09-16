#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC 2022 Week 1 G

//If we look at the binary representations of elements in a and b, we can notice something about the operations. 

//Divide operation just shifts a[i] to the right 1 place. 
//Multiply operation appends a 0 onto a[i] from the right. 

//Notice that dividing b[i] where b[i] % 2 == 0 is equivalent to multiplying an a[i] by 2.

//The solution is to pair off the numbers in a and b starting from the greatest elements. 
//if you need to divide a[i], then do so. 
//if you need to divide b[i], and b[i] % 2 == 1, then it is impossible for you to turn a into b, else, just divide b[i].

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    map<int, int> a;    //multiset
    map<int, int> b;
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        if(a.find(next) == a.end()){
            a.insert({next, 0});
        }
        a.find(next) -> second ++;
    }
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        if(b.find(next) == b.end()){
            b.insert({next, 0});
        }
        b.find(next) -> second ++;
    }
    int ans = 0;
    bool isValid = true;
    auto aPtr = a.rbegin();
    auto bPtr = b.rbegin();
    while(aPtr != a.rend() && bPtr != b.rend()) {
        if(aPtr -> first == bPtr -> first){
            //match and remove
            int amt = min(aPtr -> second, bPtr -> second);
            aPtr -> second -= amt;
            bPtr -> second -= amt;
            //cout << "dump " << aPtr -> first << " " << amt << "\n";
        }
        if(aPtr -> first > bPtr -> first){
            //decrement a
            int next = aPtr -> first / 2;
            int amt = aPtr -> second;
            ans += amt;
            if(a.find(next) == a.end()){
                a.insert({next, 0});
            }
            a.find(next) -> second += amt;
            aPtr -> second = 0;
        }
        if(bPtr -> first > aPtr -> first){
            if(bPtr -> first % 2 == 1){ //impossible for value of a to equal
                isValid = false;
                break;
            }
            //increment a
            int next = bPtr -> first / 2;
            int amt = bPtr -> second;
            ans += amt;
            if(b.find(next) == b.end()){
                b.insert({next, 0});
            }
            b.find(next) -> second += amt;
            bPtr -> second = 0;
        }
        if(aPtr -> second == 0){
            aPtr ++;
        }
        if(bPtr -> second == 0){
            bPtr ++;
        }
    }
    cout << (isValid? ans : -1) << "\n";
    
    return 0;
}
