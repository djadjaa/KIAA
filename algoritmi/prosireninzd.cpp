#include <bits/stdc++.h>
using namespace std;

long long prosireniNZD(long long x, long long y, long long &s, long long &t){
    int r0 = x, r1 = y, s0 = 1, s1=0, t0=0, t1=1;
    while(r1>0){
        long long q = r0/r1;
        long long tmp;

        tmp =r0;
        r0 = r1;
        r1 = tmp - q*r1;

        tmp = s0;
        s0 = s1;
        s1 = tmp - q*s1;

        tmp = t0;
        t0 = t1;
        t1 = tmp - q*t1;
    }
    s = s0;
    t = t0;
    return r0;
}

int main(){

    int n;
    long long x,y;
    cin >> n;
    while(n--){
        cin >> x >> y;
        long long s,t;
        long long minrazl = prosireniNZD(x,y,s,t);
        long long prvitren = min(abs(s*x),abs(t*y));
        long long drugitren = max(abs(s*x),abs(t*y));
        cout << minrazl << ' '  << prvitren << ' ' << drugitren << endl;
    }

    return 0;
}