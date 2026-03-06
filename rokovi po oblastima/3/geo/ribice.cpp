#include <bits/stdc++.h>
using namespace std;

long long orijentacija(pair<int,int>A, pair<int,int>B, pair<int,int>C){
    return (long long)(B.first-A.first)*(C.second-A.second) - (long long)(B.second-A.second)*(C.first-A.first);
}

long long rastojanje(pair<int,int>A, pair<int,int>B){
    return (long long)(A.first-B.first)*(A.first-B.first) + (long long)((A.second-B.second)*(A.second-B.second));
}

void prostMnogougao(vector<pair<int,int>> &tacke){
    //trazenje maksimalnog elementa
    auto max = max_element(begin(tacke),end(tacke),[](pair<int,int> A, pair<int,int> B){
        return A.first < B.first || (A.first == B.first && A.second > B.second);
    });

    //zamena prvog i maksimalnog
    swap(*begin(tacke),*max);
    pair<int,int> &p0 = tacke[0];

    //sortiranje ostatka
    sort(next(begin(tacke)),end(tacke),[&p0](pair<int,int>&A, pair<int,int>&B){
        long long o = orijentacija(p0,A,B);
        if(o==0)
            return rastojanje(p0,A) < rastojanje(p0,B);
        return o > 0;
    });

    //zamena kolinearnih tacaka na kraju
    auto it = prev(end(tacke));
    while(orijentacija(*prev(it),*it,p0)==0)
        it = prev(it);
    reverse(it,end(tacke));
}

bool uMnogouglu(vector<pair<int,int>>&tacke, pair<int,int> &t){
    int n = tacke.size();
    bool pripada = false;
    for(int i=0; i<n; i++){
        int j = (i+1)%n;
        if(tacke[i].first > tacke[j].first)
            swap(tacke[i],tacke[j]);
        if(tacke[i].first < t.first && t.first > tacke[j].first && orijentacija(tacke[i],tacke[j],t)<=0)
        //(tacke[i].y-P.y)*(tacke[j].x-tacke[i].x)<=(tacke[j].y-tacke[i].y)*(tacke[i].x-P.x)
            pripada = !pripada;
    }
    return pripada;
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> tacke(n);
    for(int i=0; i<n; i++)
        cin >> tacke[i].first >> tacke[i].second;
    prostMnogougao(tacke);
    pair<int,int> queryPoint;
    int res=0;
    while(m--){
        cin >> queryPoint.first >> queryPoint.second;
        if(uMnogouglu(tacke,queryPoint))
            res++;
    }
    cout << res << endl;

    return 0;
}