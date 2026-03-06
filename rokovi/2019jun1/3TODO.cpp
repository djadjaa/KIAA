#include <bits/stdc++.h>
using namespace std;

pair<long long,long long> vec(pair<long long,long long> a, pair<long long,long long> b) {
	return {b.first - a.first, b.second - a.second};
}

int cross(pair<long long,long long> u, pair<long long,long long> v) {
	return u.first * v.second - u.second * v.first;
}

int orient(pair<long long,long long> a, pair<long long,long long> b, pair<long long,long long> c) {
	return cross(vec(a, b), vec(a, c));
}


vector<pair<long long,long long>> graham(vector<pair<long long,long long>>& p){
    swap(p[0],*min_element(begin(p),end(p)));
    sort(begin(p)+1, end(p), [&](pair<long long,long long>a, pair<long long,long long>b){
        return orient(p[0],a,b) > 0;
    });
    
}

int main(){

    int m,n;
    cin >> m >> n;
    vector<pair<long long,long long>> k(m), s(n);
    for(int i=0; i<m; i++)
        cin >> k[i].first >> k[i].second;
    for(int i=0; i<n; i++)
        cin >> s[i].first >> s[i].second;

    auto hull = graham(s);

    return 0;
}