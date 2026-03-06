//kmp primena
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void izracunajLPS(string &sablon, vector<int> &lps){
    int n = sablon.size();
    lps[0] = 0;
    int i=1, j=0;
    while(i<n){
        if(sablon[i]==sablon[j]){
            lps[i] = j+1;
            i++;
            j++;
        }else{
            if(j!=0)
                j=lps[j-1];
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

void kmp(string &tekst, string &sablon, int duzinateksta){
    int n = tekst.size();
    int m = sablon.size();
    vector<int> lps(n);
    izracunajLPS(sablon,lps);
    int i=0, j=0;
    bool pronadjena=false;
    /*
    m-j - koliko jos karaktera uzorka treba da se poklopi
    n-i - koliko jos karaktera teksta imamo na raspolaganju
    n - i < m - j -> nema dovoljno teksta da bi sablon mogao da se poklopi
    */
    while((n-i)>=(m-j)){
        //dokle god nam se poklapaju karakteri sa cirkularne i sablona
        if(tekst[i]==sablon[j]){
            i++;
            j++;
        }if(j==m){//ako smo dosli do kraja sablona
            if(i-j<duzinateksta) //i-j nam je indeks gde se poklapanje desava u c, 
            //medjutim proveravamo samo indekse koji su unutar prvobitne niske
            //dakle ovim ispisujemo samo prave indekse rotacija u okviru originalne niske
                cout << i-j << ' ';
            //pamtimo poziciju dokle idemo dalje
            j = lps[j-1];
            pronadjena=true;
            continue;
            //ako nam se ipak ne poklapaju karakteri a nismo van opsega
        }if(i<n && sablon[j]!=tekst[i]){
            if(j!=0)
            /*ne moramo da vraćamo ceo uzorak unazad,
            već nastavljamo sa najdužim mogućim prefiksom koji može da se poklopi*/
                j = lps[j-1];
            else
                i++; //inace nista, idemo dalje
        }
    }
    //ako na kraju ne postoji niska
    if(!pronadjena)
        cout << -1;
}

int main(){

    string s,t;
    cin >> s >> t;
    string c = s+s; //cirkularna niska - inicijalizacija
    int slen = s.size();
    int tlen = t.size();
    while(c.size() < slen + tlen - 1) //formiranje cirkularne niske
        c += s;
    kmp(c,t,s.size());
    return 0;
}