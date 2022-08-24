#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1697D

//notice that you can only do the type 1 query 26 times, the same amount as the number
//of possible characters in the string. Thus, we need to find a way to only use the type 1 query
//when we encounter a new character. 

//The idea is that if you know the characters in a subarray of the string, and you know how many
//unique characters there are in that subarray, if you do a query that includes another character outside of the
//subarray, and the number of unique characters doesn't change, then that new character must be equal to one
//of the characters in the subarray. 

//Start from i = 0, and keep track for each character the last index you've seen it. When processing the ith character, first
//test whether it is a new one, by doing a type 2 query from 0 - i. If the amount of unique characters is greater than the amount
//of unique characters you've seen so far, then s_i is new. 

//else, you've seen s_i before. You can use binary search to quickly determine which character s_i is. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<char> out(0);
    vector<pair<char, int>> f(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        //cout << "I : " << i << endl;
        //first check if char is new
        cout << "? 2 1 " << (i + 1) << endl;
        int amt;
        cin >> amt;
        char next;
        if(amt > f.size()){ //char is new
            cout << "? 1 " << (i + 1) << endl;
            string c;
            cin >> c;
            f.push_back({c[0], i});
            next = c[0];
        }
        else {  //char is not new
            int low = 0;
            int high = f.size() - 1;
            int mid = low + (high - low) / 2;
            int ans = low;
            while(low <= high){
                int index = f[mid].second;
                cout << "? 2 " << (index + 1) << " " << (i + 1) << endl;
                int cnt;
                cin >> cnt;
                if(cnt == f.size() - mid) {
                    //cout << "YES\n";
                    ans = max(ans, mid);
                    low = mid + 1;
                }
                else{
                    //cout << "NO\n";
                    high = mid - 1;
                }
                mid = low + (high - low) / 2;
            }
            next = f[ans].first;
        }
        for(int j = 0; j < f.size(); j++){
            if(f[j].first == next){
                f[j].second = i;
            }
        }
        sort(f.begin(), f.end(), [](pair<char, int> &a, pair<char, int> &b){return a.second < b.second;});
        out.push_back(next);
    }
    cout << "! ";
    for(char c : out){
        cout << c;
    }
    cout << endl;
    
    return 0;
}
