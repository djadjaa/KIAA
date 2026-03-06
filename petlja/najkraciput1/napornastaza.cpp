#include <bits/stdc++.h>
using namespace std;


int main() {

    int m,n;
    cin >> m>> n;
    vector<vector<int>>mat(m,vector<int>(n));
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++)
            cin >> mat[i][j];
    }
    vector<vector<int>>rastojanja(m,vector<int>(n,INT_MAX));
    rastojanja[0][0]=0;
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>>pq;

    /*
    (x-1, y) – gore
    (x+1, y) – dole
    (x, y-1) – levo
    (x, y+1) – desno
    */
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    pq.push({0,0,0});
    while(!pq.empty()){
        auto [x,y,d] = pq.top();
        pq.pop();

        if(x==m-1 && y==n-1)
            break; //stigli smo do donjeg desnog elem
        if(d>rastojanja[x][y])
            continue;
        for(int dir=0; dir<4; dir++){
            int nx = x+dx[dir];
            int ny =y+dy[dir];
            if(nx<0 || nx>=m || ny<0 || ny>=n)
                continue;
            int ivica = abs(mat[x][y]-mat[nx][ny]);
            int novorast = max(d,ivica);
            if(novorast < rastojanja[nx][ny]){
                rastojanja[nx][ny] = novorast;
                pq.push({nx,ny,novorast});
            }

        }
    }
    cout << rastojanja[m-1][n-1] << endl;
    return 0;
}