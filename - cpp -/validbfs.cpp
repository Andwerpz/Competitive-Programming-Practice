
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1037D

//just simulate it, and see if it's valid.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<set<int>> c(n);
    for(int i = 0; i < n - 1; i++){
        int x, y;
        cin >> x >> y;
        x --; y --;
        c[x].insert(y);
        c[y].insert(x);
    }
    vector<int> layer(n);
    queue<int> q;
    vector<int> order(n);
    for(int i = 0; i < n; i++){
        cin >> order[i];
        order[i] --;
    }
    if(order[0] == 0){
        q.push(order[0]);
        layer[order[0]] = 0;
        int pointer = 1;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            int curLayer = layer[cur];
            while(pointer != n && c[cur].find(order[pointer]) != c[cur].end()){
                int next = order[pointer];
                q.push(next);
                pointer ++;
            }
        }
        cout << (pointer == n? "Yes\n" : "No\n");
    }
    else{
        cout << "No\n";
    }
   

    return 0;
}



