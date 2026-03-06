#include <bits/stdc++.h>

using namespace std;

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
    for(auto d : delioci)
        cout << d << ' ';
    cout << endl;
    return 0;
}