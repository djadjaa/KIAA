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

bool inverz(long long n, long long a, long long &t){
    long long s;
    long long r = prosireniNZD(n,a,s,t);
    /*
    if(t<0)
        t+=n;
    return t==1;*/
    
    if(r!=1)
        return false;
    t = mod(t,n);
    return true;
}
bool kineskaTeorema(vector<long long>&n, vector<long long>&a, long long dim, long long &res){
    long long N=1;
    for(int i=0; i<dim; i++){
        N*=n[i];
    }
    res=0;
    for(int i=0; i<dim; i++){
        long long Ni = N/n[i];
        long long m;
        if(!inverz(n[i],Ni,m))
            return false;
          
        long long proizvod = mul(a[i],m,N);
        long long proizvodFinal = pmp(proizvod,n[i],Ni);
        res = add(res,proizvodFinal,N);
        //res = (res + a[i] * Ni % N * m % N) % N;
    }
    return true;
}   

int main(){

    long long dim;
    cin >> dim;
    vector<long long> a(dim);
    vector<long long> n(dim);
    for(int i=0; i<dim; i++)
        cin >> a[i] >> n[i];
    long long res;
    if(!kineskaTeorema(n,a,dim,res))
        cout << "nisu prosti\n";
    
    cout << res << endl;

    return 0;
}