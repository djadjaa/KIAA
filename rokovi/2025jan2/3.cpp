/*
Na ulazu se unosi ime grada i šifra (opet kao niska), obe niske malim slovima engleske abecede. Šifra je 
napravljena tako da sadrži ime grada gde su sva slova niske tog imena pomerena za k. (Npr. bon za k = 1 je cpo). Potrebno 
je na izlaz ispisati u rastućem redosledu svaku vrednost koju k može imati tj. svaki k za koji postoji deo koji se poklapa u šifri.

KMP
*/

#include <bits/stdc++.h>
using namespace std;

string shifted(const string &s, int k){
    string res = s;
    for(int i=0; i<res.size(); i++)
        res[i] = 'a'+(res[i]-'a'+k)%26;
    return res;
}

void izracunajLPS(const string &s, vector<int> &lps){
    int n = s.size();
    lps[0] = 0; //na pocetku nemamo prefiks-sufiks
    int i=1, j=0;
    while(i<n){
        if(s[i]==s[j]){
            lps[i] = j+1;
            i++;
            j++;
        }else{
            if(j!=0)
                j = lps[j-1];
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
    
}

bool kmp(const string &sifra, const string &grad){
    int n = grad.size();
    int m = sifra.size();
    vector<int>lps(m);
    izracunajLPS(sifra,lps);
    int i=0, j=0;
    while(i<n){
        if(grad[i]==sifra[j]){
            i++;
            j++;
        }
        if(j==m) //ako smo dosli do kraja sablona
            return true;
        else if(i<n && grad[i]!=sifra[j]){
            if(j!=0)
                j = lps[j-1];
            else
                i++;
        }
    }
    return false;
}

int main(){

    string grad, sifra;
    cin >> grad >> sifra;
    vector<int> validK;
    for(int k=0; k<26; k++){
        string tmp = shifted(grad,k);
        if(kmp(sifra,tmp))
            validK.push_back(k);
    }
    sort(validK.begin(),validK.end());
    for(auto k : validK)
        cout << k << ' ';
    cout << endl;
    return 0;
}