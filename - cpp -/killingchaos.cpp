#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 03 C

//it takes a little thinking to turn this into a dsu problem, but once you got that, it's pretty straightforward. 

//the trick is to consider the problem in reverse. If you reverse the order of the train segments being destroyed, and
//just think of the robbers as adding the train segments to the train, you can think of the train as a linked list sort of graph
//and adding the train segment just adds edges to the train segments to each side of it. 

//come to think of it, you could probably just do this in the original order, it doesn't really matter huh. 

//i don't even think you need dsu, just some pfx sum and maps could work. 

const int N = 1e6;
vector<int> dsu(N, 0);
vector<int> amt(N, 0);

int find(int a) {
    if(dsu[a] == a) {
        return a;
    }
    return dsu[a] = find(dsu[a]);
}

bool unify(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if(ra == rb) {
        return false;
    }
    dsu[rb] = ra;
    amt[ra] += amt[rb];
    
    return true;
}

int ru(int a){
    return a % 10 == 0? a : a + 10 - a % 10;
}

int getAmt(int a){
    return ru(amt[find(a)]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> amt[i];
        dsu[i] = i;
    }
    vector<int> a(n, 0);
    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i] --;
    }
    reverse(a.begin(), a.end());
    ll ans = 0;
    vector<bool> v(n, false);
    ll cnt = 0;
    ll sum = 0;
    for(int i = 0; i < n; i++){
        int next = a[i];
        cnt ++;
        v[next] = true;
        sum += getAmt(next);
        if(next != n - 1 && v[next + 1]){
            sum -= getAmt(next);
            sum -= getAmt(next + 1);
            unify(next, next + 1);
            cnt --;
            sum += getAmt(next);
        }
        if(next != 0 && v[next - 1]) {
            sum -= getAmt(next);
            sum -= getAmt(next - 1);
            unify(next, next - 1);
            cnt --;
            sum += getAmt(next);
        }
        ans = max(ans, sum * cnt);
    }
    cout << ans << "\n";
    
    return 0;
}
