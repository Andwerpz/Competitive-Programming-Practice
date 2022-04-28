#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSES 2168

//if you pass in vectors with references instead of as copy, it's much faster.

//checking if a segment contains another segment and checking if it's nested within another segment
//is very similar. 

//first, maintain an ordered set that sorts numbers in ascending order

//To check if a segment contains another segment, we can first sort the segments in ascending order
//based on their ending point. When we get to the ith segment, we check if there is alread a segment
//we've processed with a starting point later than the current segment starting point. If yes, then this
//segment contains a segment within it. 

//this is true since all the segments we've checked so far have an ending point less than or equal to the current 
//segment, so if there exists a starting point from one of those segments that is after the current 
//starting point, then since the ending point has to be less than the current one, it has to be 
//contained within the current segment. 

//finally, we can update the set by adding the current starting point to the set. 

//To check if the current segment is nested within another segment, the logic is pretty much the same, 
//except we sort the segments using the starting position, and store in the set the ending positions. 

//if we can find an ending position in the set after the current ending position, then the current 
//segment is nested within another segment. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> nums(n, vector<int>(5));
    for(int i = 0; i < n; i++){
        cin >> nums[i][0] >> nums[i][1];
        nums[i][4] = i;
    }
    //checking for contains
    sort(nums.begin(), nums.end(), [] (vector<int>& a, vector<int>& b) {return a[1] == b[1]? a[0] > b[0] : a[1] < b[1];});
    auto compare = [] (int a, int b) {return a < b;};
    set<int, decltype(compare)> set(compare);
    for(int i = 0; i < n; i++){
        //check if there exists a segment that starts after this segment.
        set.upper_bound(nums[i][0] - 1) != set.end()? nums[i][2] = 1 : nums[i][2] = 0;
        //add start of segment to set
        set.insert(nums[i][0]);
    }
    //checking for nested
    sort(nums.begin(), nums.end(), [] (vector<int>& a, vector<int>& b) {return a[0] == b[0]? a[1] > b[1] : a[0] < b[0];});
    set.clear();
    for(int i = 0; i < n; i++){
        //check if there exists a segment that ends after this segment.
        set.upper_bound(nums[i][1] - 1) != set.end()? nums[i][3] = 1 : nums[i][3] = 0;
        //add end of segment to set
        set.insert(nums[i][1]);
    }
    sort(nums.begin(), nums.end(), [] (vector<int>& a, vector<int>& b) {return a[4] < b[4];});
    for(int i = 0; i < n; i++){
        cout << nums[i][2] << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++){
        cout << nums[i][3] << " ";
    }
    cout << endl;
    
    return 0;
}
