//kruskalov algoritam
/*
minimalno rastojanje -> ukupna minimalna suma grana
-> formiramo minimalno povezujuce stablo:
odredimo predstavnika grupe za svako minimalno povezujuce stablo
za svaka dva razlicita predstavnika primenimo union find
i tokom dodavanja tih grana sumiramo tezine grana 
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Tacka {
   int x;
   int y;

   Tacka(int x, int y) {
      this->x = x;
      this->y = y;
   }
};
/*
ostream& operator<<(ostream &out, const Tacka *t) {
   out << "[" << t->x << ", " << t->y << "]";
   return out;
}
*/

//union-find:
unordered_map<Tacka *, Tacka *> roditelj; //pokazuje na trenutnog roditelja skupa
unordered_map<Tacka *,int> rang; //spaja dva skupa u MST preko Kruskala, predstavnik se nalazi preko find
/*
Koristi se da pri spajanju dva skupa u MST (Kruskal) manja stabla budu “ubacivana” u veća, čime se smanjuje visina stabla i ubrzava find.
Ne određuje direktno koji je čvor predstavnik, ali utiče na to ko postaje roditelj prilikom spajanja.
*/

void UFInit(const vector<Tacka*> &tacke){
    for(Tacka *t : tacke){
        roditelj[t] = t; //koreni cvor
        rang[t] = 0;
    }
}

Tacka *UFFindGroup(Tacka *t){
    //dokle god ne dodjemo do korena
    while(t!=roditelj[t]){
        //svi cvorovi koje obilazimo tokom find op postaju direktno povezani sa korenom
        roditelj[t] = roditelj[roditelj[t]];
        t = roditelj[t];
    }
    return t;
}

void UFUnion(Tacka *t1, Tacka *t2){
    Tacka *findT1 = UFFindGroup(t1);
    Tacka *findT2 = UFFindGroup(t2);

    if(findT1 == findT2)
        return; //ako su predstavnici grupa jednaki
    if(rang[findT1]<rang[findT2])
        roditelj[findT1] = findT2; //na osnovu ranga odredjujemo koji je sledeci koren
    else if(rang[findT2]<rang[findT1])
        roditelj[findT2] = findT1;
    else{
        roditelj[findT1] = findT2;
        rang[findT2]++; //ili obratno svejedno je
    }
}

bool operator ==(Tacka t1, Tacka t2) {
    return t1.x == t2.x && t1.y == t2.y;
 }

//graf i kruskalov alg:
class Graph{
    private:
    int V;
    //za svaku tacku cuvamo par njene susedne tacke i tezinu odn rastojanje izmedju te dve tacke
    unordered_map<Tacka *, vector<pair<Tacka *,int>>> susedi;
    vector<pair<Tacka *, Tacka *>> grane; //rastojanja izmedju dve tacke

    void sortiraj(){
        sort(grane.begin(),grane.end(),
        [this](auto &g1, auto &g2){
            return menhetnRast(g1.first,g1.second) < menhetnRast(g2.first,g2.second);
        });
    }

    public:
    Graph(){}
    void dodajGranu(Tacka *u, Tacka *v, int w){
        susedi[u].push_back({v,w});
        susedi[v].push_back({u,w});
        grane.push_back({u,v});
    }

    int menhetnRast(Tacka *t1, Tacka *t2){
        return abs(t1->x - t2->x) + abs(t1->y - t2->y);
    }

    int kruskalAlg(){
        sortiraj();
        int sum =0;
        for(const auto &g : grane){
            Tacka *t1 = g.first; //cvor u
            Tacka *t2 = g.second; //cvor v

            Tacka *grupaT1 = UFFindGroup(t1);
            Tacka *grupaT2 = UFFindGroup(t2);
            //sprecavamo ciklus
            if(grupaT1==grupaT2)
                continue;
            UFUnion(t1,t2);
            sum+=menhetnRast(g.first,g.second);
        }
        return sum;
    }
};

int main() {
    int n, x, y;
 
    cin >> n;
 
    Graph *G = new Graph();
 
    vector<Tacka *> tacke;
 
    for (int i = 0; i < n; i++) {
       cin >> x >> y;
       Tacka *t = new Tacka(x, y);
       tacke.push_back(t);
    }
 
    UFInit(tacke);
 
    for (int i = 0; i < n; i++) {
       for (int j = i + 1; j < n; j++) {
          G->dodajGranu(tacke[i], tacke[j], G->menhetnRast(tacke[i], tacke[j]));
       }
    }
 
    cout << G->kruskalAlg() << "\n";
 
    delete G;
    return 0;
}
 