/*
Ako su serveri jeftiniji ili jednaki kablovima → postavi server na svaki sto.
Ako su serveri skuplji od kablova → u svakoj komponenti samo jedan server, ostalo obični računari povezani kablovima.

primena dfsa

pojam komponenti
*/

#include <iostream>
#include <vector>

using namespace std;

class Network{
    private:
    int numComps;
    int numCables;
    long long serverPrice;
    long long cablePrice;
    vector<vector<int>> susedi;

    public:
    //konstruktor
    Network(int numComps, int numCables, long long serverPrice, long long cablePrice){
        this->numComps = numComps;
        this->numCables = numCables;
        this->serverPrice = serverPrice;
        this->cablePrice = cablePrice;
        this->susedi.resize(numComps);
    }

    //dodavanje 'veza' izmedju kompjutera
    void addEdge(int comp1, int comp2){
        susedi[comp1].push_back(comp2);
        susedi[comp2].push_back(comp1);
    }

    //zelimo da proverimo koliko mreza ima u grafu -> komponenti (uk br grafova)
    int findNumComponents(){
        //inicijalizacija
        //za sad nijedan racunar nije ni u jednoj komponenti
        vector<int> komponente(numComps,0);
        int komponenta = 0;

        for(int komp = 0; komp < numComps; komp++){
            //ako se kompjuter ne nalazi u komponenti, ubacujemo ga
            if(komponente[komp] == 0){
                postaviKomponentu(komp,komponente,++komponenta);
            }
        }
        return komponenta;
    }

    //dodajemo susede u komponentu i zvanicno je definisemo
    void postaviKomponentu(int komp, vector<int> &komponente, int komponenta){
        komponente[komp] = komponenta;
        for(int sused:susedi[komp]){
            if(komponente[sused]==0)
                postaviKomponentu(sused,komponente,komponenta);
        }
    }

    //zvanicna fja
    int minCena(){
        if(serverPrice<=cablePrice)
            return numComps*serverPrice;
        else{
            int brKomponenti = findNumComponents();
            int brServera = brKomponenti;
            int brStandKompjutera = numComps-brServera;
            return brServera*serverPrice+brStandKompjutera*cablePrice;
        }
    }
};

int main(){

    ios_base::sync_with_stdio(false);

  int number_of_computers, number_of_cables;
  long long server_price, cable_price;
  cin >> server_price >> cable_price;
  cin >> number_of_computers >> number_of_cables;

  Network *N = new Network(number_of_computers, number_of_cables, server_price, cable_price);

  int computer_1, computer_2;
  for (int i = 0; i < number_of_cables; i++) {
    cin >> computer_1 >> computer_2;
    N->addEdge(computer_1, computer_2);
  }

  std::cout << N->minCena() << "\n";

    return 0;
}