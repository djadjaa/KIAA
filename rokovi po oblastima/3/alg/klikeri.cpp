#include <bits/stdc++.h>

using namespace std;

int prosireniNZD(long long n1, long long n2, long long &x1, long long &x2){
    long long r0 = n1, r1 = n2;
    long long s0 = 1, s1 = 0;
    long long t0 = 0, t1 = 1;

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

    x1 = s0;
    x2 = t0;
    return r0; //d
}

int main(){
    int n;
    cin >> n;
    long long c1,n1,c2,n2;
    cin >> c1 >> n1 >> c2 >> n2;
    long long x1,x2;
    int d = prosireniNZD(n1,n2,x1,x2);
    if(n%d!=0)
        cout << -1 << endl;
    else{
        //odredjujemo najmanju cenu u zavisnosti od resenja:
        //zaokruzujemo na najmanju celobrojnu vrednost
        long long kL = ceil(-x2*n/n1);
        //analogno na najvecu celobrojnu:
        long long kU = floor(x1*n/n2);

        if(kL > kU)
            cout << -1 << endl;
        else{
            //lower:
            long long m1L = (x1*n-kL*n2)/d;
            long long m2L = (x2*n+kL*n1)/d;
            long long cL = m1L*c1+m2L*c2;
            //upper:
            long long m1U = (x1*n-kU*n2)/d;
            long long m2U = (x2*n+kU*n1)/d;
            long long cU = m1U*c1+m2U*c2;

            cout << min(cL,cU) << endl;
        }
    }
    return 0;
}