/*
gruba sila - linearnom pretragom pronalazimo najmanji br koji pri
deljenju sa datim deliocima daje date ostatke

efikasnije resenje ili preko kineske teoreme ili preko eratostenovog sita
ili preko prosirene euklidove teoreme

uzecemo kinesku teoremu kao opste resenje ( ako imamo n delioca i n ostatka
(u nasem slucaju imamo 3 kom))
*/

#include <iostream>
#include <vector>

using namespace std;

//standardna nzd fja
long long nzd(long long a, long long b){
    while(b>0){
        long long ost = a%b;
        a=b;
        b = ost;
    }
    return a;
}

//dobijanje inverza:
//za t mora da vazi (a*t)mod n = 1
bool inverz(long long a, long long n, long long &t){
    //r je trenutni ostatak, na pocetku inicijalizovan kao n koji se postepeno deli, a r1 manji br
    long long r = n, r1 = a;
    t = 0;
    long long t1 = 1; //koeficijent uz a
    while(r1>0){
        long long q = r/r1; //kolicnik
        long long tmp;

        tmp = r;
        r = r1;
        r1 = tmp - q*r1; //novi ost r%r1

        tmp = t;
        t = t1; //nas multiplikatinvi inverz
        t1 = tmp - q*t1; //normalizacija
    }
    if(t<0)
        t+= n; //ako u slucaju dobijemo neg inverz
    return r == 1; //r nam je nzs
}

//modularna aritmetika:
//proizvod
long long proizvodMod (long long x, long long y, long long n){
    return ((x%n)*(y%n))%n;
}
//zbir
long long zbirMod(long long x, long long y, long long n){
    return ((x%n)+(y%n))%n;
}
//pomocna fja -> modifikovana verzija proizvoda za kinesku teoremu radi izbegavanja prekoracenja
long long pomocniProizvodMod(long long x, long long y, long long z){
    return z*(x%y);
}

bool kineskaTeorema(long long n[],long long a[], int duzina, long long& res){
    long long N=1; //proizvod svih modula, za sad je 1
    for(int i=0; i<duzina; i++)
        N*=n[i]; //N = n1*..*nk
    res = 0;
    for(int i=0; i<duzina; i++){
        long long partialProduct = N/n[i]; //delimicni proizvod odn proizvod svih modula osim n[i]
        long long partialProductInv; //inverz parcijalnog proizvoda po modulu n[i]
        //ako inverz ne postoji oni nisu uzajamno prosti
        if(!inverz(partialProduct,n[i],partialProductInv))
            return false;
        //inace vraca sumu proizvoda a*partialProductInv*partialProduct mod N
        /*
        svaki clan je konstruisan tako da je kongruentan sa ai po modulu ni
        Kada saberemo sve clanove, dobijamo broj x koji zadovoljava sve ostatke ai mod ni
        dakle, formula kombinuje sve ostatke u jedno jedinstveno resenje mod N
        */
        res = zbirMod(res,pomocniProizvodMod(proizvodMod(a[i],partialProductInv,N),n[i],partialProduct),N);
    }
    return true;
}

int main(){

    //n procesori (moduli), a podaci (ostaci)
    long long a[3], n[3]; //dimenzija moze biti n
    for(int i=0; i<3; i++)
        cin >> a[i] >> n[i];
    long long res;
    if(!kineskaTeorema(n,a,3,res))
        cout << "nisu uzajamno prosti\n" << endl;
    cout << res << endl;

    return 0;
}