/*
poruka se sifruje ovako:
y=(a⋅x)mod n
a i n su uzajamno prosti -> nzs(a,n)=1
da bi pronasli x, mora da ponisti mnozenje sa a preko multiplikativnog inverza
x = y*a^-1 mod n
-> a*a^-1 - n*k = 1
-> a*x+n*y = 1
-> a*x+n*y = nzs(a,n) - diofantova jna
*/

#include <iostream>
using namespace std;
/*
long long euklidovAlg(long long a, long long b, long long &x, long long &y){
    //Bazični slučaj
    if(a==0 && b==0){
        x=0;
        y=0;
        return 0;
    }
    if(b==0){
        //a*1+0*0=a
        x=1;
        y=0;
        return a; //nzd(a,0) = a
    }
    if(a==0){
        x=0;
        y=1;
        return b; //nzd(0,b)=b;
    }
    long long x1,y1;
    long long g = euklidovAlg(b,a%b,x1,y1); //b⋅x1+(a mod b)⋅y1
    x = x1;
    /*
    a mod b=a−(a/b)⋅b
    ubacimo u b⋅x1+(a mod b)⋅y1
    b⋅x1+(a−(a/b)⋅b)⋅y1 => a⋅y1+b⋅(x1−(a/b)⋅y1)
    tada dobijamo y: 
    */
   /* y = x1-(a/b)*y1;
    return g;
}*/

long long euklidovAlg(long long a, long long b, long long &x, long long &y){
    long long r0=a, r1=b;
    long long x0=1, x1=0;
    long long y0=0, y1=1;

    while(r1>0){
        long long q = r0/r1; //a/b
        long long tmp;

        tmp = r0;
        r0 = r1;
        r1 = tmp - q*r1;

        tmp = x0;
        x0 = x1;
        x1 = tmp - q*x1;

        tmp = y0;
        y0 = y1;
        y1 = tmp - q*y1;
    }
    x = x0, y = y0;
    return r0; //prvi ostatak
}

long long modInv(long long a,long long n){
    long long x,y;
    long long g = euklidovAlg(a,n,x,y);
    //dobijamo x i y  s tim da nam je x inverz
    if(g!=1)
        return -1;
    else
        return (x%n+n)%n; //normalizujemo inverz jer moze ispasti negativan
}

int main(){

    long long a,n;
    cin >> a >> n;
    long long inv = modInv(a,n);
    int q;
    cin >> q;
    while(q--){
        long long y;
        cin >> y;
        long long x = (y*inv)%n;
        cout << x << endl;
    }

    return 0;
}