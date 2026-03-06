#include <bits/stdc++.h>
using namespace std;

int orijentacija(pair<int,int> A, pair<int,int> B, pair<int,int> C) {
    return (B.second - A.second)*(C.first - B.first) - (B.first - A.first)*(C.second-B.second);
}

double rastojanje(pair<int,int> A, pair<int,int> B){
    return sqrt((A.first-B.first)*(A.first-B.first)+(A.second-B.second)*(A.second-B.second));
}

vector<pair<int,int>> graham(vector<pair<int,int>>&tacke, int n){
    if(n<3)
        return tacke;
    pair<int,int> p0 = *min_element(tacke.begin(), tacke.end(), [](pair<int,int>a, pair<int,int>b){
        //first - x ; second - y
        return make_pair(a.second,a.first)<make_pair(b.second,b.first);
    });
    sort(tacke.begin(), tacke.end(), [&p0](pair<int,int> &a, pair<int, int> &b){
        int val = orijentacija(p0,a,b);
        if(val==0)
            return rastojanje(p0,a) < rastojanje(p0,b);
        return val > 0;
    });
    vector<pair<int,int>> omotac;
    for(int i=0; i<n; i++){
        while(omotac.size() > 1 && orijentacija(omotac[omotac.size()-2],omotac[omotac.size()-1],tacke[i])<=0)
            omotac.pop_back();
        omotac.push_back(tacke[i]);
    }
    return omotac;
}

int main(){

    int n;
    cin >> n;
    vector<pair<int,int>> tacke(n);
    for(int i=0; i<n; i++)
        cin >> tacke[i].first >> tacke[i].second;
    pair<int,int> querypoint;
    cin >> querypoint.first >> querypoint.second;
    vector<pair<int,int>> konveksniOmotac = graham(tacke,n);
    double najboljeRastojanje = rastojanje(querypoint, konveksniOmotac[0]);
    pair<int,int> najboljaTacka = konveksniOmotac[0];

    for(int i=1; i<konveksniOmotac.size(); i++){
        if(rastojanje(konveksniOmotac[i],querypoint)<najboljeRastojanje){
            najboljeRastojanje = rastojanje(konveksniOmotac[i],querypoint);
            najboljaTacka = konveksniOmotac[i];
        }
    }
    cout << najboljaTacka.first << ' ' << najboljaTacka.second << endl;
    return 0;
}