#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Rocky Mountain Regional 2016 G

//simulation

//apparently you can also use dp to simulate

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[i][j];
        }
    }
    vector<bool> working(m, false);
    vector<priority_queue<int>> stage_pq(m, priority_queue<int>()); //{-part ind}
    priority_queue<pair<int, pair<int, int>>> worker_pq;   //{-time, {-stage ind, part ind}}
    for(int i = 0; i < n; i++){
        stage_pq[0].push(-i);
    }
    int init_part = -stage_pq[0].top();
    stage_pq[0].pop();
    worker_pq.push({-a[init_part][0], {0, init_part}});
    working[0] = true;
    vector<int> ans(n, -1);
    while(worker_pq.size() != 0){
        int stage = -worker_pq.top().second.first;
        int part_ind = worker_pq.top().second.second;
        int time = -worker_pq.top().first;
        worker_pq.pop();
        //cout << "WORKER DONE : " << time << " " << stage << " " << part_ind << "\n";
        working[stage] = false;
        //push to next stage
        if(stage != m - 1) {
            if(!working[stage + 1]) {
                //next stage isn't working, kickstart him
                //cout << "KICKSTART WORKER : " << stage + 1 << "\n";
                working[stage + 1] = true;
                worker_pq.push({-(time + a[part_ind][stage + 1]), {-(stage + 1), part_ind}});
            }
            else {
                //next stage is working, put into queue
                stage_pq[stage + 1].push({-part_ind});
            }
        }
        else {
            ans[part_ind] = time;
        }
        if(stage_pq[stage].size() == 0){
            //cout << "STAGE : " << stage << " OUT OF ITEMS\n";
            continue;
        }
        //work on new part
        working[stage] = true;
        int next_part_ind = -stage_pq[stage].top();
        stage_pq[stage].pop();
        worker_pq.push({-(time + a[next_part_ind][stage]), {-stage, next_part_ind}});
    }
    for(int i = 0; i < n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
