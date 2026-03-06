#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m;
    cin >> n >> m;
    cin.ignore(); // da obriše \n posle m

    vector<vector<char>> tastatura(n, vector<char>(m));
    unordered_map<char, vector<pair<int,int>>> pozicije;

    for(int i=0;i<n;i++){
        string red;
        getline(cin, red); // čita ceo red, uključujući *
        for(int j=0;j<m;j++){
            tastatura[i][j] = red[j];
            pozicije[red[j]].push_back({i,j});
        }
    }

    string tekst;
    cin >> tekst;

    int res = 0;
    pair<int,int> trenutnaPoz = {0,0};

    for(char c : tekst){
        if(tastatura[trenutnaPoz.first][trenutnaPoz.second]==c){
            res++;
            continue;
        }

        queue<pair<int,int>> q;
        vector<vector<int>> dist(n, vector<int>(m, -1));
        q.push(trenutnaPoz);
        dist[trenutnaPoz.first][trenutnaPoz.second] = 1; // prvi pritisak

        bool nadjeno = false;

        while(!q.empty() && !nadjeno){
            auto [x,y] = q.front();
            q.pop();

            for(auto [dx,dy] : vector<pair<int,int>>{{-1,0},{1,0},{0,-1},{0,1}}){
                int nx = x+dx;
                int ny = y+dy;

                if(nx>=0 && nx<n && ny>=0 && ny<m && dist[nx][ny]==-1){
                    dist[nx][ny] = dist[x][y]+1;
                    if(tastatura[nx][ny]==c){
                        res += dist[nx][ny];
                        trenutnaPoz = {nx,ny};
                        nadjeno = true;
                        break;
                    }
                    q.push({nx,ny});
                }
            }
        }
    }

    cout << res << endl;
    return 0;
}
