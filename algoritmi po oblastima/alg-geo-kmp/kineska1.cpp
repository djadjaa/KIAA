#include <bits/stdc++.h>
using namespace std;

long long mod(long long a, long long m){
    return (m+a%m)%m;
}

long long add(long long a, long long b, long long m){
    return mod(mod(a,m)+mod(b,m),m);
}
long long mul(long long a, long long b, long long m){
    return mod(mod(a,m)*mod(b,m),m);
}
long long pmp(long long a, long long b, long long c){
    return c*(a%b);
}

long long prosireniNZD(long long a, long long b, long long &s, long long &t){
    long long r0 = a, r1 = b, s0 = 1, s1 = 0, t0 = 0, t1 = 1;
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

long long kineskaTeorema(long long a1, long long n1, long long a2, long long n2){
    long long m1, m2;
    int d = prosireniNZD(n1,n2,m1,m2);
    if(a1%d!=a2%d)
        return -1;
    long long n = (n1/d)*n2;
    long long proizvod1 = mul(a1,m2,n);
    long long proizvod2 = mul(a2,m1,n);
    long long proizvod1Final = pmp(proizvod1,n1,n2/d);
    long long proizvod2Final = pmp(proizvod2,n2,n1/d);
    long long sum = add(proizvod1Final,proizvod2Final,n);
    if(sum<0)
        sum+=n;
    return sum;
}

int main(){

    long long a1,a2,n1,n2;
    cin >> a1 >> a2 >> n1 >> n2;
    cout << kineskaTeorema(a1,n1,a2,n2) << endl;

    return 0;
}