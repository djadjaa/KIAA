#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int redovi,kolone;
    vector<pair<int,int>> pomeraji;

    public:
    Graph(int redovi=8, int kolone=8){
        this->kolone = kolone;
        this->redovi = redovi;
        pomeraji = {{1,2}, {1,-2}, {-1,2}, {-1,-2},
        {2,1}, {2,-1}, {-2,1}, {-2,-1}};
    }

    bool uOpsegu(int x, int y){
        return x>=1 && x<=redovi && y>=1 && y<=kolone;
    }

    int bfs(int x1,int y1,int x2, int y2){
        vector<vector<int>> rastojanja(redovi+1,vector<int>(kolone+1,-1));
        queue<pair<int,int>> q;
        q.push({x1,y1});
        rastojanja[x1][y1]=0;
        if(x1==x2 && y1==y2)
            return 0;
        while(!q.empty()){
            auto [x,y] = q.front();
            q.pop();
            for(auto [dx,dy] : pomeraji){
                int nx = x+dx;
                int ny = y+dy;
                if(uOpsegu(nx,ny) && rastojanja[nx][ny]==-1){
                    rastojanja[nx][ny] = rastojanja[x][y] + 1;
                    if(nx==x2 && ny==y2)
                        return rastojanja[nx][ny];
                    q.push({nx,ny});
                }
            }
        }
        return -1;
    }
};

int main(){

    int n;
    cin >> n;
    Graph *G = new Graph(8,8);
    int x1,y1,x2,y2;
    while(n--){
        cin >> x1 >> y1 >> x2 >> y2;
        cout << G->bfs(x1,y1,x2,y2) << endl;
    }

    return 0;
}