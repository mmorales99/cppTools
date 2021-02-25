#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void ordenar(vector<float>&l1, vector<float>&l2);

int main(){

    vector<float> l1 = {61.5, 73.2, 70.0, 88.0, 75.6, 81.33, 99.8, 52.4, 88.0, 75.0}; // 10 pesos diferents
    
    vector<float> l2 = {80.0, 88.0, 70.0, 73.2, 49.12, 78.2, 91.3}; // 7 pesos diferents
    
    cout << "Listas previo a la ordenacion: " << endl << "Lista 1:\nComponentes: ";
    for ( unsigned i = 0; i < l1.size(); i++) cout << l1[i] <<" ";
    cout << endl;
    cout << "Lista 2:\nComponentes: ";
    for ( unsigned i = 0; i < l2.size(); i++) cout << l2[i] <<" ";
    cout << endl;

    ordenar(l1, l2);

    cout << "Despues de la ordenacion: \n" << "Lista 1:\nComponentes: ";
    for ( unsigned i = 0; i < l1.size(); i++) cout << l1[i] <<" ";
    cout << endl;
    cout << "Lista 2:\nComponentes: ";
    for ( unsigned i = 0; i < l2.size(); i++) cout << l2[i] <<" ";
    cout << endl;
    cout << "Suma de componentes:\nL1: ";
    unsigned total;
    for (size_t i = 0; i < l1.size(); i++) total+=l1[i];
    cout << total << endl << "L2: ";
    total = 0;
    for (size_t i = 0; i < l2.size(); i++) total+=l2[i];
    cout << total << endl;

    return 0;
}

/**
 * Devuelve la suma de todos los elementos de un vector
 * @param l1 : vector que contiene los elementos a sumar
 * @return sumatorio de los elementos del vector
 */
float get_list_sum(vector<float>l1){
    float l1_sum = 0;
    for (size_t i = 0; i < l1.size(); i++) l1_sum += l1[i];
    return l1_sum;
}

/**
 * Devuelve la similaridad entre dos listas de valores
 * @param l1 : lista 1
 * @param l2 : lista 2
 * @return cantidad de parecido entre la suma de pesos de las 2 listas, oscila entre 0 y INF
 */ 
double get_similarity(vector<float>l1, vector<float>l2){
    float l1_sum=get_list_sum(l1), l2_sum=get_list_sum(l2);
    return (l1_sum<l2_sum ? l1_sum / l2_sum : l2_sum / l1_sum);
}

/**
 * Devuelve la media de una lista de valores
 * @param l1 : lista de valores numericos
 * @return mean : media aritmetica de los valores
 */ 
double get_mean(vector<float>l1){
    double mean = 0;
    for (size_t i = 0; i < l1.size(); i++) mean+=l1[i];
    mean/=l1.size();
    return mean;
}

/**
 * Calcula la poscicion de los valores extremos de una lista. Obtenido el valor extremo de toda la lista, devuelve su posicion.
 * Detalladamente, obtiene la media de la lista, fija los parametros del primer valor, e itera sobre la lista para obtener el valor mas separado del punto medio, sea por encima o abajo del valor medio.
 * @param l1 : lista sobre la que obtener el valor mas extremo
 * @return (siendo de tipo size_t que se extiende en un unsigned long int) posicion del valor extremo en la lista
 */ 
size_t get_xtreme_pos(vector<float>l1){
    float mean = get_mean(l1); // recalcula la media de la lista
    float xtreme = l1[0]; // primer elemento de la lista
    float xtreme_dif = abs(xtreme - mean); // calcula la distancia al punto medio
    size_t xtreme_pos = 0; // establece que el punto es el primero de la lista
    for (size_t i = 1; i < l1.size(); i++){ // itera sobre toda la lista
        float aux = abs(l1[i] - mean); // recalcula cada una de las posiciones de la lista
        if(aux>xtreme_dif){ // se queda con la mas lejana
            xtreme = l1[i];
            xtreme_dif = aux;
            xtreme_pos = i;
        }
    }
    return xtreme_pos;
}

/**
 * Cambia los valores de lista.
 * @param l1 : lista 1
 * @param p1 : posicion de la lista 1
 * @param l2 : lista 2
 * @param p2 : posicion de la lista 2
 */ 
void swap_xtreme(vector<float>&l1, size_t p1, vector<float>&l2, size_t p2){
    float l1_e = l1[p1];
    float l2_e = l2[p2];
    l1.erase(l1.begin()+p1);
    l2.erase(l2.begin()+p2);
    l1.push_back(l2_e);
    l2.push_back(l1_e);
}

/**
 * Equilibra los datos de los vectores para igualar su tamanyo, si no se puede rellena con 0s
 * @param l1 : Lista 1
 * @param l2 : Lista 2
 */ 
void balance_vector_elements_cuantity(vector<float>&l1, vector<float>&l2){
    if(l1.size() != l2.size()){
        if(l1.size() > l2.size()){
            int dif = (l1.size() - l2.size())/2;
            for (size_t i = 0; i < dif; i++){ 
                l2.push_back(l1[l1.size()-1]);
                l1.pop_back();
            }
            for (size_t i = l2.size(); i < l1.size(); i++) l2.push_back(0);
        }
        if(l1.size() < l2.size()){
            int dif = (l2.size() - l1.size())/2;
            for (size_t i = 0; i < dif; i++){ 
                l1.push_back(l2[l2.size()-1]);
                l2.pop_back();
            }
            for (size_t i = l1.size(); i < l2.size(); i++) l1.push_back(0);
        }
    }
}

/**
 * Calcula la solucion con mejor optimalidad para la distribucion de cargas sobre dos listas de numeros.
 * Si las dos listas se componen por 1 unico valor cada una, no es una opcion ejecutable dado que es la solucion misma.
 * Para listas mayores comprueba que la carga no sea la misma estrictamente hablando, en dicho caso es la solucion misma.
 * Para listas no triviales donde las cargas ya esten dispuestas con equidad, este algoritmo busca por los pesos medios de las listas que se le pasen por parametro.
 * Sean listas no triviales todas aquellas con diferentes o igual cantidad de elementos, pero con medias de peso diferentes.
 * Sea por tanto operable el acercamiento de las medias.
 * Para ello es necesario calcular la distribucion ideal como la biparticion de los pesos, dado que no es posible, se procede al desplazamiento de extremos.
 * En el desplazamiento de extremos, se buscan los valores extremos de cada lista y se intercambian con el fin de obtener la combinacion mas optima.
 * @param l1 : Lista 1
 * @param l2 : Lista 2
 */
void ordenar(vector<float>&l1, vector<float>&l2){
    if(l1.size()<2 && l2.size()<2) return; // si las listas no son de mas de 1 elemento no se ejecuta el calculo
    balance_vector_elements_cuantity( l1, l2); // se balancea la cantidad de elementos de la lista mas pequenya a la mas grande
    double similaridad = get_similarity(l1,l2); // obtiene la similaridad de las listas
    if(similaridad == 1) return; // les dos lliestes son iguales de valor
    const float UMBRAL_SIMILARIDAD = ( get_list_sum(l1) + get_list_sum(l2) ) / 2; // obtiene el valor ideal de pesos de cada una de las listas
    float means_dif = 0; 
    swap_xtreme(l1, get_xtreme_pos(l1), l2, get_xtreme_pos(l2)); // obligatoriamente hace un cambio para intentar obtener un mejor resultado
    means_dif = abs(UMBRAL_SIMILARIDAD - get_mean(l1)); // guarda las nuevas medias
    do{ // recalcula un nuevo resultado sobre el obtenido anteriormente, si este nuevo resultado es mejor, lo actualiza e intenta obtener uno mejor, sino FIN DEL PROGRAMA
        float ameans_dif = 0;
        vector<float> al1 = l1, al2 = l2;
        swap_xtreme(al1, get_xtreme_pos(al1), al2, get_xtreme_pos(al2));
        ameans_dif = abs(UMBRAL_SIMILARIDAD - get_mean(al1));
        if(ameans_dif < means_dif){
            l1 = al1;
            l2 = al2;
        }
        else break;
    }while(true);
}
