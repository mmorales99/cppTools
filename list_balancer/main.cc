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


float get_list_sum(vector<float>l1){
    float l1_sum = 0;
    for (size_t i = 0; i < l1.size(); i++) l1_sum += l1[i];
    return l1_sum;
}

double get_similarity(vector<float>l1, vector<float>l2){
    float l1_sum=get_list_sum(l1), l2_sum=get_list_sum(l2);
    return (l1_sum<l2_sum ? l1_sum / l2_sum : l2_sum / l1_sum);
}

double get_mean(vector<float>l1){
    double mean = 0;
    for (size_t i = 0; i < l1.size(); i++) mean+=l1[i];
    mean/=l1.size();
    return mean;
}

size_t get_xtreme_pos(vector<float>l1){
    float mean = get_mean(l1);
    float xtreme = l1[0]; // primer elemento de la lista
    float xtreme_dif = abs(xtreme - mean);
    size_t xtreme_pos = 0;
    for (size_t i = 1; i < l1.size(); i++){
        float aux = abs(l1[i] - mean);
        if(aux>xtreme_dif){
            xtreme = l1[i];
            xtreme_dif = aux;
            xtreme_pos = i;
        }
    }
    return xtreme_pos;
}

void swap_xtreme(vector<float>&l1, size_t p1, vector<float>&l2, size_t p2){
    float l1_e = l1[p1];
    float l2_e = l2[p2];
    l1.erase(l1.begin()+p1);
    l2.erase(l2.begin()+p2);
    l1.push_back(l2_e);
    l2.push_back(l1_e);
}

void ordenar(vector<float>&l1, vector<float>&l2){
    // TODO balancear cantidad de elementos, igualar tamaños por compensacion, no añadir 0s
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
    double similaridad = get_similarity(l1,l2);
    if(similaridad == 1) return; // les dos lliestes son iguales de valor

    const float UMBRAL_SIMILARIDAD = ( get_list_sum(l1) + get_list_sum(l2) ) / 2;
    float means_dif = 0;
    swap_xtreme(l1, get_xtreme_pos(l1), l2, get_xtreme_pos(l2));
    means_dif = abs(UMBRAL_SIMILARIDAD - get_mean(l1));
    do{
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
