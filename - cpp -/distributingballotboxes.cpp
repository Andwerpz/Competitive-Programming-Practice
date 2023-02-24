#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 06 D

//basically, each city has a certain population, p[i], and you can assign one or more ballot boxes to each city. 

//the maximum amount of people going to each ballot box in the ith city is ceil(p[i] / num ballot boxes). 

//so, assign the ballot boxes one by one to the city with the highest maximum amount of people going to one ballot box. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, b;
    cin >> n >> b;
    while(n != -1){
        priority_queue<tuple<int, int, int>> p;
        b -= n;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            p.push({a, a, 1});
        }
        for(int i = 0; i < b; i++){
            tuple<int, int, int> next = p.top();
            p.pop();
            int amt = get<1>(next);
            int boxes = get<2>(next) + 1;
            int max = amt / boxes + (amt % boxes == 0? 0 : 1);
            p.push({max, amt, boxes});
        }
        cout << get<0>(p.top()) << "\n";
        cin >> n >> b;
    }
    
    return 0;
}
