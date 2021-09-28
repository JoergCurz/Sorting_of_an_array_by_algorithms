//Hecho por: Jorge Daniel Cruz Case
//Actividad 1.3 Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales
//Codigo para el ordenamiento y lectura del archivo "Bitacora" mediante algoritmos vistos en clase
//21/09/2021


//Librerias
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include "dateTime.h"
using namespace std;

//Algoritmos para la lectura de archivos, ambos fueron usados en la clase de POO del semestre pasado
//Funcion para meter la lectura del archivo en un vector base
//Complejidad total del algoritmo: O(n)
void cargaDatos(vector<string>& base, string doc){
    ifstream archivo;
    archivo.open(doc);
    int contador = 1;
    if (archivo.is_open()){//Complejidad O(n)
    //Se abrio el archivo correctamente
        string linea;
        while(getline(archivo,linea)){// Complejidad: O(1) * O(n) = O(n)
        //Se lee la primera línea
            stringstream sstr(linea);
            // Se declara un stringstream para poder leer los datos separados por ","
            string dato;
            vector<string> m;
            while (getline(sstr, dato,' ')){//Complejidad O(1)
                m.push_back(dato); 
                //Cada renglón con datos se agrega al vector
                base.push_back(dato);
            }  
            string problema = m[4];
            int n = m.size(); 
            for (int i = 5; i<n; i++) {//Complejidad: O(n)
                problema += (" " +m[5]);
                m[4] = problema;
                m.erase(m.begin()+5);
                base.erase(base.begin()+5*contador);
            } 
            base.erase(base.begin()+5*contador);
            base.push_back(m[4]);
            contador++;          
        }
         archivo.close(); 
    }
    else{
        cout<< "¡No se pudo leer el archivo!"<<endl;
    }
}

//Algoritmo para la separación por partes del vector base para leugo agregarlo al vector lista
//Complejidad total del algoritmo: O(n)
void llenarObjetos(vector<string>& base, vector <dateTime*>& lista){//Complejidad del algoritmo: O(1)*O(n) = O(n)
    int n = base.size();
    for (int  i = 0; i< n/5; i++ ){//Complejidad: O(n)
        string horario = base[2];
        stringstream sstr(horario);
        vector<string> h; 
        string hora = "";
        while (getline(sstr, hora,':')){//Complejidad: O(1)
                h.push_back(hora);
        }
        int horas = stoi(h[0]);
        int minutos = stoi(h[1]);
        int segundos = stoi(h[2]);
        int dia = stoi(base[1]);
        string mes = base[0];
        string ip = base[3];
        string error = base[4];
        lista.push_back(new dateTime(mes,dia,horas, minutos, segundos,ip,error)); 
        base.erase(base.begin());
        base.erase(base.begin());
        base.erase(base.begin());
        base.erase(base.begin());
        base.erase(base.begin());
    }
}


//Algoritmo para la escritura de los datos ordenaos en un archivo llamado "Bitacora_ordenada"
//Complejidad total del algoritmo: O(n)
void escribirArchivo(vector <dateTime*>& lista){
    ofstream file;
    string nombreArchivo = "bitacora_Ordenada.txt";
    file.open(nombreArchivo.c_str(), fstream::out);
    int n = lista.size();
    for (int i=0;  i <n;  i++){//Complejidad: O(n)
        file<<"-----------------------------------------";
        file << "Registro no. " << i+1<<"\n"<<endl;
        file << "Dia: "<< lista[i]->getDia()<<endl;
        file << "Mes: "<< lista[i]->getMes() <<endl;
        file << "Hora: "<<  lista[i]->getHoras() <<":"<<lista[i]->getMinutos()<<":"<<lista[i]->getSegundos()<<endl;
        file << "Direccion de IP: "<< lista[i]->getIP() <<endl; 
        file << "Causa de la falla: "<< lista[i]->getError()<<endl;
        file<<"-----------------------------------------";

    }
    file.close();
}

//->Quick sort inicio

//Algoritmo para el cambio entre variables
//Complejidad total: O(1)
void swap(dateTime* a, dateTime* b){
    dateTime t = *a; 
    *a = *b; 
    *b = t; 
}

//Complejidad total: O(n)
int partition (vector<dateTime*>& a, int low, int high) { 
    time_t pivote = a[high]->getDate(); 
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++){//Si tomamos a high como n-1, obtenemos que la complejidad es O(n-1) o O(n)
        if (a[j]->getDate() < pivote){ 
            i++;  
            swap(a[i], a[j]); 
        } 
    }
    swap(a[i + 1], a[high]); 
    return (i + 1); 
} 


//Complejidad total del algoritmo: O(n log n)
void quickSort(vector<dateTime*> &arr, int low, int high){
    if (low < high) {
        int pivote = partition(arr, low, high);
        quickSort(arr, low, pivote - 1);
        quickSort(arr, pivote + 1, high);
    }
}
//Quick sort final



//->Algoritmo de busqueda

//Algoritmos para la busqueda de tipo binaria para arreglos ordenados
//Complejidad O(log2 (n)) utilizando la complejidad temporal promedio
//Caso: Worst(n) = log2(n+1)ϵ O(log n)
int busquedaBinaria(vector<dateTime*>& a, time_t k) {
    int n = a.size();
    int inf = 0;
    int sup = n - 1;
    while (inf <= sup) {
        int m = (inf + (sup - inf) / 2);
        int fecha = a[m]->getDate();
        if (k == fecha) {
            return m;
        }
        else if (k < fecha) {
            sup = m - 1;
        }
        else {
        inf = m + 1;
        }
    }
    return -1;  
}



//Algoritmo para imprimir los contenidos de un vector
//Complejidad total: O(n)
void printVector(vector <dateTime*>& lista, int total, int inicio){
    for (int i=inicio;  i <=total;  i++){
            lista[i]->imprime(); // Complejidad: O(n)
    }
    cout<<endl;
}




int main(){
    //Empieza el conteo
    auto startTime = std::chrono::high_resolution_clock::now();

    //Vectores iniciales
    vector<string> b{};
    vector <dateTime*> lista;
    
    //LLenado y ordenamiento de los datos
    cargaDatos(b, "bitacora.txt");
    llenarObjetos(b , lista);
    quickSort(lista, 0, lista.size()-1);
    escribirArchivo(lista);
    
    //Tiempo de llenado
    auto endTime = std::chrono::high_resolution_clock::now();
    auto totalTime = endTime - startTime;
    cout << "Tiempo de llenado y ordenamiento: " << totalTime/std::chrono::milliseconds(1) <<" ms"<<endl;

    //Atributos
    string mes_inf, mes_sup;
    int dia_inf, dia_sup, hora_inf, hora_sup, min_inf, min_sup, seg_inf, seg_sup;
    
    int busqueda_binaria_inf;
    int busqueda_binaria_sup;
    int inf, sup;

    //Entrada de datos del usuario
    bool inf_busq = false;
    while(inf_busq==false){
        cout << "\nIngrese la fecha inferior: " << endl;
        cout << "Mes: ";
        cin >>mes_inf;
        cout << "Dia: ";
        cin>>dia_inf;
        cout << "Hora: ";
        cin>>hora_inf;
        cout << "Minuto: ";
        cin>>min_inf;
        cout << "Segundo: ";
        cin>>seg_inf;
        dateTime* fecha_inf = new dateTime(mes_inf, dia_inf, hora_inf, min_inf, seg_inf, "", "");
        for(int i = 0; i<lista.size();i++){
            if(lista[i]->getDia() == fecha_inf->getDia() && lista[i]->getMes()==fecha_inf->getMes() && lista[i]->getHoras()==fecha_inf->getHoras() && lista[i]->getMinutos()==fecha_inf->getMinutos() && lista[i]->getSegundos() == fecha_inf->getSegundos()){
                fecha_inf->setDate(lista[i]->getDate());
                inf = i;
            }
        }
        busqueda_binaria_inf = busquedaBinaria(lista, fecha_inf->getDate());
        if(busqueda_binaria_inf!=-1){
            inf_busq = true;
            int busqueda_binaria_inf = busquedaBinaria(lista, fecha_inf->getDate());
            cout <<"Resultado de la busqueda inferior: "<< busqueda_binaria_inf << endl;

        }
        else{
            cout << "\nLa fecha ingresada no se encontro, porfavor reingresela: ";
        }
    }

    //Parámetros superiores
    bool sup_busq = false;
    while(sup_busq==false){
        cout << "\nIngrese la fecha superior: " << endl;
        cout << "Mes: ";
        cin >>mes_sup;
        cout << "Dia: ";
        cin>>dia_sup;
        cout << "Hora: ";
        cin>>hora_sup;
        cout << "Minuto: ";
        cin>>min_sup;
        cout << "Segundo: ";
        cin>>seg_sup;
        dateTime* fecha_sup = new dateTime(mes_sup, dia_sup, hora_sup, min_sup, seg_sup, "", "");
        for(int k = 0; k<lista.size();k++){
            if(lista[k]->getDia() == fecha_sup->getDia() && lista[k]->getMes()==fecha_sup->getMes() && lista[k]->getHoras()==fecha_sup->getHoras() && lista[k]->getMinutos()==fecha_sup->getMinutos() && lista[k]->getSegundos() == fecha_sup->getSegundos()){
                fecha_sup->setDate(lista[k]->getDate());
                sup = k;
            }
        }
        busqueda_binaria_sup = busquedaBinaria(lista, fecha_sup->getDate());
        if(busqueda_binaria_sup!=-1){
            sup_busq = true;
            int busqueda_binaria_sup = busquedaBinaria(lista, fecha_sup->getDate());
            cout <<"Resultado de la busqueda superior: "<<busqueda_binaria_sup << endl;

        }
        else{
            cout << "\nLa fecha ingresada no se encontro, porfavor reingresela: ";
        }
    }
    //Se imprime el vector desde los parámetros dados
    printVector(lista, busqueda_binaria_sup, busqueda_binaria_inf);
}     