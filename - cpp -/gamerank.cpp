#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 04 F

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    int rank = 25;
    int stars = 0;
    int winsRow = 0;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == 'W'){
            winsRow ++;
            bool bonusStar = false;
            if(6 <= rank && rank <= 25 && winsRow >= 3) {
                bonusStar = true;
            }
            bool hasAllStars = false;
            if(21 <= rank && rank <= 25) {
                hasAllStars |= stars >= 2;
            }
            if(16 <= rank && rank <= 20) {
                hasAllStars |= stars >= 3;
            }
            if(11 <= rank && rank <= 15) {
                hasAllStars |= stars >= 4;
            }
            if(1 <= rank && rank <= 10){
                hasAllStars |= stars >= 5;
            }
            if(hasAllStars) {
                stars = 1;
                rank --;
            }
            else {
                stars ++;  
            }
            hasAllStars = false;
            if(21 <= rank && rank <= 25) {
                hasAllStars |= stars >= 2;
            }
            if(16 <= rank && rank <= 20) {
                hasAllStars |= stars >= 3;
            }
            if(11 <= rank && rank <= 15) {
                hasAllStars |= stars >= 4;
            }
            if(1 <= rank && rank <= 10){
                hasAllStars |= stars >= 5;
            }
            if(bonusStar) {
                stars ++;
                if(hasAllStars) {
                    stars = 1;
                    rank --;
                }
            }
        }
        else{
            winsRow = 0;
            if(1 <= rank && rank <= 20){
                stars --;
            }
            if(stars == -1) {
                if(rank == 20){
                    stars = 0;
                }
                else {
                    rank ++;
                    if(21 <= rank && rank <= 25) {
                        stars = 1;
                    }
                    if(16 <= rank && rank <= 20) {
                        stars = 2;
                    }
                    if(11 <= rank && rank <= 15) {
                        stars = 3;
                    }
                    if(1 <= rank && rank <= 10){
                        stars = 4;
                    }
                }
            }
        }
    }
    if(rank == 0){
        cout << "Legend\n";
    }
    else {
        cout << rank << "\n";
    }
    
    return 0;
}
