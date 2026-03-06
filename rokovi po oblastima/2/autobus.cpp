//nije neophodna klasa graf
#include <bits/stdc++.h>

using namespace std;

int main(){

    int n;
    cin >> n;
    int m, st;
    vector<vector<int>> stanicezasvakibus(n);
    unordered_map<int,vector<int>> busevinastanicama;
    for(int bus=0; bus<n; bus++){
        cin >> m;
        stanicezasvakibus[bus].resize(m);
        for(int stanica=0; stanica<m; stanica++){
            cin >> st;
            stanicezasvakibus[bus].push_back(st);
            busevinastanicama[st].push_back(bus);
        }
    }
    int start,end;
    cin >> start >> end;

    //svi su inicijalizovani na -1
    vector<int> rastojanje(n,-1);
    queue<int> q;

    //trazimo one buseve koji sadrze pocetnu stanicu (odakle se i pocinje bfs)
    //bus na stanici start
    for(int bus : busevinastanicama[start]){
        cout << "trenutni bus:" << bus << endl;
        rastojanje[bus] = 1;
        q.push(bus);
    }

    //bfs
    while(!q.empty()){
        int tmpbus = q.front();
        q.pop();
        for(int stanica : stanicezasvakibus[tmpbus]){
            if(stanica==end){
                cout << rastojanje[tmpbus] << endl;
                return 0;
            }

            //nivoi su nam autobusi, zato ih ubacujemo u red
            for(int sledecibus : busevinastanicama[stanica]){
                //ako nismo dosli 
                if(rastojanje[sledecibus]==-1){
                    rastojanje[sledecibus] = rastojanje[tmpbus]+1;
                    q.push(sledecibus);
                }
            }
            // Da ne obilazimo istu stanicu više puta
            busevinastanicama[stanica].clear();
        }
    }
    cout << -1 << endl;
    return 0;
}