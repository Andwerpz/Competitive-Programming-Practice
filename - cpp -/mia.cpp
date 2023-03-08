#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 07 D

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    while(a != 0){
        if(a > b){
            int tmp = a;
            a = b;
            b = tmp;
        }
        if(c > d){
            int tmp = c;
            c = d;
            d = tmp;
        }
        if(a == 1 && b == 2 || c == 1 && d == 2) {
            if(a == 1 && b == 2 && c == 1 && d == 2) {
                cout << "Tie.\n";
            }
            else if(a == 1 && b == 2){
                cout << "Player 1 wins.\n";
            }
            else {
                cout << "Player 2 wins.\n";
            }
        }
        else if(a == b || c == d){
            if(a == b && c == d){
                if(a > c){
                    cout << "Player 1 wins.\n";
                }
                else if(a < c){
                    cout << "Player 2 wins.\n";
                }
                else {
                    cout << "Tie.\n";
                }
            }
            else if(a == b){
                cout << "Player 1 wins.\n";
            }
            else {
                cout << "Player 2 wins.\n";
            }
        }
        else {
            int aval = b * 10 + a;
            int bval = d * 10 + c;
            if(aval > bval){
                cout << "Player 1 wins.\n";
            }
            else if(aval < bval){
                cout << "Player 2 wins.\n";
            }
            else{
                cout << "Tie.\n";
            }
        }
        cin >> a >> b >> c >> d;
    }
    
    return 0;
}
