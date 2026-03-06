#include <bits/stdc++.h>

using namespace std;

long long ojler(long long n){
    long long pr = n;
    for(long long d = 2; d*d<=n; d++){
        if(n%d==0){
            pr = (pr/d)*(d-1);
            while(n%d==0)
                n/=d;
        }
    }
    if(n>1)
        pr = (pr/n)*(n-1);
    return pr;
}

int main(){
    long long n;
    cin >> n;
    vector<long long> delioci;
    delioci.push_back(1);
    if(n>1)
        delioci.push_back(n);
    long long d;
    for(d=2; d*d<n; d++){
        if(n%d==0){
            delioci.push_back(d);
            delioci.push_back(n/d);
        }
    }
    if(d*d==n)
        delioci.push_back(d);
    
    long long sum=0;
    for(long long del : delioci)
        sum += ojler(del);
    cout << sum << endl;

    return 0;
}