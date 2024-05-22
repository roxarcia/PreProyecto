#include "string"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

using namespace std; 

//Tipos de datos


//dato raza
typedef struct {
    string nombre;
    int energia;
    int salud = 100;
    string ambiente;
    int fidelidad;
} raza;

//dato accesorio
typedef struct {
    string nombre;
    string tipo;
    int energia_consumida;
    int proteccion_inicial; //campo que sólo se rellenará si es del tipo defensa
    int porcentaje_dano; //solo en tipo ataque
    int porcentaje_proteccion; //solo en tipo defensa
    int porcentaje_recuperacion; //solo en tipo supervivencia
    string valor_recuperado; //se definirá solo en accesorios de supervivencia, e indicará a donde sumar el porcentaje de recuperacion
    string ambiente; //campo que sólo se rellenará si es del tipo acondicionamiento
} accesorio;


//dato mochila
typedef struct{
    string dueno;
    accesorio vector_mochila [5];
    int vector_usos [5];
} mochila;

//dato soldado
typedef struct {
    string Nombre;
    raza Raza;
    mochila Mochila;
}soldado;

//Nodos para la lista de ambientes
struct Nodo_ambiente{
    string nombre;
    Nodo_ambiente *siguiente;
};

//Nodos para la lista de razas
struct Nodo_raza {
    raza Raza;
    Nodo_raza *siguiente;
};

//Nodos para la lista de accesorios
struct Nodo_accesorio {
    accesorio accesorio;
    Nodo_accesorio *siguiente;
};

//Nodos para la lista de estudiantes
struct Nodo_estudiante {
    soldado Estudiante;
    Nodo_estudiante *siguiente;
};


//FUNCIONES Y PROCEDIMIENTOS
// Función para validar enteros
bool Validar_enteros(string num){
    int enteros[10]= {'0','1','2','3','4','5','6','7','8','9'};
    bool validar = false;
    int largo1=num.length();
    int cont_digitos = 0;
    for(int i = 0; i < largo1; i++){
        for (int j = 0; j < 10; j++){
            if (num[i] == enteros[j]){
                cont_digitos++;
            }
        }
    }
    if (cont_digitos == largo1) {
        validar=true;
    }
    return validar;
}

//Función para validar que un ambiente este en la lista
bool Validar_ambiente (string ambiente, Nodo_ambiente *&puntero){
    Nodo_ambiente *buscar = puntero;
    bool val = false; 
    while (buscar!=NULL)
        {
            if(buscar->nombre==ambiente){
                val=true;
            }
            buscar=buscar->siguiente;
        }
    return val;
}

//Función para validar que una raza este en la lista
bool Validar_raza (string raza, Nodo_raza *&puntero){
    Nodo_raza *buscar = puntero;
    bool val = false; 
    while (buscar!=NULL)
        {
            if(buscar->Raza.nombre==raza){
                val=true;
            }
            buscar=buscar->siguiente;
        }
    return val;
}

//Función para validar que un accesorio este en la lista
bool Validar_accesorio (string accesorio, Nodo_accesorio *&puntero){
    Nodo_accesorio *buscar = puntero;
    bool val = false; 
    while (buscar!=NULL)
        {
            if(buscar->accesorio.nombre==accesorio){
                val=true;
            }
            buscar=buscar->siguiente;
        }
    return val;
}


//Función para validar que un estutdiante este en la lista
bool Validar_estudiante (string estudiante, Nodo_estudiante *&puntero){
    Nodo_estudiante*buscar = puntero;
    bool val = false; 
    while (buscar!=NULL)
        {
            if(buscar->Estudiante.Nombre==estudiante){
                val=true;
            }
            buscar=buscar->siguiente;
        }
    return val;
}

//Función para no repetir razas
bool Raza_Unica(string nombre, Nodo_raza *&puntero) {
    Nodo_raza *recorrer = puntero;
    bool valido=true;

    while(recorrer!=NULL) {
        if (recorrer->Raza.nombre==nombre) {
            valido=false;
        }
        recorrer= recorrer->siguiente;
    }
    return valido;
    
}
//Función para no repetir ambientes
bool Ambiente_Unico(string nombre, Nodo_ambiente *&puntero) {
    Nodo_ambiente *recorrer = puntero;
    bool valido=true;

    while(recorrer!=NULL) {
        if (recorrer->nombre==nombre) {
            valido=false;
        }
        recorrer= recorrer->siguiente;
    }
    return valido;
    
}

//Función boorrar accesorios
void Borrar_Accesorio(string nombre, Nodo_accesorio *&puntero){
    Nodo_accesorio *anterior = NULL, *auxiliar = NULL;
    if (puntero == NULL){
        cout << "No hay accesorio que eliminar. Agregue un accesorio primero." << endl;
    }
    else{
        auxiliar = puntero;
        while(auxiliar!=NULL && auxiliar->accesorio.nombre != nombre){
            anterior = auxiliar;
            auxiliar=auxiliar->siguiente;
        }
        if (auxiliar==NULL){
            cout << "El accesorio que desea eliminar no existe. " <<endl;
            }
        else {
            if (auxiliar==puntero){
               puntero=puntero->siguiente;
            }
            else{        
                anterior->siguiente=auxiliar->siguiente;
            }
            delete auxiliar;
        }
    }
}

//Función para no repetir ambientes
bool Accesorio_Unico(string nombre, Nodo_accesorio*&puntero) {
    Nodo_accesorio *recorrer = puntero;
    bool valido=true;

    while(recorrer!=NULL) {
        if (recorrer->accesorio.nombre==nombre) {
            valido=false;
        }
        recorrer= recorrer->siguiente;
    }
    return valido;
    
}


//Funcion Para agregar razas a la lista
void Agregar_Razas (raza r, Nodo_raza *&puntero){
    Nodo_raza *nuevo = new Nodo_raza();
    nuevo->Raza = r;
    if (puntero == NULL){
        puntero = nuevo;
    }
    else{
        nuevo->siguiente=puntero;
        puntero = nuevo;
    }
    
}
//Funcion Para eliminar razas de la lista
void Borrar_Razas(string nombre, Nodo_raza *&puntero){
    Nodo_raza *anterior = NULL, *auxiliar = NULL;
    if (puntero == NULL){
        cout << "No hay razas que eliminar. Agregue una raza primero." << endl;
    }
    else{
        auxiliar = puntero;
        while(auxiliar!=NULL && auxiliar->Raza.nombre!= nombre){
            anterior = auxiliar;
            auxiliar=auxiliar->siguiente;
        }
        if (auxiliar==NULL){
            cout << "La raza que desea eliminar no existe. " <<endl;
            }
        else {
            if (auxiliar==puntero){
               puntero=puntero->siguiente;
            }
            else{        
                anterior->siguiente=auxiliar->siguiente;
            }
            delete auxiliar;
        }
    }
}

//Función Modificar razas
void Modificar_Razas(string nombre, Nodo_raza *&puntero1, Nodo_ambiente *&puntero2){
    Nodo_raza *buscar = puntero1;
    while (buscar->Raza.nombre!=nombre){
        buscar=buscar->siguiente;
    }
    
        
    bool repetir_validacion=true;
    string nuevo_nombre;

    //Validar que el nuevo nombre de la raza no sea igual a uno ya existente
            while (repetir_validacion==true)
                {
                    cout << "Ingrese el nuevo nombre de su raza." << endl;
                    cin >> nuevo_nombre;
                    if (Raza_Unica(nuevo_nombre,puntero1)==true){
                        buscar->Raza.nombre = nuevo_nombre;
                        repetir_validacion=false;
                        }

                    else{
                        cout << "La raza " <<nuevo_nombre<< "ya existe. Dos razas no pueden tener el mismo nombre. Intente de nuevo" <<endl; 
                        }
                }
            
            
            string ener;
            //Validar que la nueva energía de la raza sea correcta
            while (repetir_validacion==true)
                {
                    cout << "Ingrese la nueva energia de su raza" << endl;
                    cin >> ener;
                    if (Validar_enteros(ener)==true){
                        int energia=stoi(ener);
                        buscar->Raza.energia = energia;
                        repetir_validacion=false;
                        }

                    else{
                        cout << "La cantidad de energia debe ser un numero entero positivo. Intente nuevo." << endl; 
                        }
                }
            repetir_validacion=true;
            while (repetir_validacion==true) 
                {
                    cout<<"Ingrese el nuevo ambiente para su raza. "<< endl;
                    cout<<endl;
                    cout << "AMBIENTES DISPONIBLES" << endl;
                    Nodo_ambiente *imprimir=puntero2;
                    int cont_ambiente = 1;
                    while (imprimir!=NULL) 
                        {
                            if (cont_ambiente%10 != 0){
                            cout << imprimir->nombre<< " ";
                            }
                            else{
                                cout << imprimir->nombre << endl;
                                }
                            imprimir=imprimir->siguiente;
                            cont_ambiente+=1;
                        }
                    string ambi;
                    cin>>ambi;
                    if (Validar_ambiente(ambi,puntero2)==false){
                        cout<< "El ambiente que introdujo para su raza no existe en la lista. Revise el nombre o agruéguelo en la seccion ambientes. " << endl;
                    }
                    else{
                        repetir_validacion=false;
                        buscar->Raza.ambiente=ambi;
                        }             
                }
                
        
}
// Función para buscar una raza e imprimir sus detalles

void Funcion_buscar(string nombre, Nodo_raza *&puntero){
    Nodo_raza *buscar = puntero;
    while (buscar->Raza.nombre!=nombre){
        buscar=buscar->siguiente;
    }
    if(buscar != NULL){
        cout<<"- NOMBRE:"<< buscar->Raza.nombre<<endl;
        cout<<"- SALUD:"<< buscar->Raza.salud<<endl;;
        cout<<"- ENERGIA:"<< buscar->Raza.energia<<endl;;
        cout<<"- AMBIENTE:"<< buscar->Raza.ambiente<<endl;;
    }


}

void Buscar_Accesorios(string nombre, Nodo_accesorio*&puntero){
    Nodo_accesorio *buscar = puntero;
    while (buscar->accesorio.nombre!=nombre){
        buscar=buscar->siguiente;
    }
    if(buscar != NULL){
        if (buscar->accesorio.tipo=="ataque") {
            cout<<"- NOMBRE:"<< buscar->accesorio.nombre;
            cout<<"- TIPO: Ataque";
            cout<<"- PORCENTAJE DE DAÑO"<< buscar->accesorio.porcentaje_dano;
            cout<<"- ENERGIA CONSUMIDA"<< buscar->accesorio.energia_consumida;
        }
        else if (buscar->accesorio.tipo=="defensa") {
            cout<<"- NOMBRE:"<< buscar->accesorio.nombre;
            cout<<"- TIPO: Defensa";
            cout<<"- PORCENTAJE DE PROTECCIÓN:"<< buscar->accesorio.porcentaje_proteccion;
            cout<<"- PROTECCIÓN INICIAL:"<< buscar->accesorio.proteccion_inicial;
            cout<<"- ENERGIA CONSUMIDA"<< buscar->accesorio.energia_consumida;
        }

        else if (buscar->accesorio.tipo=="supervivencia") {
            cout<<"- NOMBRE:"<< buscar->accesorio.nombre;
            cout<<"- TIPO: Supervivencia";
            cout<<"- PORCENTAJE DE RECUPERACIÓN:"<< buscar->accesorio.porcentaje_proteccion;
            cout<<"- VALOR RECUPERADO:"<< buscar->accesorio.valor_recuperado;
            cout<<"- ENERGIA CONSUMIDA"<< buscar->accesorio.energia_consumida;
        }
        else if (buscar->accesorio.tipo=="acondicionamiento") {
            cout<<"- NOMBRE:"<< buscar->accesorio.nombre;
            cout<<"- TIPO: Acondicionamiento";
            cout<<"- HÁBITAT:"<< buscar->accesorio.ambiente;
            cout<<"- ENERGIA CONSUMIDA"<< buscar->accesorio.energia_consumida;
        }
    }
        

}


//Funcion para Filtrar la lista
void Funcion_Filtrar(string parametro, char opcion, Nodo_raza *&puntero) {
    Nodo_raza *buscar = puntero;
    bool vali = false;
    if (opcion=='b') 
    {
        int energia=stoi(parametro);
        buscar= puntero;
        while (buscar!=NULL) 
        {
            if (buscar->Raza.energia==energia) 
                {
                    vali=true;
                    int cont_raza=1;
                    if (cont_raza %10 == 0)
                        {
                            cout <<"["<< buscar->Raza.nombre << "] ";
                        }
                    else{
                            cout <<"["<< buscar->Raza.nombre <<"]"<< endl;
                        }
                    cont_raza+=1;
                }
            buscar=buscar->siguiente;    
        }
        if(vali == false){ 
            cout<<"No hay ninguna raza con esa energía."<<endl;
        }
    }
      
    if (opcion=='c') 
    {
        buscar=puntero;
        while(buscar!=NULL) {
            if (buscar->Raza.ambiente==parametro) 
                {
                    vali=true;
                    int cont_raza=1;
                    if (cont_raza %10 == 0)
                        {
                            cout<<"["<< buscar->Raza.nombre<<"] ";
                        }
                    else 
                        {
                            cout<<"["<< buscar->Raza.nombre<<"]"<< endl;  
                        }    
                    cont_raza+=1;
                }
            buscar=buscar->siguiente;
        }
        if(vali==false){
            cout<<"No hay ninguna raza que tenga ese ambiente."<<endl;
        }
    }
}       

void Filtrar_Accesorios(string parametro, char opcion, Nodo_accesorio *&puntero) {
    Nodo_accesorio *buscar = puntero;
    bool vali = false;
    if (opcion=='1') {
        int dano=stoi(parametro);
        while (buscar!=NULL && buscar->accesorio.tipo=="ataque")
        {   
            if (buscar->accesorio.porcentaje_dano==dano) 
                {
                    int cont_accesorios=1;
                    vali=true;
                    if (cont_accesorios %10 == 0)
                        {
                            cout<<"["<< buscar->accesorio.nombre<<"] ";
                        }
                    else 
                        {
                            cout<<"["<< buscar->accesorio.nombre<<"]"<< endl;  
                        }    
                    cont_accesorios+=1;
                }    
            buscar=buscar->siguiente;    
        }
        if(vali == false){
            cout<<"No hay ningun accesorio con ese porcentaje de dano."<<endl;
        }
    }

    else if(opcion=='2') {
        int proteccion=stoi(parametro);
        while (buscar!=NULL && buscar->accesorio.tipo=="defensa")
        {   
            if (buscar->accesorio.porcentaje_proteccion==proteccion) 
                {
                    int cont_accesorios=1;
                    vali=true;
                    if (cont_accesorios %10 == 0)
                        {
                            cout<<"["<< buscar->accesorio.nombre<<"] ";
                        }
                    else 
                        {
                            cout<<"["<< buscar->accesorio.nombre<<"]"<< endl;  
                        }    
                    cont_accesorios+=1;
                }

            buscar=buscar->siguiente;  
        }
        if(vali == false){
            cout<<"No hay ningun accesorio con ese porcentaje de proteccion."<<endl;
        }
    }   

    else if (opcion=='3') 
        {
            int recuperacion=stoi(parametro);
            while(buscar!=NULL && buscar->accesorio.tipo=="supervivencia") {
                if (buscar->accesorio.porcentaje_recuperacion==recuperacion) 
                    {
                        int cont_accesorios=1;
                        vali=true;
                        if (cont_accesorios %10 == 0)
                            {
                                cout<<"["<< buscar->accesorio.nombre<<"] ";
                            }
                        else 
                            {
                                cout<<"["<< buscar->accesorio.nombre<<"]"<< endl;  
                            }    
                        cont_accesorios+=1;
                
                    }
                
                buscar=buscar->siguiente; 
                }
            if(vali == false){
                cout<<"No hay ningun accesorio con ese porcentaje de recuperación."<<endl;
            }   
        }

    else if (opcion=='4') {
            while(buscar!=NULL && buscar->accesorio.tipo=="acondicionamiento") {
                if (buscar->accesorio.ambiente==parametro) 
                    {
                        int cont_accesorios=1;
                        vali=true;
                        if (cont_accesorios %10 == 0)
                            {
                                cout<<"["<< buscar->accesorio.nombre<<"] ";
                            }
                        else 
                            {
                                cout<<"["<< buscar->accesorio.nombre<<"]"<< endl;  
                            }    
                        cont_accesorios+=1;
                    }
                buscar=buscar->siguiente; 
                }
            
            if(vali == false){
                cout<<"No hay ningun accesorio creado para ese ambiente."<<endl;
                
            }
    }

    else if (opcion=='c') {

        int energia=stoi(parametro);
        while (buscar!=NULL)
            {
                if (buscar->accesorio.energia_consumida==energia) 
                    {
                        int cont_accesorios=1;
                        vali=true;
                        if (cont_accesorios %10 == 0)
                            {
                                cout<<"["<< buscar->accesorio.nombre<<"] ";
                            }
                        else 
                            {
                                cout<<"["<< buscar->accesorio.nombre<<"]"<< endl;  
                            }    
                        cont_accesorios+=1;
                    }
                buscar=buscar->siguiente;    
            }

        if(vali == false){
            cout<<"No hay ningun accesorio que consuma esa energía."<<endl;
        }
    }
} 


void Agregar_ambientes(string ambiente, Nodo_ambiente*&puntero){
    Nodo_ambiente *nuevo = new Nodo_ambiente();
    nuevo->nombre = ambiente;
    if (puntero == NULL){
        puntero = nuevo;
    }
    else{
        nuevo->siguiente=puntero;
        puntero = nuevo;
    }
}

//Función Borrar ambientes
void Borrar_ambientes(string ambiente, Nodo_ambiente *&puntero1, Nodo_raza*&puntero2, Nodo_accesorio *&puntero3){
    Nodo_ambiente *anterior = NULL, *auxiliar = NULL;
    
        auxiliar = puntero1;
        while(auxiliar!=NULL && auxiliar->nombre!= ambiente){
            anterior = auxiliar;
            auxiliar=auxiliar->siguiente;
        }
        if (auxiliar==NULL){
            cout << "El ambiente que desea eliminar no existe. " <<endl;
            }
        else {
            Nodo_raza *buscar_raza = puntero2;
            Nodo_accesorio *buscar_accesorio= puntero3;
            char seguro;
            bool raza_ambiente = false;
            bool accesorio_ambiente = false;
            while(buscar_raza!=NULL)
                {
                    if(buscar_raza->Raza.ambiente==ambiente)
                        {
                            raza_ambiente=true;
                        }

                    buscar_raza=buscar_raza->siguiente;

                    if(buscar_accesorio->accesorio.ambiente==ambiente)
                        {
                            accesorio_ambiente=true;
                        }
                    buscar_accesorio=buscar_accesorio->siguiente;
                }
                

            if (raza_ambiente==true)
                {
                    cout<<"! Si elimina este ambiente eliminara las siguientes razas:"<<endl;
                    buscar_raza=puntero2;
                    while(buscar_raza!=NULL)
                        {
                            if(buscar_raza->Raza.ambiente==ambiente)
                                {
                                    cout << buscar_raza->Raza.nombre << "  ";
                                }
                            buscar_raza=buscar_raza->siguiente;
                        }
                    cout << endl;
                    cout << endl;
                    cout<<"Esta segur@? S/N"<<endl;
                    bool validar_seguro = true;
                    while (validar_seguro==true)
                        {
                            validar_seguro=false;
                            cin >> seguro;
                            seguro=toupper(seguro);
                            if (seguro=='S')
                                {   
                                    buscar_raza=puntero2;
                                    while(buscar_raza!=NULL)
                                        {
                                            if(buscar_raza->Raza.ambiente==ambiente)
                                                {
                                                    string eliminar_raza=buscar_raza->Raza.nombre;
                                                    Borrar_Razas(eliminar_raza,puntero2);
                                                }
                                            buscar_raza=buscar_raza->siguiente;
                                        }
                                }
                            else if(seguro=='N')
                            {

                            }
                            else 
                                {
                                    cout << "Indique si esta seguro con S/N"<<endl;
                                    validar_seguro=true;
                                }
                        }
                }
            if (accesorio_ambiente==true)
                {

                    cout<<"! Si elimina este ambiente eliminara los siguientes accesorios:"<<endl;
                    buscar_accesorio=puntero3;
                    while(buscar_accesorio!=NULL)
                        {
                            if(buscar_accesorio->accesorio.ambiente==ambiente)
                                {
                                    cout <<"["<< buscar_accesorio->accesorio.ambiente << "]  ";
                                }
                            buscar_accesorio=buscar_accesorio->siguiente;
                        }
                    cout << endl;
                    cout << endl;
                    cout<<"Esta segur@? S/N"<<endl;
                    bool validar_seguro = true;
                    while (validar_seguro==true)
                        {
                            validar_seguro=false;
                            cin >> seguro;
                            seguro=toupper(seguro);
                            if (seguro=='S')
                                {   
                                    buscar_accesorio=puntero3;
                                    while(buscar_accesorio!=NULL)
                                        {
                                            if(buscar_accesorio->accesorio.ambiente==ambiente)
                                                {
                                                    string eliminar_accesorio=buscar_accesorio->accesorio.nombre;
                                                    Borrar_Accesorio(eliminar_accesorio,puntero3);
                                                }
                                            buscar_accesorio=buscar_accesorio->siguiente;
                                        }
                                }
                            else if(seguro=='N')
                                {
                                }
                            else 
                                {
                                    cout << "Indique si esta seguro con S/N"<<endl;
                                    validar_seguro=true;
                                }
                        }
                }
            if(seguro=='S')
                if (auxiliar==puntero1)
                    {
                        puntero1=puntero1->siguiente;
                    }
                else
                    {        
                        anterior->siguiente=auxiliar->siguiente;
                    }       
        }
    
}

void Modificar_Ambiente(string nombre, Nodo_raza *&puntero1, Nodo_ambiente *&puntero2, Nodo_accesorio *&puntero3){
    Nodo_ambiente *buscar = puntero2;

    while ((buscar->nombre!=nombre)){
        buscar=buscar->siguiente;
    }
                
                
    bool repetir_validacion=true;
    string nuevo_nombre;

    //Validar que el nuevo nombre del ambiente no sea igual a uno ya existente
    while (repetir_validacion==true)
        {
            cout << "Ingrese el nuevo nombre de su ambiente." << endl;
            cin >> nuevo_nombre;
            if (Ambiente_Unico(nuevo_nombre,puntero2)==true){

                    buscar->nombre = nuevo_nombre;
                    repetir_validacion=false;
                }

            else{
                cout << "El ambiente " <<nuevo_nombre<< " ya existe. Dos ambientes no pueden tener el mismo nombre. Intente de nuevo" <<endl; 
                }
        }
    Nodo_raza *buscar_raza=puntero1;
    Nodo_accesorio *buscar_accesorio=puntero3;
    while(buscar_raza!=NULL)
        {
            if(buscar_raza->Raza.ambiente==nombre)
                {
                    buscar_raza->Raza.ambiente=nuevo_nombre;
                
                }
            buscar_raza=buscar_raza->siguiente;
        }

    while(buscar_accesorio!=NULL)
        {
            if(buscar_accesorio->accesorio.nombre==nombre)
                {
                    buscar_accesorio->accesorio.nombre=nuevo_nombre;
                
                }
            buscar_accesorio=buscar_accesorio->siguiente;
        }
                
                           
        
}
                

//Función agregar accesorios
void Agregar_Accesorio (accesorio a, Nodo_accesorio *&puntero){
    Nodo_accesorio *nuevo = new Nodo_accesorio();
    nuevo->accesorio= a;
    if (puntero == NULL){
        puntero = nuevo;
    }
    else{
        nuevo->siguiente=puntero;
        puntero = nuevo;
    }
}






  
//CÓDIGO PRINCIPAL
int main(){ 
    Nodo_raza *lista_razas=NULL;
    Nodo_ambiente *lista_ambientes=NULL;
    Nodo_accesorio *lista_accesorios=NULL;
    Nodo_estudiante *lista_estudiantes=NULL;
    
//MENU PRINCIPAL
    cout << endl; 
    cout << "Bienvenido a Invasion Extraterrestre 'El Juego'" << endl; 
    cout << endl; 
    bool menu1 = true; 
    char opcion_menu;
    while (menu1==true){ 
        menu1=false;
        cout<<"  MENU PRINCIPAL"<<endl;
        cout <<endl;
        cout << "1 - Empezar partida"  << endl;
        cout << "2 - Ambientes" << endl;
        cout << "3 - Razas" << endl;
        cout << "4 - Accesorios " << endl;
        cout << "5 - Salir" << endl;
        cin >> opcion_menu;
        

        //OPCION 1

        if (opcion_menu == '1')
            {
                if (lista_ambientes==NULL || lista_razas==NULL || lista_accesorios==NULL) {
                    cout<<"Antes de crear un estudiante, primero debe crear ambientes, raza y accesorios."<<endl;
                    cout<<endl;
                    menu1=true;
                }
                
            }

                
           
        //SECCION AMBIENTES    
        else if(opcion_menu=='2') {
            bool menu_ambiente=true;

            while(menu_ambiente==true)
                {
                    menu_ambiente=false;    
                    cout<<endl;
                    cout<<"  AMBIENTES:"<<endl;
                    cout<<endl;

                    if (lista_ambientes==NULL)
                        {    
                            cout<<"[ No hay ambientes. ]"<<endl;;
                            cout<<endl;
                        }
                    else 
                        {
                            Nodo_ambiente *imprimir= lista_ambientes;
                            int cont_ambiente= 1;
                            while (imprimir!=NULL) 
                                {
                                    cout<<"[";
                                    if (cont_ambiente %10 != 0){
                                        cout << imprimir->nombre<< "";
                                        }
                                    else{
                                        cout << imprimir->nombre << endl;
                                        }
                                    cont_ambiente+=1;
                                    cout<<"] ";
                                    imprimir=imprimir->siguiente;
                                }
                            cout<<endl;
                            cout<<endl;
                        }
                    cout <<endl;
                    cout <<"   ACCIONES"<<endl;
                    cout << "1 - Agregar ambiente" << endl;
                    cout << "2 - Eliminar ambiente"  << endl;
                    cout << "3 - Modificar ambiente"  << endl;
                    cout << "4 - Volver al menú principal" << endl;
                    char opcion_ambiente;
                    cin>>opcion_ambiente;

                    if (opcion_ambiente=='1') 
                        {   
                            bool repetir_validacion = true;
                            //Validar que el usuario no pueda ingresar 2 ambientes con el mismo nombre
                            while(repetir_validacion==true) {
                                cout<<"Ingrese el nombre de su ambiente para crearlo." << endl;
                                string nombre_ambiente;
                                cin>>nombre_ambiente;
                                if (Ambiente_Unico(nombre_ambiente,lista_ambientes)==true) {
                                    Agregar_ambientes(nombre_ambiente,lista_ambientes);
                                    menu_ambiente=true;
                                    repetir_validacion=false;
                                }
                                else {
                                    cout<<"El ambiente "<<nombre_ambiente<< " ya existe. Dos ambientes no pueden llamarse de la misma manera. Intente de nuevo."<<endl;
                                }
                            }
                        }

                        
                    else if (opcion_ambiente=='2')
                        {
                            cout<<endl;
                            cout<<"! Si elimina un ambiente, eliminará todas las razas y accessorios que pertenezcan a él."<<endl;
                            cout<<endl;  
                                    
                            if (lista_ambientes==NULL)
                                {
                                    cout<<endl;
                                    cout<<"No hay ambientes que eliminar"<<endl;
                                    menu_ambiente=true;
                                }
                            else
                                {   
                                    bool repetir_validacion=true;
                                    while (repetir_validacion==true) 
                                        {
                                            cout<<"Ingrese el nombre del ambiente que desea eliminar." << endl;
                                            string nombre_ambiente;
                                            cin>>nombre_ambiente;
                                            cout<<endl;

                                            if (Validar_ambiente(nombre_ambiente,lista_ambientes)==true) 
                                                {
                                                    repetir_validacion=false;
                                                    Borrar_ambientes(nombre_ambiente,lista_ambientes, lista_razas,lista_accesorios);
                                                    menu_ambiente=true;
                                                }
                                            else 
                                                {
                                                    cout<<"El ambiente que desea eliminar no existe. Intente de nuevo." << endl;
                                                    cout<<endl;
                                                }
                                            }
                                    
                                }
                        }
                    
                    else if (opcion_ambiente=='3')
                        {
                            cout<<endl;
                            cout<<"! Si modifica el nombre de un ambiente, se actualizara también el ambiente de las razas. "<<endl;
                            cout<<endl; 
                            if (lista_ambientes==NULL)
                                {
                                    cout<<endl;
                                    cout<<"No hay ambientes que modificar."<<endl;
                                    menu_ambiente=true;
                                }
                            else 
                                { 
                                    bool repetir_validacion=true;
                                    while (repetir_validacion==true) 
                                        {
                                            cout<<"Ingrese el nombre del ambiente cuyo nombre desea modificar." << endl;
                                            string nombre_ambiente;
                                            cin>>nombre_ambiente;
                                            cout<<endl;

                                            if (Validar_ambiente(nombre_ambiente,lista_ambientes)==true) 
                                                {
                                                    repetir_validacion=false;
                                                    Modificar_Ambiente(nombre_ambiente,lista_razas, lista_ambientes,lista_accesorios);
                                                    menu_ambiente=true;
                                                }
                                            else 
                                                {
                                                    cout<<"El ambiente que desea modificar no existe. Intente de nuevo." << endl;
                                                    cout<<endl;
                                                }
                                        }
                                }
                            
                        }   
                        
                    else if (opcion_ambiente=='4') {
                        menu1=true;
                    }
                    else {
                        cout<<endl;
                        cout<<"ERROR: Ingrese una opción del menú" << endl;
                        cout<<endl;
                        menu_ambiente=true;
                    }
                }
            }


        

        //OPCION RAZAS
        else if (opcion_menu == '3')
            {
                if (lista_ambientes==NULL)
                    {    
                        cout << "No puede ingresar a esta sección sin haber creado un ambiente primero. Regrese después de añadir un ambiente." << endl;
                        cout<<endl;
                        menu1=true;
                    }
                else
                    {   
                        cout << "RAZAS" << endl;
                        cout << endl; 
                        if (lista_razas==NULL){
                            cout << "[ No hay razas ]" << endl;
                            cout << endl;
                            }
                        else 
                            {
                                //FILTRO RAZAS
                                bool menuvisualizar=true;
                                char opcion_visualizar;
                                while (menuvisualizar==true) {  
                                    cout << "Como desea visualizar las razas? " << endl;
                                    cout << "a - Ver Todas      b - Filtrar por Energia      c - Filtrar por Ambiente  " << endl;
                                    cin>>opcion_visualizar;
                                    opcion_visualizar=tolower(opcion_visualizar);
                                    //Imprime todas las razas
                                    
                                    if (opcion_visualizar=='a')
                                        {
                                            Nodo_raza *buscar= lista_razas;
                                            int cont_raza = 1;
                                            while (buscar!=NULL) 
                                                {
                                                    if (cont_raza %10 != 0){
                                                        cout << buscar->Raza.nombre << " • ";
                                                    }
                                                    else{
                                                        cout << buscar->Raza.nombre << endl;
                                                    }
                                                    buscar=buscar->siguiente;
                                                    cont_raza+=1;
                                                }
                                            menuvisualizar=false;
                                        }
                                    
                                    // Imprime por energia    
                                    else if(opcion_visualizar=='b') 
                                        {
                                            menuvisualizar=false;
                                            string filtro_ener;
                                            bool repetir_validacion=true;

                                            //Validación de que el usuario introdujo una energía correcta
                                            while (repetir_validacion==true) 
                                                {
                                                    cout<<"Ingrese la cantidad de energía por la que quiere filtrar la lista"<< endl;
                                                    cin>>filtro_ener;

                                                    if (Validar_enteros(filtro_ener)==true) {
                                                        Funcion_Filtrar(filtro_ener, opcion_visualizar, lista_razas);
                                                        repetir_validacion=false;
                                                    }
                                                    else{
                                                        cout<<"Introdujo una energía inválida. La energía debe ser un número entero positivo. Intente de nuevo:" << endl;
                                                    }
                                                }  
                                        } 
                                    
                                    //Imprime según el ambiente
                                    else if (opcion_visualizar=='c')
                                        {
                                            menuvisualizar=false;
                                            string filtro_amb;
                                            bool repetir_validacion;
                                                while (repetir_validacion==true) 
                                                    {
                                                        cout << "Ingrese el nombre del ambiente por el que quiere filtrar la lista" << endl;
                                                        cin>>filtro_amb;
                                                        repetir_validacion=false;
                                                        Funcion_Filtrar(filtro_amb,opcion_visualizar,lista_razas);
                                                    }
                                        }  

                                    else
                                        {
                                            cout<<"ERROR: Introduzca una opción del menú. Intente de nuevo."<<endl;
                                            cout<<endl;
                                        }
                                }
                            }

                        //SUBMENU RAZAS
                        bool menu_razas = true;
                        while (menu_razas == true)
                            {
                                menu_razas=false;
                                cout <<endl;
                                cout <<"ACCIONES"<<endl;
                                cout << "1 - Ver detalles de una raza" << endl;
                                cout << "2 - Agregar raza"  << endl;
                                cout << "3 - Eliminar raza" << endl;
                                cout << "4 - Modificar raza" << endl;
                                cout << "5 - Volver al menu principal" << endl;  
                                char opcion_razas;
                                cin >> opcion_razas;

                                if (opcion_razas=='1')
                                    {
                                        if (lista_razas==NULL){
                                            cout << "No hay razas para buscar" << endl;
                                            menu_razas=true;
                                        }
                                        else
                                            {
                                                bool repetir_validacion;
                                                while (repetir_validacion==true) 
                                                    {
                                                        cout << "Ingrese el nombre de la raza de la cual desea ver sus detalles." << endl;
                                                        string nombre_raza;
                                                        cin >> nombre_raza;
                                                        cout<<endl;

                                                        if (Validar_raza(nombre_raza,lista_razas)==true) 
                                                            {
                                                                repetir_validacion=false;
                                                                Funcion_buscar(nombre_raza, lista_razas);
                                                                menu_razas=true;
                                                            }
                                                        else 
                                                            {
                                                                cout<<"La raza de la que desea ver sus detalles no existe. Intente de nuevo." << endl;
                                                                cout<<endl;
                                                    
                                                            }
                                                    }
                                            }
                                    }
                                else if (opcion_razas=='2') 
                                {  
                                    //Agregar una raza
                                    raza raza_nueva;
                                    bool repetir_validacion=true;
                                    
                                    //Validar que la raza no tenga el mismo nombre que otra
                                    string agregar_raza;
                                    while (repetir_validacion==true){
                                        cout << "Ingrese el nombre de su nueva raza." << endl;
                                        cin >> agregar_raza;                            
                                        if (Raza_Unica(agregar_raza,lista_razas)==true){
                                            raza_nueva.nombre = agregar_raza;
                                            repetir_validacion=false;
                                        }

                                        else{
                                            cout << "La raza" << agregar_raza << "ya existe. Dos razas no pueden tener el mismo nombre. Intente de nuevo" <<endl; 
                                            }
                                    }
                                    

                                    string ener;

                                    //Validar que la energía de la nueva raza sea correcta
                                    repetir_validacion=true;
                                    while (repetir_validacion==true)
                                        {
                                            cout << "Ingrese la energia de su nueva raza" << endl;
                                            cin >> ener;
                                            if (Validar_enteros(ener)==true){
                                                int energia=stoi(ener);
                                                raza_nueva.energia = energia;
                                                repetir_validacion=false;
                                                }

                                            else{
                                                cout << "La cantidad de energia debe ser un numero entero positivo. Intente nuevo." << endl; 
                                                }
                                        }
                                    repetir_validacion=true;
                                    while (repetir_validacion==true) 
                                        {
                                            cout<<"Ingrese el ambiente propio de su raza. "<<endl;
                                            cout << "AMBIENTES DISPONIBLES " << endl;
                                            Nodo_ambiente *imprimir= lista_ambientes;
                                            int cont_ambiente = 1;
                                            while (imprimir!=NULL) 
                                                {
                                                    if (cont_ambiente %10 != 0){
                                                    cout<<"[";
                                                    cout << imprimir->nombre<< " ";
                                                    }
                                                    else{
                                                        cout << imprimir->nombre << endl;
                                                        }
                                                    cout<<"]";
                                                    imprimir=imprimir->siguiente;
                                                    cont_ambiente+=1;
                                                }
                                            cout<<endl;
                                            string ambi;
                                            cin>>ambi;
                                            if (Validar_ambiente(ambi,lista_ambientes)==false){
                                                cout<< "El ambiente que introdujo para su raza no existe en la lista. Revise el nombre o agruéguelo en la seccion ambientes. " << endl;
                                            }
                                            else{
                                                repetir_validacion=false;
                                                raza_nueva.ambiente=ambi;
                                                }             
                                        }
                                    Agregar_Razas(raza_nueva,lista_razas);
                                    menu_razas=true;
                                }
                                
                                else if (opcion_razas=='3')
                                    if (lista_razas==NULL) {
                                        cout << "No hay razas para eliminar" << endl;
                                        menu_razas=true;
                                    }
                                    else {
                                        bool repetir_validacion;
                                        while (repetir_validacion==true) 
                                                    {
                                                        cout << "Ingrese el nombre de la raza que desea eliminar" << endl;
                                                        string eliminar_raza;
                                                        cin>>eliminar_raza;
                                                        cout<<endl;

                                                        if (Validar_raza(eliminar_raza,lista_razas)==true) 
                                                            {
                                                                repetir_validacion=false;
                                                                Borrar_Razas(eliminar_raza,lista_razas);
                                                                menu_razas=true;
                                                            }
                                                        else 
                                                            {
                                                                cout<<"La raza que desea eliminar no existe. Intente de nuevo." << endl;
                                                                cout<<endl;
                                                    
                                                            }
                                                    }
                                    
                                    }


                                else if (opcion_razas=='4') 
                                    {
                                        if (lista_razas==NULL) {
                                            cout << "No hay razas para modificar." << endl;
                                            menu_razas=true;
                                        }
                                        else 
                                        {   
                                            bool repetir_validacion;
                                            while (repetir_validacion==true) 
                                                    {
                                                        cout << "Ingrese el nombre de la raza que desea modificar" << endl;
                                                        string modificar_raza;
                                                        cin>>modificar_raza;
                                                        cout<<endl;

                                                        if (Validar_raza(modificar_raza,lista_razas)==true) 
                                                            {
                                                                repetir_validacion=false;
                                                                Modificar_Razas(modificar_raza,lista_razas,lista_ambientes);
                                                                menu_razas=true;
                                                            }
                                                        else 
                                                            {
                                                                cout<<"La raza que desea modificar no existe. Intente de nuevo." << endl;
                                                                cout<<endl;
                                                            }
                                            } 
                                        } 
                                    }  
                                else if (opcion_razas=='5')   
                                    {
                                        menu1=true;
                                    } 
                                else
                                    {
                                        cout<<"ERROR: Ingrese una opcion del menu."<< endl;
                                        menu_razas=true;
                                    }                          
                            }
                    }
            }

        //SECCION ACCESORIOS   
        else if (opcion_menu=='4')
            {
                if (lista_ambientes==NULL)
                    {
                        cout << "No puede ingresar a esta sección sin haber creado un ambiente primero. Regrese después de añadir un ambiente." << endl;
                        cout<<endl;
                        menu1=true;
                    }
                else
                    {

                        cout << "ACCESORIOS" << endl;
                        cout << endl; 
                        if (lista_accesorios==NULL){
                            cout << "[ No hay accesorios ]" << endl;
                            cout << endl;
                                    }
                        else 
                            { 
                                bool menuvisualizar=true;
                                char opcion_visualizar;
                                        while (menuvisualizar==true) { 
                                            cout << "Como desea visualizar los accesorios? " << endl;
                                            cout << "a - Ver Todos      b - Filtrar por tipo" << endl;
                                            cout << "c - Filtrar por Energia" << endl;
                                            cin>>opcion_visualizar;
                                            opcion_visualizar=tolower(opcion_visualizar);
                                            
                                            //Imprime todos los accesorios
                                            
                                            if (opcion_visualizar=='a')
                                                {
                                                    menuvisualizar=false;
                                                    Nodo_accesorio *buscar= lista_accesorios;
                                                    while (buscar!=NULL) 
                                                        {   
                                                            cout<<"[";
                                                            cout << buscar->accesorio.nombre << "  ";
                                                            cout<<"]";
                                                            buscar=buscar->siguiente;
                                                        }
                                                }
                                                
                                            
                                            // Imprime por tipo 
                                            else if(opcion_visualizar=='b') 
                                                {   
                                                    cout << "Escoja el tipo por el que desea filtrar: " << endl;
                                                    cout << "1 - Ataque        2 - Defensa"<< endl;
                                                    cout << "3 - Supervivencia     4 - Acondicionamiento" << endl;
                                                    char opcion_tipo;
                                                    cin>>opcion_tipo;
                                                    opcion_tipo=tolower(opcion_tipo);

                                                    if(opcion_tipo=='1')
                                                        {   
                                                            Nodo_accesorio *buscar= lista_accesorios;
                                                            cout<<"ACCESORIOS DE ATAQUE"<<endl;
                                                            cout<<endl;
                                                            while (buscar!=NULL && buscar->accesorio.tipo=="ataque") 
                                                                {   
                                                                    cout<<"[";
                                                                    cout << buscar->accesorio.nombre << "  ";
                                                                    cout<<"]";
                                                                    buscar=buscar->siguiente;
                                                                }

                                                            
                                                            bool repetir=true;
                                                            while (repetir==true) { 
                                                                cout<<"Quiere filtrarlos por porcentaje de ataque? (S/N)"<<endl;
                                                                char respuesta;
                                                                cin>>respuesta;
                                                                respuesta=tolower(respuesta);
                                                                repetir=false;
                                                                if (respuesta=='s') {
                                                                    bool repetir_validacion = true;
                                                                    while (repetir_validacion==true) 
                                                                        {
                                                                            cout<<"Ingrese el porcentaje de ataque por el cual filtrar la lista"<< endl;
                                                                            string porcentaje_ataque;
                                                                            cin>>porcentaje_ataque;

                                                                            if (Validar_enteros(porcentaje_ataque)==true) {
                                                                                cout<<"ACCESORIOS DE ATAQUE"<<endl;
                                                                                Filtrar_Accesorios(porcentaje_ataque, '1',lista_accesorios);
                                                                                repetir_validacion=false;
                                                                            }
                                                                            else{
                                                                                cout<<"Introdujo un porcentaje invalido, este debe ser un número entero positivo. Intente de nuevo:" << endl;
                                                                            }
                                                                        }  
                                                                }
                                                                else if (respuesta=='n') {
                                                                    menuvisualizar=false;
                                                                }
                                                                else {
                                                                    cout<<"Por favor, introduzca S para si o N para no"<<endl;
                                                                    repetir=true;
                                                                    cout<<endl;
                                                                }                                               
                                                            }
                                                        }
                                                    else if(opcion_tipo=='2')
                                                        {   
                                                            Nodo_accesorio *buscar= lista_accesorios;
                                                            cout<<"ACCESORIOS DE DEFENSA"<<endl;
                                                            cout<<endl;
                                                            while (buscar!=NULL && buscar->accesorio.tipo=="defensa") 
                                                                {   
                                                                    cout<<"[";
                                                                    cout << buscar->accesorio.nombre << "  ";
                                                                    cout<<"]";
                                                                    buscar=buscar->siguiente;
                                                                }

                                                            
                                                            bool repetir=true;
                                                            while (repetir==true) { 
                                                                cout<<"Quiere filtrarlos por porcentaje de protección? (S/N)"<<endl;
                                                                char respuesta;
                                                                cin>>respuesta;
                                                                respuesta=tolower(respuesta);
                                                                repetir=false;
                                                                if (respuesta=='s') {
                                                                    bool repetir_validacion = true;
                                                                    while (repetir_validacion==true) 
                                                                        {
                                                                            cout<<"Ingrese el porcentaje de proteccion por el cual filtrar la lista"<< endl;
                                                                            string porcentaje_proteccion;
                                                                            cin>>porcentaje_proteccion;

                                                                            if (Validar_enteros(porcentaje_proteccion)==true) {
                                                                                cout<<"ACCESORIOS DE DEFENSA"<<endl;
                                                                                Filtrar_Accesorios(porcentaje_proteccion, '2',lista_accesorios);
                                                                                repetir_validacion=false;
                                                                            }
                                                                            else{
                                                                                cout<<"Introdujo un porcentaje invalido, este debe ser un número entero positivo. Intente de nuevo:" << endl;
                                                                            }
                                                                        }  
                                                                }
                                                                else if (respuesta=='n') {
                                                                    menuvisualizar=false;
                                                                }
                                                                else {
                                                                    cout<<"Por favor, introduzca S para si o N para no"<<endl;
                                                                    repetir=true;
                                                                    cout<<endl;
                                                                }                                               
                                                            }
                                                        } 
                                                    else if(opcion_tipo=='3')
                                                        {   
                                                            Nodo_accesorio *buscar= lista_accesorios;
                                                            cout<<"ACCESORIOS DE SUPERVIVENCIA"<<endl;
                                                            cout<<endl;
                                                            while (buscar!=NULL && buscar->accesorio.tipo=="supervivencia") 
                                                                {   
                                                                    cout<<"[";
                                                                    cout << buscar->accesorio.nombre << "  ";
                                                                    cout<<"]";
                                                                    buscar=buscar->siguiente;
                                                                }

                                                            
                                                            bool repetir=true;
                                                            while (repetir==true) { 
                                                                cout<<"Quiere filtrarlos por porcentaje de recuperacion? (S/N)"<<endl;
                                                                char respuesta;
                                                                cin>>respuesta;
                                                                respuesta=tolower(respuesta);
                                                                repetir=false;
                                                                if (respuesta=='s') {
                                                                    bool repetir_validacion = true;
                                                                    while (repetir_validacion==true) 
                                                                        {
                                                                            cout<<"Ingrese el porcentaje de recuperacion por el cual filtrar la lista"<< endl;
                                                                            string porcentaje_recuperacion;
                                                                            cin>>porcentaje_recuperacion;

                                                                            if (Validar_enteros(porcentaje_recuperacion)==true) {
                                                                                cout<<"ACCESORIOS DE SUPERVIVENCIA"<<endl;
                                                                                Filtrar_Accesorios(porcentaje_recuperacion, '3',lista_accesorios);
                                                                                repetir_validacion=false;
                                                                            }
                                                                            else{
                                                                                cout<<"Introdujo un porcentaje invalido, este debe ser un número entero positivo. Intente de nuevo:" << endl;
                                                                            }
                                                                        }  
                                                                }
                                                                else if (respuesta=='n') {
                                                                    menuvisualizar=false;
                                                                }
                                                                else {
                                                                    cout<<"Por favor, introduzca S para si o N para no"<<endl;
                                                                    repetir=true;
                                                                    cout<<endl;
                                                                }                                               
                                                            }
                                                        } 
                                                    else if(opcion_tipo=='4')
                                                        {   
                                                            Nodo_accesorio *buscar= lista_accesorios;
                                                            cout<<"ACCESORIOS DE ACONDICIONAMIENTO"<<endl;
                                                            cout<<endl;
                                                            while (buscar!=NULL && buscar->accesorio.tipo=="acondicionamiento") 
                                                                {   
                                                                    cout<<"[";
                                                                    cout << buscar->accesorio.nombre << "  ";
                                                                    cout<<"]";
                                                                    buscar=buscar->siguiente;
                                                                }

                                                            
                                                            bool repetir=true;
                                                            while (repetir==true) { 
                                                                cout<<"Quiere filtrarlos por el ambiente para el que fueron creados? (S/N)"<<endl;
                                                                char respuesta;
                                                                cin>>respuesta;
                                                                respuesta=tolower(respuesta);
                                                                repetir=false;
                                                                if (respuesta=='s') {
                                                                    bool repetir_validacion = true;
                                                                    while (repetir_validacion==true) 
                                                                        {
                                                                            cout<<"Ingrese el ambiente por el cual filtrar la lista"<< endl;
                                                                            string filtro_ambiente;
                                                                            cin>>filtro_ambiente;

                                                                            if (Validar_ambiente(filtro_ambiente,lista_ambientes)==true) {
                                                                                cout<<"ACCESORIOS DE ACONDICIONAMIENTO "<<endl;
                                                                                Filtrar_Accesorios(filtro_ambiente, '4',lista_accesorios);
                                                                                repetir_validacion=false;
                                                                            }
                                                                            else{
                                                                                cout<<"El ambiente que estableció como filtro no existe. Intente de nuevo." << endl;
                                                                                cout<<endl;
                                                                            }
                                                                        }  
                                                                }
                                                                else if (respuesta=='n') {
                                                                    menuvisualizar=false;
                                                                }
                                                                else {
                                                                    cout<<"Por favor, introduzca S para si o N para no"<<endl;
                                                                    repetir=true;
                                                                    cout<<endl;
                                                                }                                               
                                                            }
                                                        } 
                                                            
                                                }
                                                    
                                            else if (opcion_visualizar='c')
                                                {
                                                    bool repetir_validacion = true;
                                                    while (repetir_validacion==true) 
                                                        {
                                                            cout<<"Ingrese la cantidad de energia consumida por la que quiere filtrar la lista"<< endl;
                                                            string energ;
                                                            cin>>energ;

                                                            if (Validar_enteros(energ)==true) {
                                                                cout<<"ACCESORIOS POR ENERGIA"<<endl;
                                                                Filtrar_Accesorios(energ, 'c',lista_accesorios);
                                                                repetir_validacion=false;
                                                                }
                                                                else{
                                                                    cout<<"Introdujo un porcentaje invalido, este debe ser un número entero positivo. Intente de nuevo:" << endl;
                                                                    }
                                                        }  

                                                }
                                            else 
                                                {
                                                    bool menu_visualizar=true;
                                                    cout<<"ERROR:Introduzca una opcion del  menu."<<endl;
                                                    cout<<endl;
                                                }

                                //SUBMENU ACCESORIOS
                                bool menu_accesorios = true;
                                while (menu_accesorios == true)
                                    {
                                        menu_accesorios=false; 
                                        cout << "1 - Ver detalles de un accesorio" << endl;
                                        cout << "2 - Agregar accesorio"  << endl;
                                        cout << "3 - Eliminar accesorio" << endl;
                                        cout << "4 - Modificar accesorio" << endl;
                                        cout << "5 - Volver" << endl;  
                                        char opcion_accesorios;
                                        cin >> opcion_accesorios;

                                        if (opcion_accesorios=='1')
                                            {
                                                if (lista_accesorios==NULL)
                                                    {
                                                        cout << "No hay accesorios de los cuales buscar detalles." << endl;
                                                        menu_accesorios=true;
                                                    }
                                                else
                                                    {
                                                        string nombre1;
                                                        //validar que el accesorio exista
                                                        cout << "Ingrese el nombre del accesorio del cual desea ver sus detalles." << endl;
                                                        cin >> nombre1;

                                                        if (Validar_accesorio(nombre1,lista_accesorios)==true) {
                                                            Buscar_Accesorios(nombre1, lista_accesorios);
                                                        }
                                                        else {
                                                            cout<<"El accesorio que busca no existe. Revise la lista e intentelo de nuevo."<<endl;
                                                            cout<<endl;
                                                        }
                                                
                                                        menu_accesorios=true;
                                                    }
                                            }
                                        else if (opcion_accesorios=='2') 
                                            {  
                                                //Agregar un accesorio
                                                accesorio accesorio_nuevo;
                                                bool repetir_validacion=true;
                                                
                                                //Validar que la raza no tenga el mismo nombre que otra
                                                string agregar_acc;
                                                while (repetir_validacion==true){
                                                    cout << "Ingrese el nombre de su nuevo accesorio." << endl;
                                                    cin >> agregar_acc;                            
                                                    if (Accesorio_Unico(agregar_acc,lista_accesorios)==true){
                                                        accesorio_nuevo.nombre = agregar_acc;
                                                        repetir_validacion=false;
                                                    }

                                                    else{
                                                        cout << "El accesorio" << agregar_acc << "ya existe. Dos accesorios no pueden tener el mismo nombre. Intente de nuevo" <<endl; 
                                                        cout<<endl;
                                                        }
                                                }
                                                
                                                //Solicitar el tipo de accesorio
                                                char tipo_acc;
                                                cout << "Seleccione el tipo de su nuevo accesorio." << endl;
                                                cout << "a - ATAQUE   b - DEFENSA    c - SUPERVIVENCIA    d - ACONDICIONAMIENTO." << endl;
                                                cin >> tipo_acc;
                                                tipo_acc=tolower(tipo_acc);
                                                bool menu_tipo=true;

                                                while(menu_tipo==true) { 
                                                    menu_tipo=false;

                                                    if (tipo_acc=='a') {
                                                        accesorio_nuevo.tipo="ataque";
                                                        repetir_validacion=true;
                                                        while (repetir_validacion==true)
                                                        {
                                                            cout << "Ingrese el porcentaje de daño de su nuevo accesorio de ataque." << endl;
                                                            string ataque;
                                                            cin >> ataque;
                                                            if (Validar_enteros(ataque)==true){
                                                                int porcentaje=stoi(ataque);
                                                                accesorio_nuevo.porcentaje_dano = porcentaje;
                                                                repetir_validacion=false;
                                                                }

                                                            else{
                                                                cout << "El porcentaje debe ser un numero entero positivo. Intente nuevo." << endl; 
                                                                cout<<endl;
                                                                }
                                                        }
                                                    }
                                                    else if (tipo_acc=='b') 
                                                        {
                                                            accesorio_nuevo.tipo="defensa";
                                                            repetir_validacion=true;
                                                            while (repetir_validacion==true)
                                                                {
                                                                    cout << "Ingrese el porcentaje en que su accesorio de defensa disminuye el dano." << endl;
                                                                    string proteccion;
                                                                    cin >> proteccion;
                                                                    if (Validar_enteros(proteccion)==true){
                                                                        int porcentaje=stoi(proteccion);
                                                                        accesorio_nuevo.porcentaje_proteccion = porcentaje;
                                                                        repetir_validacion=false;
                                                                        }

                                                                    else{
                                                                        cout << "El porcentaje debe ser un numero entero positivo. Intente nuevo." << endl; 
                                                                        cout<<endl;
                                                                    }

                                                                }
                                                            repetir_validacion=true;
                                                            while (repetir_validacion==true)
                                                                {
                                                                    cout << "Ingrese el la protección inicial que su accesorio de defensa aporta." << endl;
                                                                    string inicial;
                                                                    cin >> inicial;
                                                                    if (Validar_enteros(inicial)==true){
                                                                        int porcentaje=stoi(inicial);
                                                                        accesorio_nuevo.proteccion_inicial = porcentaje;
                                                                        repetir_validacion=false;
                                                                        }

                                                                    else{
                                                                        cout << "La protección inicial debe ser un numero entero positivo. Intente nuevo." << endl; 
                                                                        cout<<endl;
                                                                    }
                                                                    
                                                                }
                                                        
                                                        }
                                                    else if (tipo_acc=='c') 
                                                        {
                                                            accesorio_nuevo.tipo="supervivencia";
                                                            repetir_validacion=true;
                                                            while (repetir_validacion==true)
                                                                {
                                                                    cout << "Ingrese el porcentaje de recuperación que brindará su accesorio de supervivencia." << endl;
                                                                    string recuperacion;
                                                                    cin >> recuperacion;
                                                                    if (Validar_enteros(recuperacion)==true){
                                                                        int porcentaje=stoi(recuperacion);
                                                                        accesorio_nuevo.porcentaje_recuperacion = porcentaje;
                                                                        repetir_validacion=false;
                                                                        }

                                                                    else{
                                                                        cout << "El porcentaje debe ser un numero entero positivo. Intente nuevo." << endl; 
                                                                        cout<<endl;
                                                                    }

                                                                }

                                                            repetir_validacion=true;
                                                            while (repetir_validacion==true)
                                                                {      
                                                                    repetir_validacion=false;
                                                                    cout << "Indique si con el accesorio el soldado recupera SALUD (s) o ENERGIA (e)." << endl;
                                                                    char valor_recuperado;
                                                                    valor_recuperado=tolower(valor_recuperado);
                                                                    if (valor_recuperado=='s') {
                                                                        accesorio_nuevo.valor_recuperado="Salud";
                                                                    }
                                                                    else if (valor_recuperado=='e') {
                                                                        accesorio_nuevo.valor_recuperado="Energia";
                                                                    }
                                                                    else {
                                                                        cout<<"Introduzca una opción válida (s / e). Intente de nuevo."<<endl;
                                                                        cout<<endl;
                                                                        repetir_validacion=true;
                                                                    }

                                                                }
                                                        }
                                                    else if (tipo_acc=='d') 
                                                        {
                                                            accesorio_nuevo.tipo="acondicionamiento";
                                                            repetir_validacion=true;
                                                            while (repetir_validacion==true)
                                                            {
                                                                repetir_validacion=false;
                                                                cout << "AMBIENTES DISPONIBLES " << endl;
                                                                Nodo_ambiente *imprimir= lista_ambientes;
                                                                while(imprimir!=NULL) 
                                                                    {
                                                                        int cont_ambientes=1;
                                                                        if (cont_ambientes %10 == 0)
                                                                            {
                                                                                cout<<"["<< imprimir->nombre<<"] ";
                                                                            }
                                                                        else 
                                                                            {
                                                                                cout<<"["<< imprimir->nombre<<"]"<< endl;  
                                                                            }    
                                                                        cont_ambientes+=1;
                                                                    }
                                                                imprimir=imprimir->siguiente;    
                                                            }
                                                                cout<<endl;
                                                                cout << "Ingrese el ambiente para el cual su accesorio sera creado." << endl;
                                                                string ambi;
                                                                cin >> ambi;
                                                                cout<<endl;
                                                                if (Validar_ambiente(ambi,lista_ambientes)==true)
                                                                    {
                                                                        accesorio_nuevo.ambiente = ambi;
                                                                    }

                                                                else{
                                                                    cout << "El ambiente que ingresó para su accesorio de acondicionamiento no existe. Intente nuevo." << endl; 
                                                                    cout<<endl;
                                                                    repetir_validacion=true;
                                                                    }
                                                            
                                                        }
                                                }

                                            }   
                                        else if (opcion_accesorios=='3')
                                            {
                                                if (lista_accesorios==NULL) 
                                                    {
                                                        cout << "No hay accesorios para eliminar" << endl;
                                                        menu_accesorios=true;
                                                    }         
                                                else
                                                    {
                                                        bool repetir_validacion;
                                                        while (repetir_validacion==true) 
                                                                    {
                                                                        repetir_validacion=false;
                                                                        cout << "Ingrese el nombre del accesorio que desea eliminar" << endl;
                                                                        string eliminar_accesorio;;
                                                                        cin>>eliminar_accesorio;
                                                                        cout<<endl;

                                                                        if (Validar_accesorio(eliminar_accesorio,lista_accesorios)==true) 
                                                                            {
                                                                                repetir_validacion=false;
                                                                                Borrar_Accesorio(eliminar_accesorio,lista_accesorios);
                                                                                menu_accesorios=true;
                                                                            }
                                                                        else 
                                                                            {
                                                                                cout<<"El accesorio que desea eliminar no existe. Intente de nuevo." << endl;
                                                                                repetir_validacion=true;
                                                                                cout<<endl;
                                                                    
                                                                            }
                                                                    }    
                                                    }
                                            }
                                        /*
                                        
                                        
                                        
                                        else if (opcion_accesorios=='')
                                            {
                                                cout << endl; 
                                                cout<<"ESTUDIANTES"<<endl;
                                                cout <<endl;

                                                if (lista_estudiantes==NULL) {
                                                    cout<<"[ No hay estudiantes. ]";
                                                    cout <<endl;
                                                }
                                                else 
                                                    {

                                                    Nodo_estudiante *imprimir= lista_estudiantes;
                                                    while (imprimir!=NULL) 
                                                        {
                                                            cout<<"[";
                                                            cout << imprimir->Estudiante.Nombre<< "  ";
                                                            cout<<"] ";
                                                            imprimir=imprimir->siguiente;
                                                        }
                                                    }

                                                cout <<endl;
                                                cout <<"ACCIONES";
                                                cout << "5 - Volver" << endl;

                                                if (opcion_menu=='5') 
                                                    {
                                                    menu1=true;
                                            }
                                        */
                                        else if (opcion_accesorios == '5')
                                            {
                                                menu1=true;
                                            }
            else if (opcion_menu=='5'){
                menu1=false;
                }
            else
                {
                    cout<<"Ingrese una opcion valida del menu principal"<<endl;
                    cout<<endl;
                    menu1=true;
                }
                            }
                        }

                    }
                                
                                
            
        
        
            }
        }
    }   
    return 0;
}