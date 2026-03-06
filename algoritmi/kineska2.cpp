#include <bits/stdc++.h>

using namespace std;

//proizvod
long long pm(long long x, long long y, long long n) {
    return ((x % n) * (y % n)) % n;
  }
  
  // racuna (z * x) mod (z * y)
  long long pmp(long long x, long long y, long long z) {
    return z * (x % y);
  }
  
  // zbir brojeva x i y po modulu n
  long long zm(long long x, long long y, long long n) {
    return ((x % n) + (y % n)) % n;
  }

long long prosireniNZD(long long a, long long b, long long &s, long long &t){
    int r0 = a, r1 = b, s0 = 1, s1 = 0, t0 = 0, t1 = 1;
    while(r1>0){
        long long q = r0/r1;
        long long tmp;

        tmp = r0;
        r0 = r1;
        r1 = tmp - q*r1;

        tmp = s0;
        s0 = s1;
        s1 = tmp - q*s1;

        tmp = t0;
        t0 = t1;
        t1 = tmp- q*t1;
    }
    s = s0;
    t = t0;
    return r0;
}

long long kineska(long long a, long long n, long long aj, long long nj){
    long long m, mj;
    long long g = prosireniNZD(n,nj,m,mj);
    long long N = n*nj; //modul
    long long proizvod1 = pm(a,mj,N);
    long long proizvod2 = pm(aj,m,N);

    long long proizvodfinal1 = pmp(proizvod1,n,nj);
    long long proizvodfinal2 = pmp(proizvod2,nj,n);

    long long res = zm(proizvodfinal1,proizvodfinal2,N);

    if(res<0)
        res+=N;
    return res;
}

int main(){

    long long a,n;
    cin >> a >> n;
    int vel=2;
    while(vel--){
        long long aj,nj;
        cin >> aj >> nj;
        a = kineska(a,n,aj,nj);
        n*=nj;
    }
    cout << a << endl;

    return 0;
}