#include "ProgramacionDinamica.h"
#include <vector>
#include <limits>
#include <utility>

using std::vector;
using std::pair;
using std::numeric_limits;

pair<double, vector<int>> encontrarSeamPDRec(const vector<vector<double>>& energia, int i,int j, int n, int m, vector<vector<pair<double, vector<int>>>>& memo) {
    if (j < 0 || j >= m) {
        return {numeric_limits<double>::infinity(), {}};
    }
    if (memo[i][j].first != -1) {
        return memo[i][j];
    }
    if (i == n-1) {
        memo[i][j] = {energia[i][j], {j}};
        return memo[i][j];
    }
    auto izq = encontrarSeamPDRec(energia, i+1, j-1, n, m, memo);
    auto med = encontrarSeamPDRec(energia, i+1, j, n, m, memo);
    auto der = encontrarSeamPDRec(energia, i+1, j+1, n, m, memo);
    auto mejor = izq;
    if (med.first < mejor.first) {
        mejor = med;
    }
    if (der.first < mejor.first) {
        mejor = der;
    }
    vector<int> camino;
    camino.push_back(j);
    camino.insert(camino.end(), mejor.second.begin(), mejor.second.end());
    memo[i][j] = {energia[i][j] + mejor.first, camino};
    return memo[i][j];
}

vector<int> encontrarSeamPD(const vector<vector<double>>& energia) {
    if (energia.empty() || energia[0].empty()) {
        return {};
    }
    int n = energia.size();
    int m = energia[0].size();
    vector<vector<pair<double, vector<int>>>> memo(n, vector<pair<double, vector<int>>>(m, {-1, {}}));
    double mejorEnergia = numeric_limits<double>::infinity();
    vector<int> mejorCamino;
    for (int j = 0; j < m; j++) {
        pair<double, vector<int>> actual = encontrarSeamPDRec(energia, 0, j, n, m, memo);
        if (actual.first < mejorEnergia) {
            mejorEnergia = actual.first;
            mejorCamino = actual.second;
        }
    }
    for (int i = 0; i < mejorCamino.size(); i++) {
        mejorCamino[i] += 1;
    }
    return mejorCamino;
}