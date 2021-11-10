
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1332C

//you can split each string into parts that you need to make equal. You know that you need to make it palindromic, and also cyclic. This means that the cycles must also be
//palindromic. If the cycles weren't palindromic, then if the whole string is palindromic, the cycles aren't cycles, and if the string isn't palindromic, then we've
//just broken the other rule.

//From each cycle, since they must be palindromic, you know that the first and last must be equal, second first and second last, and so on. You also know that the first of
//every cycle must be equal, and so on. From there, you can form your groups. 

//in a group, just record the occurrences of each character. Change every other character to the one that occurs the most. You can do each group one by one since
//one group won't affect another group.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        int ans = 0;
        int low = 0;
        int high = k - 1;
        while(true){
            vector<int> charCount(26);
            for(int i = 0; i < n; i += k){
                charCount[s[low + i] - 'a'] ++;
                charCount[s[high + i] - 'a'] ++;
            }
            int total = (n / k) * 2;
            int max = 0;
            for(int i = 0; i < charCount.size(); i++){
                max = std::max(max, charCount[i]);
            }
            if(low == high){
                ans += (total - max) / 2;
            }
            else{
                ans += total - max;
            }
            low ++;
            high --;
            if(low > high){
                break;
            }
        }
        cout << ans << endl;
    }

    return 0;
}



