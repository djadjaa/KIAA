#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <queue>

using namespace std;

int main()
{
	string str = "ABCDBAGHCHFAC";
	int k = 3;

    //mapa koja kao kljuc ima slovo a vrednost par u kom je prvi broj pojavljivanja a drugi poslednja pozicija u kom se pojavljuje
	map<char, pair<int,int>> map; 
    for(int i=0; i<str.length(); i++){
        map[str[i]].first++;
        map[str[i]].second = i;
    }
    priority_queue<int,vector<int>,greater<int>>heap;
    for(auto it:map){
        int brpojavljivanja = it.second.first;
        int poslednjapoz = it.second.second;

        if(brpojavljivanja==1)
            heap.push(poslednjapoz);
    }
    //uzimamo prvih k elem hipa
    while(k-- && !heap.empty()){
        //poslednji elem:
        int minPoslPoz = heap.top();
        heap.pop();
        cout << str[minPoslPoz] << " "; //ispisujemo karakter koji se nalazi na toj poz
    }
    cout << "\n";
	return 0;
}
