/*
ng pocinje u isto vreme ali su godine razlicite u zasebnim nacijama
znamo da su vladari iz razlicitih nacija koji su ratovali vladali u istom periodu
zelimo proveriti da li postoji period u kom su vladari iz razlicitih nacija
vladali tj da li je mogla potencijalno biti bitka izmedju njih

posmatrajmo vladare kao cvorove u grafu
bitke su grane izmedju vladara koji su vladali/ziveli u isto vreme

upit se svodi na to da li dva vladara odn dva cvora pripadaju istoj komponenti grafa

prvi nacin:flojd varsal
drugi nacin: dfs
*/
#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>> nacije;

    public:
    Graph(int V){
        this->V = V;
        nacije.resize(V);
    }

    void dodajGranu(int vladar1, int vladar2){
        nacije[vladar1].push_back(vladar2);
        nacije[vladar2].push_back(vladar1);
    }

    vector<int> brojKomponenti(){
        vector<int> komponente(V,-1);
        int brKomponente=0;
        for(int vladar=0; vladar<V; vladar++){
            if(komponente[vladar]==-1)
                postaviKomponentu(vladar,komponente,++brKomponente);
        }
        return komponente;
    }

    void postaviKomponentu(int vladar, vector<int>&komponente, int komponenta){
        komponente[vladar] = komponenta;
        for(int vladar2 : nacije[vladar]){
            if(komponente[vladar2]==-1)
                postaviKomponentu(vladar2,komponente,komponenta);
        }
    }

    void daLiSeSusrecu(int vladar1, int vladar2){
        vector<int> susret = brojKomponenti();
        if(susret[vladar1]==susret[vladar2])
            cout << "da\n";
        else
            cout << "ne\n";
    }
};

int main(){
    int n;
    cin >> n;
    Graph *G = new Graph(n);
    


    return 0;
}