#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 11 A

//interesting max flow problem

//we can use edges in the graph to 'enforce' some of the rules in the problem. 

//there are 4 rules: 
// - Each club gets one representative
// - Each person can only represent clubs they are in
// - Each person can only be the representative of 1 club
// - Each party cannot make up half or more of the entire council

//to enforce the first rule, we can draw edges of capacity 1 from the source to nodes that represent each of the clubs. 
//to enforce the second rule, draw edges of capacity 1 from each club node, to all of the people in that club
//to enforce the third rule, split each person node into two nodes, and draw between them an edge of capacity 1
//to enforce the fourth rule, connect all of the people nodes to nodes of their parties, and from the party nodes, connect them to the sink
//with edges of capacity numClubs - (numClubs % 2 == 0)

vector<pair<int, ll>> edges;
vector<vector<int>> adj;

ll dinic(int n, vector<vector<pair<int, ll>>> c, int source, int sink) {
    ll ans = 0;
    //redo organization of edges
    edges = vector<pair<int, ll>>(0);
    adj = vector<vector<int>>(n, vector<int>(0));
    int m = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j].first;
            ll cap = c[i][j].second;
            adj[u].push_back(m);
            adj[v].push_back(m + 1);
            edges.push_back({v, cap});
            edges.push_back({u, 0});
            m += 2;
        }
    }
    while(true) {
        //create level graph
        vector<int> level(n, -1);
        queue<int> q;
        vector<bool> v(n, false);
        v[source] = true;
        q.push(source);
        level[source] = 0;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < adj[cur].size(); i++) {
                int nEdge = adj[cur][i];
                int next = edges[nEdge].first;
                if(v[next]) {
                    continue;
                }
                if(edges[nEdge].second == 0){
                    //no flow
                    continue;
                }
                v[next] = true;
                q.push(next);
                level[next] = level[cur] + 1;
            }
        }
        if(!v[sink]){
            //we're done here
            break;
        }
        while(true) {
            //do dfs until there is no path from source to sink along level graph
            stack<int> s;
            s.push(source);
            stack<int> est;
            stack<int> ist;
            ist.push(0);
            while(s.size() != 0){
                int cur = s.top();
                if(cur == sink) {   
                    //we've found path from source to sink
                    break;
                }
                bool foundNext = false;
                for(int i = ist.top(); i < adj[cur].size(); i++){
                    int nEdge = adj[cur][i];
                    int next = edges[nEdge].first;
                    if(level[next] <= level[cur]){
                        continue;
                    }
                    if(edges[nEdge].second == 0){
                        continue;
                    }
                    s.push(next);
                    est.push(nEdge);
                    ist.pop();
                    ist.push(i + 1);
                    ist.push(0);
                    foundNext = true;
                    break;
                }
                if(!foundNext) {
                    s.pop();
                    ist.pop();
                    if(est.size() != 0){
                        est.pop();
                    }
                    //mark this node as a dead end
                    level[cur] = -1;
                }
            }
            if(s.size() != 0 && s.top() == sink) {
                //found a path yay, now we update flow for edges on path
                ll bn = 1e18;
                vector<int> path(est.size(), 0);
                for(int i = 0; i < path.size(); i++){
                    path[i] = est.top();
                    est.pop();
                    bn = min(bn, edges[path[i]].second);
                }
                for(int i = 0; i < path.size(); i++){
                    //forward edge
                    edges[path[i]].second -= bn;
                    //backwards edge
                    edges[path[i] ^ 1].second += bn;
                }
                ans += bn;
            }
            else {
                //the maximum flow for this level configuration has been reached. 
                break;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int ptr = 0;
        vector<int> peopleIn(n);
        vector<int> peopleOut(n);
        map<string, int> peopleMap;
        map<string, int> clubMap;
        map<string, int> partyMap;
        map<int, vector<int>> peopleClubs;
        map<int, int> peopleParties;
        for(int i = 0; i < n; i++){
            string name;
            cin >> name;
            peopleMap.insert({name, ptr ++});
            peopleIn[i] = peopleMap.find(name) -> second;
            peopleOut[i] = ptr ++;
            string partyName;
            cin >> partyName;
            if(partyMap.find(partyName) == partyMap.end()) {
                partyMap.insert({partyName, ptr ++});
            }
            peopleParties.insert({peopleIn[i], partyMap.find(partyName) -> second});
            int cCnt;
            cin >> cCnt;
            peopleClubs.insert({peopleMap.find(name) -> second, {}});
            for(int j = 0; j < cCnt; j++){
                string clubName;
                cin >> clubName;
                if(clubMap.find(clubName) == clubMap.end()) {
                    clubMap.insert({clubName, ptr ++});
                }
                peopleClubs.find(peopleIn[i]) -> second.push_back(clubMap.find(clubName) -> second);
            }  
        }
        int source = ptr ++;
        int sink = ptr ++;
        vector<vector<pair<int, ll>>> c(ptr, vector<pair<int, ll>>(0));
        for(auto i = clubMap.begin(); i != clubMap.end(); i++){
            //edge from source to each club of flow 1
            //enforces each club gets 1 rep
            c[source].push_back({i -> second, 1});
            //cout << "FROM SINK : " << source << " " << i -> second << "\n";
        }
        for(int i = 0; i < n; i++){
            //edge from each club to every person they have
            //each club can choose reps from people in the club
            vector<int> clubs = peopleClubs.find(peopleIn[i]) -> second;
            for(int j = 0; j < clubs.size(); j++){
                int clubID = clubs[j];
                c[clubID].push_back({peopleIn[i], 1});
                //cout << "FROM CLUB : " << clubID << " " << peopleIn[i] << "\n";
            }
        }
        for(int i = 0; i < n; i++){
            //enforce each person can only be representative of one club
            //draw edge from person in node to person out node of flow 1
            c[peopleIn[i]].push_back({peopleOut[i], 1});
            //cout << "PEOPLE INTERNAL : " << peopleIn[i] << " " << peopleOut[i] << "\n";
        }
        for(int i = 0; i < n; i++){
            //link everyone to their political party
            c[peopleOut[i]].push_back({peopleParties.find(peopleIn[i]) -> second, 1});
            //cout << "PEOPLE OUT : " << peopleOut[i] << " " << peopleParties.find(peopleIn[i]) -> second << "\n";
        }
        for(auto i = partyMap.begin(); i != partyMap.end(); i++){
            //enforce each party cannot have numClubs / 2 or more reps
            int flow = clubMap.size() / 2 - (clubMap.size() % 2 == 0);
            if(flow < 0){
                flow = 0;
            }
            c[i -> second].push_back({sink, flow});
            //cout << "PARTY TO SINK : " << i -> second << " " << sink << " " << flow << "\n";
        }
        ll maxFlow = dinic(ptr, c, source, sink);
        //cout << "MAX FLOW : " << maxFlow << "\n";
        if(maxFlow != clubMap.size()) {
            cout << "Impossible.\n";
            continue;
        }
        map<int, string> peopleRMap;
        map<int, string> clubRMap;
        for(auto i = peopleMap.begin(); i != peopleMap.end(); i++){
            peopleRMap.insert({i -> second, i -> first});
        }
        for(auto i = clubMap.begin(); i != clubMap.end(); i++){
            clubRMap.insert({i -> second, i -> first});
        }
        for(auto i = clubMap.begin(); i != clubMap.end(); i++){
            int club = i -> second;
            for(int j = 0; j < adj[club].size(); j++){
                int nEdge = adj[club][j];
                int dest = edges[nEdge].first;
                ll flow = edges[nEdge].second;
                if(flow == 0){
                    cout << peopleRMap.find(dest) -> second << " " << clubRMap.find(club) -> second << "\n";
                }
            }
        }
    }
    
    return 0;
}
