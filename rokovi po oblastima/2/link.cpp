/*
 zadati su linkovi ka stranicama (usmerene grane),
naći prosečan broj klikova koji je potreban za svaku stranicu ako 
uzmemo u obzir da ne postoje linkovi na samog
sebe kao ni stranice koje nisu povezane
*/

#include <bits/stdc++.h>
using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<bool> posecen;
    vector<int>rastojanje;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        posecen.resize(V,false);
        rastojanje.resize(V,-1);
    }

    void addEdge(int u, int v){
        susedi[u].push_back(v);
    }

    void bfs(){
        vector<double> avg(V);
        int sum=0;
        int brObradjenih=0;
        for(int i=0; i<V; i++){
            queue<int> q;
            rastojanje[i] = 0;
            posecen[i] = true;
            q.push(i);
            while(!q.empty()){
                int tmp = q.front();
                q.pop();
                for(int sused : susedi[tmp]){
                    if(posecen[sused])
                        continue;
                    posecen[sused] = true;
                    rastojanje[sused] = rastojanje[tmp]+1;
                    sum+=rastojanje[sused];
                    brObradjenih++;
                    q.push(sused);
                }
            }
            avg[i] = (double)sum/brObradjenih;
        }
        cout << avg[avg.size()-1] << endl;
    }
};

int main(){
    Graph *g = new Graph(4);

    g->addEdge(0, 1);
    g->addEdge(0, 2);
    g->addEdge(1, 2);
    g->addEdge(2, 3);
    g->addEdge(3, 0);

    g->bfs();    

    return 0;
}