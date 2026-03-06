#include <bits/stdc++.h>

using namespace std;
struct comparator
{
  bool operator()(const pair<int, double> &p1, const pair<int, double> &p2)
  {
    return p1.second > p2.second;
  }
};


class Graph{
    private:
    int V;
    vector<vector<pair<int,double>>> susedi; //cuvamo i grane
    vector<bool>pronadjen;
    vector<double>rastojanje;
    vector<int>put;

    public:
    Graph(int V){
        this->V = V;
        rastojanje.resize(V,numeric_limits<double>::infinity());
        pronadjen.resize(V,false);
        susedi.resize(V);
        put.resize(V,-1);
    }

    void dodajGranu(int u,int v, double w){
        susedi[u].emplace_back(v, w);
        susedi[v].emplace_back(u, w);

        /*
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});*/
    }

    double Dajkstra(int u,int v){
        priority_queue<pair<int,double>,vector<pair<int,double>>,comparator>pq;

        rastojanje[0]=0;
        pq.push({u,rastojanje[0]});

        while(!pq.empty()){
            auto [cvor,tezina] = pq.top();
            pq.pop();

            if(pronadjen[cvor])
                continue;
            pronadjen[cvor]=true;
            if(cvor==v)
                return tezina;
            for(auto &[sused,tezinasused] : susedi[cvor]){
                double novatezina = tezina+tezinasused;
                if(novatezina < rastojanje[sused]){
                    rastojanje[sused] = novatezina;
                    put[sused]= cvor;
                    pq.push({sused,novatezina});
                }
            }
        }
        return -1;
    }

    void ispisi(int start, int end){
        double res = Dajkstra(start,end);
        if(res==-1)
            cout << "ne\n";
        else{
            cout << fixed << showpoint << setprecision(5)
            << res << endl;
            stack<int>s;
            int node = end;
            while(node!=-1){
                s.push(node);
                node = put[node];
            }
            while(!s.empty()){
                cout << s.top() << ' ';
                s.pop();
            }
            cout << endl;
        }
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin >> n >> m;
    Graph *G = new Graph(n);
    int u,v;
    double w;
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        G->dodajGranu(u,v,w);
    }
    int start,end;
    cin >> start >> end;
    G->ispisi(start,end);
    delete G;
    return 0;
}