#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int redovi, kolone;
    vector<pair<int,int>> pomeraji;

    public:
    Graph(int redovi=8, int kolone=8){
        this->redovi = redovi;
        this->kolone = kolone;
        //ako si trenutno na (x,y), možeš da skočiš na (x+2, y+1), (x+2, y-1), …
        pomeraji = {{2,1}, {2,-1}, {-2,1}, {-2,-1},
        {1,2}, {1,-2}, {-1,2}, {-1,-2}};
        
    }

    bool uPolju(int x, int y){
        return x >= 1 && x<=redovi && y>=1 && y<=kolone;
    }

    int bfs(int x1, int y1, int x2, int y2){
    //vector<vector<bool>> posecen; - nije nam neophodno zbog rastojanja koji ce da se inicijalizuje na -1 ako polje nije poseceno
    //cuva minimalan broj poteza od starta do (x,y)
        vector<vector<int>> rastojanje(redovi+1, vector<int>(kolone+1,-1));
        //ako se nalazi uveliko na cilju
        if(x1==x2 && y1==y2)
            return 0;
        //bfs:
        queue<pair<int,int>> q;
        q.push({x1,y1});
        rastojanje[x1][y1] = 0; //obidjeno

        while(!q.empty()){
            auto [x,y] = q.front();
            q.pop();
            //jedan od mogucih poteza:
            for(auto [dx,dy] : pomeraji){
                //nove pomerene pozicije
                int nx = x+dx;
                int ny = y+dy;
                if(uPolju(nx,ny) && rastojanje[nx][ny]==-1){
                    rastojanje[nx][ny] = rastojanje[x][y] + 1;
                    if(nx == x2 && ny == y2) //ako smo stigli do cilja
                        return rastojanje[nx][ny];
                    q.push({nx,ny});
                }
            }
        }
        return -1; //ako je nemoguce;
    }

};
int main() {

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