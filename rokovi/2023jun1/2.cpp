//kako je prostorna O(1) primenicemo ovde geometrijski algoritam

/*
posto imamo periodicno kretanje -> i1,j1 svakim korakom ide na dole, a kad dođe do dna (i = n), 
vraća se na vrh (i = 0) i nastavlja iz sledeće kolone (j+1).
analogno i2,j2 svakim korakom ide udesno, a kad dođe do kraja (j = n), 
vraća se na početak (j = 0) i nastavlja iz sledećeg reda (i+1).

-> primenicemo kinesku teoremu o ostacima

preko koje cemo pronaci nasu periodu odnosno trenutak gde obe
kongruencije za red i kolonu daju isti rezultat -> zajednicko resenje kongruencija
*/
#include <iostream>

using namespace std;

//diofantova jednacina
int prosireniEuklid(int a, int b, int &x, int &y) {
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    int x1,y1;
    int g  = prosireniEuklid(b,a%b,x1,y1);
    x = y1;
    y = x1-(a/b)*y1;
    return g;
}

int kineskaTeorema(int a, int n, int b, int m){
    int x,y;
    int g = prosireniEuklid(n,m,x,y);
    //sistem kongruencija ima resenje samo ako je razlika deljiva sa gcd(n,m) sto nam je g
    if((b-a)%g!=0)
        return -1;
    int nzs = n/g*m; //konacno resenje mora biti unutar [0,nzs)
    int t = (a+(b-a)/g*x%(m/g)*n)%nzs;
    /*
    glavna formula:
    g nam je nzd(n,m);

    (b - a) / g - normalizuje razliku

    b-a predstavlja koliko se ostatak po modulu m razlikuje od ostatka po modulu n.

    x%(m/g) - redukuje se koeficijent po modulu m/g
    *n - prvi kongruencijski uslov ima modul n
    a+ ... - pomeramo rešenje tako da zadovoljava prvi uslov (≡ a (mod n))
    %nzs - konacno resenje mora biti unutar [0,nzs)
    */
    if(t<0)
        t+=nzs; //zbog nenegativnosti
    return t;
}

int main(){

    int n;
    int i1, j1, i2, j2;
    cin >> n >> i1 >> j1 >> i2 >> j2;

    // Normalizacija modula
    int a = ((i2 - i1) % n + n) % n;       // t ≡ a (mod n)
    int b = ((j1 - j2) % (n+1) + (n+1)) % (n+1); // t ≡ b (mod n+1)

    int ans = kineskaTeorema(a, n, b, n+1);

    cout << ans << "\n";

    return 0;
}