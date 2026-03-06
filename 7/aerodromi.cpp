/*
primena Dajkstre:
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

#define INFINITY numeric_limits<int>::max()

using namespace std;

struct poredjenje
{
  bool operator()(const pair<int, int> &p1, const pair<int, int> &p2)
  {
    return p1.first > p2.first;
  }
};

class Graph{
    private:
    int V;
    //lista suseda takva da za svaki sused se cuva info o indeksu susednog cvora i tezinu grane koja spaja polazni cvor sa susedom
    vector<vector<pair<int,int>>> susedi;
    vector<int> udaljenosti;
    vector<bool> nadjeniPutevi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        udaljenosti.resize(V,INFINITY);
        nadjeniPutevi.resize(V,false);
    }

    //w tezina
    void dodajGranu(int u,int v,int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
    }

    void reset(){
        fill(udaljenosti.begin(),udaljenosti.end(),INFINITY);
        fill(nadjeniPutevi.begin(),nadjeniPutevi.end(),false);
    }

    int Dajkstra(int u, int v, int izbegni){
        //hip vadi cvor sa trenutno najmanjom poznatom udaljenoscu <udaljenost,cvor>
        priority_queue<pair<int,int>,vector<pair<int,int>>,poredjenje> hip;
        //prvi cvor ima udaljenost nula ostali inf
        udaljenosti[u] = 0;
        hip.push(make_pair(udaljenosti[u],u));
        pair<int,int>tmp;//tmp.first je udaljenost od starta a tmp.second je indeks trenutnog cvora
        while(!hip.empty()){
            //tekuci cvor:
            tmp = hip.top();//uzimamo cvor sa najmanjom vrednoscu
            hip.pop();
            //ako smo ga vec obradili, ne obradjujemo ga ponovo
            if(nadjeniPutevi[tmp.second])
                continue;
            nadjeniPutevi[tmp.second] = true;
            /*lista_suseda[tmp.second] vraća listu svih suseda tog čvora, 
            gde je svaki sused predstavljen parom (čvor, težina_grane)
            indeks suseda nam je par:
            sused.first → indeks susednog čvora
            sused.second → težina grane od trenutnog čvora do tog suseda
            
            lista_suseda[0] = { {1, 4}, {2, 7} };
            čvor 1 tezina grane 4 itd
            */
            for(pair<int,int> &sused:susedi[tmp.second]){
                if(sused.first == izbegni)
                    continue;

                //Da li smo našli kraći put do čvora sused.first preko trenutnog čvora tmp.second nego što smo do sada imali?         
                if(udaljenosti[sused.first]>udaljenosti[tmp.second]+sused.second){
                    //Ako je uslov tačan, znači da je novi put kraći
                    udaljenosti[sused.first] = udaljenosti[tmp.second]+sused.second;
                    //Upisujemo tu vrednost kao novu najbolju (najkraću) poznatu udaljenost i indeks tog cvora cija mu je udaljenost manja
                    hip.push(make_pair(udaljenosti[sused.first],sused.first));
                }
            }
        }
        return udaljenosti[v];
    }

    int najjeftinijiLet(int u, int v, int idiDo, int izbegni){
        reset();
        int res = Dajkstra(u,idiDo,izbegni);
        reset();
        return res+Dajkstra(idiDo,v,izbegni);
    }
};

int main(){

    int n, m;

   cin >> n >> m;

   Graph *G = new Graph(n);

   int u, v, w;
   for (int i = 0; i < m; i++) {
      cin >> u >> v >> w;
      G->dodajGranu(u, v, w);
   }

   int q;
   cin >> q;

   int a, b, idi_do, izbegni;
   while (q--) {
      cin >> a >> b >> idi_do >> izbegni;
      cout << G->najjeftinijiLet(a, b, idi_do, izbegni) << "\n";
   }

   delete G;

    return 0;
}