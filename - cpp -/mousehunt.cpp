
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1027D

//since there are n nodes and only n directed edges, there are some special properties that we can exploit. 

//first, notice that the graph is not necessarily fully connected, and for each connected component, we only need to place 1 trap to cover the entire thing. 

//next, notice that each connected component contains either 0 or 1 loops. 0 loop components are essentially trees, and the solutions is to place your 1 trap 
//at the root of the tree.

//1 loop components are slightly more complicated. First, figure out which nodes are part of the loop, and then put the trap in the node with the least cost.

//it is impossible for a component to have 2 or more loops. Given n nodes, having 2 separate loops that contain all the nodes already requires n edges, so adding
//an extra edge would place us above our budget: or in other words, 1 node has to have 2 outgoing edges for that to work. 

using namespace std;

int main() {

    int n;
    cin >> n;
    vector<int> cost(n);
    vector<int> a(n);
    vector<vector<int>> c(n);
    for(int i = 0; i < n; i++){
        cin >> cost[i];
    }
    for(int i = 0; i < n; i++){
        int next;
        cin >> next;
        next --;
        c[i].push_back(next);
        c[next].push_back(i);
        a[i] = next;
    }
    vector<vector<int>> groups;
    vector<bool> v(n);
    fill(v.begin(), v.end(), false);
    for(int i = 0; i < n; i++){
        //cout << i << "\n";
        if(!v[i]){
            //cout << "YES\n";
            stack<int> s;
            s.push(i);
            v[i] = true;
            vector<int> nextGroup;
            nextGroup.push_back(i);
            while(s.size() != 0){
                int cur = s.top();
                s.pop();
                for(int j = 0; j < c[cur].size(); j++){
                    int next = c[cur][j];
                    if(!v[next]){
                        v[next] = true;
                        s.push(next);
                        nextGroup.push_back(next);
                    }
                }
            }
            groups.push_back(nextGroup);
        }
    }
    fill(v.begin(), v.end(), false);
    int ans = 0;
    for(int i = 0; i < groups.size(); i++){
        //cout << i << "\n";
        bool hasLoop = false;
        stack<int> s;
        s.push(groups[i][0]);
        v[groups[i][0]] = true;
        int last = 0;
        while(s.size() != 0){
            int cur = s.top();
            last = cur;
            s.pop();
            int next = a[cur];
            if(next == cur){
                break;
            }
            if(v[next]){
                last = next;
                hasLoop = true;
                break;
            }
            else{
                s.push(next);
                v[next] = true;
            }
        }
        if(hasLoop){
            //cout << "HAS LOOP\n";
            int min = cost[last];
            int pointer = a[last];
            while(pointer != last){
                min = std::min(min, cost[pointer]);
                pointer = a[pointer];
            }
            ans += min;
        }
        else{
            //cout << "NO LOOP\n";
            ans += cost[last];
        }
    }
    cout << ans << endl;

    return 0;
}



