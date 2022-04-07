
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES 1642

//notice that you can convert this problem into one that looks more like sum of 2 values. 

//generate all sums of 2 distinct values and save them. Now, if you combine 2 values from this array, 
//you'll get the sum of 4 values. 

//the one problem is that you need to sum 4 different values to x. If you add 2 numbers from the combined
//array, it is possible to get duplicate values. To prevent this, just save the original indexes along with
//the values in the array, and when you find a match, just check if all the indicies are distinct. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x;
    cin >> n >> x;
    vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    //create set of combined numbers
    vector<int> comb;
    vector<pair<int, int>> combId;
    map<int, vector<pair<int, int>>> m;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            int sum = nums[i] + nums[j];
            pair<int, int> nextId {i, j};
            combId.push_back(nextId);
            comb.push_back(sum);
            if(m.find(sum) == m.end()){
                m.insert({sum, vector<pair<int, int>>()});
            }
            m.at(sum).push_back(nextId);
        }
    }
    vector<int> ans(0);
    for(int i = 0; i < comb.size(); i++){
        int diff = x - comb[i];
        int a = combId[i].first;
        int b = combId[i].second;
        if(m.find(diff) != m.end()){
            vector<pair<int, int>> nextIds = m.at(diff);
            for(int j = 0; j < nextIds.size(); j++){
                int c = nextIds[j].first;
                int d = nextIds[j].second;
                if(a != c && a != d && b != c && b != d){
                    ans = vector<int> {a, b, c, d};
                    goto endloop;
                }
            }
        }
    }
    endloop:;
    if(ans.size() == 0){
        cout << "IMPOSSIBLE" << endl;
    }
    else{
        for(int i : ans){
            cout << (i + 1) << " ";
        }
        cout << endl;
    }
    
    return 0;
}
