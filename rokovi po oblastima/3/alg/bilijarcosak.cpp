#include <bits/stdc++.h>

using namespace std;

int nzd(int x, int y){
    while(y>0){
        int tmp = x%y;
        x = y;
        y = tmp;
    }
    return x;
}

int main(){

    int n,m;
    cin >> m >> n;
    //rastojanje ce biti nzs(m,n)
    //broj odbijanja ceo dobiti podelom rastojanja sa sirinom odnosno duzinom
    //uk br odbijanja sabiramo
    int NZD = nzd(m,n); 
    //nzs je (m*n)/nzd
    int nx = n/NZD; // nzs/m
    int ny = m/NZD; // nzs/n
    //koordinate:
    /*
    Ako je broj nx neparan, loptica se nalazi u nekoj rupi na desnoj,
    a ako je paran, nalazi se u nekoj rupi na levoj ivici stola,
    pa x koordinatu rupe lako određujemo analizom parnosti broja nx. 
    */
    int x = nx % 2 == 0 ? 0 : m;
    int y = ny % 2 == 0 ? 0 : n;
    cout << x << ' ' << y << endl;
    cout << (nx-1)+(ny-1) << endl;
    return 0;
}