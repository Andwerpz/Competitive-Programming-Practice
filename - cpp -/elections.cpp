
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1019A

//you can do an n^2 algorithm, you should take advantage of that.

//to test the cost of a target amount of votes, x, requires linear time. So for a simple n^2 algorithm, you just need to test the minimum for each amount of 
//target votes from 1 - n, and take the minimum.

using namespace std;

ll getAns(vector<vector<int>> votes, int target){
    ll ans = 0;
    int numVotes = votes[0].size();
    vector<int> unbought;
    for(int i = 1; i < votes.size(); i++){
        for(int j = 0; j < votes[i].size(); j++){
            if(votes[i].size() - j >= target){
                ans += votes[i][j];
                numVotes ++;
            }
            else {
                unbought.push_back(votes[i][j]);
            }
        }
    }
    if(numVotes >= target){
        return ans;
    }
    sort(unbought.begin(), unbought.end());
    for(int i = 0; i < unbought.size(); i++){
        ans += unbought[i];
        numVotes ++;
        if(numVotes >= target){
            return ans;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> votes(m);
    for(int i = 0; i < n; i++){
        int p, c;
        cin >> p >> c;
        p --;
        votes[p].push_back(c);
    }
    for(int i = 0; i < m; i++){
        sort(votes[i].begin(), votes[i].end());
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++){
        if(i == 1){
            ans = getAns(votes, i);
        }
        else{
            ans = min(ans, getAns(votes, i));
        }
    }
    cout << ans << endl;

    return 0;
}



