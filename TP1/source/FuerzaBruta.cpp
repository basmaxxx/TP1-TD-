#include "FuerzaBruta.h"

double calcular_energia(vector<int> & camino, vector<std::vector<double>>& energia){
    double total =0;
    int n= energia.size();
    
    for(int i=0; i<n;i++){
        total += energia[i][camino[i]];
    }
    return total;
}
vector<int> encontrarSeamFuerzaBrutarrec(const std::vector<std::vector<double>>& energia, i, j,n,m,S,B) {
    if(i==n || j==m){
        if(calcular_energia(S)< calcular_energia(B)){
            B=S;
        }
        return B;
    }
    if(j>0){
        vector<int> CI= S + {j-1};
        encontrarSeamFuerzaBrutarrec(energia,i+1,j-1,n,m,CI,B)
        if(j<m){
            vector<int> CD= S + {j+1};
            encontrarSeamFuerzaBrutarrec(energia,i+1,j+1,n,m,CD,B)}
    }
    vector<int> CM= S + {j};
    encontrarSeamFuerzaBrutarrec(energia,i+1,j+1,n,m,CM,B)
    }


std::vector<int> encontrarSeamFuerzaBruta(const std::vector<std::vector<double>>& energia) {
    int n= energia.size();
    int m= energia[0].size();
    vector<int> S;
    vector<int> B;
    int i, j=0;
    return encontrarSeamFuerzaBruta(energia,i,j, n,m, S,B);
}
