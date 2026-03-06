#include <bits/stdc++.h>

using namespace std;

string shifted(string &s,int k){
    string res = s;
    for(int i=0; i<res.size(); i++)
        res[i] = 'a'+(res[i]-'a'+k)%26;
    
    return res;
}

void izracunajLPS(string &sifra, vector<int> &lps){
    int n = sifra.size();
    lps[0] = 0;
    int j=0;
    for(int i=1; i<n; i++){
        while(j>0 && sifra[i]!=sifra[j])
            j = lps[j-1];
        if(sifra[i]==sifra[j])
            j++;
        lps[i] = j;
    }
}

bool kmp(string &sifra, string &str){
    bool flag = false;
    int n = str.size();
    int m = sifra.size();
    vector<int> lps(m);
    izracunajLPS(sifra,lps);
    int j=0;
    for(int i=0; i<n; i++){
        while(j>0 && str[i]!=sifra[j])
            j = lps[j-1];
        if(str[i]==sifra[j])
            j++;
        if(j==m){
            flag = true;
            j = lps[j-1];
        }
    }
    return flag;
}

int main(){
    string grad, poruka;
    cin >> grad >> poruka;
    vector<int> res;
    for(int k=0; k<26; k++){
        string tmp = shifted(grad,k);
        if(kmp(tmp,poruka))
            res.push_back(k);
    }
    sort(begin(res),end(res));
    for(auto x : res)
        cout << x << endl;

    return 0;
}