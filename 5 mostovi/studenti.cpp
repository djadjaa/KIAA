/*bipartitan graf*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

//nisu neophodne klase
int main(){
    int n,m;
    cin >> n >> m;

    vector<vector<int>> susedi(n);

    int u,v;

    for (int i=0; i<m; i++){
        cin >> u >> v;
        susedi[u].push_back(v);
        susedi[v].push_back(u);
    }

    bool moguceformiranje=true;

    vector<int> oznake(n,-1);
    int oznaka=0;
    //DFS (Moze i BFS svejedno je)
    stack<int> s;
    s.push(0);

    oznake[0] = 0;

    while(!s.empty() && moguceformiranje){
        int tmpcvor = s.top();
        s.pop();
        //susedi tekuceg cvora moraju biti rasporedjeni u suprotnoj grupi od one u kojoj je tekuci cvor
        oznaka = 1-oznake[tmpcvor];
        for(int sused:susedi[tmpcvor]){
            //ako je susedu dodeljena grupa
            //ako se sused nalazi u istoj grupi u kojoj je tekuci cvor
            if(oznake[sused]!=-1 && oznake[sused]!=oznaka){
                moguceformiranje=false;
                break;
            }

            //ako nije ipak dodeljena grupa susedu
            if(oznake[sused]==-1){
                oznake[sused] = oznaka;
                s.push(sused);
            }
        }
    }
    if(moguceformiranje){
        for(int i=0; i<n; i++){
            if(oznake[0]==oznake[i])
                cout << i << ' ';
        }
    }else
        cout << '-';
    cout << endl;
    return 0;
}