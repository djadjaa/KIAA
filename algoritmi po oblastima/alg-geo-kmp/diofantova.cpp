#include <bits/stdc++.h>

using namespace std;
long long mod(long long a, long long m){
    return (m+a%m)%m;
}
long long prosireniNZD(long long x, long long y, long long &s, long long &t){
    long long r0=x, r1=y, s0=1, s1=0, t0=0, t1=1;
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
    s = s0;
    t = t0;
    return r0;
}

bool inverz(long long a, long long n, long long &t){
    long long s;
    long long res = prosireniNZD(n,a,s,t);
    if(res!=1)
        return false;
    t = mod(t,n);
    return true;
}

int main(){

    long long x,y;
    cin >> x >> y;
    long long s,t;
    cout << s << ' ' << t << ' ' << prosireniNZD(x,y,s,t) << endl;
    cout << (inverz(x,y,t) ? "inverz\n" : "nije inverz\n");

    return 0;
}