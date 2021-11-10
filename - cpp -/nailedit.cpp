
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//DMOJ - ccc17s3

//nailed it! 

//you can easily calculate for each height, the maximum length achievable. O(n^2)

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> lengths(2001);
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        lengths[next] ++;
    }
    vector<int> ans(4001);
    for(int i = 1; i < lengths.size(); i++){
        ans[i * 2] += lengths[i] / 2;
        for(int j = i + 1; j < lengths.size(); j++){
            int next = i + j;
            ans[next] += min(lengths[i], lengths[j]);
        }
    }
    //cout << "TEST " << (3 / 2) << endl;
    int maxLength = 0;
    int maxAmt = 0;
    for(int i = 0; i < ans.size(); i++){
        int next = ans[i];
        if(next > maxLength){
            maxLength = next;
            maxAmt = 1;
        }
        else if(next == maxLength){
            maxAmt ++;
        }
    }
    cout << maxLength << " " << maxAmt << endl;

    return 0;
}



