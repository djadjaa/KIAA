#include <bits/stdc++.h>

using namespace std;

long long prosireniNZD(long long a, long long b, long long &s, long long &t){
    long long r0=a, r1=b, s0=1, s1=0, t0=0, t1=1;
    while(r1>0){
        long long q = r0/r1;
        long long tmp;

        tmp = r0;
        r0 = r1;
        r1 = tmp-q*r1;

        tmp = s0;
        s0 = s1;
        s1 = tmp-q*s1;

        tmp = t0;
        t0 = t1;
        t1 = tmp-q*t1;
    }
    s=s0;
    t=t0;
    return r0;
}
/*
bool inverz(long long n, long long a, long long &t){
    long long s;
    long long r = prosireniNZD(n,a,s,t);
    if(t<0)
        t+=n;
    return t==1;
}
*/
long long kineska(long long a, long long n, long long b, long long m){
    long long x,y;
    long long g = prosireniNZD(n,m,x,y);
    if((b-a)%g!=0)
        return -1;
    int nzs = n/g*m;
    int t = (a+(b-a)/g*x%(m/g)*n)%nzs;
    if(t<0)
        t+=nzs;
    return t;
}

int main(){

    long long n;
    long long i1, j1, i2, j2;
    cin >> n >> i1 >> j1 >> i2 >> j2;

    int a = ((i2 - i1) % n + n) % n;       // t ≡ a (mod n)
    int b = ((j1 - j2) % (n+1) + (n+1)) % (n+1); // t ≡ b (mod n+1)

    long ans = kineska(a, n, b, n+1);

    cout << ans << "\n";



    return 0;
}