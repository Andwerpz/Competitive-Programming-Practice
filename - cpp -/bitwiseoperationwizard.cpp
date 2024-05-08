#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//Codeforces - 1936A

//if we have a permutation from 0 to n - 1, then the greatest xor sum we can make from two elements
//is (1 << b) - 1, where (1 << b) is the most significant bit of n - 1. Essentially, we can turn every
//bit on. 

//to solve, we have a 3 step process: first we find the greatest element. This just ensure that we find
//an element that has the most significant bit. This can be done in n - 1 queries. 

//next, we find the list of all elements in the permutation that when or'd with the greatest element
//will maximize the value. n - 1 queries as well. 

//finally, out of all the elements in the above list, we get the minimum one. The minimum element 
//shouldn't have any overlapping bits with the maximum element. This can be done in around n - 1 queries

//our answer is simply the maximum element and our minimum element. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        //find greatest element
        int g_ind = 0;
        for(int i = 1; i < n; i++){
            cout << "? " << g_ind << " " << g_ind << " " << i << " " << i << endl;
            char v;
            cin >> v;
            if(v == '<') {
                g_ind = i;
            }
        }
        //find set of elements that will maximize the or sum with the greatest element
        vector<int> g_list(1, 0);
        for(int i = 1; i < n; i++){
            cout << "? " << g_ind << " " << g_list[0] << " " << g_ind << " " << i << endl;
            char v;
            cin >> v;
            if(v == '<') {
                g_list.clear();
                g_list.push_back(i);
            }
            else if(v == '=') {
                g_list.push_back(i);
            }
        }
        //find the minimum of the set of aforementioned elements
        int l_ind = g_list[0];
        for(int i = 1; i < g_list.size(); i++){
            cout << "? " << l_ind << " " << l_ind << " " << g_list[i] << " " << g_list[i] << endl;
            char v;
            cin >> v;
            if(v == '>') {
                l_ind = g_list[i];
            }
        }
        cout << "! " << g_ind << " " << l_ind << endl;
    }
    
    return 0;
}
