/*
polupovezan -> ako imamo jedno od dva usmerenja
(kod komponenti jake povezanosti imamo obostrana usmerenja)
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<vector<int>> susediReverse;
    //lista suseda na nivou komponenti:
    vector<vector<int>> susediKomponente; //opisuje medjusobnu povezanost sused
    vector<bool>posecen;
    stack<int>odlaznaNumeracija;
    vector<int>komponente;
    vector<int>pozUTopSort;
    int brKomponente=0;

    void dfsDirect(int cvor){
        posecen[cvor] = true;
        for(int sused : susedi[cvor])
            if(!posecen[sused])
                dfsDirect(sused);
        //dfs za pamcenje pozicija zavrsetka obilaska radi formiranja komponente jake povezanosti u drugom dfsu
        odlaznaNumeracija.push(cvor);
    }

    void dfsReverse(int cvor,vector<bool>&posecen){
        posecen[cvor] = true;
        komponente[cvor] = brKomponente;
        for(int sused: susediReverse[cvor])
            if(!posecen[sused])
                dfsReverse(sused,posecen);
    }

    void nadjiKomponente(){
        fill(posecen.begin(),posecen.end(),false);
        for(int i=0; i<V; i++)
            if(!posecen[i])
                dfsDirect(i);
        fill(posecen.begin(),posecen.end(),false);
        while(!odlaznaNumeracija.empty()){
            int cvor = odlaznaNumeracija.top();
            odlaznaNumeracija.pop();
            if(!posecen[cvor]){
                dfsReverse(cvor,posecen);
                brKomponente++;
            }
        }
    }

    void DFSTopoloskoSort(int cvor, stack<int>&s){
        posecen[cvor] = true;

        for(int sused : susediKomponente[cvor]){
            if(!posecen[cvor])
                DFSTopoloskoSort(sused,s);
        }

        s.push(cvor);
    }

    void KanovAlg(){
        fill(posecen.begin(),posecen.end(),false);
        stack<int>s;
        for(int u=0; u<brKomponente; u++){
            if(!posecen[u])
                DFSTopoloskoSort(u,s);
        }
        while(!s.empty()){
            auto cvor = s.top();
            s.pop();

            pozUTopSort.push_back(cvor);
        }
    }

    void kompresovaniGraf(){
        //formiramo kondenzovani graf; ovo je lista suseda u kondenzovanom grafu
        //inicijalizacija:
        susediKomponente = vector<vector<int>>(brKomponente);
        /*dobijamo
        lista_suseda_komponente = [
            {},   // susedi komponente 0
            {},   // susedi komponente 1
            {}    // susedi komponente 2
        ]
        */
       //skup da spreči dupliranje grana između istih komponenti
        set<pair<int,int>> ubaceneGrane;

        for(int u=0; u<V; u++){
            for(auto v : susedi[u]){
                /*
                Proverava da li grana između dve komp jake povezanosti već postoji.
                Ako je već dodata, ne dodaje je ponovo.
                Ovo sprečava duple grane u kondenzovanom grafu.
                */
                if(komponente[u]!=komponente[v] && ubaceneGrane.count({komponente[u],komponente[v]})==0){
                    susediKomponente[komponente[u]].push_back(komponente[v]);
                    ubaceneGrane.emplace(komponente[u],komponente[v]);
                }
            }
        }
    }

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        susediReverse.resize(V);
        posecen.resize(V,false);
        komponente.resize(V);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susediReverse[v].push_back(u);
    }

    bool polupovezan(){
        nadjiKomponente();
        kompresovaniGraf();
        KanovAlg();

        for(int i=0; i<brKomponente-1; i++){
            auto tekuci = pozUTopSort[i];
            auto sledeci = pozUTopSort[i+1];

            bool povezan = false;

            for(auto sused:susediKomponente[tekuci]){
                if(sused == sledeci)
                    povezan =true;
            }
            if(!povezan)
                return false;
        }
        return true;
    }

};

int main(){
    int N, M, u, v;

    cin >> N >> M;
    Graph *G = new Graph(N);
    for(int i = 0; i < M; i++) {
        cin >> u >> v;
        G->dodajGranu(u, v); 
    }

    cout << (G->polupovezan() ? "Da" : "Ne") << endl;

    delete G;
    return 0;
}