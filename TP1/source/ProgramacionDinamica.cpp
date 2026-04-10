#include "ProgramacionDinamica.h"
#include <vector>
#include <limits>
#include <utility>


// función recursiva
std::pair<double, std::vector<int>> encontrarSeamPDRec(const std::vector<std::vector<double>>& energia, int i,int j, int n, int m, std::vector<std::vector<std::pair<double, std::vector<int>>>>& memo) {

    if (j < 0 || j >= m) {          // columna inválida
        return {std::numeric_limits<double>::infinity(), {}}; 
    }

    if (memo[i][j].first != -1) {             // si ya resolvió este subproblema reutiliza el resultado (memorización)
        return memo[i][j]; 
    }

    if (i == n-1) {                             // si está en el final de la imagen el camino es el píxel ese
        memo[i][j] = {energia[i][j], {j}}; 
        return memo[i][j];
    }

    auto izq = encontrarSeamPDRec(energia, i+1, j-1, n, m, memo);       // recursión por izquierda
    auto med = encontrarSeamPDRec(energia, i+1, j, n, m, memo);         // recursión por centro
    auto der = encontrarSeamPDRec(energia, i+1, j+1, n, m, memo);       // recursión por derecha

    auto mejor = izq;                   // asume izquierda como mejor 
    if (med.first < mejor.first) {      // comparo con el del centro
        mejor = med;
    }
    if (der.first < mejor.first) {      // comparo con el de la derechaderecha
        mejor = der;
    }

    std::vector<int> camino;
    camino.push_back(j);                // agrega pixel actual
    camino.insert(camino.end(), mejor.second.begin(), mejor.second.end());  // concatena el mejor camino para abajo
    memo[i][j] = {energia[i][j] + mejor.first, camino}; 
    return memo[i][j];
}


// función principal
std::vector<int> encontrarSeamPD(const std::vector<std::vector<double>>& energia) {
    if (energia.empty() || energia[0].empty()) { 
        return {};
    }

    int n = energia.size();         // filas
    int m = energia[0].size();      // columnas
    std::vector<std::vector<std::pair<double, std::vector<int>>>> memo(n, std::vector<std::pair<double, std::vector<int>>>(m, {-1, {}}));     // tabla de memoización
    double mejorEnergia = std::numeric_limits<double>::infinity();
    std::vector<int> mejorCamino;

    for (int j = 0; j < m; j++) {               // comenzando desde cada columna posible en la primer fila
        std::pair<double, std::vector<int>> actual = encontrarSeamPDRec(energia, 0, j, n, m, memo); 
        if (actual.first < mejorEnergia) {      // si encuentra un mejor camino
            mejorEnergia = actual.first;
            mejorCamino = actual.second;
        }
    }

    for (int i = 0; i < mejorCamino.size(); i++) { 
        mejorCamino[i] += 1;                    // pasa de base 0 a base 1 (formato de salida)
    }
    return mejorCamino;
}