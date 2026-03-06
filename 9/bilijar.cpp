/*
horizontalno kretanje -> predjeno rastojanje je umnozak sirine
vertikalno kretanje -> predjeno rastojanje je umnozak visine
kako su intezitet brzine u hor i ver pravcu isti rastojanje predjeno
u hor i ver smeru je uvek isto
-> svako pomeranje udesno za 1 je i nagore za 1
loptica upada u rupu ako horizontalno predje ceo sto neki ceo br puta
kao i vertikalno
i kako su  nam predjena rastojanja u oba pravca isto, trazimo najmanji br
koji je kako umnozak od m (hor) tako od n (ver) odnosno NZS

te ce broj puta prelaska sirine stola biti nzs/m := nx
 a visine stola nzs/n := ny

nx paran -> loptica zavrsava na levoj str jer se br puta kada je presla m ponisti tj vraca na pocetnu ivicu
inace na desnoj str

ny paran -> loptica je gore jer se br puta kada je presla n ponisti
inace na donjoj str

svaki put kad loptica predje sirinu nx puta tada se odbila od vertikalnih ivica nx-1 puta
isto tako visinu ny puta odbila se od horizontalnih ivica ny-1 puta

odbijanja predstavljaju sumu ovih odbijanja
(-1 jer ne racunamo startno kretanje)
*/

#include <iostream>
using namespace std;

int nzd(int a, int b){
    while(b>0){
        int ost = a%b;
        a=b;
        b=ost;
    }
    return a;
}
/*
long long nzs(int a, int b){
    return ((long long)a/nzd(a,b))*b;
}*/

int main(){
    int m,n;
    //sirina i visina
    cin >> m >> n;
    long long NZD = nzd(m,n);
    //broj puta prelaska sirine i visine stola
    /*
    nzs(m,n)=(mn)/nzd(m,m)

    umesto nx = NZS/m -> m/NZS
    analogno za ny
    */
    int nx = n/NZD, ny = m/NZD;
    //
    int x = nx%2 == 0 ? 0 : m; //ako je paran zavrsavamo na levom zidu te je 0 a inace na desnom odn cela sirina
    int y = ny%2 == 0 ? 0 : n; //-||- odn visina
    cout << x << ' ' << y << endl;
    cout << ((nx-1)+(ny-1)) << endl;

    return 0;
}