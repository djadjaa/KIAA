//Flojd Varsal
/*
naivnija implementacija bi bila da uklanjamo cvor i pokrenemo flojd varsala
posle svake iteracije
efikasnije bi bilo dodavanje cvorova obratnim redosledom
zatim za ostatak cvorova pokrecemo flojd varsala
i na kraju azuriramo matricu najkraceg puta
*/

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>
#include <algorithm>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> susedi;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        for(int i=0; i<V; i++)
            susedi[i].resize(V);
    }

    void dodajGranu(int u,int v, int weight){
        susedi[u][v] = weight;
    }

    void flojdVarsal(vector<int> &poredakUklanjanja){
        //obrnemo prvo niz da bismo uklonili cvorove u obratnom poretku
        reverse(poredakUklanjanja.begin(),poredakUklanjanja.end());
        //aktivan vektor filtrira koje čvorove trenutno posmatramo
        //on nam je samo indikator da raucnamo sumu samo aktivnih clanova umesto da brisemo elemente matrice
        vector<bool> aktivan(V);
        fill(aktivan.begin(),aktivan.end(),false); //na pocetku nijedan nije aktivan
        vector<int> resSuma(V); //ovde smestamo rezultujuce sume
        for(int i=0; i<V; i++){
            int cvor = poredakUklanjanja[i];
            aktivan[cvor] = true;
            for(int j=0; j<V; j++){
                for(int k=0; k<V; k++){
                    //flojd varsal matrica - azuriramo najkrace puteve koji prolaze kroz tekuci cvor
                    susedi[j][k] = min(susedi[j][k],susedi[j][cvor]+susedi[cvor][k]);
                }
            }
            int sum = 0;
            for(int j=0; j<V; j++){
                if(!aktivan[j])
                    continue;
                for(int k=0; k<V; k++){
                    if(!aktivan[k])
                        continue;
                    sum += susedi [j][k];
                }
            }
            resSuma.push_back(sum);
        }
        //posto smo isli od pozadi vracamo pravi poredak
        reverse(resSuma.begin(),resSuma.end());
        for(int i=0; i<V; i++)
            cout << resSuma[i] << " ";
        cout << endl;
    }
};

int main(){
    int n;
    cin>>n;

   Graph *G = new Graph(n);

   int w;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> w;
            G->dodajGranu(i, j, w);
        }
    }

    vector<int> poredak_uklanjanja(n);
    for(int i=0;i<n;i++){
        cin>>poredak_uklanjanja[i];
        poredak_uklanjanja[i]--; //zbog indeksa
    }

   G->flojdVarsal(poredak_uklanjanja);

    delete G;

    return 0;
}