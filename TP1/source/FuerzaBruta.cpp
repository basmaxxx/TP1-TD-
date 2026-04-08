#include "FuerzaBruta.h"
#include <limits>

double calcular_energia(std::vector<int> &camino, const std::vector<std::vector<double>>& energia) {
    double total = 0;
    int n = energia.size();
    for (int i = 0; i < n; i++) {
        total += energia[i][camino[i]];
    }
    return total;
}
void encontrarSeamFuerzaBrutaRec(const std::vector<std::vector<double>>& energia, int i,int j,int n ,int m ,std::vector<int>&S ,std::vector<int>&B, double energiaActual, double& mejorEnergia) {
    if(i==n){
        if(B.empty() || energiaActual < mejorEnergia ){
            mejorEnergia = energiaActual;
            B = S;
        }
        return;
    }

    if(j>0){ //bajamos por la izquierda siempre y cuando no estemos en un borde
        S.push_back(j - 1);
        encontrarSeamFuerzaBrutaRec(energia, i + 1, j - 1, n, m, S, B, energiaActual + energia[i][j - 1], mejorEnergia);
        S.pop_back();
    }
    
    //en todos los casos vamos a bajar por la rama del medio
    S.push_back(j);
    encontrarSeamFuerzaBrutaRec(energia, i + 1, j, n, m, S, B, energiaActual + energia[i][j], mejorEnergia);
    S.pop_back();
    
    if(j<m-1){ //bajamos por la rama derecha siempre y cuando no estemos en un borde
        S.push_back(j + 1);
        encontrarSeamFuerzaBrutaRec(energia, i + 1, j + 1, n, m, S, B, energiaActual + energia[i][j + 1], mejorEnergia);
        S.pop_back();
    }
}

std::vector<int> encontrarSeamFuerzaBruta(const std::vector<std::vector<double>>& energia) {
    if (energia.empty()) {
        return {};
    }
    int n= energia.size();
    int m= energia[0].size();
    std::vector<int> B;
    double mejorEnergia = std::numeric_limits<double>::infinity();
    for (int j = 0; j < m; j++) { //hago la funcion recursiva por cada elemento de la primera fila
        std::vector<int> S;
        S.push_back(j);
        encontrarSeamFuerzaBrutaRec(energia, 1, j, n, m, S, B, energia[0][j], mejorEnergia);
    }
    return B;
}


//ESTA MAL CONTAR DESDE CERO Y NO DE 1?????