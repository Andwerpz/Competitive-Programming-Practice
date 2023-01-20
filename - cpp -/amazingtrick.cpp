#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1773A

//we can try to randomly generate p permutations, and build the q permutation based off of the generated p permutation. 

//how can we make a permutation, b, so that we can take an arbitrary permutation, x, and make x[b[i]] = i true?
//well, if b[x[i]] = i is true, then x[b[i]] = i is also true. Replacing x[i] with a[p[i]], and b with q, we get 
//a[p[q[i]]] = i if q[a[p[i]]] = i. We can use this to generate q based off of a and p. 

//what is the probability of generating a p permutation with no fixed points?
//according to sources, the probability is around e^-1, so we should have enough time to generate them randomly. 

//now if n <= 4, then there is a chance that there is no solution, so we should just try all of them. 
//or we can be lazy and just generate them until we generated around 1000 or so, and call it quits if we didn't find a 
//valid permutation. 

void randomizePermutation(vector<int>& a) {
    for(int i = 0; i < a.size() - 1; i++){
        int ind = rand() % (a.size() - i) + i;
        int temp = a[i];
        a[i] = a[ind];
        a[ind] = temp;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] --;
        }
        vector<int> p(n);
        for(int i = 0; i < n; i++){
            p[i] = i;
        }
        vector<int> q(n);
        bool isValid = false;
        int cnt = 0;
        while(n > 4 || (n <= 4 && cnt != 1000)){
            cnt ++;
            randomizePermutation(p);
            isValid = true;
            for(int i = 0; i < n; i++){
                if(p[i] == i || a[p[i]] == i){
                    isValid = false;
                    break;
                }
                q[a[p[i]]] = i;
            }
            if(isValid){
                break;
            }
        }
        if(!isValid){
            cout << "Impossible\n";
            continue;
        }
        cout << "Possible\n";
        for(int i = 0; i < n; i++){
            cout << p[i] + 1 << " ";
        }
        cout << "\n";
        for(int i = 0; i < n; i++){
            cout << q[i] + 1 << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
