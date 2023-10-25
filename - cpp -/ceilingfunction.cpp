#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2016 C

//just brute force check how many different tree structures there are. 

struct Node {
    int val;
    Node *left, *right;
    Node(int val, Node *left = nullptr, Node *right = nullptr) : val{val}, left{left}, right{right} {}
};

Node* insert(Node* root, int val) {
    if(root == nullptr) {
        return new Node(val);
    }
    if(root -> val > val) {
        root -> left = insert(root -> left, val);
    }
    else {
        root -> right = insert(root -> right, val);
    }
    return root;
}

bool is_tree_same(Node* a, Node* b) {
    if(a == nullptr && b == nullptr) {
        return true;
    }
    if(a == nullptr ^ b == nullptr) {
        return false;
    }
    return is_tree_same(a -> left, b -> left) && is_tree_same(a -> right, b -> right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int k;
    cin >> k;
    vector<Node*> a(0);
    for(int i = 0; i < n; i++){
        Node* root = nullptr;
        for(int j = 0; j < k; j++){
            int next;
            cin >> next;
            root = insert(root, next);
        }
        a.push_back(root);
    }
    vector<Node*> unique(0);
    for(int i = 0; i < a.size(); i++){
        Node* cur = a[i];
        bool is_unique = true;
        for(int j = 0; j < unique.size(); j++){
            if(is_tree_same(cur, unique[j])) {
                is_unique = false;
            }
        }
        if(is_unique) {
            unique.push_back(cur);
        }
    }
    cout << unique.size() << "\n";
    
    return 0;
}
