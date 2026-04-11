#include "ProgramacionDinamica.h"
#include <limits>
#include <vector>


std::pair<std::vector<int>, double> encontrarSeamPDRec(const std::vector<std::vector<double>>& energia, int i, int j, int n, int m, std::vector<std::vector<std::pair<std::vector<int>, double>>>& memo) {
    if(memo[i][j].second != std::numeric_limits<double>::infinity()){   //caso base: el memo no esta vacio
        return memo[i][j];
    }
    if(i==0){                   //caso base estoy en la primera fila 
        std::pair<std::vector<int>, double > res; 
        res.first.push_back(j);
        res.second= energia[i][j];
        memo[i][j]= res;
        return res;
    }
    
    //incrementamos la energia actual



    if(j > 0 && j < m-1){    //si no estoy en un borde 
        std::pair<std::vector<int>, double > min;
        min.first= {};
        min.second= std::numeric_limits<double>::infinity();
        for(int k=j-1; k <= j+1; k++){
            std::pair<std::vector<int>, double> aux= encontrarSeamPDRec(energia, i-1, k, n , m, memo);
            if(min.second>aux.second){
                min=aux;
                }
        }
        min.first.push_back(j);
        min.second += energia[i][j];

        memo[i][j]= min;
        return memo[i][j];
    }
    else if(j==0){
        std::pair<std::vector<int>, double> min;
        min.first= {};
        min.second= std::numeric_limits<double>::infinity();
        for(int k=j; k <= j+1; k++){
            std::pair<std::vector<int>, double> aux= encontrarSeamPDRec(energia, i-1, k, n , m, memo);
            if(min.second>aux.second){
                min=aux;
                
            }
        }
        min.first.push_back(j);
        min.second += energia[i][j];
        memo[i][j]= min;
        return memo[i][j];
    }
    else{
        std::pair<std::vector<int>, double> min;
        min.first= {};
        min.second= std::numeric_limits<double>::infinity();
        for(int k=j-1; k <= j; k++){
            std::pair<std::vector<int>, double> aux = encontrarSeamPDRec(energia, i-1, k, n , m, memo);
            if(min.second>aux.second){
                min=aux;
            }
        }
        min.first.push_back(j);
        min.second += energia[i][j];
        memo[i][j]= min;
        return memo[i][j];
    }
    //PENSAR QUE HACER QUE CASO PARA PONER EL ELSE
}


std::vector<int> encontrarSeamPD(const std::vector<std::vector<double>>& energia) {
    //creo la estructura de datos-->MEMO
    int n= energia.size();
    int m= energia[0].size();
    std::vector<std::vector<std::pair<std::vector<int>, double>>> memo(
    n,
    std::vector<std::pair<std::vector<int>, double>>(
        m,
        { {}, std::numeric_limits<double>::infinity() }
    )
);


    for(int j = 0; j < m; j++){
        encontrarSeamPDRec(energia, n-1, j, n, m, memo);
    }   
    
    /*ahora busco el minimo-> luego del primer ciclo, todos los elementos de la ultima fila 
      ya estan resueltos con los minimos caminos llenos de energia*/

    //primer elemento de la ultima fila del memo(primer valor posible)
    std::pair<std::vector<int>, double> min= memo[n-1][0];

    //empiezo a comparar desde el primero
    for(int i=1; i<m; i++){
        if(min.second>memo[n-1][i].second){
            min=memo[n-1][i];
        }
    }
    return min.first;
}


//Desde aca es el codigo nuevo

std::pair<int, double> encontrarSeamPDRec(const std::vector<std::vector<double>>& energia, int i, int j, int n, int m, std::vector<std::vector<std::pair<int, double>>>& memo) {
    if(memo[i][j].second != std::numeric_limits<double>::infinity()){   //caso base: el memo no esta vacio
        return memo[i][j];
    }
    if(i==0){                   //caso base estoy en la primera fila 
        std::pair<int, double > res; 
        res.first=-1;
        res.second= energia[i][j];
        memo[i][j]= res;
        return res;
    }
    
    //definimos un mejor para comparar
    std::pair<int, double > min;
    int mejor; //la posicion del minimo
    min.second= std::numeric_limits<double>::infinity();

    if(j > 0 && j < m-1){    //si no estoy en un borde 
        
        //ciclo por las opciones del caso del medio => {j-1, j, j+1}
        for(int k=j-1; k <= j+1; k++){
            std::pair<int, double> aux= encontrarSeamPDRec(energia, i-1, k, n , m, memo); //llamado rec con la posicion k
            if(min.second>aux.second){//comparo energias

                //actualizo los valores en caso de un nuevo minimo
                min=aux;
                mejor=k;
                }
        }

    }
    else if(j==0){
        
        //pos para iterar=> {j, j+1}
        for(int k=j; k <= j+1; k++){
            std::pair<int, double> aux= encontrarSeamPDRec(energia, i-1, k, n , m, memo);
            if(min.second>aux.second){
                min=aux;
                mejor=k;
                
            }
        }
        
    }
    else{
        //pos para iterar=> {j-1, j}

        for(int k=j-1; k <= j; k++){
            std::pair<int, double> aux = encontrarSeamPDRec(energia, i-1, k, n , m, memo); 
            if(min.second>aux.second){
                min=aux;
                mejor= k;
            }
        }
        
    }
    //pongo solamente en el first la posicion del elemento de donde vino
        min.first= mejor;
        min.second += energia[i][j]; //sumo la energia acumulada


        //actualizo memo
        memo[i][j]= min;
        return memo[i][j];
    
}

//funcion para invertir la solucion dado que en la reconstruccion queda como primer posicion el ultimo elemento del camino
//devuelve el vector en orden=>primer elemento el primer elemento del camino
std::vector<std::pair<int,int>> invertirPairs(std::vector<std::pair<int,int>> aInvertir){
    std::vector<std::pair<int,int>> res;
    for(int i=aInvertir.size()-1; i>=0; i--){
        res.push_back(aInvertir[i]);
    }
    return res;
}


//funcion que arma un vector(queda invertido) del camino de la costura optima(de menor energia)
std::vector<std::pair<int,int>> reconstruccion(const std::vector<std::vector<double>>& energia, std::vector<std::vector<std::pair<int, double>>> &memo, int colInicio){
    
    int i= energia.size()-1;//empiezo en la ult fila
    int j= colInicio;//columna pasada por parametro de que tiene menor energia acumulada
    std::vector<std::pair<int, int>> respuesta; //vector con las <i,j>
    respuesta.push_back({i,colInicio});//pusheo el ult elemento, obs: el vector va a estar invertido
    i--;//reduzco la iteracion
    while(i >= 0){
        int posAnterior= memo[i][j].first;// valor de la pos del elemento anterior
        respuesta.push_back({i-1, posAnterior});
        j = posAnterior;//actualizo la columna en donde estoy
        i--;
    }

    //llamo a la funcion que invierte la solucion, asi se devuelve el vector en el orden esperado
    std::vector<std::pair<int,int>> res= invertirPairs(respuesta);
    return res;

}

std::vector<std::pair<int,int>> encontrarSeamPDNueva(const std::vector<std::vector<double>>& energia) {
    //creo el memo
    int n= energia.size();
    int m= energia[0].size();
    //memo= vector de vectores pair<int: columna "de donde viene", double: energia acumulada>
    std::vector<std::vector<std::pair<int, double>>> memo(
    n,
    std::vector<std::pair<int, double>>(m, {-1, std::numeric_limits<double>::infinity()}));

    //se hace un llamado de la auxiliar por columna
    for(int j = 0; j < m; j++){
        encontrarSeamPDRec(energia, n-1, j, n, m, memo);
    }   
    
    /*ahora busco el minimo-> luego del primer ciclo, todos los elementos de la ultima fila 
      ya estan resueltos con los minimos caminos llenos de energia*/

    //primer elemento de la ultima fila del memo(primer valor posible)
    std::pair<int, double> min= memo[n-1][0];
    
    //posicion con la que voy a hacer la recursion para reconstruir el camino
    int pos=0;

    //empiezo a comparar desde el primero
    for(int i=1; i<m; i++){
        if(min.second>memo[n-1][i].second){
            min=memo[n-1][i];
            pos= i;
        }
    }

    //hago para la reconstruccion
    std::vector<std::pair<int, int>> posColumna= reconstruccion(energia, memo, pos);
    return posColumna;
}
