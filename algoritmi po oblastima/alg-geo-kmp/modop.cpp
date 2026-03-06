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

unsigned long long stepen(long long a, long long n, long long m){
    unsigned long long s = 1;
    while(n>0){
        if((n&1)==0){
            a = ((unsigned long long)a*(unsigned long long)a)%m;
            n = n>>1;
        }else{
            s =((unsigned long long)s*(unsigned long long)a)%m;
            n--;
        }
    }
    return s;
}

long long pmp(long long a, long long b, long long c){
    return c*(a%b);
}

int main(){
    long long a,b,m;
    cin >> a >> b >> m;
    cout << mod(a,m) << ' ' << add(a,b,m) << ' ' << mul(a,b,m) << ' ' << stepen(a%m,b,m) << endl;


    return 0;
}