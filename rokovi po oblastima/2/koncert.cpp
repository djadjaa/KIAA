//kljucni gradovi su artiklacione tacke
#include <bits/stdc++.h>
using namespace std;

vector<int> atmosfere;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;
    vector<int> disc;
    vector<int> low;
    vector<bool> posecen;
    vector<int> roditelj;
    vector<bool> artikulacione;
    int discoveryTime;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        disc.resize(V,-1);
        low.resize(V,-1);
        posecen.resize(V,false);
        artikulacione.resize(V,false);
        roditelj.resize(V,-1);
        discoveryTime=0;
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    void Tarjan(int cvor){
        int numChilds=0;
        posecen[cvor] = true;
        disc[cvor] = discoveryTime++;
        low[cvor] = disc[cvor];

        for(auto sused: susedi[cvor]){
            if(posecen[sused]){
                //ako sused nije potomak
                if(roditelj[cvor]!=sused)
                    low[cvor] = min(low[cvor],disc[sused]);
            }else{
                //ako sused jeste potomak
                numChilds++;
                roditelj[sused] = cvor;
                //dodeljujemo discoverytime i lowertime za susede
                Tarjan(sused);
                low[cvor] = min(low[cvor],low[sused]);

                //ako nismo u korenu i vazi sledece:
                //i L(v) >= d(U)
                if(roditelj[cvor]!=-1 && low[sused]>=disc[cvor])
                    artikulacione[cvor] = true;
            }
        }
        //ako smo u korenu to je automatski artikulaciona tacka
        if(roditelj[cvor]==-1 && numChilds>1)
            artikulacione[cvor] = true;
    }
    
    void res(){
        Tarjan(0);
        int sum=0;
        for(int i=0; i<artikulacione.size(); i++){
            if(artikulacione[i])
                sum += atmosfere[i];
        }

        if(sum>0)
            cout << "POZITIVNA ";
        else
            cout << "NEGATIVNA ";
        cout << sum << endl;
    }
};

int main(){
    int n,m;
    cin >> n >> m;
    atmosfere.resize(n);
    for(int i=0; i<n; i++)
        cin >> atmosfere[i];
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v;
        cin >> u >> v;
        G->dodajGranu(u,v);
    }
    G->res();
    return 0;
}