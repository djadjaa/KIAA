//BFS
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;

    /*kako je dijametar najveca udaljenost od jednog do drugog cvora, 
    napravicemo bfs algoritam kao privatnu metodu
    i primeniti je u racunanju dijametra

    odradjicemo bfs od cvora u do v pa od cvora v do proizvoljnog cvora
    pa napraviti udaljenost izmedju ta dva 

    posto mi trazimo dijametar izmedju u i v, uradicemo rastojanje od pocetka do u pa od u do v 
    */

    private:
    //prvi clan je poslednji cvor odn najdalji cvor od onog odakle zapocinjemo BFS
    //drugi je udaljenost izmedju ta dva cvora
    pair<int, int> bfs(int node){
        vector<int> rastojanja(V,-1);

        queue<int> q;
        q.push(node); //ubacujemo prvo cvor odakle pocinjemo bfs
        rastojanja[node] = 0;

        int poslednjiposecen = node;

        while(!q.empty()){
            int prvi = q.front();
            q.pop();

            for(auto drugi : susedi[prvi]){
                //ako nismo posetili cvor
                if(rastojanja[drugi] == -1){
                    //skacemo na njega i ubacujemo ga u red rastojanja
                    rastojanja[drugi] = rastojanja[prvi] + 1;
                    q.push(drugi);
                    poslednjiposecen = drugi;
                }
            }
        }
        return {poslednjiposecen, rastojanja[poslednjiposecen]};
    }

    public:
    //konstruktor
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void addEdge(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    int diameter(){
        /*trazimo najudaljeniji cvor od 0, 
        u ovom slucaju ignorisemo udaljenost od 0 do tog cvora 
        jer je udaljenost sam taj cvor koji razmatramo*/
        auto [prvikraj, _] = bfs(0);
        auto [drugikraj, dijametar] = bfs(prvikraj);
        return dijametar;
    }
};

int main(){

    int V;
    cin >> V;

    Graph *G = new Graph(V);

    int u,v;
    for(int i=0; i<V-1; i++){
        cin >> u >> v;
        G->addEdge(u,v);
    }
    cout << G->diameter() << endl;
    delete G;
    return 0;
}