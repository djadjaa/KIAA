/*
ababcabab
strlen = 9

ababcabab
     ababcabab

abab - prefix-sufix koji se poklapa -> 4 := k

strlen += (strlen-k) => 9+(9-4) = 9+5 = 14

ababcabab
     ababcabab
          ababcabab

primetimo da ponavljajucih stringova ima n-1 puta i da mi 
tu konacnu duzinu racunamo n-1 puta
dakle:
uk = strlen + (strlen-k)*(n-1)
gde je prvi sabirak pocetna velicina niske a drugi velicine ponavljajucih

primena kmp!!
*/

#include <bits/stdc++.h>

using namespace std;

int main(){

    string s;
    int n;

    cin >> s >> n;

    //trazimo najveci prefiks-sufiks
    vector<int> kmp(s.size(),0);

    kmp[0] = 0;
    int i=1, j=0;
    while(i<s.size()){
        if(s[i]==s[j]){
            kmp[i]=j+1;
            i++;
            j++;
        }else{
            if(j!=0)
                j=kmp[j-1];
            else{
                kmp[i]=0;
                i++;
            }
        }
    }
    //uk = strlen + (strlen-k)*(n-1)
    cout << s.size() + (s.size()-kmp[s.size()-1])*(n-1) << endl;
    return 0;
}