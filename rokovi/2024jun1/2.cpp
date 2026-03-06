/*
zadati su linkovi ka stranicama (usmerene grane),
naći prosečan broj klikova koji je potreban za svaku stranicu 
ako uzmemo u obzir da 
ne postoje linkovi na samog sebe kao 
ni stranice koje nisu povezane

-usmeren graf gde su cvorovi stranice, a linkovi grane
-trazimo prosecnu duzinu najkraceg puta od te stranice do ostalih stranica preko kojih moze da se dodje
-graf nije nuzno tezinski(ako postoji link tezina grane je 1 inace 0)
-racunamo samo prosecan br linkova ako postoji link izmedju tih stranica
-ne racunamo linkove koji su povezani na same sebe
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> rastojanje; //postojanje linka

    public:
    Graph(int V){
        this->V = V;
        rastojanje.resize(V, vector<int>(V,INT_MAX));
        for(int i=0; i<V; i++)
            rastojanje[i][i] = 0;
    }
    void addEdge(int u, int v, int w){
        rastojanje[u][v] = w;
    }
    void flojdVarsal(){
        for(int k=0; k<V; k++){
            for(int i=0; i<V; i++){
                for(int j=0; j<V; j++){
                    /*
                    Za svaku stranicu i računa se prosečna udaljenost 
                    do svih čvorova j koji su dostupni (tj. dist[i][j] != ∞ i i != j)
                    */
                   if(rastojanje[i][k]!=INT_MAX && rastojanje[k][j] != INT_MAX)
                        rastojanje[i][j] = min(rastojanje[i][j],rastojanje[i][k]+rastojanje[k][j]);
                }
            }
        }
    }
    void prosecanKlik(){
        for(int i=0; i<V; i++){
            int sum = 0, count = 0;
            for(int j=0;j<V; j++){
                //ako ne pokazuje stranica na samu sebe i postoji link na nju
                if(i!=j && rastojanje[i][j]!=INT_MAX){
                    sum+=rastojanje[i][j];
                    count++;
                }
            }
            if(count==0)
                cout << "nista\n";
            else{
                double avg = (double)sum/count;
                cout << i << ' ' << avg << endl;
            }
        }
    }

};

int main(){

    Graph *g = new Graph(4);

    g->addEdge(0, 1, 1);
    g->addEdge(0, 2, 1);
    g->addEdge(1, 2, 1);
    g->addEdge(2, 3, 1);
    g->addEdge(3, 0, 1);

    g->flojdVarsal();

    g->prosecanKlik();

    return 0;
}