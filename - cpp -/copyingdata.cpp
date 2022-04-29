#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 292E

//make a range assignment seg tree. Due to the problem, we have to assign in a special way. 

//instead of assigning a number, we assign 2 numbers, the x and y of the operation we performed on the segment. 
//using this x and y, we can derive the value if we have our b array index, i. 

//to do this, just take the difference between i - y = d, and add to x, d : x + d. This is the 
//index in the a array that corresponds to i in the b array.

vector<int> a(1e5);
vector<int> b(1e5);
vector<vector<int>> t(1e5 * 2 + 100, vector<int>(3));   //x, y, priority : higher priority takes precedent
int n;

int query(int i) {
    int ans = b[i];
    int priority = 0;
    int oi = i;
    i += n;
    if(t[i][2] > priority){
        int diff = oi - t[i][1];
        priority = t[i][2];
        ans = a[t[i][0] + diff];
    }
    for(; i > 0; i /= 2){
        if(t[i][2] > priority){
            int diff = oi - t[i][1];
            priority = t[i][2];
            ans = a[t[i][0] + diff];
        }
    }
    return ans;
}

void modify(int l, int r, int x, int y, int priority){
    for(l += n, r += n; l < r; l /= 2, r /= 2){
        if(l % 2 == 1){
            if(t[l][2] < priority){
                t[l][0] = x;
                t[l][1] = y;
                t[l][2] = priority;
            }   
            l++;
        }
        if(r % 2 == 1){
            r--;
            if(t[r][2] < priority){
                t[r][0] = x;
                t[r][1] = y;
                t[r][2] = priority;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i];
    }
    int p = 1;
    while(m-- > 0){
        int t;
        cin >> t;
        if(t == 1){
            int x, y, k;
            cin >> x >> y >> k;
            y--;
            x--;
            int l = y;
            int r = l + k;
            modify(l, r, x, y, p++);
        }
        else{
            int x;
            cin >> x;
            cout << query(--x) << endl;
        }
    }
    
    return 0;
}
