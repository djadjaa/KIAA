#include <bits/stdc++.h>

using namespace std;

string shifted(string &s, int k){
    string res = s;
    for(int i=0; i<res.size(); i++){
        res[i] = 'a'+(res[i]-'a'+k)%26;
    }
    return res;
}

void izracunajLPS(const string &sifra, vector<int>&lps){
    int n = sifra.size();
    lps[0] = 0;
    int j=0;
    for(int i=1; i<n; i++){
        while(j>0 && sifra[i]!=sifra[j])
            j = lps[j-1];
        if(sifra[i]==sifra[j])
            j++;
        lps[i]=j;
        //cout << "lps poz:" << lps[i] << endl;
    }
}

int kmp(const string &sifra, const string &string){
    int flag=0;
    int n = string.size();
    int m = sifra.size();
    vector<int> lps(m);
    izracunajLPS(sifra,lps);
    /*
    for(int i=0; i<lps.size();i++)
        cout << lps[i] << ' ';*/
    int j=0;
    for(int i=0; i<n; i++){
        while(j>0 && string[i]!=sifra[j])
            j = lps[j-1];
        if(string[i]==sifra[j])
            j++;
        if(j==m){
            flag=1;
            j=lps[j-1];
        }
    }
    return flag;
}

int main(){

    string grad, sifra;
    cin >> grad >> sifra;
    vector<int> res;
    for(int k=0; k<26; k++){
        string tmp = shifted(grad,k);
        //cout << tmp << endl;
        if(kmp(tmp,sifra))
            res.push_back(k);
    }
    sort(begin(res),end(res));
    for(auto x : res)
        cout << x << endl;

    return 0;
}