#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int redovi, kolone;
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
        //ovde cuvamo koliko puta idemo do zeljenog cilja
        vector<vector<int>> rastojanja(redovi+1,vector<int>(kolone+1,-1));
        queue<pair<int,int>> q;
        q.push({x1,y1});
        //pocetak
        rastojanja[x1][y1]=0;
        //ako smo vec na cilju vracamo 0
        if(x1==x2 && y1==y2)
            return 0;
        while(!q.empty()){
            auto [x,y] = q.front();
            q.pop();
            //formiramo puteve
            for(auto [dx,dy] : pomeraji){
                int nx = x+dx;
                int ny = y+dy;
                //ako nismo obelezili da postoji put
                if(uOpsegu(nx,ny) && rastojanja[nx][ny]==-1){
                    //azuriramo da put postoji
                    rastojanja[nx][ny] = rastojanja[x][y]+1;
                    //ako smo stigli do cilja
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
    while (n--)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        cout << G->bfs(x1,y1,x2,y2) << endl;
    }
    

    return 0;
}