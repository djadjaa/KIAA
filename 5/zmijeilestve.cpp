//primena BFS algoritma
//ciklusi + minimalno rastojanje

//zmije i lestvice su nam samo alati kako brze doci do cilja
#include <iostream>
#include <map>
#include <queue>

using namespace std;

class Graph{
    private:
    int V;
    int maxstep;
    //kljuc je pocetno polje odakle igrac skace, a vrednost polje na koje igrac stize
    map<int, int> snakesLadders;

    public:
    Graph(int V, int maxstep){
        this->V = V;
        this->maxstep = maxstep;
    }

    /*
    Ako polje start_field već postoji u mapi → vrednost se ažurira (menja na end_field)
    inače se formira nova putanja
    */
    void addSnakeLadder(int start, int end){
        snakesLadders[start] = end;
    }

    int findShortestPath(){
        vector<int> rastojanja(V,-1); //cuvamo minimalna rastojanja

        queue<int> q; //redosled obrade polja 
        q.push(0);
        rastojanja[0] = 0; //pocetno rastojanje

        while(!q.empty()){
            int trenutnopolje = q.front();
            q.pop();
            
            /*
            Od svakog polja p bacanjem kockice možemo stići na polja p+1, p+2, …, p+k 
            */
            for(int i=1; i<=maxstep && trenutnopolje + i < V; i++){
                int sledecepolje = trenutnopolje + i;

                bool ciklus = false;

                while(true){
                    //da li postoji takva putanja:
                    auto it = snakesLadders.find(sledecepolje);
                    if(it == snakesLadders.end())
                        break;
                    
                    sledecepolje = it->second; //skacemo na naredno polje
                    
                    //ako azurirano naredno polje je zapravo polje iz kog smo krenuli
                    if(sledecepolje == trenutnopolje + i){
                        //tada je u pitanju ciklus:
                        ciklus = true;
                        break;
                    }
                }

                //inace imamo sledeci slucaj:
                //ako nije ciklus i ako to polje nije poseceno
                if(!ciklus && rastojanja[sledecepolje]==-1){
                    //tada smo bacili kockicu i azurirali nase polje
                    rastojanja[sledecepolje] = rastojanja[trenutnopolje] + 1;
                    q.push(sledecepolje); //ubacujemo ga u nas redosled
                    
                    //poslednje polje
                    if(sledecepolje == V-1)
                        break;
                }
                /*
                „Ako sam stigao na novo, neistraženo i bezbedno polje, 
                zabeleži minimalan broj koraka, ubaci ga u red za dalju obradu, 
                i prekini odmah ako je to poslednje polje.”
                */
            }
        }
        return rastojanja[V-1];
    }
};


int main(){

    int V, maxstep;
    cin >> V >> maxstep;

    int numSnakesLadders;
    cin >> numSnakesLadders;

    Graph *G = new Graph(V,maxstep);
    int start, end;

    for(int i=0; i<numSnakesLadders; i++){
        cin >> start >> end;
        G->addSnakeLadder(start,end);
    }
    cout << G->findShortestPath() << "\n";
    return 0;
}