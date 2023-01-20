#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 01 C

//brute force lmao

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0) {
        //brute force lmao
        int nSum = 0;
        int tmp = n;
        while(tmp != 0){
            nSum += tmp % 10;
            tmp /= 10;
        }
        int p = 11;
        while(true) {
            int next = p * n;
            int sum = 0;
            while(next != 0) {
                sum += next % 10;
                next /= 10;
            }
            if(sum == nSum) {
                break;
            }
            p++;
        }
        cout << p << "\n";
        cin >> n;
    }
    
    return 0;
}
