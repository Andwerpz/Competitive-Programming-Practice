#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 02 E

//we can represent the stacks as a tree structure, with the original stack being the root. 
//the value of each node in the tree is equal to the top element of the stack. 

//on operations of type a v, we create a child of v denoted with i. 
//on operations of type b v, it's the same as creating another instance of v.parent, so we can just map i to v.parent. 
//on operations of type c u v, the tree doesn't change since we are duplicating node u

//to output the answer for b v, notice that stack v always has v as it's top element. So you can just ouput v. 

//to output the answer for c u v, notice that the answer is simply the number of elements in the least common ancestor
//of u and v. Instead of answering the queries online, we can simply notice that the contents of the stacks within the tree
//never change, and so we can just collect all of the queries and answer them all offline at the end. 

//to solve LCA offline, we can use a range minimum query over an in order traversal of the tree. Generating the in order traversal is different
//from a normal binary tree, as you have to print the root between the prints of every child. 
//RMQ can be done with segment tree. 

const int N = 3e6;  //limit for segtree size
int n;
int t[2 * N];

void build() { // build the tree
    for (int i = n - 1; i > 0; i--) {   
        t[i] = min(t[i * 2], t[i * 2 + 1]);
    }
}

void modify(int p, int value) { // set value at position p
    p += n;
    t[p] = value;
    for (p /= 2; p > 0; p /= 2) {
        t[p] = min(t[p * 2], t[p * 2 + 1]);
    }
}

int query(int l, int r) { // min on interval [l, r)
    int res = t[l + n];
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
        if (l % 2 == 1) {
            res = min(res, t[l]);
            l++;
        }
        if (r % 2 == 1) {
            r--;
            res = min(res, t[r]);
        }
    }
    return res;
}

void getInOrder(vector<int>& ans, map<int, vector<int>>& child, int i) {
    vector<int> c = child.find(i) -> second;
    //getInOrder(ans, child, c[0]);
    for(int j = 0; j < c.size(); j++){
        ans.push_back(i);
        getInOrder(ans, child, c[j]);
    }
    ans.push_back(i);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q;
    cin >> q;
    map<int, int> nodeMap;
    map<int, int> amtMap;
    map<int, int> parentMap;
    map<int, vector<int>> childMap;
    nodeMap.insert({0, 0});
    amtMap.insert({0, 0});
    childMap.insert({0, vector<int>(0)});
    vector<pair<int, int>> ans(0);
    for(int i = 0; i < q; i++){
        string type;
        cin >> type;
        int node = i + 1;
        if(type == "a") {
            int val;
            cin >> val;
            nodeMap.insert({node, node});
            amtMap.insert({node, amtMap.find(nodeMap.find(val) -> second) -> second + 1});
            parentMap.insert({node, nodeMap.find(val) -> second});
            childMap.insert({node, vector<int>(0)});
            childMap.find(nodeMap.find(val) -> second) -> second.push_back(node);
            //cout << node << " IS NOW CHILD OF " << nodeMap.find(val) -> second << "\n";
        }
        else if(type == "b") {
            int val;
            cin >> val;
            nodeMap.insert({node, parentMap.find(nodeMap.find(val) -> second) -> second});
            //amtMap.insert({node, amtMap.find(val) -> second - 1});
            //parentMap.insert({node, parentMap.find(nodeMap.find(node) -> second) -> second});
            ans.push_back({-1, nodeMap.find(val) -> second});
        }
        else if(type == "c"){ 
            int val, w;
            cin >> val >> w;
            nodeMap.insert({node, nodeMap.find(val) -> second});
            ans.push_back({val, w});
        }
        //cout << node << " : " << nodeMap.find(node) -> second << "\n";
    }
    //generate 'in order' traversal
    vector<int> inOrder(0);
    getInOrder(inOrder, childMap, 0);
    n = inOrder.size();
    map<int, int> posMap;
    for(int i = 0; i < inOrder.size(); i++){
        //t[i] = inOrder[i];
        posMap.insert({inOrder[i], i});
        modify(i, inOrder[i]);
        //cout << inOrder[i] << " ";
    }
    //cout << "\n";
    // for(int i = 1; i < n * 2; i++){
    //     cout << t[i] << " ";
    // }
    // cout << "\n";
    //print answers
    for(int i = 0; i < ans.size(); i++){
        if(ans[i].first == -1) {
            cout << ans[i].second << "\n";
        }
        else {
            int l = posMap.find(nodeMap.find(ans[i].first) -> second) -> second;
            int r = posMap.find(nodeMap.find(ans[i].second) -> second) -> second;
            if(r < l) {
                int tmp = l;
                l = r;
                r = tmp;
            }
            r ++;
            //cout << "BOUNDS : " << l << " " << r << "\n";
            //cout << "QUERY : " << query(l, r) << "\n";
            //cout << "AMT : " << amtMap.find(query(l, r)) -> second << "\n";
            //cout << "QUERY " << ans[i].first << " " << ans[i].second << "\n";
            cout << amtMap.find(query(l, r)) -> second << "\n";
        }
        //cout << ans[i].first << " " << ans[i].second << "\n";
    }
    
    return 0;
}
