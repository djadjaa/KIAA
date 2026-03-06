//primena Dajkstre
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<pair<int, pair<int, int>>>> susedi;
    /*
    [0,[{1,{2,2}}]]
    za svaki cvor cuvamo sused koji je predstavljen kao par:
    prvi - taj sused
    drugi - rastojanje i cena od cvora do suseda
    */

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u,int v, int rastojanje, int cena){
        susedi[u].push_back({v,{rastojanje,cena}});
        susedi[v].push_back({u,{rastojanje,cena}});
    }

    void dajkstra(int src, int dest, int budzet){
        /*
        red sa prioritetom trojki celih brojeva u koji ćemo ubacivati čvor do kog vodi tekuća grana, 
        ukupnu dužinu, kao i cenu koja se dostiže koristeći datu granu. 
        Red će sortirati elemente prvo po dužini, a zatim po ceni
        */
        priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
        vector<int>rastojanja(V,numeric_limits<int>::max()); //inicijalizacija
        vector<int> minCena(V,numeric_limits<int>::max());

        pq.push({0,0,src});
        rastojanja[src] = 0;
        minCena[src] = 0;

        while(!pq.empty()){
            auto [trenutnoRast, trenutnaCena, trenutniCvor] = pq.top();
            pq.pop();

            if(trenutniCvor==dest){
                cout << trenutnoRast << ' ' << trenutnaCena << endl;
                return;
            }

            if(trenutnoRast > rastojanja[trenutniCvor] || trenutnaCena > minCena[trenutniCvor])
                continue;
            
            for(auto &[sused, tezine] : susedi[trenutniCvor]){
                auto [tmprast, tmpcena] = tezine;
                int sledeceRastojanje = trenutnoRast+tmprast;
                int sledecaCena = trenutnaCena + tmpcena;

                if(sledecaCena <= budzet && (sledeceRastojanje<rastojanja[sused] || sledecaCena<minCena[sused])){
                    rastojanja[sused] = sledeceRastojanje;
                    minCena[sused] = sledecaCena;
                    pq.push({sledeceRastojanje,sledecaCena,sused});
                }
            }
        }
        cout <<"-"<<endl;
    }
};

int main(){
    int n, m;

    cin >> n >> m;
 
    Graph *G = new Graph(n);
 
    int u, v, d, c;
    for (int i = 0; i < m; i++) {
       cin >> u >> v >> d >> c;
       G->dodajGranu(u, v, d, c);
    }
 
    int src, dest, budget;
    cin >> src >> dest >> budget;
 
    G->dajkstra(src, dest, budget);
 
    delete G;

    return 0;
}