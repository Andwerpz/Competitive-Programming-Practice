#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1695B

//mike and joe will go around the circle taking turns to remove stones. 

//notice that if n is odd, then after one cycle, mike and joe will take from the piles that 
//the other took from the previous round. This means that in order to win, each must take all 
//the stones from the pile whenever they can, since on the next cycle the other player can't play on 
//the piles they took from. Since mike goes first, he wins everytime. 

//else, n is even, then mike and joe will never take from each other's piles. This means that each
//wants to prolong the game for as long as possible, only taking 1 stone each time. This means 
//the person with the minimum pile that comes first will lose. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        if(n % 2 == 1){
            cout << "Mike\n";
            continue;
        }
        int min = a[0];
        int index = 0;
        for(int i = 0; i < n; i++){
            if(a[i] < min){
                min = a[i];
                index = i;
            }
        }
        cout << (index % 2 == 1? "Mike\n" : "Joe\n");
    }
    
    return 0;
}
