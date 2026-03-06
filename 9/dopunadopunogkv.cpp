/*
gruba sila: provera svih delioca do onog koji daje potpun kvadrat
najmanji je onaj koji je manji od sqrt(n)
međutim ako imamo broj n/d ne znamo da li je on najmanji

efikasnije resenje:
rastavljanje na proste cinioce
brojimo visestrukost cinioca i ukoliko su visestrukosti neparne dopunimo
do parne vrednosti jer paran br cinioca zaista daje kvadrat
*/
#include <iostream>
using namespace std;

int main(){
    long long n;
    cin >> n;
    //dobijena dopuna
    long long res=1;
    //kandidat za prosti cinilac
    long long p=2;
    while(p*p<=n){
        int k=0; //visestrukost
        while(n%p==0){ //dokle god je broj deljiv sa nasim 'ciniocem' odn nije cinilac prost
            n/=p;
            k++;//uvecavamo visestrukost
        }
        if(k%2!=0)
            res*=p; //dopuna do parnog broja cinilaca
        p++; //sledeci kandidat
    }
    //ako se broj sveo na svoj najveci prost cinilac
    if(n>1)
        res *= n;
    cout << res << endl;

    return 0;
}