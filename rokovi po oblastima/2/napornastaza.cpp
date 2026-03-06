#include <bits/stdc++.h>

using namespace std;

int main(){

    int n,m;
    cin >> n >> m;
    vector<vector<int>> visine(n,vector<int>(m));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++)
            cin >> visine[i][j];
    }
    vector<vector<int>>rastojanja(n,vector<int>(m,numeric_limits<int>::max()));
    vector<vector<bool>>posecen(n,vector<bool>(m,false));

    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> pq;
    rastojanja[0][0] = 0;
    pq.push({0,0,0});
    while(!pq.empty()){
        auto [rast,u,v] = pq.top();
        pq.pop();

        if(posecen[u][v])
            continue;
        posecen[u][v] = true;

        int du[] = {-1,1,0,0};
        int dv[] = {0,0,-1,1};

        for(int i=0; i<4; i++){
            int DU = u+du[i];
            int DV = v+dv[i];
            if(!(DU>=0 && DU < n && DV >= 0 && DV < m))
                continue;
            if(posecen[DU][DV])
                continue;
            int novoRast = max(rastojanja[u][v],abs(visine[DU][DV]-visine[u][v]));
            if(novoRast < rastojanja[DU][DV]){
                rastojanja[DU][DV] = novoRast;
                pq.push({novoRast,DU,DV});
            }
        }
    }
    cout << rastojanja[n-1][m-1] << endl;
    return 0;
}