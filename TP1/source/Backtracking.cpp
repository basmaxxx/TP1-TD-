#include "Backtracking.h"

void encontrarSeamBacktrackingRec(const std::vector<std::vector<double>>& energia, int i,int j,int n ,int m ,std::pair<std::vector<int>, double>&S ,std::pair<std::vector<int>, double>&B) {
    if(i==n){
        if(B.first.empty() || S.second < B.second){
            B=S;
        }
        return;
    }
    if (S.second < B.second){
        if(j>0){ //bajamos por la izquierda siempre y cuando no estemos en un borde
            S.first.push_back(j - 1);
            S.second+=energia[i][j-1];
            encontrarSeamBacktrackingRec(energia, i + 1, j - 1, n, m, S, B);
            S.first.pop_back();
            S.second-=energia[i][j-1];
    }
    
        //en todos los casos vamos a bajar por la rama del medio
        S.first.push_back(j);
        S.second+=energia[i][j];
        encontrarSeamBacktrackingRec(energia, i + 1, j, n, m, S, B);
        S.first.pop_back();
        S.second-=energia[i][j];
    
        if(j<m-1){ //bajamos por la rama derecha siempre y cuando no estemos en un borde
            S.first.push_back(j + 1);
            S.second+=energia[i][j+1];
            encontrarSeamBacktrackingRec(energia, i + 1, j + 1, n, m, S, B);
            S.first.pop_back();
            S.second-=energia[i][j+1];
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
        S.first.push_back(j);
        encontrarSeamBacktrackingRec(energia, 1, j, n, m, S, B);
    }
    return B.first;
}
