#include <bits/stdc++.h>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<vector<int>> mat(n,vector<int>(n));
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cin >> mat[i][j];
    }
    vector<vector<int>> najkraciPutevi = mat;
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                najkraciPutevi[i][j] = min(najkraciPutevi[i][j], 
                    najkraciPutevi[i][k]+najkraciPutevi[k][j]);
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << mat[i][j] - najkraciPutevi[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}