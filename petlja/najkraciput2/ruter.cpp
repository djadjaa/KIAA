/*
Znači — ne traži se skraćenje puta od 0 do n−1,
nego se traži maksimalno skraćenje između bilo koja dva povezana čvora!

*/

#include <bits/stdc++.h>
using namespace std;
const int INF = numeric_limits<int>::max();
/*
struct comparator{
    bool operator()(const pair<int,int> &p1, const pair<int, int> &p2){
        return p1.first > p2.first;
    }
};
*/
class Graph{
    private:
    int V;
    vector<vector<pair<int,int>>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v, int w){
        susedi[u].push_back({v,w});
    }

    int Dajkstra(){
        int res = 0;
        for(int cvor = 0; cvor < V; cvor++){
            /*
            Za svako polazno čvorište i:
            Izračunaju najkraća rastojanja od i do svih drugih čvorova (minVremeOdI).
            */
            vector<int> minVreme(V,INF); //vektor rastojanja
            vector<bool> pronadjen(V,false);

            priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;

            minVreme[cvor]  = 0;
            pq.push({minVreme[cvor],cvor});

            while(!pq.empty()){
                auto [vreme,tmp] = pq.top();
                pq.pop();

                if(pronadjen[tmp])
                    continue;
                pronadjen[tmp]=true;

                for(auto [sused,susedvreme] : susedi[tmp]){
                    int newvreme = susedvreme+vreme;
                    if(!pronadjen[sused] && newvreme < minVreme[sused]){
                        minVreme[sused] = newvreme;
                        pq.push({minVreme[sused], sused});
                    }
                }
            }
            /*
            Onda za svaku granu (i, j, w) uporede:
            skracenje = w - minVreme[j]
            i uzima se maksimum od tih skracenja
            */
            for(const auto[susedcvor,susedcvorvreme] : susedi[cvor])
                res = max(res,susedcvorvreme-minVreme[susedcvor]);
            
        }
        return res;
    }
    
    
};

int main(){

    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        G->dodajGranu(u,v,w);
    }
    cout << G->Dajkstra() << endl;
    return 0;
}