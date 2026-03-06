//dfs (moze i bfs svejedno)
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <tuple>
#include <limits>

using namespace std;

//cvorovi svakog od delova pravougaonika
/*
  0
1   2
  3
*/
enum deo {GORE=0, DOLE, LEVO, DESNO};

class Graph{
    private:
    int m;
    int n;
    vector<string> ziveOgrade;
    //posecen[i][j][k]
    //i - red u mrezi, j - kolona u mrezi, k - deo u kom se nalazi elem [i][j]
    vector<vector<vector<bool>>> posecen;

    public:
    //konstruktor
    Graph(int m, int n){
        this->m = m;
        this->n = n;
        init();
    }

    void dodajZivuOgradu(string linija){
        ziveOgrade.push_back(linija);
    }

    void init(){
        posecen.resize(m);
        for(int i=0; i<m; i++){
            posecen[i].resize(n);
            for(int j=0; j<n; j++){
                posecen[i][j].resize(4,false); //4 cvorova imamo u po jednoj oblasti
            }
        }
    }

    void dfs(int vrsta, int kolona, int deo){
        //za dfs koristimo stek iterativno
        stack<tuple<int,int,int>>s;
        s.emplace(vrsta,kolona,deo);
        posecen[vrsta][kolona][deo] = true;

        int v,k,d; //opsti podaci

        while(!s.empty()){
            //kreiranje trojke:
            tie(v, k, d) = s.top();
            s.pop();

            vector<tuple<int,int,int>> susedi;

            //u kom smo delu:
            //'/' = sporedna dijagonala '\\' = glavna dijagonala
            switch(d){
                case GORE:
                    //ako nije tu glavna dijagonala mozemo gore ka levo da idemo
                    if(ziveOgrade[v][k]!='\\')
                        susedi.emplace_back(v,k,LEVO);
                    //ako nije tu sporedna dijagonala mozemo od gore ka desno da idemo
                    if(ziveOgrade[v][k]!='/')
                        susedi.emplace_back(v,k,DESNO);
                    //ako postoji kvadrat iznad oblasti u kojoj se nalazimo, idemo ka njegovom donjem cvoru (fakticki gore)
                    if(v>0)
                        susedi.emplace_back(v-1,k,DOLE);
                    break;
                case DOLE:
                    //analogno kao za gore samo suprotno
                    if(ziveOgrade[v][k]!='\\')
                        susedi.emplace_back(v,k,DESNO);
                    if(ziveOgrade[v][k]!='/')
                        susedi.emplace_back(v,k,LEVO);
                    //ako postoji polje ispod oblasti u kojoj se nalazimo, idemo ka njegovom gornjem cvoru(fakticki dole)
                    if(v<m-1)
                        susedi.emplace_back(v+1,m,GORE);
                    break;
                case LEVO:
                    if(ziveOgrade[v][k]!='\\')
                        susedi.emplace_back(v,k,GORE);
                    if(ziveOgrade[v][k]!='/')
                        susedi.emplace_back(v,k,DOLE);
                    //ako postoji polje desno od onog u kom se nalazimo, idemo ka njegovom desnom cvoru(fakticki levo)
                    if(k>0)
                        susedi.emplace_back(v,k-1,DESNO);
                    break;
                case DESNO:
                    //analogno kao za levo
                    if(ziveOgrade[v][k]!='\\')
                        susedi.emplace_back(v,k,DOLE);
                    if(ziveOgrade[v][k]!='/')
                        susedi.emplace_back(v,k,GORE);
                    //ako postoji polje levo od onog u kom se nalazimo, idemo ka njegovom levom cvoru(fakticki desno)
                    if(k<n-1)
                        susedi.emplace_back(v,k+1,LEVO);
                    break;
            }

            int vtmp,ktmp,dtmp; //tekuci podaci
            //razmatramo sve susede tekuceg cvora
            for(const auto& sused : susedi){
                tie(vtmp,ktmp,dtmp) = sused;
                if(!posecen[vtmp][ktmp][dtmp]){
                    posecen[vtmp][ktmp][dtmp] = true;
                    s.push(sused);
                }
            }
        }   
    }
    //broj komponenti povezanosti grafa
    int numAreas(){
        int res = 0;
        for(int v=0; v<m; v++){
            for(int k=0; k<n; k++){
                //enum deo {GORE=0, DOLE, LEVO, DESNO};
                //GORE nam je 0 a DESNO 3
                for(int d=GORE; d<=DESNO; d++){
                    if(!posecen[v][k][d]){
                        dfs(v,k,d);
                        res++;
                    }
                }
            }
        }
        return res;
    }
};


int main() {
    int m, n;
    cin >> m >> n;
  
    // na ovaj nacin praznimo bafer za ucitavanje, kako ne bismo imali
    // problem sa getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
    Graph *G = new Graph(m, n);
  
    string linija;
    // ucitavamo crtez lavirinta
    for (int i = 0; i < m; i++) {
      getline(cin, linija);
      G->dodajZivuOgradu(linija);
    }
  
    cout << G->numAreas() << endl;
  
    return 0;
  }