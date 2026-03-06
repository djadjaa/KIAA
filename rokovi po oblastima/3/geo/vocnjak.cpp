//https://petlja.org/sr-Latn-RS/biblioteka/r/Zbirka3/konveksni_omotac

#include <bits/stdc++.h>
using namespace std;
/*
int orijentacija(pair<int,int> A, pair<int,int> B, pair<int,int> C) {
    return (B.first - A.first)*(C.second-A.second)-(B.second - A.second)*(C.first - A.first);
}*/

long long orijentacija(pair<int,int> A,
    pair<int,int> B,
    pair<int,int> C) {
return 1LL * (B.first - A.first) * (C.second - A.second)
- 1LL * (B.second - A.second) * (C.first - A.first);
}

/*
double rastojanje(pair<int,int> A, pair<int,int> B){
    return sqrt((A.first-B.first)*(A.first-B.first)+(A.second-B.second)*(A.second-B.second));
}*/

long long rastojanje(pair<int,int> A, pair<int,int> B) {
    long long dx = A.first - B.first;
    long long dy = A.second - B.second;
    return dx*dx + dy*dy;
}


vector<pair<int,int>> graham(vector<pair<int,int>> &tacke, int n){
    if(n<3)
        return tacke;
    pair<int,int> max = *max_element(tacke.begin(), tacke.end(), [](pair<int,int>&a, pair<int,int>&b){
        return a.first < b.first || (a.first==b.first && a.second > b.second);
    });

    auto it0 = find(tacke.begin(), tacke.end(), max);
    swap(*tacke.begin(), *it0);
    pair<int,int> &p0 = tacke[0];

    //sortiranje ostatka:
    sort(next(begin(tacke)), tacke.end(), [&p0](pair<int,int>&a, pair<int,int> &b){
        long long orij = orijentacija(p0,a,b);
        if(orij==0)
            return rastojanje(p0,a) < rastojanje(p0,b);
        return orij > 0;
    });

    //obrtanje poslednje kolinearne tacke:
    auto it = prev(end(tacke));
    while(it != tacke.begin()+1 && orijentacija(*prev(it), *it, p0)==0)
        it = prev(it);
    reverse(it,end(tacke));

    vector<pair<int,int>> omotac;
    omotac.push_back(tacke[0]);
    omotac.push_back(tacke[1]);
    for(int i=2; i<n; i++){
        while(omotac.size() >= 2  && orijentacija(omotac[omotac.size()-2], omotac[omotac.size()-1], tacke[i])<=0)
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
    vector<pair<int,int>> konveksniOmotac = graham(tacke,n);

    cout << konveksniOmotac.size() << endl;
    for(auto &p : konveksniOmotac)
        cout << p.first << ' ' << p.second << endl;

    return 0;
}