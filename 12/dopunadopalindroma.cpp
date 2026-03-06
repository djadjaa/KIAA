//kmp algoritam
/*
trazimo sve one koji su i prefiks i sufiks

*/
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void izracunajLPS(string &pattern,vector<int>&lps){
    int n = pattern.size();
    //za prvi karakter ne postoji nijedan pravi prefiks koji je i sufiks = 0
    lps[0] = 0;
    int i=1, j=0; //i ide kroz nisku a j ce odrediti duzinu prefiksa i sufiksa koji se poklapaju
    while(i<n){
        //ako se karakteri poklapaju, azuriramo vrednost najduzeg prefiksa-sufiksa
        if(pattern[i]==pattern[j]){
            lps[i] = j+1;
            i++;
            j++;
        }else{ //inace
            if(j!=0)
            /*
            ne moramo da vraćamo ceo uzorak unazad,
            već nastavljamo sa najdužim mogućim prefiksom koji može da se poklopi
            */
                j = lps[j-1];
            else{
                lps[i] = 0; //inace nista
                i++; //idemo dalje
            }
        }
    }
}

int main(){
    string s;
    cin >> s;
    string tmpreverse = s;
    string tmp = tmpreverse;
    reverse(tmpreverse.begin(),tmpreverse.end());
    tmp += "#";
    tmp+= tmpreverse;
    int n = tmp.size();

    //lps – longest prefix-suffix
    /*
    Kada tražimo uzorak u tekstu, ako dođe do neuspeha u poklapanju, 
    možemo da znamo od koje pozicije u uzorku možemo da nastavimo pretragu bez vraćanja unazad po tekstu.
    */
    vector<int>lps(n);

    izracunajLPS(tmp,lps);

    //odredjivanje sufiksa od nase pozicije gde smo izracunali poklapanje
    string sufiks = s.substr(lps[n-1]);
    //palindrom
    reverse(sufiks.begin(),sufiks.end());

    sufiks+=s;

    cout << sufiks << endl;

    return 0;
}