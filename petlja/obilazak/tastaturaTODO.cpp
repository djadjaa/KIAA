#include <bits/stdc++.h>

using namespace std;

int main(){

    int n,m;
    cin >> n >> m;
    //nije neophodna klasa
    vector<vector<char>> tastatura(n,vector<char>(m));
    unordered_map<char, vector<pair<int,int>>> pozicije;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> tastatura[i][j];
            pozicije[tastatura[i][j]].push_back({i,j});
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

        //bfs:
        //prvi elem je par pozicija, drugi elem je koliko pritiska ima na to dugme
        queue<pair<int,int>> q;
        
        vector<vector<int>> rastojanje(n, vector<int>(m,-1));
        int minBrPritisaka = INT_MAX;

        for(const auto &p : pozicije[c]){
            q.push({p,1}); //za prvo dugme je 1 pritisak
            posecen[p.first][p.second]=true;
        }

        while(!q.empty()){
            auto [dugme,pritisci] = q.front();
            q.pop();

            if(tastatura[dugme.first][dugme.second]==c){
                minBrPritisaka = pritisci+1;
                trenutnaPoz = dugme;
                break;
            }
            //za svaki pomeraj:
            for(auto [dx,dy] : vector<pair<int,int>>{{-1,0},{1,0},{0,-1},{0,1}}){
                int nx = dugme.first + dx;
                int ny = dugme.second + dy;
                if(nx >= 0 && nx < n && ny>=0 && ny<m && !posecen[nx][ny]){
                    posecen[nx][ny] = true;
                    q.push({{nx,ny},pritisci+1});
                }
            }
        }
        /*
        if(minBrPritisaka!=INT_MAX){
            res += minBrPritisaka;
            //trenutnaPoz = {trenutnaPoz.first,trenutnaPoz.second};
        }*/
       res+=minBrPritisaka;
    }
    cout << res << endl;
    return 0;
}