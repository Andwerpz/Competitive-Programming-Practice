#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1852C

//i read the editorial, and idk why and how this works D:

//let's say that we know how many times each octopus regenerates. Then, we can denote each
//of their total healths in the array 'c', where c[i] = a[i] + r[i] * k, where r
//is the amount of times each one regenerates. 

//in this case, the answer is simply all the positive differences of c[i + 1] - c[i]. 

//how can we efficiently determine the values in c? First, notice that any two adjacent
//values in c have to differ by less than k. If they differ by more, we could just always make a 
//better answer by subtracting k from some range. 

//so, if we determined c[i], then there are at most 2 choices for c[i + 1], either going 'up', or
//'down'. We can employ a greedy method to then solve this problem:

//we keep track of where we currently are in 'cur'. Initially, cur := a[0]. Then, for each i from
//1 to n - 1, we try to make it so that we move 'down' from cur to c[i]. If a[i] < (cur % k), then
//we can already just move down from cur to c[i]. Otherwise, we must change some other transition before
//i, so that it moves upwards. We always want to change the one that will add the minimum, so we maintain
//a priority queue to tell us what's the transition that when changed to move upwards will add the 
//minimum to the answer. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            a[i] %= k;
        }
        priority_queue<ll> add;
        ll ans = a[0];
        ll cur = a[0];
        for(int i = 1; i < n; i++){
            ll next = a[i];
            if(next < cur) {
                ll diff = cur - next;
                next += (diff / k) * k;
            }
            if(next <= cur) {
                //we can just go down
                ll diff = cur - next;
                add.push(-(k - diff));
            }
            else {
                //we have to go up
                add.push(-(next - cur));
                ans += -add.top();
                add.pop();
            }
            cur = next;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
