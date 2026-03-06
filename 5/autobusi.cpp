/*
cvorovi su stanice a ruta postoji akko postoji autobus na cijoj se ruti nalaze obe stanice
efikasnije: cvorovi su kako stanice tako i autobusi

kada bi cvorovi bili iskljucivo stanice, autobus ima prebrojivo mnogo ruta
kojima moze ici, a ako su cvorovi i autobusi postojace ogranicen br ruta
kojom ce ici autobus sto povlaci dekrementaciju ruta

bfs

-> najkrace rast izmedju pocetne i krajnje stanice, gde rastojanje povecavamo
samo kad prelazimo sa cvora autobusa na cvor stanice (jer logicno tad silazimo)
(da je obrnuto doslovno povecavamo sebi put)
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

enum Node_type { BUS, STATION };

class Graph{
    private:
    int brBuseva;
    //za svaku stanicu pamtimo buseve koji staju na njoj
    unordered_map<int, vector<int>> buseviNaStanicama;

    //18 -> [autokom, ljubicka..]

    //za svaki bus pamtimo na kojim sve stanicama staje
    vector<vector<int>> staniceZaSvakiBus;

    //493 (autokom): [17,18,46,55...]

    //za svaku stanicu pamtimo koliko ima do odredista
    unordered_map<int,int> brVoznjiDoStanice;

    //brace jerkovic -> {mitrovo brdo, sc sport eko ... autokom -> 10 stanica}

    //za svaki bus pamtimo koliko ima do sledeceg autobusa kojim nastavljamo put
    vector<int> voznjaDoBusa;

    //10 5 7 (10 min 18icom, 5 min do sajma 55icom, 7 min do pozeske 49kom)

    //formiranje bipartitivnog grafa:
    void dodajStanicuZaBus(int bus, int stanica){
        staniceZaSvakiBus[bus].push_back(stanica);
    }

    void dodajBusNaStanici(int bus, int stanica){
        buseviNaStanicama[stanica].push_back(bus);
    }

    public:
    //konstruktor
    Graph(int brBuseva){
        this->brBuseva = brBuseva;
        voznjaDoBusa.resize(brBuseva,-1);
        staniceZaSvakiBus.resize(brBuseva);
    }

    //dodavanje grana
    void upariBusIStanicu(int bus, int stanica){
        dodajBusNaStanici(bus,stanica);
        dodajStanicuZaBus(bus,stanica);
    }

    int minimalniBrVoznji(int pocetna, int krajnja){
        int res=-1;

        Node_type stanicaCvor = STATION;
        Node_type busCvor = BUS;

        //bfs:
        queue<pair<Node_type,int>> q; //red parova
        //direktno kreiranje elementa:
        q.emplace(stanicaCvor, pocetna); //inicijalizacija
        brVoznjiDoStanice[pocetna] = 0;

        while(!q.empty()){
            //[vrstaCvora, brBusevaIliStanica] = q.front();
            Node_type vrstaCvora = q.front().first;
            int brBusevaIliStanica = q.front().second;
            q.pop();

            //ako smo stigli
            if(vrstaCvora == STATION && brBusevaIliStanica == krajnja){
                res = brVoznjiDoStanice[brBusevaIliStanica];
                break;
            }

            //ako smo na nekoj stanici
            if(vrstaCvora == STATION){
                int stanica = brBusevaIliStanica;
                //gledamo koji autobus nam je potreban na stanici na kojoj smo rn 
                for(int bus: buseviNaStanicama[stanica]){
                    if(voznjaDoBusa[bus]==-1){ //ako se nismo vozili do sad datim busem
                        //azuriramo br voznji do stanice sa busom kojim se nismo vozili do sad
                        voznjaDoBusa[bus] = brVoznjiDoStanice[stanica];
                        q.emplace(BUS,bus);

                        /*
                        Imaš stanicu 0 i bus A koji ide preko stanica {0, 1, 2}.
                        Startuješ iz stanice 0, pa rides_to_station[0] = 0.
                        Kada dođeš do stanice 0, gledaš koji busevi staju tu → bus A.
                        Pošto si već na stanici 0, za bus A važi: rides_to_bus[A] = rides_to_station[0] = 0
                        */
                    }
                }
            }

            //ako smo u busu rn
            else if(vrstaCvora == BUS){
                int bus = brBusevaIliStanica;
                //sada razmatramo na kojoj stanici silazimo
                for(int stanica : staniceZaSvakiBus[bus]){
                    //ako smo dosli do takve stanice
                    if(brVoznjiDoStanice.find(stanica) == brVoznjiDoStanice.end()){
                        //do nje smo dosli koristeci bus vise nego do sada
                        brVoznjiDoStanice[stanica] = voznjaDoBusa[bus]+1;
                        q.emplace(STATION,stanica);
                        /*
                        Ako smo do autobusa A stigli bez presedanja (rides_to_bus[A] = 0),
                        onda do bilo koje njegove stanice stižemo sa 0 + 1 = 1 vožnjom.
                        */
                    }
                }
            }
        }
        return res;
    }
};
int main() {
    ios_base::sync_with_stdio(false);
  
    int number_of_buses;
    cin >> number_of_buses;
  
    Graph *G = new Graph(number_of_buses);
  
    int number_of_stations, station;
    for (int bus = 0; bus < number_of_buses; bus++) {
      cin >> number_of_stations;
  
      for (int i = 0; i < number_of_stations; i++) {
        cin >> station;
        G->upariBusIStanicu(bus, station);
      }
    }
  
    int start_station, end_station;
    cin >> start_station >> end_station;
  
    cout << G->minimalniBrVoznji(start_station, end_station) << endl;
  
    delete G;
    return 0;
  }