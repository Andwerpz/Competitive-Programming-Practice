#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

struct HuffmanNode {
    HuffmanNode *zero, *one, *parent;
    HuffmanNode() : zero{nullptr}, one{nullptr}, parent{nullptr} {}
    HuffmanNode(HuffmanNode* zero, HuffmanNode* one) : zero{zero}, one{one}, parent{nullptr} {};
};

vector<vector<bool>> generate_huffman_coding(vector<ld>& prob) {
    vector<HuffmanNode*> nodes(0);
    priority_queue<pair<ld, int>> q;
    for(int i = 0; i < prob.size(); i++){
        HuffmanNode* node = new HuffmanNode();
        nodes.push_back(node);
        q.push({-prob[i], i});
    }
    while(q.size() > 1){
        int zero = q.top().second;
        ld zero_p = q.top().first;
        q.pop();
        int one = q.top().second;
        ld one_p = q.top().first;
        q.pop();
        HuffmanNode* parent = new HuffmanNode(nodes[zero], nodes[one]);
        nodes[zero] -> parent = parent;
        nodes[one] -> parent = parent;
        q.push({zero_p + one_p, nodes.size()});
        nodes.push_back(parent);
    }
    vector<vector<bool>> ans(0);
    for(int i = 0; i < prob.size(); i++){
        HuffmanNode* ptr = nodes[i];
        vector<bool> code(0);
        while(ptr -> parent != nullptr) {
            HuffmanNode* parent = ptr -> parent;
            code.push_back(parent -> one == ptr);
            ptr = parent;
        }
        ans.push_back(code);
    }
    return ans;
}

ld calc_average_code_length(vector<ld>& prob) {
    ld ans = 0;
    vector<vector<bool>> coding = generate_huffman_coding(prob);
    for(int i = 0; i < prob.size(); i++){
        ans += prob[i] * (ld) coding[i].size();
    }
    return ans;
}

