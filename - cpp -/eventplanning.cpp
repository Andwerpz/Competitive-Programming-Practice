#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 01 D

//the problem statement really be throwing these distractions D:

//just go through each hotel, and check if it's within your budget to stay there. 
//if it is, then if you can find a week where there is enough capacity, then you can stay there
//find the minimum. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, b, h, w;
    cin >> n >> b >> h >> w;
    int cost = (int) 1e9;
    for(int i = 0; i < h; i++){
        int p;
        cin >> p;
        bool isValid = false;
        for(int j = 0; j < w; j++){
            int next;
            cin >> next;
            if(next >= n) {
                isValid = true;
            }
        }
        if(isValid) {
            cost = min(cost, p * n);
        }
    }
    if(cost <= b){
        cout << cost << "\n";
    }
    else {
        cout << "stay home\n";
    }
    
    return 0;
}
