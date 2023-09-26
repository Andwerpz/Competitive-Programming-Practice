#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//UVA - 588

//being able to see every part of the room is equivalent to being able to see every wall in the room. 

//in order to see a certain wall, we must be on the 'correct side' of the wall. For example, if a wall
//is facing to the left, then we must be to the left of the wall in order to 'see' it. 

//since all the walls are axis-aligned, this problem then becomes very simple. We just need to keep track of the
//minimum and maximum position in both the x and y axis that we can place the camera. Then, for each wall, 
//we keep tightening our bounds. If the minimum and maximum bounds in either axis go over each other, then
//we know that it is impossible to place the camera. 

//one issue is how do we know which side of the wall is the 'inside' side? Well, since the problem always gives
//you the walls in clockwise order, you can know what side it is based off of the direction the wall is going, 
//but you can also just try both ways. 

bool solve(vector<pair<int, int>>& a) {
    ll minX = -1e18;
    ll maxX = 1e18;
    ll minY = -1e18;
    ll maxY = 1e18;
    for(int i = 0; i < a.size() - 1; i++){
        char curDir = 0;
        if(a[i].first == a[i + 1].first) {
            if(a[i].second < a[i + 1].second) {
                curDir = 'U';
            }
            else {
                curDir = 'D';
            }
        }
        else {
            if(a[i].first < a[i + 1].first) {
                curDir = 'R';
            }
            else {
                curDir = 'L';
            }
        }
        char curFacing = 0; //what direction is pointing 'in'. 
        if(curDir == 'U') {
            curFacing = 'R';
        }
        if(curDir == 'D') {
            curFacing = 'L';
        }
        if(curDir == 'R') {
            curFacing = 'D';
        }
        if(curDir == 'L'){
            curFacing = 'U';
        }
        //cout << curDir << " " << curFacing << "\n";
        if(curFacing == 'U') {
            minY = max(minY, (ll) a[i].second);
        }
        if(curFacing == 'D') {
            maxY = min(maxY, (ll) a[i].second);
        }
        if(curFacing == 'L') {
            maxX = min(maxX, (ll) a[i].first);
        }
        if(curFacing == 'R') {
            minX = max(minX, (ll) a[i].first);
        }
    }
    return minY <= maxY && minX <= maxX;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int tcnt = 0;
    while(n != 0){
        tcnt ++;
        vector<pair<int, int>> a(n, {0, 0});
        for(int i = 0; i < a.size(); i++){
            cin >> a[i].first >> a[i].second;
        }
        //try once
        bool ans = solve(a);
        reverse(a.begin(), a.end());
        ans |= solve(a);
        cout << "Floor #" << tcnt << "\n";
        cout << "Surveillance is " << (ans? "possible" : "impossible") << ".\n" << "\n";
        cin >> n;
    }
    
    return 0;
}
