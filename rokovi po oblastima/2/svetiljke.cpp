

#include <bits/stdc++.h>

using namespace std;

class Graph{
    private:
    int V;
    vector<vector<int>>susedi;
    vector<int> boje;

    public:
    Graph(int V){
        this->V = V;
        susedi.resize(V);
        boje.resize(V,-1);
    }

    void dodajGranu(int u, int v){
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }
    //primena dfs-a
    bool bipartitan(int cvor,int &cnt0, int &cnt1){
        stack<int> s;
        s.push(cvor);
        boje[cvor] = 0;
        cnt0=1;
        cnt1=0;
        while(!s.empty()){
            int tmp = s.top();
            s.pop();

            for(int sused : susedi[tmp]){
                if(boje[sused]==-1){//dodela boje
                    boje[sused] = 1-boje[tmp];
                    if(boje[sused]==0)
                        cnt0++;
                    else
                        cnt1++;
                    s.push(sused);
                }
                else if(boje[sused]==boje[tmp]) //ako su jednake boje
                    return false;
            }
        }
        return true;
    }

    int brSvetiljki(){
        int res=0;
        for(int i=0; i<V; i++){
            if(boje[i]==-1){ //ako nije dodeljena boja, pokrecemo dfs
                int cnt0=0, cnt1=0;
                if(!bipartitan(i,cnt0,cnt1)) //ako se ispostavi da ne moze da se dodeli boja:
                    return -1;
                res+=min(cnt0,cnt1);
            }
        }
        return res;

        /*
        int num1=0, num2=0;
        for(int i=0; i<V; i++){
            if(boje[i]==0)
                num1++;
            else if(boje[i]==1)
                num2++;
        }
        return min(num1,num2)
        
        ovde bojimo ceo graf i onda uzimamo minimum od ukupno boja
        pravilno je dok smo u momentu bojenja da istovremeno odredimo
        koliko ima cvorova prve a koliko druge komponente, tj minimalni broj cvorova koji su obojeni
        jednom od boja

        dakle mi smo ovde radili:
        min( (0 u svim komponentama), (1 u svim komponentama) )

        a zapravo bi trebalo:
        min(0,1 u komponenti 1)
        + min(0,1 u komponenti 2)
        + ...

        tldr: uzeli smo minimum globalno za ceo graf, a trebalo je da uzmemo minimum posebno 
        za svaku povezanu komponentu i te minimume saberemo

        */
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
    cout << G->brSvetiljki() << endl;

    return 0;
}