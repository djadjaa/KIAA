#include <bits/stdc++.h>

using namespace std;

long long prosireniEuklid(long long a, long long b, long long &s, long long &t){
    long long r0=a, r1=b, s0=1, s1=0, t0=0, t1=1;
    while(r1>0){
        long long q = r0/r1;
        long long tmp;

        tmp = r0;
        r0 =r1;
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

int main(){
    int n;
    cin >> n;
    while(n--){
        long long a,b;
        cin >> a >> b;
        long long x,y;
        long long minRazlika = prosireniEuklid(a,b,x,y);
        long long prviUdaracTrenutak = min(abs(x*a),abs(y*b));
        long long drugiUdaracTrenutak = max(abs(x*a),abs(y*b));
        cout << minRazlika << ' ' << prviUdaracTrenutak << ' ' << drugiUdaracTrenutak << endl;
    }

    return 0;
}