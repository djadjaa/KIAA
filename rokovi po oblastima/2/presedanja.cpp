
#include <bits/stdc++.h>
using namespace std;

int bfs(string &src, string &dest, map<string,vector<string>>&gradovi){
    //cuvamo par grad i njegov id tj indeks
    queue<pair<string,int>> q; 
    q.push({src,0});
    set<string>posecen;

    while(!q.empty()){
        auto [grad,presedanje] = q.front();
        q.pop();
        posecen.insert(grad);

        auto it = gradovi.find(grad);
        //ako taj grad postoji:
        if(it!=gradovi.end()){
            //tada prolazimo kroz sve susede
            for(const string &sused : it->second){
                if(posecen.find(sused)!=posecen.end())
                    continue;
                if(sused == dest)
                    return presedanje+1;
                q.push({sused,presedanje+1});
            }
        }
    }
    return -1;
}

int main(){

    int n;
    cin >> n;
    map<string,vector<string>>gradovi;
    string src,dest;
    for(int i=0; i<n; i++){
        cin >> src >> dest;
        gradovi[src].push_back(dest);
    }
    int q;
    cin >> q;
    while(q--){
        cin >> src >> dest;
        int res = bfs(src,dest,gradovi);
        if(res==-1)
            cout << "ne\n";
        else
            cout << res << endl;
    }
    return 0;
}