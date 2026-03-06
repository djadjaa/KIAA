//Primov algoritam
/*
svodimo ovaj problem neusmerenim tezinskim grafom, gde su cvorovi
gradovi, grane konekcije a tezine grana cene odrzavanja

posto ne moraju svi gradovi biti povezani na pocetku mozemo imati vise
komponenti povezanosti i tim povodom trazimo minimalno razapinjuce stablo
za svaku od komponenti povezanosti 

minimalno razapinjuce stablo je takav podgraf koji ima najmanju ukupnu
sumu tezina grana
*/
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

class Graph{
    private:
    int V;
    //za svaki cvor cuvamo sused i tezinu grane
    vector<vector<pair<int,int>>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u,int v, int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    int Prim(){
        //cuvamo cvor kandidata (kog bi trebalo ubaciti u minimalno razapinjuce drvo) i tezinu grane
        priority_queue<pair<int,int>,vector<pair<int,int>>, greater<pair<int,int>>> pq;
        vector<int> kljuc(V,INF); //pamti minimalnu tezinu grane kojom je svaki cvor povezan sa trenutno izgradjenim minimalno razapinjucem drvetom
        vector<bool> pripadaMinimalnomRazapinjucem(V,false);
        int ukTezina=0;

        for(int start = 0; start<V; ++start){
            if(!pripadaMinimalnomRazapinjucem[start]){
                pq.push(make_pair(0,start));
                kljuc[start] = 0;

                while(!pq.empty()){
                    int tmp = pq.top().second;
                    pq.pop();
                    if(pripadaMinimalnomRazapinjucem[tmp])
                        continue;
                    pripadaMinimalnomRazapinjucem[tmp] = true;
                    ukTezina+= kljuc[tmp];

                    for(auto&[sused,tezina]:susedi[tmp]){
                        if(!pripadaMinimalnomRazapinjucem[sused] && kljuc[sused]>tezina){
                            kljuc[sused]=tezina;
                            pq.push(make_pair(kljuc[sused],sused));
                        }
                    }
                }
            }
        }
        return ukTezina;
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    for (int i = 0; i < m; ++i) {
       int u, v, w;
       cin >> u >> v >> w;
       G->dodajGranu(u-1, v-1, w); 
    }
    cout << G->Prim() << endl;
 
    delete G;
    return 0;
}