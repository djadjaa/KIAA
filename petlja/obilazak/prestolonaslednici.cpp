#include <bits/stdc++.h>

using namespace std;

void dfs(const map<string,vector<string>>&deca, const string &kralj, map<string,int>& redosled){
    int no =0; //redni broj tokom obilaska;
    stack<string> s;
    s.push(kralj);

    while(!s.empty()){
        string tmp = s.top();
        s.pop();

        redosled[tmp]=no;
        no++;

        //trazimo njegove naslednike koje stavljamo u obratnom smeru da bi najstariji bio na vrhu steka
        auto it = deca.find(tmp);
        if(it!=deca.end()){
            const vector<string> &tmpdeca = it->second;
            for(auto it = tmpdeca.rbegin(); it!= tmpdeca.rend(); it++)
                s.push(*it);
        }
    }
}

int main(){
    int n;
    cin >> n;

    map<string,bool> imaRoditelja;
    map<string,vector<string>> potomci;

    for(int i=0; i<n-1; i++){
        string roditelj;
        string dete;
        cin >> roditelj >> dete;
        imaRoditelja[dete] = true;

        //ako za sad nemamo roditelja u mapi
        if(imaRoditelja.find(roditelj)==imaRoditelja.end())
            imaRoditelja[roditelj]=false;
        potomci[roditelj].push_back(dete);
    }

    //odredjivanje kralja - cvor stabla
    string kralj;
    for(auto it : imaRoditelja)
        if(!it.second)
            kralj = it.first;
    
    map<string,int> naslednici;
    dfs(potomci, kralj, naslednici);

    string upit;
    while(cin >> upit)
        cout << upit << ' ' << naslednici[upit] << endl;
    return 0;
}