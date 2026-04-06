#include "Backtracking.h"

void encontrarSeamBacktrackingRec(const std::vector<std::vector<double>>& energia, int i,int j,int n ,int m ,std::pair<std::vector<int>, double>&S ,std::pair<std::vector<int>, double>&B) {
    if(i==n){
        if(B.empty() || S[1] < B[1]){
            B=S;
        }
        return;
    }
    if (S[1] < B[1]){
        if(j>0){ //bajamos por la izquierda siempre y cuando no estemos en un borde
        S[0].push_back(j - 1);
        s[1]+=energia[i][j-1];
        encontrarSeamFuerzaBrutaRec(energia, i + 1, j - 1, n, m, S, B);
        S[0].pop_back();
        s[1]-=energia[i][j-1];
    }
    
        //en todos los casos vamos a bajar por la rama del medio
        S[0].push_back(j);
        s[1]+=energia[i][j];
        encontrarSeamFuerzaBrutaRec(energia, i + 1, j, n, m, S, B);
        S[0].pop_back();
        s[1]-=energia[i][j];
    
        if(j<m-1){ //bajamos por la rama derecha siempre y cuando no estemos en un borde
            S[0].push_back(j + 1);
            s[1]+=energia[i][j+1];
            encontrarSeamFuerzaBrutaRec(energia, i + 1, j + 1, n, m, S, B);
            S[0].pop_back();
            s[1]-=energia[i][j+1];
        }
    }else{
        return;}
    
}

std::vector<int> encontrarSeamBacktracking(const std::vector<std::vector<double>>& energia) {
    int n= energia.size();
    int m= energia[0].size();
    std::pair<std::vector<int>,double> B;
    for (int j = 0; j < m; j++) { //hago la funcion recursiva por cada elemento de la primera fila
        std::pair<std::vector<int>,double> S;
        S[0].push_back(j);
        encontrarSeamBacktrackingRec(energia, 1, j, n, m, S, B);
    }
    return B;
}
