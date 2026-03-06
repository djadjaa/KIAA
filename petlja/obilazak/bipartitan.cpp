#include <bits/stdc++.h>

using namespace std;

struct Graph{
    private:
    int V;
    vector<vector<int>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    void bipartitanDFS(){
        bool moguceformiranje = true;
        vector<int> oznake(V,-1); //smestamo rezultate
        int id=0;
        stack<int> s;
        s.push(0);

        //inicijalna boja
        oznake[0]=0;

        while(!s.empty() && moguceformiranje){
            int tmp = s.top();
            s.pop();

            //suprotna boja
            id = 1-oznake[tmp];

            for(int sused: susedi[tmp]){
                if(oznake[sused]!=-1 && oznake[sused]!=id){ //ako je boja dodeljena i razlikuju im se boje
                    moguceformiranje=false;
                    break;
                }

                if(oznake[sused]==-1){ //ako boja nije dodeljena
                    oznake[sused]=id; //dodeljujemo onu koja je suprotna od one koje ima roditelj
                    s.push(sused);
                }
            }
        }
        if(moguceformiranje){
            for(int i=0; i<V; i++){
                if(oznake[0]==oznake[i])
                    cout << i << ' ';
            }
        }else
            cout << '-';
        cout<<  endl;
    }

    
};

int main(){

    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    for(int i=0; i<m; i++){
        int u,v;
        cin >> u >> v;
        G->dodajGranu(u,v);
    }
    G->bipartitanDFS();
    return 0;
}