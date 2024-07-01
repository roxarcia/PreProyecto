#include <iostream>
#include <stdlib.h>
#include <sstream> //reemplazo stoi
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <time.h>
#include <cstdlib>

#define color SetConsoleTextAttribute

using namespace std;


//---------------------------------------------  Tipos de datos --------------------------------------------------

//Tipo de dato - Raza
typedef struct {
    string nombre;
    int energia;
    int salud = 100;
    string ambiente;
} raza;

//Tipo de dato - Accesorio
typedef struct {
    string nombre;
    string tipo;
    int energia_consumida; //midoclirias consumidas
    int valor; //porcentaje de daño -ataque, porcentaje de proteccion-defensa, porcentaje de recuperacion-supervivencia, 0-acondicionamiento
    string recuperacion; //si es de tipo acondicionamiento, es el ambiente para el que fue creado. Si es de tipo supervivencia, es si el valor se le suma a la salud o a la energia
    int contenedor; //proteccion inicial, solo defensa
    string ambiente="none"; 
} accesorio;

 //Tipo de dato - Mochila
typedef struct{
    string dueno;
    accesorio vector_mochila [5];
    int vector_usos [5];
} mochila;


//Tipo de dato - Soldado
typedef struct {
    string nombre;
    raza Raza;
    int salud;
    int proteccion = 0;
    int escudo = 0;
    int energia;
    string ambiente;
    char fidelidad;
    mochila Mochila;
    accesorio Submochila[3];
    int Submochila_usos[3];
}estudiante;

//Nodos para la lista de ambientes
struct Nodo_ambiente{
    string nombre;
    Nodo_ambiente *siguiente;
};

//Nodo para la lista de razas
struct Nodo_raza {
    raza Raza;
    Nodo_raza *siguiente;
};

//Nodo para la lista de accesorios
struct Nodo_accesorio {
    accesorio accesorio;
    Nodo_accesorio *siguiente;
};

//-----------------------------------------------------------------------------------------------------------
//---------------------------------------------    Funciones    --------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
bool Validar_enteros(string num){
    char enteros[10]= {'0','1','2','3','4','5','6','7','8','9'};
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


string Randomizar_Fidelidad(int argc, char**argv){
    int humanos=0;
    int andromedanos=0;


    srand(time(NULL));
    int num;
    string lista_fidelidad[6];

    for (int i=0;i<6;i++) {
        num=1 + rand()%(2);
        string num1=to_string(num);
        lista_fidelidad[i]=num1;
    }
    

    for (int i=0;i<6;i++) {
        if (lista_fidelidad[i]=="1") {
            humanos+=1;
        }
        else {
            andromedanos+=1;
        }

        if (humanos>3) {
           lista_fidelidad[i]="2"; 
        }
        if (andromedanos>3) {
           lista_fidelidad[i]="1"; 
        }
    }

    string retorno="";
    for (int i=0;i<6;i++) {
        retorno=(retorno+lista_fidelidad[i]);
    }
    
    return retorno;
}


int Stoi(string dato) {
    int dato_int;
    stringstream convert;
    convert<<dato;
    convert>>dato_int;

    return dato_int;
}

//Función para no repetir ambientes
bool Existe_Ambiente (string ambiente, Nodo_ambiente *&puntero){
    Nodo_ambiente *buscar = puntero;
    bool existe = false; 
    while (buscar!=NULL)
        {
            if(buscar->nombre==ambiente){
                existe=true;
            }
            buscar=buscar->siguiente;
        }
    return existe;
}

bool Existe_Raza (string parametro, Nodo_raza *&puntero,char filtro){
    Nodo_raza *buscar = puntero;
    bool existe=false;

    //verifica si existe una raza con ese nombre
    if (filtro=='N') {
        while (buscar!=NULL)
            {
                if(buscar->Raza.nombre==parametro){
                    existe=true;
                }
                buscar=buscar->siguiente;
            }
        }

    //verifica si existe una raza con ese ambiente
    else if (filtro==('A')) {
        while (buscar!=NULL)
            {
                if(buscar->Raza.ambiente==parametro){
                    existe=true;
                }
                buscar=buscar->siguiente;
            }
    }
    else if (filtro==('E')) {
        int energia=Stoi(parametro);
        while (buscar!=NULL)
            {
                if(buscar->Raza.energia==energia){
                    existe=true;
                }
                buscar=buscar->siguiente;
            }
    }
    return existe;
}

bool Existe_Accesorio (string parametro, Nodo_accesorio *&puntero,char filtro){
    Nodo_accesorio *buscar = puntero;
    bool existe=false;

    //verifica si existe un accesorio con ese nombre
    if (filtro==('N')) {
        while (buscar!=NULL)
            {
                if(buscar->accesorio.nombre==parametro){
                    existe=true;
                }
                buscar=buscar->siguiente;
            }
        }

    //verifica si existe un accesorio con ese ambiente
    else if (filtro==('A')) {
        while (buscar!=NULL)
            {
                if(buscar->accesorio.ambiente==parametro){
                    existe=true;
                }
                buscar=buscar->siguiente;
            }
    }
    //verifica si existe un accesorio de ese tipo
    else if (filtro==('T')) {
        while (buscar!=NULL)
            {
                if(buscar->accesorio.tipo==parametro){
                    existe=true;
                }
                buscar=buscar->siguiente;
            }
    }
    
    return existe;
}

int Contar_NodosAmb(Nodo_ambiente *&puntero) {
    int cont_nodos=0;

    if (puntero==NULL) {
        cont_nodos=0;
    }
    else {
        Nodo_ambiente *contar = puntero;

        while(contar!=NULL) {
            cont_nodos+=1;
            contar = contar->siguiente;
        }
    }

    return cont_nodos;
}


string Randomizar_Ambiente(int argc, char**argv,Nodo_ambiente*&puntero){
    string ambiente_random;
    int num_nodos=Contar_NodosAmb(puntero);
    
    srand(time(NULL));
    int random;
    random= 1 + rand()%(num_nodos);
    
    Nodo_ambiente*buscar=puntero;
    
    while (buscar!=NULL) 
        {
            random=(random-1);
            if (random==0) {
                ambiente_random = buscar->nombre;
            }
            buscar = buscar->siguiente;
        } 
    return ambiente_random;
}

    

//
void Mostrar_Ambientes(Nodo_ambiente *&puntero) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (puntero==NULL)
        {    
            color(hConsole, 8);
            cout<<"[ No hay ambientes. ]"<<endl;
            cout<<endl;
            color(hConsole, 7);
        }
    else 
        {
            Nodo_ambiente *mostrar= puntero;
            while (mostrar!=NULL) 
                {
                    color(hConsole, 13);
                    cout<<"[ ";
                    color(hConsole, 7);
                    cout << mostrar->nombre;
                    color(hConsole, 13);
                    cout<<" ] ";
                    mostrar=mostrar->siguiente;
                    color(hConsole, 7);
                }
                cout<<endl;
                cout<<endl;
        }
}
void Mostrar_Razas(char filtro, string parametro,Nodo_raza *&puntero) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (filtro=='N')
        {    
            color(hConsole, 8);
            cout<<"[ No hay razas. ]"<<endl;;
            cout<<endl;
            color(hConsole, 7);
        }
    else 
        {

            Nodo_raza *mostrar= puntero;
            //Muestra todas las razas
            if ((filtro=='T')) {
                while (mostrar!=NULL) 
                    {
                        color(hConsole, 13);
                        cout<<"[ ";
                        color(hConsole, 7);
                        cout << mostrar->Raza.nombre;
                        color(hConsole, 13);
                        cout<<" ] ";
                        mostrar=mostrar->siguiente;
                        color(hConsole, 7);
                    }
            }
            cout<<endl;

            //Filtrar raza por energía
            mostrar= puntero;
            if (filtro==('E')) {
                int energia=Stoi(parametro);
                bool filtrado=false;
                color(hConsole, 13);
                cout<<"- RAZAS -"<<endl;
                color(hConsole, 7);
                while (mostrar!=NULL)
                    {
                            if (mostrar->Raza.energia==energia) {
                                color(hConsole, 13);
                                cout<<"[ ";
                                color(hConsole, 7);
                                cout << mostrar->Raza.nombre; //Muestra todas aquellas que tengan esa energía 
                                color(hConsole, 13);
                                cout<<" ] ";
                                filtrado=true;
                                color(hConsole, 7);
                            }
                            mostrar=mostrar->siguiente;    
                    }
                    cout<<endl;
                if (filtrado==false) {
                    color(hConsole, 13);
                    cout<<"- RAZAS -"<<endl;
                    cout<<endl;
                    color(hConsole, 8);
                    cout<<"[  No hay razas con esa energia  ]"<<endl;
                    cout<<endl;
                    color(hConsole, 7);
                    }
            
            }

            //Imprime por ambiente
            else if (filtro==('A')) {
                mostrar= puntero;
                bool filtrado=false;
                color(hConsole, 13);
                cout<<"- RAZAS -"<<endl;
                color(hConsole, 7);
                while (mostrar!=NULL)
                    {   
                        if (mostrar->Raza.ambiente==parametro) {
                            color(hConsole, 13);
                            cout<<"[ ";
                            color(hConsole, 7);
                            cout << mostrar->Raza.nombre;
                            color(hConsole, 13);
                            cout<<" ] ";
                            color(hConsole, 7);
                            filtrado=true;
                        }
                        mostrar=mostrar->siguiente;   
                    }
                    cout<<endl;
                if (filtrado==false) {
                    color(hConsole, 13);
                    cout<<"- RAZAS -"<<endl;
                    cout<<endl;
                    color(hConsole, 8);
                    cout<<"[  No hay razas con ese ambiente.  ]"<<endl;
                    cout<<endl;
                    color(hConsole, 7);
                }
            }           
        }
}

string Minusculas(string texto) {
    for (int i = 0; ((i) < (texto.length())); i++) {
        texto[i] = tolower(texto[i]);
    }
    return texto;
}


void Menu_Razas(char tipo, Nodo_raza*&puntero1, Nodo_ambiente*&puntero2){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if (tipo=='1') {
        color(hConsole, 7);
        cout << "1 - Ver detalles de una raza" << endl;
        cout << "2 - Agregar raza"  << endl;
        cout << "3 - Eliminar raza" << endl;
        cout << "4 - Modificar raza" << endl;
        cout << "5 - Cargar archivo" << endl;
        cout << "6 - Volver al menu principal" << endl;
        cout << endl;
    }
    else if (tipo=='2') {
        bool repetir=true;
        while (repetir==true) {
            color(hConsole, 13);
            repetir=false;
            cout << "Como desea visualizar las razas? " << endl;
            cout << "a) - Ver Todas      b) - Filtrar por Energia      c) - Filtrar por Ambiente  " << endl;
            string opcion;
            cout<<endl;
            color(hConsole, 7);
            getline(cin,opcion);
            opcion=Minusculas(opcion);
            cout<<endl;

            if (opcion=="a") 
                {   
                    Mostrar_Razas('T',"none",puntero1);
                    cout<<endl;
                }
            else if (opcion=="b") 
                {
                    bool repetir_validacion=true;
                    while (repetir_validacion==true) 
                        {
                            color(hConsole, 13);
                            repetir_validacion=false;
                            cout<<"Ingrese la cantidad de energia por la que filtrar su raza.";
                            cout<<endl;
                            color(hConsole, 7);
                            string energia;
                            getline(cin,energia);
                            
                            if (Validar_enteros(energia)==true) 
                                {
                                    Mostrar_Razas('E',energia,puntero1);
                                }
                            else {
                                color(hConsole, 4);
                                cout<<"! El porcentaje de energia debe ser un numero entero positivo. Intente de nuevo.";
                                cout<<endl;
                                repetir_validacion=true;
                                color(hConsole, 7);
                            }
                        }
                }
            else if (opcion=="c") 
                {
                    bool repetir_validacion=true;
                        while (repetir_validacion==true) 
                            {
                                repetir_validacion=false;
                                cout<<"Ingrese el ambiente por el que filtrar su raza.";
                                cout<<endl;
                                color(hConsole, 13);
                                cout<<"- AMBIENTES DISPONIBLES -"<<endl;
                                color(hConsole, 7);
                                Mostrar_Ambientes(puntero2);
                                cout<<endl;
                                string ambiente;
                                getline(cin,ambiente);
                                cout<<endl;
                                
                                if (Existe_Ambiente(ambiente,puntero2)==true) {
                                    Mostrar_Razas('A',ambiente,puntero1);
                                }
                                else {
                                    color(hConsole, 4);
                                    cout<<"! El ambiente ";
                                    color(hConsole, 7);
                                    cout<<ambiente;
                                    color(hConsole, 4);
                                    cout<< " no existe. Intente de nuevo.";
                                    color(hConsole, 7);
                                    cout<<endl;
                                    repetir_validacion=true;
                                }
                            }
                }
            else 
                {
                    color(hConsole, 4);
                    cout<<"! Por favor, introduzca una opcion del menu.";
                    cout<<endl;
                    repetir=true;
                    color(hConsole, 7);
                }

        }
    }
}



bool Agregar_Razas (string nombre, Nodo_raza *&puntero1, Nodo_ambiente *&puntero2){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Nodo_raza *nuevo = new Nodo_raza();
    bool agregada;
    raza nueva_raza;

    //Validar que el nuevo nombre de la raza no sea igual a uno ya existente
    if (Existe_Raza(nombre,puntero1,'N')==true) {
        color(hConsole, 4);
        cout<<"La raza "<<nombre<<" ya existe. Dos razas no pueden tener el mismo nombre. Intente de nuevo";
        cout<<endl;
        agregada=false;
        color(hConsole, 7);
    }
    else {
        nueva_raza.nombre=nombre;
        bool repetir_validacion=true;
        cout<<endl;
            
        repetir_validacion=true;
        while (repetir_validacion==true)
            {
                cout << "Ingrese la salud de su nueva raza" << endl;
                cout<<endl;
                string sal; 
                getline(cin,sal);
                cout<<endl;
                if (Validar_enteros(sal)==true){
                    int salud=Stoi(sal);
                    nueva_raza.energia = salud;
                    repetir_validacion=false;
                }

                else{
                    color(hConsole, 4);
                    cout << "! La cantidad de salud debe ser un numero entero positivo. Intente nuevo." << endl;
                    cout<<endl;
                    color(hConsole, 7);
                    }
            }
        //Validar que la  energía de la nueva raza sea correcta
        repetir_validacion=true;
        while (repetir_validacion==true)
            {
                cout << "Ingrese la energia de su nueva raza" << endl;
                cout<<endl;
                string ener; 
                getline(cin,ener);
                cout<<endl;
                if (Validar_enteros(ener)==true){
                    int energia=Stoi(ener);
                    nueva_raza.energia = energia;
                    repetir_validacion=false;
                }

                else{
                    color(hConsole, 4);
                    cout << "! La cantidad de energia debe ser un numero entero positivo. Intente nuevo." << endl;
                    cout<<endl;
                    color(hConsole, 7);
                    }
            }
                
        repetir_validacion=true;
        while (repetir_validacion==true) 
            {
                cout<<"Ingrese el nuevo ambiente para su raza. "<< endl;
                cout<<endl;
                color(hConsole, 13);
                cout << "- AMBIENTES DISPONIBLES -" << endl;
                color(hConsole, 7);
                cout<<endl;
                Mostrar_Ambientes(puntero2);
                cout<<endl;
                string ambiente;
                getline(cin,ambiente);
                cout<<endl;
                if (Existe_Ambiente(ambiente,puntero2)==false){
                    color(hConsole, 4);
                    cout<< "! El ambiente ";
                    color(hConsole, 7);
                    cout<<ambiente;
                    color(hConsole, 4);
                    cout<<" no existe. Intente de nuevo."<< endl;
                    cout<<endl;
                    color(hConsole, 7);
                }
                else{
                    repetir_validacion=false;
                    nueva_raza.ambiente=ambiente;
                    }             
            } 

        nuevo->Raza = nueva_raza;
        agregada=true;

        if (puntero1 == NULL){
            puntero1 = nuevo;
        }
        else{
            nuevo->siguiente=puntero1;
            puntero1 = nuevo;
        }
    }
   return agregada; 
}

bool Eliminar_Razas(string parametro, Nodo_raza *&puntero, char filtro){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Nodo_raza *anterior = NULL, *auxiliar = NULL;
    bool eliminada;
    
        //Eliminar raza segun su nombre
    if (filtro=='N') {
        auxiliar = puntero;
        while(auxiliar!=NULL && auxiliar->Raza.nombre!= parametro){
            anterior = auxiliar;
            auxiliar=auxiliar->siguiente;
        }
        if (auxiliar==NULL){
            color(hConsole, 4);
            cout << "! La raza ";
            color(hConsole, 7);
            cout <<parametro;
            color(hConsole, 4);
            cout <<"  no existe. Intente de nuevo. " <<endl;
            color(hConsole, 7);
            eliminada=false;
            
        }
        else 
            {
                if (auxiliar==puntero){
                puntero=puntero->siguiente;
                }
                else{        
                    anterior->siguiente=auxiliar->siguiente;
                }
                delete auxiliar;
                eliminada=true;
            }
        }

        //Eliminar raza segun su ambiente
    if (filtro=='A') {
        anterior = puntero;
        auxiliar = puntero; 
        while(auxiliar!=NULL){
            if (auxiliar->Raza.ambiente==parametro){
                if (auxiliar==puntero){
                    puntero=puntero->siguiente;
                    delete auxiliar;
                    auxiliar = puntero;
                }
                else{        
                    anterior->siguiente=auxiliar->siguiente;
                    delete auxiliar;
                    auxiliar = anterior->siguiente;
                }
            }
            else{
                anterior=auxiliar;
                auxiliar=auxiliar->siguiente;
            }
        }
        
    }
    
    return eliminada;
}

void Modificar_Razas(string nombre, Nodo_raza *&puntero1, Nodo_ambiente *&puntero2){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Nodo_raza *buscar = puntero1;
    while (buscar->Raza.nombre!=nombre){
        buscar=buscar->siguiente;
    }
    

    //Validar que el nuevo nombre de la raza no sea igual a uno ya existente
    bool repetir_validacion=true;
    while (repetir_validacion==true)
        {
            cout<<endl;
            cout << "Ingrese el nuevo nombre de su raza." << endl;
            cout<<endl;
            string nuevo_nombre;
            getline(cin,nuevo_nombre);
            if (Existe_Raza(nuevo_nombre,puntero1,'N')==false){
                buscar->Raza.nombre = nuevo_nombre;
                repetir_validacion=false;
                }

            else{
                color(hConsole, 4);
                cout << "! La raza ";
                color(hConsole, 7);
                cout <<nuevo_nombre;
                color(hConsole, 4);
                cout << " ya existe. Dos razas no pueden tener el mismo nombre. Intente de nuevo" <<endl; 
                cout<<endl;
                color(hConsole, 7);
                }
        }
            
            
    //Validar que la nueva energía de la raza sea correcta
    repetir_validacion=true;
    while (repetir_validacion==true)
        {   
            cout<<endl;
            cout << "Ingrese la nueva energia de su raza" << endl;
            cout<<endl;
            string ener; 
            getline(cin,ener);
            if (Validar_enteros(ener)==true){
                int nueva_energia=Stoi(ener);
                buscar->Raza.energia = nueva_energia;
                repetir_validacion=false;
            }

            else{
                color(hConsole, 4);
                cout << "! La cantidad de energia debe ser un numero entero positivo. Intente nuevo." << endl;
                cout<<endl;
                color(hConsole, 7);
                }
        }
    repetir_validacion=true;
    while (repetir_validacion==true)
        {
            cout << "Ingrese la nueva salud de su nueva raza" << endl;
            cout<<endl;
            string sal; 
            getline(cin,sal);
            cout<<endl;
            if (Validar_enteros(sal)==true){
                int nueva_salud=Stoi(sal);
                buscar->Raza.salud = nueva_salud;
                repetir_validacion=false;
            }

            else{
                color(hConsole, 4);
                cout << "! La cantidad de salud debe ser un numero entero positivo. Intente nuevo." << endl;
                cout<<endl;
                color(hConsole, 7);
                }
        }
    repetir_validacion=true;
    while (repetir_validacion==true) 
        {   
            cout<<endl;
            cout<<"Ingrese el nuevo ambiente para su raza. "<< endl;
            cout<<endl;
            color(hConsole, 13);
            cout << "- AMBIENTES DISPONIBLES -" << endl;
            color(hConsole, 7);
            cout<<endl;
            Mostrar_Ambientes(puntero2);
            cout<<endl;
            string nuevo_ambiente;
            getline(cin,nuevo_ambiente);
            cout<<endl;
            if (Existe_Ambiente(nuevo_ambiente,puntero2)==false){
                color(hConsole, 4);
                cout<< "! El ambiente ";
                color(hConsole, 7);
                cout<<nuevo_ambiente;
                color(hConsole, 4);
                cout<<"  no existe en la lista. Intente de nuevo." << endl;
                cout<<endl;
                color(hConsole, 7);
            }
            else{
                repetir_validacion=false;
                buscar->Raza.ambiente=nuevo_ambiente;
                }             
        } 
}

bool Detalles_Raza(Nodo_raza *&puntero){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    bool repetir=true;
    bool hecho=false;
    string nombre;

    while (repetir==true) {
        repetir=false;
        cout<<"Introduzca el nombre de la raza de la que desea ver detalles."<<endl;
        getline(cin,nombre);


        if (Existe_Raza(nombre,puntero,'N')==true) 
            {
                Nodo_raza *buscar = puntero;
                while (buscar->Raza.nombre!=nombre){
                    buscar=buscar->siguiente;
                }
                
                color(hConsole, 13);
                cout<<"- NOMBRE: ";
                color(hConsole, 7);
                cout<<buscar->Raza.nombre;
                cout<<endl;
                color(hConsole, 13);
                cout<<"- SALUD: ";
                color(hConsole, 7);
                cout<<buscar->Raza.salud;
                cout<<endl;
                color(hConsole, 13);
                cout<<"- ENERGIA: ";
                color(hConsole, 7);
                cout<<buscar->Raza.energia;
                cout<<endl;
                color(hConsole, 13);
                cout<<"- AMBIENTE: ";
                color(hConsole, 7);
                cout<<buscar->Raza.ambiente;
                cout<<endl;
                hecho=true;
            }
        else {
            color(hConsole, 4);
            cout<<"! La raza ";
            color(hConsole, 7);
            cout<<nombre;
            color(hConsole, 4);
            cout<<" no existe. Intente de nuevo.";
            repetir=true;
            cout<<endl;
            color(hConsole, 7);
        }
    }
    return hecho;
}


//ACCESORIOS

bool Validar_Tipo(string tipo) {
    string tipos[4] = {"ataque","defensa","supervivencia","acondicionamiento"};
    bool encontrado=false;
    for (int i = 0; i < 4; i++) {
        if (tipos[i]==tipo) {
            encontrado=true;
        }
    }
    return encontrado;
}

void Aclaraciones_Acc(string tipo){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if (tipo=="ataque") {
        color(hConsole, 8);
        cout<<"! Estara ingresando el porcentaje de dano"<<endl;
        color(hConsole, 7);
    }
    else if (tipo=="defensa") {
        color(hConsole, 8);
        cout<<"! Estara ingresando el porcentaje de proteccion normal"<<endl;
        color(hConsole, 7);
    }
    else if (tipo=="supervivencia") {
        color(hConsole, 8);
        cout<<"! Estara ingresando el porcentaje de recuperacion (Usted decidira si se recupera energia o salud)"<<endl;
        color(hConsole, 7);
    }
}

bool Agregar_Accesorios (string nombre, Nodo_accesorio *&puntero1, Nodo_ambiente *&puntero2){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Nodo_accesorio *nuevo = new Nodo_accesorio();
    bool agregado;
    accesorio nuevo_accesorio;

    //Validar que el nuevo nombre de la raza no sea igual a uno ya existente
    if (Existe_Accesorio(nombre,puntero1,'N')==true) {
        color(hConsole, 4);
        cout<<"El accesorio "<<nombre<<" ya existe. Dos accesorios no pueden tener el mismo nombre. Intente de nuevo";
        cout<<endl;
        agregado=false;
        color(hConsole, 7);
    }
    else {
        nuevo_accesorio.nombre=nombre;
        bool repetir_validacion=true;
            
        //Ingresar un tipo
        while (repetir_validacion==true)
            {   
                repetir_validacion=false;
                cout<<endl;
                cout << " - Ingrese el tipo de su accesorio -" << endl;
                cout<< "(a) Ataque  -  (b) Defensa  - (c) Supervivencia  -  (d) Acondicionamiento";
                cout<<endl;
                string tipo; 
                getline(cin,tipo);
                tipo=Minusculas(tipo);
                
                if (tipo=="a") 
                    {
                        tipo="ataque";
                        nuevo_accesorio.tipo = tipo;
                        nuevo_accesorio.contenedor=0;
                        nuevo_accesorio.recuperacion=" ";
                    }
                else if (tipo=="b") 
                    {
                        tipo="defensa";
                        nuevo_accesorio.tipo=tipo;
                        nuevo_accesorio.recuperacion=" ";
                        bool repetir=true;
                        while (repetir==true) 
                                {
                                    repetir=false;
                                    string opcion;
                                    cout<<endl;
                                    cout<<"Ingrese el porcentaje de proteccion inicial que brinda su accesorio"<<endl;
                                    cout<<endl;
                                    getline(cin,opcion);

                                    if (Validar_enteros(opcion)==true) 
                                        {
                                            int proteccion_inicial=Stoi(opcion);
                                            nuevo_accesorio.contenedor=proteccion_inicial;
                                        }
                                    else 
                                        {
                                            color(hConsole, 4);
                                            cout<<"! El porcentaje debe ser un numero entero positivo. Intente de nuevo"<<endl;
                                            cout<<endl;
                                            repetir=true;
                                            color(hConsole, 7);
                                        }
                                }
                    }
                else if (tipo=="c")
                    {
                        tipo="supervivencia";
                        nuevo_accesorio.tipo = tipo;
                        nuevo_accesorio.contenedor=0;
                    }
                else if (tipo=="d")
                    {
                        tipo="acondicionamiento";
                        nuevo_accesorio.valor=0;
                        nuevo_accesorio.contenedor=0;
                        nuevo_accesorio.tipo=tipo;
                        bool repetir=true;
                        while (repetir==true){
                            repetir=false;
                            string ambiente;
                            cout<<"Ingrese el ambiente que quiere asignar a su accesorio"<<endl;
                            cout<<endl;
                            color(hConsole, 13);
                            cout<<"- AMBIENTES DISPONIBLES -"<<endl;
                            color(hConsole, 7);
                            cout<<endl;
                            Mostrar_Ambientes(puntero2);
                            cout<<endl;
                            getline(cin,ambiente);
                            cout<<endl;

                            if (Existe_Ambiente(ambiente,puntero2)==true) {
                                nuevo_accesorio.ambiente=ambiente;
                                nuevo_accesorio.recuperacion=ambiente;
                            }
                            else{
                                color(hConsole, 4);
                                repetir=true;
                                cout<<"! El ambiente ";
                                color(hConsole, 7);
                                cout<<ambiente;
                                color(hConsole, 4);
                                cout<< " no existe. Revise e intente de nuevo."<<endl;
                                cout<<endl;
                                color(hConsole, 7);
                            }
                        }
                    }
                else 
                    {
                        color(hConsole, 4);
                        cout<<"! Por favor, ingrese una opcion del menu.";
                        cout<<endl;
                        cout<<endl;
                        repetir_validacion=true;
                        color(hConsole, 7);
                    }
            }

            //Asignar Valor
        string tipo=nuevo_accesorio.tipo;
        if (tipo!="acondicionamiento")
            {
                repetir_validacion=true;
                while (repetir_validacion==true)
                    {   
                        repetir_validacion=false;
                        cout<<endl;
                        cout << "Ingrese el valor de su accesorio" << endl;
                        cout<<endl;
                        Aclaraciones_Acc(tipo);
                        cout<<endl;
                        string valor; 
                        getline(cin,valor);
                        cout<<endl;
                                
                        if (Validar_enteros(valor)==false) 
                            {
                                color(hConsole, 4);
                                cout<<"! El porcentaje debe ser un numero entero positivo. Intente de nuevo"<<endl;
                                repetir_validacion=true;
                                cout<<endl;
                                color(hConsole, 7);
                            }
                        else 
                            {
                                int valor1=Stoi(valor);
                                nuevo_accesorio.valor= valor1;

                                if (tipo=="supervivencia") 
                                    {
                                        bool repetir=true;
                                        while (repetir==true) {
                                            repetir=false;
                                            string opcion;
                                            cout<<endl;
                                            cout<<"Seleccione si quiere que el porcentaje establecido se recupere en salud o en energia."<<endl;
                                            cout<<"a- Salud    b-Energia"<<endl;
                                            cout<<endl;
                                            getline(cin,opcion);
                                            opcion=Minusculas(opcion);

                                            if (opcion=="a") {
                                                nuevo_accesorio.recuperacion="salud";
                                            }
                                            else if (opcion=="b") {
                                                nuevo_accesorio.recuperacion="energia";
                                            }
                                            else {
                                                color(hConsole, 4);
                                                cout<<"! Por favor, introduzca una opcion valida."<<endl;
                                                cout<<endl;
                                                repetir=true;
                                                color(hConsole, 7);
                                            }
                                        }
                                    }   
                            }
                    }
            }
        
            //Asignar energia
        repetir_validacion=true;
        while (repetir_validacion==true) 
            {
                string ener;
                cout<<endl;
                cout<<"Ingrese la energia que consumira su accesorio"<<endl;
                cout<<endl;
                getline(cin,ener);

                if (Validar_enteros(ener)==true)
                    {
                        int energia=Stoi(ener);
                        nuevo_accesorio.energia_consumida= energia;
                        repetir_validacion=false;
                    }

                else{
                    color(hConsole, 4);
                    cout << "! La cantidad de energia debe ser un numero entero positivo. Intente nuevo." << endl;
                    cout<<endl;
                    color(hConsole, 7);
                    }
            }
                
        nuevo->accesorio = nuevo_accesorio;
        agregado=true;
        if (puntero1 == NULL){
            puntero1 = nuevo;
        }
        else{
            nuevo->siguiente=puntero1;
            puntero1 = nuevo;
        }
    }
   return agregado; 
}



bool Eliminar_Accesorios(string parametro, Nodo_accesorio *&puntero, char filtro){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Nodo_accesorio *anterior = NULL, *auxiliar = NULL;
    bool eliminado;
    if (puntero == NULL){
        color(hConsole, 4);
        cout << "No hay accesorios para eliminar. Agregue un accesorio primero." << endl;
        eliminado=true;
        cout<<endl;
        color(hConsole, 7);
    }
    else{
        //eliminar accesorio segun su nombre
        if (filtro=='N') 
            {
                auxiliar = puntero;
                while(auxiliar!=NULL && auxiliar->accesorio.nombre!= parametro){
                    anterior = auxiliar;
                    auxiliar=auxiliar->siguiente;
                }
                if (auxiliar==NULL){
                    color(hConsole, 4);
                    cout << "! El accesorio ";
                    color(hConsole, 7);
                    cout<<parametro;
                    color(hConsole, 8);
                    cout<<"  no existe. " <<endl;
                    eliminado=false;
                    color(hConsole, 7);
                    }
                else {
                    if (auxiliar==puntero){
                    puntero=puntero->siguiente;
                    }
                    else{        
                        anterior->siguiente=auxiliar->siguiente;
                    }
                    delete auxiliar;
                    eliminado=true;
                }
            }

        //Eliminar accesorio segun su ambiente
        if (filtro=='A') 
            {
                anterior = NULL;
                auxiliar = puntero; 
                while(auxiliar!=NULL){
                    if (auxiliar->accesorio.ambiente==parametro)
                        {
                            if (auxiliar==puntero)
                                {
                                    puntero=puntero->siguiente;
                                    delete auxiliar;
                                    auxiliar = puntero;
                                }
                            else
                                {        
                                    anterior->siguiente=auxiliar->siguiente;
                                    delete auxiliar;
                                    auxiliar = anterior->siguiente;
                                }
                        }
                    else
                        {
                            anterior=auxiliar;
                            auxiliar=auxiliar->siguiente;
                        }
                }
            
            }
    }
    return eliminado;
}

bool Confirmacion_FiltroAcc (string tipo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    bool confirmado;
    bool repetir_validacion=true;

    while (repetir_validacion==true) {
        repetir_validacion=false;
        cout<<endl;
        string opcion;
        cout<<"Quiere filtrarlos tambien por porcentaje de "<<tipo<<" ? (s/n)"<<endl;
        cout<<endl;
        getline(cin,opcion);
        
        if ( (opcion=="S")  || (opcion=="s") ) {
            confirmado=true;
        }
        else if ((opcion=="N") || (opcion=="n")) {
            confirmado=false;
        }
        else {
            color(hConsole, 4);
            cout<<"! Debe marcar S o N para confirmar. Intente de nuevo";
            cout<<endl;
            repetir_validacion=true;
            color(hConsole, 7);
        }

    }
    return confirmado;
}

void Mostrar_AccesoriosFilt(string tipo, Nodo_accesorio *&puntero) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    bool repetir_validacion = true;
    string caracteristica;
    Nodo_accesorio *buscar = puntero;
    if (tipo=="ataque") {
        caracteristica="dano";
    }
    if (tipo=="defensa") {
        caracteristica="proteccion";
    }
    if (tipo=="supervivencia") {
        caracteristica="recuperacion";
    }
    
    while (repetir_validacion==true) 
        {

            repetir_validacion=false;
            cout<<"Ingrese el porcentaje de "<<caracteristica<<" por el cual filtrar la lista"<< endl;
            string porcentaje;
            cout<<endl;
            getline(cin,porcentaje);

            if (Validar_enteros(porcentaje)==true) 
                {   
                    int filtro=Stoi(porcentaje);
                    bool existe=false;
                    while (buscar!=NULL)
                        {   
                            if ((buscar->accesorio.tipo==tipo)&&(buscar->accesorio.valor==filtro)) {
                                existe=true;
                                color(hConsole, 13);
                                cout<<"[ ";
                                color(hConsole, 7);
                                cout<< buscar->accesorio.nombre;
                                color(hConsole, 13);
                                cout<<" ] ";
                                cout<<"  ";
                                }
                                color(hConsole, 7);
                            buscar=buscar->siguiente;    
                        }
                            cout<<endl;
                            
                            if (existe!=true){
                                color(hConsole, 8);
                                cout<<"[ No hay ningun accesorio de tipo ";
                                color(hConsole, 7);
                                cout<<tipo;
                                color(hConsole, 8);
                                cout<<" con ese porcentaje de ";
                                color(hConsole, 7);
                                cout<<caracteristica;
                                color(hConsole, 8);
                                cout<<" ]";
                                color(hConsole, 7);
                                cout<<endl;
                            }
                }  
            else {
                color(hConsole, 4);
                cout<<"! El porcentaje de ";
                color(hConsole, 7);
                cout<<caracteristica;
                color(hConsole, 4);
                cout<<" debe ser un numero entero. Intente de nuevo."<<endl;
                color(hConsole, 7);
                cout<<endl;
                repetir_validacion=true;
            }
        }
} 

   
bool Mostrar_TodosTipo(string tipo, Nodo_accesorio *&puntero) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Nodo_accesorio*buscar=puntero;
    bool existe=false;
    while (buscar!=NULL) 
        {   
            if (buscar->accesorio.tipo==tipo) {
                existe=true;
                color(hConsole, 13);
                cout<<"[ ";
                color(hConsole, 7);
                cout << buscar->accesorio.nombre << "  ";
                color(hConsole,7);
                cout<<"]"; 
                }
            buscar=buscar->siguiente;
        }
        cout<<endl;

    return existe;
}
void Mostrar_TipoAccesorios(Nodo_accesorio *&puntero,Nodo_ambiente *&puntero1) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Nodo_accesorio *buscar = puntero;
    string opcion;
    bool repetir=true;
    bool existe;
    

    while (repetir==true) {
        repetir=false;
        cout << "Escoja el tipo por el que desea filtrar: " << endl;
        cout << "a - Ataque            b - Defensa"<< endl;
        cout << "c - Supervivencia     d - Acondicionamiento" << endl;
        cout<<endl;
        getline(cin,opcion);
        opcion=Minusculas(opcion);
        cout<<endl;
        if ((opcion=="a"))
            {   
                string tipo="ataque";
                color(hConsole, 13);
                cout<<"- ACCESORIOS DE ATAQUE -"<<endl;
                color(hConsole, 7);
                existe=Mostrar_TodosTipo(tipo,puntero);
                if (existe==false) {
                    color(hConsole, 8);
                    cout<<"[ No hay ningun accesorio de tipo ataque ]";
                    cout<<endl;
                    color(hConsole, 7);
                }
                else {
                    cout<<endl;
                    if (Confirmacion_FiltroAcc("dano")==true) {
                        Mostrar_AccesoriosFilt(tipo,puntero);
                    }
                    else 
                        {   
                            color(hConsole, 13);
                            cout<<"- ACCESORIOS -"<<endl;
                            color(hConsole, 7);
                            cout<<endl;
                            Mostrar_TodosTipo(tipo,puntero);
                            cout<<endl;
                        }  
                }
            }

        else if (opcion=="b") {
            string tipo="defensa";
            color(hConsole, 13);
            cout<<"- ACCESORIOS DE DEFENSA -"<<endl;
            color(hConsole, 7);
            existe=Mostrar_TodosTipo(tipo,puntero);
            if (existe==false) {
                color(hConsole, 8);
                cout<<"[ No hay ningun accesorio de tipo defensa ]";
                cout<<endl;
                color(hConsole, 7);
            }
            else {
                cout<<endl;
                if (Confirmacion_FiltroAcc("proteccion")==true) {
                    Mostrar_AccesoriosFilt(tipo,puntero);
                }
                else {
                    color(hConsole, 13);
                    cout<<"- ACCESORIOS -"<<endl;
                    color(hConsole, 7);
                    cout<<endl;
                    Mostrar_TodosTipo(tipo,puntero);
                }
            }
        }

        else if (opcion=="c") {
                string tipo="supervivencia";
                color(hConsole, 13);
                cout<<"- ACCESORIOS DE SUPERVIVENCIA -"<<endl;
                color(hConsole, 7);
                existe=Mostrar_TodosTipo(tipo,puntero);
                if (existe==false) {
                    color(hConsole, 8);
                    cout<<"[ No hay ningun accesorio de tipo supervivencia ]";
                    cout<<endl;
                    color(hConsole, 7);
                }
                else {
                    if (Confirmacion_FiltroAcc("recuperacion")==true) {
                        Mostrar_AccesoriosFilt(tipo,puntero);
                    }
                    else {
                        color(hConsole, 13);
                        cout<<"- ACCESORIOS -"<<endl;
                        color(hConsole, 7);
                        cout<<endl;
                        Mostrar_TodosTipo(tipo,puntero);
                    }
                }
                

            }

        else if (opcion=="d") {
            string tipo="acondicionamiento";
            bool repetir_validacion=true;

            while (repetir_validacion==(true)){
                repetir_validacion=false;
                cout<<"Ingrese el nombre del ambiente por el que desea filtrar los accesorios"<<endl;
                cout<<endl;
                color(hConsole, 13);
                cout<<"- AMBIENTES DISPONIBLES -"<<endl;
                color(hConsole, 7);
                cout<<endl;
                Mostrar_Ambientes(puntero1);
                cout<<endl;
                string filtro_ambiente;
                getline(cin,filtro_ambiente);
                cout<<endl;

                if (Existe_Ambiente(filtro_ambiente,puntero1)==true) {
                    color(hConsole, 13);
                    cout<<"ACCESORIOS DE ACONDICIONAMIENTO"<<endl;
                    color(hConsole, 7);
                    while (buscar!=NULL) 
                        {                               if (buscar->accesorio.ambiente==filtro_ambiente) {
                                color(hConsole, 13);
                                cout<<"[";
                                color(hConsole, 7);
                                cout << buscar->accesorio.nombre << "  ";
                                color(hConsole, 13);
                                cout<<"]";
                                existe=true;
                                color(hConsole, 7);
                            }
                            buscar=buscar->siguiente;
                        }
                    if (existe==false) {
                            color(hConsole, 8);
                            cout<<"[ No hay ningun accesorio de acondicionamiento con el ambiente ";
                            color(hConsole, 7);
                            cout<<filtro_ambiente;
                            color(hConsole, 8);
                            cout<<" ]";
                            cout<<endl;
                            color(hConsole, 7);
                        }
                    }
                else {
                    color(hConsole, 4);
                    cout<<"! El ambiente ";
                    color(hConsole, 7);
                    cout<<filtro_ambiente;
                    color(hConsole, 4);
                    cout<<" no existe. Intente de nuevo";
                    repetir_validacion=true;
                    color(hConsole, 7);
                    cout<<endl;
                    }
                }
            
            }
        
        else {
            color(hConsole, 4);
            cout<<"! Por favor, introduzca una opción del menu."<<endl;
            cout<<endl;
            repetir=true;
            color(hConsole, 7);
        }
    }
}

void Mostrar_TodosAcc(Nodo_accesorio*&puntero) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Nodo_accesorio *buscar = puntero;
    while (buscar!=NULL) 
        {   
            color(hConsole, 13);
            cout<<"[ ";
            color(hConsole, 7);
            cout << buscar->accesorio.nombre;
            color(hConsole, 13);
            cout<<" ] ";
            color(hConsole, 7);
            buscar=buscar->siguiente;
        }
    cout<<endl;
}


void Menu_Accesorios(char tipo, Nodo_accesorio*&puntero1, Nodo_ambiente*&puntero2) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if (tipo=='1') 
        {
            bool repetir=true;
            while (repetir==true) 
                {
                    repetir=false;
                    cout << "Como desea visualizar los accesorios? " << endl;
                    cout << "a- Ver Todos      b- Filtrar por Tipo" << endl;
                    cout << "c- Filtrar por Energia" << endl;
                    cout<<endl;
                    string opcion;
                    getline(cin,opcion);
                    if (opcion=="a") 
                        {
                            Mostrar_TodosAcc(puntero1);
                        }
                    else if (opcion=="b") 
                        {   
                            cout<<endl;
                            Mostrar_TipoAccesorios(puntero1,puntero2);
                        }
                    
                    else if (opcion=="c") 
                        {
                            bool repetir_validacion=true;
                            Nodo_accesorio*buscar = puntero1;
                            while (repetir_validacion==true) 
                                {
                                    repetir_validacion=false;
                                    cout<<endl;
                                    cout<<"Ingrese el porcentaje de energia por el cual filtrar la lista"<< endl;
                                    cout<<endl;
                                    string porcentaje;
                                    getline(cin,porcentaje);
                                    cout<<endl;
                                    if (Validar_enteros(porcentaje)==true) 
                                        {   
                                            int filtro=Stoi(porcentaje);
                                            bool existe=false;
                                            while (buscar!=NULL)
                                                {   
                                                    if ((buscar->accesorio.energia_consumida==filtro)) {
                                                        cout<<"[ ";
                                                        cout << buscar->accesorio.nombre;
                                                        existe=true;
                                                        cout<<" ] ";
                                                        cout<<"  ";
                                                        }
                                                    buscar=buscar->siguiente;    
                                                }
                                                if (existe!=true){
                                                    color(hConsole, 8);
                                                    cout<<"[ No hay ningun accesorio con ese porcentaje de energia ]";
                                                    cout<<endl;
                                                    color(hConsole, 7);
                                                }
                                        }  
                                    else 
                                        {
                                            color(hConsole, 4);
                                            cout<<"! El porcentaje de energia debe ser un numero entero. Intente de nuevo."<<endl;
                                            cout<<endl;
                                            repetir_validacion=true;
                                            color(hConsole, 7);
                                        }
                                }
                        }       
                    else 
                        {
                            color(hConsole, 4);
                            cout<<"! Por favor, introduzca una opcion del menu.";
                            cout<<endl;
                            repetir=true;
                            color(hConsole, 7);
                        }
                }
        }

    if (tipo=='2') {
        cout << "1 - Ver detalles de un accesorio" << endl;
        cout << "2 - Agregar accesorio"  << endl;
        cout << "3 - Eliminar accesorio" << endl;
        cout << "4 - Modificar accesorio" << endl;
        cout << "5 - Cargar archivo" << endl;
        cout << "6 - Volver al menu principal" << endl;
        cout<<endl;
    }
}



void Modificar_Accesorios(string nombre, Nodo_accesorio *&puntero1, Nodo_ambiente *&puntero2) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Nodo_accesorio*buscar = puntero1;
    while (buscar->accesorio.nombre!=nombre){
        buscar=buscar->siguiente;
    }
    

    //Validar que el nuevo nombre del accesorio no sea igual a uno ya existente
    bool repetir_validacion=true;
    while (repetir_validacion==true)
        {
            cout<<endl;
            cout << "Ingrese el nuevo nombre de su accesorio." << endl;
            cout<<endl;
            string nuevo_nombre;
            getline(cin,nuevo_nombre);
            if (Existe_Accesorio(nuevo_nombre,puntero1,'N')==false){
                buscar->accesorio.nombre = nuevo_nombre;
                repetir_validacion=false;
                }

            else{
                color(hConsole, 4);
                cout<< "! El accesorio ";
                color(hConsole, 7);
                cout<<nuevo_nombre;
                color(hConsole, 4);
                cout<< " ya existe. Dos accesorios no pueden tener el mismo nombre. Intente de nuevo" <<endl; 
                cout<<endl;
                color(hConsole, 7);
                }
        }
    
            
        //Ingresar un tipo
        repetir_validacion=true;
        while (repetir_validacion==true)
            {   
                repetir_validacion=false;
                cout << "Ingrese el nuevo tipo de su accesorio" << endl;
                cout<< "(a) Ataque  -  (b) Defensa  - (c)Supervivencia  -  d-Acondicionamiento";
                cout<<endl;
                string tipo; 
                getline(cin,tipo);
                tipo=Minusculas(tipo);
                
                if (tipo=="a") 
                    {
                        tipo="ataque";
                        buscar->accesorio.tipo = tipo;
                        buscar->accesorio.contenedor=0;
                        buscar->accesorio.recuperacion=" ";
                    }
                else if (tipo=="b") 
                    {
                        tipo="defensa";
                        buscar->accesorio.tipo=tipo;
                        buscar->accesorio.recuperacion=" ";
                        bool repetir=true;
                        while (repetir==true) 
                                {
                                    repetir=false;
                                    string opcion;
                                    cout<<endl;
                                    cout<<"Ingrese el porcentaje de proteccion inicial que brinda su accesorio"<<endl;
                                    cout<<endl;
                                    getline(cin,opcion);

                                    if (Validar_enteros(opcion)==true) 
                                        {
                                            int proteccion_inicial=Stoi(opcion);
                                            buscar->accesorio.contenedor=proteccion_inicial;
                                        }
                                    else 
                                        {
                                            color(hConsole, 4);
                                            cout<<"! El porcentaje debe ser un numero entero positivo. Intente de nuevo"<<endl;
                                            cout<<endl;
                                            repetir=true;
                                            color(hConsole, 7);
                                        }
                                }
                    }
                else if (tipo=="c")
                    {
                        tipo="supervivencia";
                        buscar->accesorio.tipo = tipo;
                        buscar->accesorio.contenedor=0;
                    }
                else if (tipo=="d")
                    {
                        tipo="acondicionamiento";
                        buscar->accesorio.valor=0;
                        buscar->accesorio.contenedor=0;
                        bool repetir=true;
                        while (repetir==true){
                            repetir=false;
                            string ambiente;
                            cout<<"Ingrese el ambiente que quiere asignar a su accesorio"<<endl;
                            color(hConsole, 13);
                            cout<<endl;
                            cout<<"- AMBIENTES DISPONIBLES -"<<endl;
                            color(hConsole, 7);
                            cout<<endl;
                            Mostrar_Ambientes(puntero2);
                            cout<<endl;
                            getline(cin,ambiente);
                            cout<<endl;

                            if (Existe_Ambiente(ambiente,puntero2)==true) {
                                buscar->accesorio.ambiente=ambiente;
                                buscar->accesorio.recuperacion=ambiente;
                            }
                            else{
                                color(hConsole, 4);
                                repetir=true;
                                cout<<"! El ambiente ";
                                color(hConsole, 7);
                                cout<<ambiente;
                                color(hConsole, 4);
                                cout<< " no existe. Revise e intente de nuevo."<<endl;
                                cout<<endl;
                                color(hConsole, 7);
                            }
                        }
                    }
                else 
                    {
                        color(hConsole, 4);
                        cout<<"! Por favor, ingrese una opcion del menu.";
                        cout<<endl;
                        cout<<endl;
                        repetir_validacion=true;
                        color(hConsole, 7);
                    }
            }

            //Asignar Valor
            string tipo=buscar->accesorio.tipo;
        if (tipo!="acondicionamiento")
            {
                repetir_validacion=true;
                while (repetir_validacion==true)
                    {   
                        repetir_validacion=false;
                        cout<<endl;
                        cout << "Ingrese el nuevo valor de su accesorio" << endl;
                        cout<<endl;
                        Aclaraciones_Acc(tipo);
                        string valor; 
                        getline(cin,valor);
                        cout<<endl;
                                
                        if (Validar_enteros(valor)==false) 
                            {
                                color(hConsole, 4);
                                cout<<"! El porcentaje debe ser un numero entero positivo. Intente de nuevo"<<endl;
                                repetir_validacion=true;
                                cout<<endl;
                                color(hConsole, 7);
                            }
                        else 
                            {
                                int valor1=Stoi(valor);
                                buscar->accesorio.valor= valor1;

                                if (tipo=="supervivencia") 
                                    {
                                        bool repetir=true;
                                        while (repetir==true) {
                                            repetir=false;
                                            string opcion;
                                            cout<<endl;
                                            cout<<"Seleccione si quiere que el porcentaje establecido se recupere en salud o en energia."<<endl;
                                            cout<<"a- Salud    b-Energia"<<endl;
                                            getline(cin,opcion);
                                            opcion=Minusculas(opcion);

                                            if (opcion=="a") {
                                                buscar->accesorio.recuperacion="salud";
                                            }
                                            else if (opcion=="b") {
                                                buscar->accesorio.recuperacion="energia";
                                            }
                                            else {
                                                color(hConsole, 4);
                                                cout<<"! Por favor, introduzca una opcion valida."<<endl;
                                                cout<<endl;
                                                repetir=true;
                                                color(hConsole, 7);
                                            }
                                        }
                                    }   
                            }
                    }
            }
        
            //Asignar energia
        repetir_validacion=true;
        while (repetir_validacion==true) 
            {
                string ener;
                cout<<endl;
                cout<<"Ingrese la nueva energia que consumira su accesorio"<<endl;
                cout<<endl;
                getline(cin,ener);

                if (Validar_enteros(ener)==true)
                    {
                        int energia=Stoi(ener);
                        buscar->accesorio.energia_consumida= energia;
                        repetir_validacion=false;
                    }

                else{
                    color(hConsole, 4);
                    cout << "! La cantidad de energia debe ser un numero entero positivo. Intente nuevo." << endl;
                    cout<<endl;
                    color(hConsole, 7);
                    }
            }   
}




bool Detalles_Accesorio(Nodo_accesorio *&puntero){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    bool repetir=true;
    bool hecho=false;
    string nombre;

    while (repetir==true) {
        repetir=false;
        cout<<"Introduzca el nombre del accesorio del que desea ver detalles."<<endl;
        cout<<endl;
        getline(cin,nombre);


        if (Existe_Accesorio(nombre,puntero,'N')==true) 
            {
                Nodo_accesorio *buscar = puntero;
                while (buscar->accesorio.nombre!=nombre){
                    buscar=buscar->siguiente;
                }
                color(hConsole, 13);
                cout<<"- NOMBRE: ";
                color(hConsole, 7);
                cout << buscar->accesorio.nombre;
                cout<<endl;
                color(hConsole, 13);
                cout<<"- TIPO: ";
                color(hConsole, 7);
                cout << buscar->accesorio.tipo;
                cout<<endl;
                color(hConsole, 13);
                cout<<"- VALOR: ";
                color(hConsole, 7);
                cout<< buscar->accesorio.valor;
                cout<<endl;
                if (buscar->accesorio.tipo=="acondicionamiento") 
                    {
                        color(hConsole, 13);
                        cout<<"- RECUPERACION: ";
                        color(hConsole, 7);
                        cout<< buscar->accesorio.ambiente;
                        cout<<endl;
                    }
                else if (buscar->accesorio.tipo=="supervivencia") 
                    {
                        color(hConsole, 13);
                        cout<<"- RECUPERACION: ";
                        color(hConsole, 7);
                        cout<< buscar->accesorio.recuperacion;
                        cout<<endl;
                    }
                else {
                    cout<<"- RECUPERACION: Ninguna";
                    cout<<endl;
                }
                color(hConsole, 13);
                cout<<"- ENERGIA: ";
                color(hConsole, 7);
                cout<< buscar->accesorio.energia_consumida;
                cout<<endl;
                color(hConsole, 13);
                cout<<"- CONTENEDOR (proteccion inicial): ";
                color(hConsole, 7);
                cout<< buscar->accesorio.contenedor;
                cout<<endl;
                hecho=true;
            }
        else {
            color(hConsole, 4);
            cout<<"! La raza ";
            color(hConsole, 7);
            cout<<nombre;
            color(hConsole, 4);
            cout<< " no existe. Intente de nuevo.";
            repetir=true;
            cout<<endl;
            color(hConsole, 7);
        }
    }
    return hecho;
}

//AMBIENTES
void Menu_Ambientes(Nodo_ambiente *&puntero) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Mostrar_Ambientes(puntero);
    color(hConsole,7);
    cout << "1 - Agregar ambiente" << endl;
    cout << "2 - Eliminar ambiente"  << endl;
    cout << "3 - Modificar ambiente"  << endl;
    cout << "4 - Cargar archivo"  << endl;
    cout << "5 - Volver al menú principal" << endl;
    cout<<endl;
}


bool Agregar_Ambientes(string ambiente, Nodo_ambiente*&puntero){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    bool agregado;
    Nodo_ambiente *nuevo = new Nodo_ambiente();


    if ((Existe_Ambiente(ambiente,puntero)==false)) {
        nuevo->nombre = ambiente;
        agregado=true;
        if (puntero == NULL){
            puntero = nuevo;
        }
        else{
            nuevo->siguiente=puntero;
            puntero = nuevo;
        }
    }
    else {
        color(hConsole, 4);
        agregado=false;
        cout<<"! El ambiente ";
        color(hConsole, 7);
        cout<<ambiente;
        color(hConsole, 4);
        cout<<" ya existe. Dos ambientes no pueden tener el mismo nombre. Intente de nuevo."<<endl;
        cout<<endl;
        color(hConsole, 7);
    }
    return agregado;
}

bool Confirmacion_EliminarAmbiente (string ambiente, Nodo_raza *&puntero1, Nodo_accesorio *&puntero2) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    bool confirmado;
    
    bool validar=true;
    while(validar==true) {
        validar=false;
        cout<<"Esta seguro que quiere eliminar este ambiente? (s/n)"<<endl;
        cout<<endl;
        if (Existe_Raza(ambiente,puntero1,'A')==true) {
            color(hConsole, 8);
            cout<<"! Si elimina este ambiente, eliminara las siguientes razas:"<<endl;
            Mostrar_Razas('A',ambiente,puntero1);
            cout<<endl;
            color(hConsole, 7);
        }
        if (Existe_Accesorio(ambiente,puntero2, 'A')==true){
            color(hConsole, 8);
            cout<<"! Si elimina este ambiente, eliminara los siguientes accesorios:"<<endl;
            Nodo_accesorio*& buscar = puntero2;
            color(hConsole, 7);
            while (buscar!=NULL) 
                {   
                    if (buscar->accesorio.ambiente==ambiente) {
                        cout<<"[ ";
                        cout << buscar->accesorio.nombre;
                        cout<<" ]";
                        }
                    buscar=buscar->siguiente;
                }
            cout<<endl;
        }
        string opcion;
        getline(cin,opcion);
        opcion=Minusculas(opcion);

        if (opcion=="s") {
            confirmado=true;
        }
        else if (opcion=="n") {
            confirmado=false;
        }
        else {
            color(hConsole, 4);
            cout<<"! Introduzca 's' para 'SI' y 'n' para 'NO'. En letras minusculas."<<endl;
            cout<<endl;
            validar=true;
            color(hConsole, 7);
        } 
                                                
    }
    
    return confirmado;
}
bool Eliminar_Ambiente(string ambiente, Nodo_ambiente *&puntero1, Nodo_raza*&puntero2, Nodo_accesorio *&puntero3){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Nodo_ambiente *anterior = NULL, *auxiliar = NULL;
    bool eliminado;
    auxiliar = puntero1;
    
    while(auxiliar!=NULL && auxiliar->nombre!= ambiente){
        anterior = auxiliar;
        auxiliar=auxiliar->siguiente;
    }
    if (auxiliar==NULL){
        color(hConsole, 4);
        cout << "! El ambiente que desea eliminar no existe. " <<endl;
        eliminado=false;
        color(hConsole, 7);
        
    }
    else {
            
            if (auxiliar==puntero1)
                {
                    puntero1=puntero1->siguiente;
                }
            else
                {        
                    anterior->siguiente=auxiliar->siguiente;
                }
                delete auxiliar;
                eliminado=true;

            if (Existe_Raza(ambiente,puntero2,'A')==true) {
                Eliminar_Razas(ambiente,puntero2,'A');
            }

            if (Existe_Accesorio(ambiente,puntero3,'A')==true) {
                Eliminar_Accesorios(ambiente,puntero3,'A');
            }
                
        }
    return eliminado;
}
//Modificar
void Modificar_Ambiente(string nombre, Nodo_raza *&puntero1, Nodo_ambiente *&puntero2, Nodo_accesorio *&puntero3){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    Nodo_ambiente *buscar = puntero2;

    while ((buscar->nombre!=nombre)){
        buscar=buscar->siguiente;
    }
                
                
    bool repetir_validacion=true;
    string nuevo_nombre;

    //Validar que el nuevo nombre del ambiente no sea igual a uno ya existente
    while (repetir_validacion==true)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            cout << "Ingrese el nuevo nombre de su ambiente." << endl;
            cout<<endl;
            getline(cin,nuevo_nombre);
            if (Existe_Ambiente(nuevo_nombre,puntero2)==false){
                    buscar->nombre = nuevo_nombre;
                    repetir_validacion=false;
                }

            else{
                color(hConsole, 4);
                cout << "! El ambiente ";
                color(hConsole, 7);
                cout<<nuevo_nombre;
                
                color(hConsole, 4);
                cout<< " ya existe. Dos ambientes no pueden tener el mismo nombre. Intente de nuevo" <<endl; 
                cout<<endl;
                color(hConsole, 7);
                
                }
        }
    if (Existe_Raza(nombre,puntero1,'A')==true) 
        {
            Nodo_raza *buscar_raza=puntero1;
            while(buscar_raza!=NULL)
                {
                    if(buscar_raza->Raza.ambiente==nombre)
                        {
                            buscar_raza->Raza.ambiente=nuevo_nombre;
                        
                        }
                    buscar_raza=buscar_raza->siguiente;
                }
        }

    if (Existe_Accesorio(nombre,puntero3,'A')==true) {
        Nodo_accesorio *buscar_accesorio=puntero3;
        while(buscar_accesorio!=NULL)
            {
                if(buscar_accesorio->accesorio.ambiente==nombre)
                    {
                        buscar_accesorio->accesorio.ambiente=nuevo_nombre;
                        
                    }
                buscar_accesorio=buscar_accesorio->siguiente;
            }
    }
                              
}

//MANEJO DE ARCHIVOS
string Tipo_Archivo(string direccion) {
    string tipo;
    ifstream archivo(direccion);
    string linea;
    int cont_lineas=0;
    int num_campos=0;

    while(getline(archivo,linea)) 
        {
            cont_lineas+=1;
            if (Validar_enteros(linea)==false) 
                {
                    if (linea!="--") 
                        {
                            num_campos+=1;
                        }
                    else 
                        {   
                            if (cont_lineas>2) 
                                {
                                    break;
                                }
                        }
                }
        }

    if (num_campos==6) {
        tipo="accesorios";
    }
    else if (num_campos==1) {
        tipo="ambiente";
    }
    else if (num_campos==4) {
        tipo="especies";
    }
    cout<<tipo<<endl;
    return tipo;
}


void Cargar_Raza (raza r, Nodo_raza *&puntero){
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


void Cargar_Accesorio (accesorio a, Nodo_accesorio *&puntero){
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

void Cargar_Ambiente (string ambiente, Nodo_ambiente*&puntero){
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
void Cargar_ArchivoRaz(string direccion, Nodo_raza *&puntero, Nodo_ambiente *&puntero2) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ifstream archivo(direccion);
    string linea;
    string datos_raza=""; //Se ingresará en el mismo string todos los datos de la raza
    

    getline(archivo,linea);
    int num_razas=Stoi(linea);
    string razas[num_razas];


    int cont_razas=0; //Cuenta de cuántas razas se han leído los datos
     //Cuenta la cantidad de datos de la raza que han sido agregados. Cuando llega a 4 se reestablece.

    while (getline(archivo,linea)) 
        {   
            if (Validar_enteros(linea)==false) 
                {       
                    
                    if ((linea != "--"))
                        {
                            datos_raza=(datos_raza+linea+".");
                        }
                    else 
                        {   
                            if (datos_raza!="") {
                                razas[cont_razas]=datos_raza;
                                datos_raza="";
                                cont_razas+=1;
                            }
                        }
                }
        }
    razas[(num_razas-1)]=datos_raza;
    
    

    //distribuir cada dato
    string datos[4]; //Se crea una lista con 4 posiciones, correspondientes a los 4 campos que tiene cada raza
    string dato=""; 
    int posicion=0; //Las posiciones de la lista que tendrá todos los datos de una sola raza
    bool error=false;

    for (int i=0;i<num_razas;i++) 
        {
            string raza1=razas[i]; //Se almacenará en la variable "raza" el conjunto de datos de la raza en dicha posicion. 
            for(int j=0;j<(raza1.size());j++) {
                if (raza1[j]!='.') { //Mientras el algoritmo no encuentre el punto, querrá decir que aún está almacenando el mismo dato
                    if (raza1[j]==':') { //Cuando el algoritmo se tope con el caracter ':', querrá decir que lo que le sigue es el valor de la energía o la salud de la raza.
                        dato=""; //Por ello, se limpia la variable que almacena el dato, para que, a partir de ahora, solo pueda almacenar SOLO el número y no "Salud:valor" o "Energia:valor" 
                    }
                    else { //Si el algoritmo no se topa con el caracter ':', es porque estamos ante el nombre o el ambiente de la raza, datos que sí deben almacenarse completos
                        dato+=raza1[j];
                    }
                }
                else { //Cuando encuentre el punto:
                    datos[posicion]=dato; //Se almacena en la posicion correspondiente el dato que ha estado recabando hasta ahora
                    posicion+=1;
                    dato=""; //se deja vacía la variable para que pueda almacenar un nuevo dato
                }
            };


            raza raza_nueva; //Una vez llena la lista con todos los datos de la raza, se procede con la creacion de la raza que será cargada
            //Se rellena cada campo ya que conocemos el orden en el que fue ordenada la lista de datos (nombre-energia-salud-ambiente)
            raza_nueva.nombre=datos[0]; 
            int energia;
            energia=Stoi(datos[1]);
            raza_nueva.energia=energia;
            int salud;
            salud=Stoi(datos[2]);
            raza_nueva.salud=salud; 
            raza_nueva.ambiente=datos[3]; 

            if ((Existe_Raza(raza_nueva.nombre,puntero,'N')==true)||(Existe_Ambiente(raza_nueva.ambiente,puntero2)==false)) 
                {
                    error=true;
                }
                
            if ((raza_nueva.nombre!="") &&(Existe_Raza(raza_nueva.nombre,puntero,'N')==false)&&(Existe_Ambiente(raza_nueva.ambiente,puntero2)==true)){
                Cargar_Raza(raza_nueva,puntero);
            }



            posicion=0; //La posicion se vuelve a inicializar en cero para que  se pueda llenar nuevamente la lista con la siguiente raza
        }
    
    if (error==true) 
    {
        cout << endl;
        cout << endl;
        color(hConsole, 4);
        cout<<"! Es posible que no se hayan anadido algunas razas"<<endl;
        color(hConsole,8);
        cout<<"Puede que se llamaran igual a otras ya existentes o que su ambiente no exista."<<endl;
        color(hConsole, 7);
        cout<<endl;
    }
}


void Cargar_ArchivoAcc(string direccion, Nodo_accesorio *&puntero, Nodo_ambiente*&puntero2) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ifstream archivo(direccion);
    string linea;
    string datos_acc=""; //Se ingresará en el mismo string todos los datos del accesorio
    

    getline(archivo,linea);
    int num_acc=Stoi(linea);
    string accesorios[num_acc];


    int cont_acc=0; //Cuenta de cuántos accesorios se han leído los datos


    while (getline(archivo,linea)) 
        {   
            if (Validar_enteros(linea)==false) 
                {       
                    
                    if ((linea != "--"))
                        {
                            datos_acc=(datos_acc+linea+".");
                        }
                    else 
                        {   
                            if (datos_acc!="") {
                                accesorios[cont_acc]=datos_acc;
                                datos_acc="";
                                cont_acc+=1;
                            }
                        };
                }
        }
    accesorios[(num_acc-1)]=datos_acc;
    

    //distribuir cada dato
    string datos[6]; //Se crea una lista con 4 posiciones, correspondientes a los 4 campos que tiene cada raza
    string dato=""; 
    int posicion=0; //Las posiciones de la lista que tendrá todos los datos de una sola raza
    bool error1=false;
    bool error2=false;
    for (int i=0;i<num_acc;i++) 
        {
            string accesorio1=accesorios[i]; //Se almacenará en la variable "raza" el conjunto de datos de la raza en dicha posicion. 
            for(int j=0;j<(accesorio1.size());j++) {
                if (accesorio1[j]!='.') { //Mientras el algoritmo no encuentre el punto, querrá decir que aún está almacenando el mismo dato
                    if (accesorio1[j]==':') { //Cuando el algoritmo se tope con el caracter ':', querrá decir que lo que le sigue es el valor de la energía o la salud de la raza.
                        dato=""; //Por ello, se limpia la variable que almacena el dato, para que, a partir de ahora, solo pueda almacenar lo contiguo a los dos puntos 
                    }
                    else { //Si el algoritmo no se topa con el caracter ':', es porque estamos ante el nombre o el ambiente de la raza, datos que sí deben almacenarse completos
                        dato+=accesorio1[j];
                    }
                }
                else { //Cuando encuentre el punto:
                    datos[posicion]=dato; //Se almacena en la posicion correspondiente el dato que ha estado recabando hasta ahora
                    posicion+=1;
                    dato=""; //se deja vacía la variable para que pueda almacenar un nuevo dato
                }
            };


            accesorio accesorio_nuevo; //Una vez llena la lista con todos los datos de la raza, se procede con la creacion de la raza que será cargada
            //Se rellena cada campo ya que conocemos el orden en el que fue ordenada la lista de datos (nombre-energia-salud-ambiente)
            accesorio_nuevo.nombre=datos[0];
            string tipo=Minusculas(datos[1]);
            accesorio_nuevo.tipo=tipo;
            int valor=Stoi(datos[2]);
            accesorio_nuevo.valor=valor;
            accesorio_nuevo.recuperacion=datos[3];
            if (tipo=="acondicionamiento") {
                accesorio_nuevo.ambiente=datos[3];
            }
            int energia;
            energia=Stoi(datos[4]);
            accesorio_nuevo.energia_consumida=energia;
            int contenedor=Stoi(datos[5]);
            accesorio_nuevo.contenedor=contenedor;
            

            if (tipo!="acondicionamiento") 
                {
                    if (Existe_Accesorio(accesorio_nuevo.nombre,puntero,'N')==true){
                        error1=true;
                    }
                    
                    if ((accesorio_nuevo.nombre!="") &&(Existe_Accesorio(accesorio_nuevo.nombre,puntero,'N')==false)){
                        Cargar_Accesorio(accesorio_nuevo,puntero);
                    }
                }
            else 
                {
                    if (Existe_Ambiente(accesorio_nuevo.recuperacion,puntero2)==false){
                        error2=true;
                    }
                    if ((accesorio_nuevo.nombre!="") &&(Existe_Accesorio(accesorio_nuevo.nombre,puntero,'N')==false)&&(Existe_Ambiente(accesorio_nuevo.recuperacion,puntero2)==true))
                        {
                            Cargar_Accesorio(accesorio_nuevo,puntero);
                        }

                }

            posicion=0; //La posicion se vuelve a inicializar en cero para que  se pueda llenar nuevamente la lista con la siguiente raza
        }
    if (error1==true) {
        color(hConsole, 4);
        cout<<"! Es posible que no se hayan anadido algunos accesorios."<<endl;
        color(hConsole,8);
        cout<<"Puede que se llamaran igual a otros ya existentes."<<endl;
        color(hConsole, 7);
        cout<<endl;
    }
    
}

void Cargar_ArchivoAmb(string direccion, Nodo_ambiente *&puntero) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool error=false;
    ifstream archivo(direccion);
    string linea;

    while (getline(archivo,linea)) 
        {  
             if (Existe_Ambiente(linea,puntero)==true) 
                {
                    error=true;
                }
                
            if (Validar_enteros(linea)==false) 
                {       
                    
                    if ((linea != "--")&&(Existe_Ambiente(linea,puntero)==false))
                        {
                            Cargar_Ambiente(linea,puntero);
                        }
                }
        }
    
    if (error==true) {
        cout << endl;
        cout << endl;
        color(hConsole, 4);
        cout<<"! Es posible que no se hayan anadido algunos ambientes."<<endl;
        color(hConsole,8);
        cout<<"Puede que se llamaran igual a otros ya existentes."<<endl;
        color(hConsole, 7);
    }
}

//SUBMENUS
//SUBMENU ACCESORIOS
bool Opcion1Acc(Nodo_accesorio*&lista_accesorios) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool hecho;
    if (lista_accesorios==NULL) 
        {
            color(hConsole, 4);
            cout<<"! No hay accesorios para detallar. Agregue uno primero"<<endl;                        
            hecho=true;
            color(hConsole, 7);

        }
        else 
            {
                hecho=Detalles_Accesorio(lista_accesorios);
            }
    return hecho;
}

bool Opcion2Acc(Nodo_accesorio*&lista_accesorios, Nodo_ambiente*&lista_ambientes) {
    //Agregar Accesorios
    bool agregado=false;
    while (agregado==(false)) 
        {   
            cout<<"Ingrese el nombre de su nuevo accesorio."<<endl;
            cout<<endl;
            string nombre_accesorio;
            getline(cin,nombre_accesorio);
            agregado=Agregar_Accesorios(nombre_accesorio,lista_accesorios,lista_ambientes);
        }
    return agregado;
}

bool Opcion3Acc(Nodo_accesorio*&lista_accesorios) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool eliminado;
    if (lista_accesorios==NULL) 
        {
            color(hConsole, 4);
            cout<<"! No hay accesorios para eliminar. Agregue uno primero"<<endl;                        
            eliminado=true;
            color(hConsole, 7);
        }
    else 
        {
            eliminado=false;
            while (eliminado==false) {
                eliminado=true;
                cout<<endl;
                cout<<"Ingrese el nombre del accesorio que desea eliminar."<<endl;
                cout<<endl;
                string nombre;
                getline(cin,nombre);

                eliminado=Eliminar_Accesorios(nombre,lista_accesorios,'N'); //eliminará el accesorio segun su nombre
            }
        }
    return eliminado;
}

bool Opcion4Acc(Nodo_ambiente*&lista_ambientes,Nodo_accesorio*&lista_accesorios) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool continuar;
    if (lista_accesorios==NULL) 
        {
            color(hConsole, 4);
            cout<<"! No hay accesorios para modificar. Agregue uno primero";
            cout<<endl;
            continuar=true;
            color(hConsole, 7);

        }
    else 
        {
            bool modificado=false;
            while (modificado==false) 
                {
                    cout<<"Ingrese el nombre del accesorio que desee modificar."<<endl;
                    string accesorio;
                    cout<<endl;
                    getline(cin,accesorio);

                    if (Existe_Accesorio(accesorio,lista_accesorios,'N')==true)   
                        {
                            Modificar_Accesorios(accesorio,lista_accesorios,lista_ambientes);
                            modificado=true;
                            continuar=true;
                        }
                    else 
                        {
                            color(hConsole, 4);
                            cout<<"! El accesorio ";
                            color(hConsole, 7);
                            cout<<accesorio;
                            color(hConsole, 4);
                            cout<<" no existe. Intente de nuevo."<<endl;
                            cout<<endl;
                            modificado=false;
                            color(hConsole, 7);
                        }
                }
        }
    return continuar;
}


bool Opcion5Acc(Nodo_accesorio*&puntero, Nodo_ambiente*&puntero2){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool cargado;
    bool repetir_validacion=true;
    while (repetir_validacion==true) {
        repetir_validacion=false;
        cout<<"Ingrese la ruta de acceso del archivo que desea cargar."<<endl;
        color(hConsole, 8);
        cout<<"Ejemplo: C://Usuarios//Descargas//accesorios.inv"<<endl; //color clarito
        color(hConsole, 7);
        string direccion;
        getline(cin,direccion);
        cout<<endl;
        cout<<"Archivo: ";
    
        ifstream archivo;

        archivo.open(direccion,ios::in);

        if (archivo.fail()) {
            color(hConsole, 4);
            cout<<"! No se encontro ningun archivo bajo esa ruta. Revise e intente de nuevo."<<endl;
            cout<<endl;
            repetir_validacion=true;
            color(hConsole, 7);
        }
        else {
            string tipo=Tipo_Archivo(direccion);
            
            if (tipo!="accesorios") 
                {
                    color(hConsole, 4);
                    cout<<"! El archivo que ingreso no contiene accesorios. "<<endl;
                    cout<<endl;
                    repetir_validacion=true;
                    color(hConsole, 7);
                }
            else 
                {
                    Cargar_ArchivoAcc(direccion,puntero,puntero2);
                    cargado=true;
                }
        }
    }
    cout << endl;
    return cargado;
}



//SUBMENU RAZAS
//OPCION 1 (VER DETALLES DE UNA RAZA)
bool Opcion1Raz(Nodo_raza*&lista_razas) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool hecho;
    if (lista_razas==NULL) 
        {
            color(hConsole, 4);
            cout<<"! No hay razas para detallar. Agregue una primero"<<endl;                        
            hecho=true;
            color(hConsole, 7);
        }
        else 
            {
                hecho=Detalles_Raza(lista_razas);
            }
    return hecho; //returnea un valor que le indicará si toma una accion o repite el submenu
}

//OPCION 2 (AGREGAR UNA RAZA)
bool Opcion2Raz(Nodo_raza*&lista_razas,Nodo_ambiente*&lista_ambientes) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //Agregar Razas
    bool agregado=false;
    while (agregado==(false)) 
        {   
            cout<<"Ingrese el nombre de su nueva raza."<<endl;
            cout<<endl;
            string nombre_raza;
            getline(cin,nombre_raza);
            agregado=Agregar_Razas(nombre_raza,lista_razas,lista_ambientes); //dentro de la funcion agregar razas se evaluara si el nombre introducido es correcto. Devolvera un valor que le permitira saber al submenu si debe repetirse o tomar accion.
        }
    return agregado;
}

//OPCION3 (ELIMINAR UNA RAZA)
bool Opcion3Raz(Nodo_raza*&lista_razas) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool eliminado;
    if (lista_razas==NULL) 
        {
            color(hConsole, 4);
            cout<<"! No hay razas para eliminar. Agregue una primero"<<endl;                        
            eliminado=true;
            color(hConsole, 7);
        }
    else 
        {
            eliminado=false;
            while (eliminado==false) {
                eliminado=true;
                cout<<endl;
                cout<<"Ingrese el nombre de la raza que desea eliminar."<<endl;
                cout<<endl;
                string nombre_raza;
                getline(cin,nombre_raza);

                eliminado=Eliminar_Razas(nombre_raza,lista_razas,'N'); //eliminará la raza segun su nombre
                }
        }
    return eliminado;
}

//OPCION 4 (MODIFICAR UNA RAZA)
bool Opcion4Raz(Nodo_ambiente*&lista_ambientes,Nodo_raza*&lista_razas) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool continuar;
    if (lista_razas==NULL) 
        {
            color(hConsole, 4);
            cout<<"! No hay razas para modificar. Agregue una primero";
            cout<<endl;
            continuar=true;
            color(hConsole, 7);
        }
    else 
        {
            bool modificado=false;
            while (modificado==false) 
                {
                    cout<<"Ingrese el nombre de la raza que desee modificar."<<endl;
                    cout<<endl;
                    string raza;
                    getline(cin,raza);

                    if (Existe_Raza(raza,lista_razas,'N')==true)   
                        {
                            Modificar_Razas(raza,lista_razas,lista_ambientes);
                            modificado=true;
                            continuar=true;
                        }
                    else 
                        {
                            color(hConsole, 4);
                            cout<<"! La raza ";
                            color(hConsole, 7);
                            cout<<raza;
                            color(hConsole, 4);
                            cout<<" no existe. Intente de nuevo."<<endl;
                            cout<<endl;
                            modificado=false;
                            color(hConsole, 7);
                        }
                }
        }
    return continuar;
}


bool Opcion5Raz(Nodo_raza*&puntero, Nodo_ambiente*&puntero2){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool cargado;
    bool repetir_validacion=true;
    while (repetir_validacion==true) {
        repetir_validacion=false;
        cout<<"Ingrese la ruta de acceso del archivo que desea cargar."<<endl;
        color(hConsole, 8);
        cout<<"Ejemplo: C://Usuarios//Descargas//especies.inv"<<endl; //color clarito gris
        color(hConsole, 7);
        string direccion;
        getline(cin,direccion);
        cout<<endl;
        cout<<"Archivo: ";

        ifstream archivo;

        archivo.open(direccion,ios::in);

        if (archivo.fail()) {
            color(hConsole, 4);
            cout<<"! No se encontro ningun archivo bajo esa ruta. Revise e intente de nuevo."<<endl;
            cout<<endl;
            repetir_validacion=true;
            color(hConsole, 7);
        }
        else {
            string tipo=Tipo_Archivo(direccion);
            
            if (tipo!="especies") 
                {
                    color(hConsole, 4);
                    cout<<"! El archivo que ingreso no contiene especies. "<<endl;
                    cout<<endl;
                    repetir_validacion=true;
                    color(hConsole, 7);
                }
            else 
                {
                    Cargar_ArchivoRaz(direccion,puntero,puntero2);
                    cargado=true;
                }
        }
    }
    cout << endl;

    return cargado;
}


//SUBMENU AMBIENTES
//OPCION 1 (AGREGAR UN AMBIENTE)
bool Opcion1Amb(Nodo_ambiente*&lista_ambientes) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //Agregar Ambientes
    bool agregado=false;
    while (agregado==(false)) 
        {   
            cout<<endl;
            cout<<"Ingrese el nombre del ambiente que desea agregar."<<endl;
            cout<<endl;
            string nombre_ambiente;
            getline(cin,nombre_ambiente);
            if (nombre_ambiente!="none"){
                agregado=Agregar_Ambientes(nombre_ambiente,lista_ambientes);
            }
            else {
                color(hConsole, 4);
                agregado=false;
                cout<<endl;
                cout << "No se puede crear un ambiente llamado none" <<endl;
                color(hConsole, 7);
            }
        }
    return agregado;
}

//OPCION 2 (ELIMINAR UN AMBIENTE)
bool Opcion2Amb(Nodo_ambiente*&lista_ambientes, Nodo_raza*&lista_razas, Nodo_accesorio*&lista_accesorios) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool repetir;
    if (lista_ambientes==NULL) 
        {
            color(hConsole, 4);
            cout<<"! No hay ambientes para eliminar. Agregue uno primero"<<endl;                        
            repetir=true;
            color(hConsole, 7);
        }
        else 
            {
                bool eliminado=false;
                while (eliminado==false) {
                    eliminado=true;
                    cout<<endl;
                    cout<<"Ingrese el nombre del ambiente que desea eliminar."<<endl;
                    cout<<endl;
                    string nombre_ambiente;
                    getline(cin,nombre_ambiente);

                                                                
                    bool confirmado;
                    if ((Existe_Raza(nombre_ambiente,lista_razas, 'A')==true) || (Existe_Accesorio(nombre_ambiente, lista_accesorios, 'A')==true)) {
                        confirmado=Confirmacion_EliminarAmbiente(nombre_ambiente,lista_razas,lista_accesorios);

                        if (confirmado==true) {
                            eliminado= Eliminar_Ambiente(nombre_ambiente,lista_ambientes,lista_razas,lista_accesorios);
                            repetir=true;
                            }
                        else{
                                eliminado=true;
                            }    
                    }
                                                                
                    else {
                            eliminado=Eliminar_Ambiente(nombre_ambiente,lista_ambientes,lista_razas,lista_accesorios);
                            repetir=true;
                        }
                }
            }
    return repetir;
}

//OPCION 3 (MODIFICAR UN AMBIENTE)
bool Opcion3Amb(Nodo_ambiente*&lista_ambientes,Nodo_raza*&lista_razas, Nodo_accesorio*&lista_accesorios) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool continuar;
    if (lista_ambientes==NULL) 
        {
            color(hConsole, 4);
            cout<<"! No hay ambientes para modificar. Agregue uno primero";
            cout<<endl;
            continuar=true;
            color(hConsole, 7);
        }
    else 
        {
            bool modificado=false;
            while (modificado==false) 
                {
                    cout<<"Ingrese el nombre del ambiente que desee modificar."<<endl;
                    cout<<endl;
                    string ambiente;
                    getline(cin,ambiente);

                    if (Existe_Ambiente(ambiente,lista_ambientes)==true)   
                        {
                            Modificar_Ambiente(ambiente,lista_razas,lista_ambientes,lista_accesorios);
                            modificado=true;
                            continuar=true;
                        }
                    else 
                        {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            color(hConsole, 4);
                            cout<<"! El ambiente que desea modificar no existe. Intente de nuevo."<<endl;
                            cout<<endl;
                            modificado=false;
                            color(hConsole, 7);
                        }
                }
        }
    return continuar;
}

bool Opcion4Amb(Nodo_ambiente*&puntero){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool cargado;
    bool repetir_validacion=true;
    while (repetir_validacion==true) {
        repetir_validacion=false;
        cout<<"Ingrese la ruta de acceso del archivo que desea cargar."<<endl;
        color(hConsole, 8);
        cout<<"Ejemplo: C://Usuarios//Descargas//ambiente.inv"<<endl; //color clarito
        color(hConsole, 7);
        string direccion;
        getline(cin,direccion);
        cout<<endl;
        cout<<"Archivo: ";

        ifstream archivo;

        archivo.open(direccion,ios::in);

        if (archivo.fail()) {
            color(hConsole, 4);
            cout<<"! No se encontro ningun archivo bajo esa ruta. Revise e intente de nuevo."<<endl;
            cout<<endl;
            repetir_validacion=true;
            cargado=false;
            color(hConsole, 7);
        }
        
        else {
                string tipo=Tipo_Archivo(direccion);
            
                if (tipo!="ambiente") 
                    {
                        color(hConsole, 4);
                        cout<<"! El archivo que ingreso no contiene ambientes. "<<endl;
                        cout<<endl;
                        repetir_validacion=true;
                        color(hConsole, 7);
                    }
                else 
                    {
                        Cargar_ArchivoAmb(direccion,puntero);
                        cargado=true;
                    }    
            }
            
        
    }
    cout << endl;
    return cargado;
}


raza Escoger_raza(string nombre, Nodo_raza *&puntero)
{   
    raza raza_seleccionada;
    Nodo_raza *escoger=puntero;
    raza raza;
    while(escoger->Raza.nombre!=nombre){
        escoger=escoger->siguiente;
    }

    raza_seleccionada = escoger->Raza;
    return raza_seleccionada;
}

accesorio Escoger_accesorio(string nombre, Nodo_accesorio *&puntero)
{
    Nodo_accesorio *escoger=puntero;
    accesorio accesorio_seleccionado;
    while(escoger->accesorio.nombre!=nombre){
        escoger=escoger->siguiente;
    }
    accesorio_seleccionado=escoger->accesorio;
    return accesorio_seleccionado;
}



int Definir_Usos(accesorio x){
    int usos = 0;
    if (x.tipo=="ataque"){
        usos=-1;
    }
    else if (x.tipo=="defensa"){
        usos=1;
    }
    else if (x.tipo=="supervivencia"){
        usos=1;
    }
    else if (x.tipo=="acondicionamiento"){
        usos=1;
    }

    return usos;
}


void Mostrar_Equipo(estudiante lista[3]) {
    for (int i=0;i<3;i++) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        color(hConsole, 13);
        cout<<"[ ";
        color(hConsole, 7);
        cout<<lista[i].nombre;
        color(hConsole, 13);
        cout<<" ]";
        color(hConsole, 7);
    }
    cout<<endl;
}
bool Existe_estudiante (string nombre, estudiante x[3])
{
    bool val = false;
    for (int i = 0; i<3; i++)
    {
        if (x[i].nombre==nombre)
        {
            val=true;
        }
    }
    
    return val;
}

void Crear_Equipo (Nodo_ambiente *&puntero1, Nodo_raza *&puntero2, Nodo_accesorio *&puntero3, estudiante x[3], estudiante y[3])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "°Creación de personajes°" << endl;
    cout << endl;
    color(hConsole, 3);
    cout << "-) Jugador 1 - Humanos (-"<<endl;
    color(hConsole, 7);
    for (int i = 0; i<3; i++)
        {
            cout << endl;
            cout << "Cree su soldado " << i+1 << endl;

            string nombre;
            bool val = true;
            while (val == true)
            {   
                color(hConsole, 3);
                cout << "Nombre : ";
                color(hConsole, 7);

                getline(cin,nombre);
                if ((Existe_estudiante(nombre, x)==false)&&(Existe_estudiante(nombre, y)==false))
                {
                    val=false;
                    x[i].nombre=nombre;
                    cout << endl; 
                } 
                else
                {
                    color(hConsole, 4);
                    cout <<"! Ya un soldado tiene ese nombre. Intente de nuevo"<<endl;
                    cout <<endl;
                    color(hConsole, 7);
                }   
            }

            x[i].Mochila.dueno=nombre;
            cout << endl;

            string raza1;
            bool val1 = true;
            while (val1==true)
                {   

                    cout << endl;
                    color(hConsole, 13);
                    cout << "- RAZAS DISPONIBLES -" << endl; //morado
                    color(hConsole, 7);
                    cout<<endl;
                    Mostrar_Razas('T',"none",puntero2);
                    cout << endl;
                    val1=false;
                    cout<<endl;
                    cout<<"1) Ver detalles de raza"<<endl;
                    cout<<"2) Ingrese la raza de su soldado"<<endl;

                    string opcion1;
                    getline(cin,opcion1);
                    
                    if (opcion1=="1") {
                        val1=Opcion1Raz(puntero2);
                        cout << endl;
                    }
                    else if (opcion1=="2") {
                        color(hConsole, 3);
                        cout<<"Raza: ";
                        color(hConsole, 7);
                        getline(cin,raza1);
                        cout<<endl;

                        if (Existe_Raza(raza1,puntero2,'N')==true)
                            {   
                                raza Raza;
                                Raza=Escoger_raza(raza1,puntero2);
                                x[i].Raza=Raza;
                                x[i].energia=Raza.energia;
                                x[i].salud=100;
                                x[i].ambiente=Raza.ambiente;
                            }
                        else
                            {
                                color(hConsole, 4);
                                val1=true;
                                cout<<"! La raza ";
                                color(hConsole, 7);
                                cout<<raza1;
                                color(hConsole, 4);
                                cout<<" no existe. Intente de nuevo."<<endl;
                                cout<<endl;
                                color(hConsole, 7);
                            }
                    }
                    else {
                        cout<<"! Por favor, ingrese una opcion del menu."<<endl;;
                        val1=true;
                        cout<<endl;
                    }
                }

            
                    
            cout << endl;
            string accesorio;
            string usados[5];


        
            for (int j=0;j<5;j++)
                {
                    bool repetir_validacion=true;
                    while (repetir_validacion==true) 
                        {   
                            color(hConsole, 3);
                            cout << " MOCHILA" << endl;
                            color(hConsole, 7);
                            repetir_validacion=false;
                            color(hConsole, 13);
                            cout << "- ACCESORIOS DISPONIBLES -" << endl; //morado
                            color(hConsole, 7);
                            cout << endl;
                            Mostrar_TodosAcc(puntero3);
                            cout << endl;
                            cout<<"1) Ver detalles de accesorio"<<endl;
                            cout<<"2) Ingresar accesorio"<<endl;
                            color(hConsole, 7);
                            string opcion2;
                            getline(cin,opcion2);

                            if (opcion2=="1") 
                                {
                                    repetir_validacion=Opcion1Acc(puntero3);
                                    cout<<endl;
                                    cout<<endl;
                                }
                            else if (opcion2=="2") 
                                {   
                                    color(hConsole, 3);
                                    cout<<"Accesorio "<<j+1<<": ";
                                    color(hConsole, 7);
                                    getline(cin,accesorio);
                                    cout<<endl;
                                    cout<<endl;
                                    if (Existe_Accesorio(accesorio, puntero3,'N')==true)
                                    {
                                        for (int k = 0;k<5;k++)
                                        {
                                            if (accesorio==usados[k]){
                                                color(hConsole, 4);
                                                repetir_validacion=true;
                                                cout <<" ! Ya ingreso ese accesorio a su mochila. Seleccione otro. " <<endl;
                                                cout<<endl;
                                                color(hConsole, 7);
                                            }
                                        }

                                        if (repetir_validacion==false)
                                            {
                                                x[i].Mochila.vector_mochila[j]=Escoger_accesorio(accesorio,puntero3);
                                                x[i].Mochila.vector_usos[j]=Definir_Usos(Escoger_accesorio(accesorio,puntero3));
                                                usados[j]=accesorio;
                                            }   

                                    }
                                    else{
                                        color(hConsole, 4);
                                        cout<<"! Ese accesorio no existe. Intente de nuevo"<< endl;
                                        repetir_validacion=true;
                                        color(hConsole, 7);
                                        cout << endl;
                                    }

                                }
                            else {
                                cout<<"! Por favor, ingrese una opcion del menu."<<endl;
                                cout<<endl;
                                repetir_validacion=true;
                            }
                        }        
                }
            for (int k = 0;k<5;k++)
                {
                    usados[k]="";
                }
        }  
    cout << endl;
    cout << endl;
    color(hConsole, 10);
    cout << "-) Jugador 2 - Andromedanos (-"<<endl;
    color(hConsole, 7);
    for (int i = 0; i<3; i++)
        {
            cout << endl;
            cout << "Cree su soldado " << i+1 << endl;

            string nombre;
            bool val = true;
            while (val == true)
            {   
                color(hConsole, 10);
                cout << "Nombre : ";
                color(hConsole, 7);

                getline(cin,nombre);
                if ((Existe_estudiante(nombre, x)==false)&&(Existe_estudiante(nombre, y)==false))
                {
                    val=false;
                    y[i].nombre=nombre;
                    cout << endl; 
                } 
                else
                {
                    color(hConsole, 4);
                    cout <<"! Ya un soldado tiene ese nombre. Intente de nuevo"<<endl;
                    cout <<endl;
                    color(hConsole, 7);
                }   
            }

            y[i].Mochila.dueno=nombre;
            cout << endl;

            string raza1;
            bool val1 = true;
            while (val1==true)
                {   

                    cout << endl;
                    color(hConsole, 10);
                    cout << "- RAZAS DISPONIBLES -" << endl; //morado
                    color(hConsole, 7);
                    cout<<endl;
                    Mostrar_Razas('T',"none",puntero2);
                    cout << endl;
                    val1=false;
                    cout<<endl;
                    cout<<"1) Ver detalles de raza"<<endl;
                    cout<<"2) Ingrese la raza de su soldado"<<endl;

                    string opcion1;
                    getline(cin,opcion1);
                    
                    if (opcion1=="1") {
                        val1=Opcion1Raz(puntero2);
                        cout << endl;
                    }
                    else if (opcion1=="2") {
                        color(hConsole, 10);
                        cout<<"Raza: ";
                        color(hConsole, 7);
                        getline(cin,raza1);
                        cout<<endl;

                        if (Existe_Raza(raza1,puntero2,'N')==true)
                            {   
                                raza Raza;
                                Raza=Escoger_raza(raza1,puntero2);
                                y[i].Raza=Raza;
                                y[i].energia=Raza.energia;
                                y[i].salud=100;
                                y[i].ambiente=Raza.ambiente;
                            }
                        else
                            {
                                color(hConsole, 4);
                                val1=true;
                                cout<<"! La raza ";
                                color(hConsole, 7);
                                cout<<raza1;
                                color(hConsole, 4);
                                cout<<" no existe. Intente de nuevo."<<endl;
                                cout<<endl;
                                color(hConsole, 7);
                            }
                    }
                    else {
                        cout<<"! Por favor, ingrese una opcion del menu."<<endl;;
                        val1=true;
                        cout<<endl;
                    }
                }

            
                    
            cout << endl;
            string accesorio;
            string usados[5];


        
            for (int j=0;j<5;j++)
                {
                    bool repetir_validacion=true;
                    while (repetir_validacion==true) 
                        {   
                            color(hConsole, 3);
                            cout << " MOCHILA" << endl;
                            color(hConsole, 7);
                            repetir_validacion=false;
                            color(hConsole, 13);
                            cout << "- ACCESORIOS DISPONIBLES -" << endl; //morado
                            color(hConsole, 7);
                            cout << endl;
                            Mostrar_TodosAcc(puntero3);
                            cout << endl;
                            cout<<"1) Ver detalles de accesorio"<<endl;
                            cout<<"2) Ingresar accesorio"<<endl;
                            color(hConsole, 7);
                            string opcion2;
                            getline(cin,opcion2);

                            if (opcion2=="1") 
                                {
                                    repetir_validacion=Opcion1Acc(puntero3);
                                    cout<<endl;
                                    cout<<endl;
                                }
                            else if (opcion2=="2") 
                                {   
                                    color(hConsole, 10);
                                    cout<<"Accesorio "<<j+1<<": ";
                                    color(hConsole, 7);
                                    getline(cin,accesorio);
                                    cout<<endl;
                                    cout<<endl;
                                    if (Existe_Accesorio(accesorio, puntero3,'N')==true)
                                    {
                                        for (int k = 0;k<5;k++)
                                        {
                                            if (accesorio==usados[k]){
                                                color(hConsole, 4);
                                                repetir_validacion=true;
                                                cout <<" ! Ya ingreso ese accesorio a su mochila. Seleccione otro. " <<endl;
                                                cout<<endl;
                                                color(hConsole, 7);
                                            }
                                        }

                                        if (repetir_validacion==false)
                                            {
                                                y[i].Mochila.vector_mochila[j]=Escoger_accesorio(accesorio,puntero3);
                                                y[i].Mochila.vector_usos[j]=Definir_Usos(Escoger_accesorio(accesorio,puntero3));
                                                usados[j]=accesorio;
                                            }   

                                    }
                                    else{
                                        color(hConsole, 4);
                                        cout<<"! Ese accesorio no existe. Intente de nuevo"<< endl;
                                        repetir_validacion=true;
                                        color(hConsole, 7);
                                        cout << endl;
                                    }

                                }
                            else {
                                cout<<"! Por favor, ingrese una opcion del menu."<<endl;
                                cout<<endl;
                                repetir_validacion=true;
                            }
                        }        
                }
            for (int k = 0;k<5;k++)
                {
                    usados[k]="";
                }
        }  
}



bool Detallar_Soldado(estudiante x[3],string nombre)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    bool val = false;    
    estudiante soldado;
    for (int i = 0;i<3;i++)
    {
        if (x[i].nombre==nombre)
        {
            val=true;
            soldado=x[i];
            color(hConsole, 13);
            cout << "- NOMBRE: ";
            color(hConsole, 7);
            cout << soldado.nombre <<endl;
            color(hConsole, 13);
            cout << "- SALUD: ";
            color(hConsole, 7);
            cout << soldado.salud <<endl;
            color(hConsole, 13);
            cout << "- ENERGIA: ";
            color(hConsole, 7);
            cout << soldado.energia <<endl;
            color(hConsole, 13);
            cout << "- AMBIENTE: ";
            color(hConsole, 7);
            cout << soldado.ambiente <<endl;
            color(hConsole, 13);
            cout << "- ACCESORIOS MOCHILA: " << endl;
            cout << " #1. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[0].nombre << endl;
            color(hConsole, 13);
            cout << " #2. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[1].nombre << endl;
            color(hConsole, 13);
            cout << " #3. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[2].nombre << endl;
            color(hConsole, 13);
            cout << " #4. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[3].nombre << endl;
            color(hConsole, 13);
            cout << " #5. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[4].nombre << endl;
        }
    }
    return val;
}

void Menu_Equipos (char tipo, estudiante Equipo1[3],estudiante Equipo2[3])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (tipo=='1') {
        color(hConsole, 13);
        cout<<" - EQUIPOS - "<< endl;
        color(hConsole, 7);
        cout<<"1 - Visualizar Equipos"<< endl;
        cout<<"2 - Empezar partida "<< endl;
    }

    if (tipo=='2') {
        color(hConsole, 3);
        cout<<"- () EQUIPO 1 -"<< endl;
        color(hConsole, 7);
        Mostrar_Equipo(Equipo1);
        cout<<"1 - Ver detalles de un soldado"<< endl;
        cout<<"2 - Modificar soldados"<< endl;
        cout<<"3 - Volver "<< endl;
    }

    if (tipo=='3') {
        color(hConsole, 10);
        cout<<"- () EQUIPO 2 -"<< endl;
        color(hConsole, 7);
        Mostrar_Equipo(Equipo2);
        cout<<"1 - Ver detalles de un soldado"<< endl;
        cout<<"2 - Modificar soldados"<< endl;
        cout<<"3 - Volver "<< endl;
    }

    if (tipo=='4') {
        cout<<"(a) Ver Equipo 1 -  (b) Ver Equipo 2" << endl;
    }
    
}



void Modificar_soldado(string nombre, estudiante Equipo1[3], estudiante Equipo2[3], Nodo_ambiente *&puntero1, Nodo_raza *&puntero2, Nodo_accesorio *&puntero3)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int posicion; 
    for (int i = 0; i<3;i++)
    {
        if (Equipo1[i].nombre==nombre)
        {
            posicion=i;
        }
    }

    string nuevo_nombre;
    bool val = true;
    while (val == true)
    {
        cout << " Ingrese nuevo nombre: ";
        getline(cin, nuevo_nombre);
        if ((Existe_estudiante(nuevo_nombre, Equipo1)==false)&&(Existe_estudiante(nuevo_nombre, Equipo2)==false))
        {
            val=false;
            Equipo1[posicion].nombre=nuevo_nombre;
            cout << endl; 
        } 
        else
        {
            color(hConsole, 4);
            cout <<"! Ya un soldado tiene ese nombre. Intente de nuevo"<<endl;
            val=true;
            cout <<endl;
            color(hConsole, 7);
        }
    }
    Equipo1[posicion].Mochila.dueno=nombre; 
    cout<<endl;
    string nueva_raza;
    bool val1 = true;
    while (val1==true)
    {   

            cout << endl;
            color(hConsole, 10);
            cout << "- RAZAS DISPONIBLES -" << endl; //morado
            color(hConsole, 7);
            cout<<endl;
            Mostrar_Razas('T',"none",puntero2);
            cout << endl;
            val1=false;
            cout<<endl;
            cout<<"1) Ver detalles de raza"<<endl;
            cout<<"2) Ingrese la nueva raza de su soldado"<<endl;

            string opcion1;
            getline(cin,opcion1);
                    
            if (opcion1=="1") {
                val1=Opcion1Raz(puntero2);
                cout << endl;
            }
            else if (opcion1=="2") {
                cout<<"Raza: ";
                getline(cin,nueva_raza);
                cout<<endl;

                if (Existe_Raza(nueva_raza,puntero2,'N')==true)
                    {   
                        raza Raza;
                        Raza=Escoger_raza(nueva_raza,puntero2);
                        Equipo1[posicion].Raza=Raza;
                        Equipo1[posicion].energia=Raza.energia;
                        Equipo1[posicion].salud=100;
                        Equipo1[posicion].ambiente=Raza.ambiente;
                    }
                    else
                        {
                            color(hConsole, 4);
                            val1=true;
                            cout<<"! La raza ";
                            color(hConsole, 7);
                            cout<<nueva_raza;
                            color(hConsole, 4);
                            cout<<" no existe. Intente de nuevo."<<endl;
                            cout<<endl;
                            color(hConsole, 7);
                        }
                    }
                    else {
                        cout<<"! Por favor, ingrese una opcion del menu."<<endl;;
                        val1=true;
                        cout<<endl;
                    }
            }

            
                    
        cout << endl;
        string usados[5];

        string nuevo_accesorio;
        for (int j=0;j<5;j++)
        {
            bool repetir_validacion=true;
            while (repetir_validacion==true) 
            {   
                color(hConsole, 3);
                cout << " MOCHILA" << endl;
                color(hConsole, 7);
                repetir_validacion=false;
                color(hConsole, 13);
                cout << "- ACCESORIOS DISPONIBLES -" << endl; //morado
                color(hConsole, 7);
                cout << endl;
                Mostrar_TodosAcc(puntero3);
                cout << endl;
                cout<<"1) Ver detalles de accesorio"<<endl;
                cout<<"2) Ingresar accesorio"<<endl;
                color(hConsole, 7);
                string opcion2;
                getline(cin,opcion2);

                if (opcion2=="1") 
                    {
                        repetir_validacion=Opcion1Acc(puntero3);
                        cout<<endl;
                        cout<<endl;
                    }
                else if (opcion2=="2") 
                    {   
                                    
                        cout<<"Accesorio "<<j+1<<": ";
                        getline(cin,nuevo_accesorio);
                        cout<<endl;
                        cout<<endl;
                         if (Existe_Accesorio(nuevo_accesorio, puntero3,'N')==true)
                        {
                            for (int k = 0;k<5;k++)
                                {
                                    if (nuevo_accesorio==usados[k]){
                                        color(hConsole, 4);
                                        repetir_validacion=true;
                                        cout <<" ! Ya ingreso ese accesorio a su mochila. Seleccione otro. " <<endl;
                                        cout<<endl;
                                        color(hConsole, 7);
                                    }
                                }

                            if (repetir_validacion==false)
                                {
                                    Equipo1[posicion].Mochila.vector_mochila[j]=Escoger_accesorio(nuevo_accesorio,puntero3);
                                    Equipo1[posicion].Mochila.vector_usos[j]=Definir_Usos(Escoger_accesorio(nuevo_accesorio,puntero3));
                                    usados[j]=nuevo_accesorio;
                                }   

                        }
                        else
                            {
                                    color(hConsole, 4);
                                    cout<<"! Ese accesorio no existe. Intente de nuevo"<< endl;
                                    repetir_validacion=true;
                                    color(hConsole, 7);
                                    cout << endl;
                            }

                    }
                    else {
                        cout<<"Por favor, ingrese una opcion del menu."<<endl;
                        cout<<endl;
                        repetir_validacion=true;
                        }
            }        
    }
        for (int k = 0;k<5;k++)
            {
                usados[k]="";
            }   
    
}



bool Examinar_vidas(estudiante Equipo[3])
{
    bool vivitos=true;
    int cont_muertos = 0;
    for (int i = 0; i<3; i++)
    {
        if((Equipo[i].energia==0)||(Equipo[i].salud==0))
        {
            cont_muertos+=1;
        }
    }
    if (cont_muertos==3)
    {
        vivitos=false;
    }
    return vivitos;
}

bool Examinar_usos(estudiante x)
{
    bool oficio=true;
    int cont_acabados = 0;
    for (int i = 0; i<3; i++)
    {
        if((x.Mochila.vector_usos[i]==0))
        {
            cont_acabados+=1;
        }
    }
    if (cont_acabados==3)
    {
        oficio=false;
    }
    return oficio;
}
bool Revisar_vitalidad(estudiante x)
{
    bool coleando=true;
    if ((x.salud==0)||(x.energia==0))
    {
        coleando=false;
    }
    return coleando;
}

estudiante Escoger_estudiante (string nombre, estudiante Equipo[3])
{
    estudiante soldado;
    int posicion;
    for (int i = 0; i<3; i++)
    {
        if (Equipo[i].nombre==nombre)
        {
            posicion=i;
        }
    }
    soldado=Equipo[posicion];
    return soldado;
}

bool Escoger_accesorio_submochila (accesorio x, estudiante y, int numero)
{
    bool sin_usar = true;
    accesorio uso=y.Submochila[numero];
    if (y.Submochila_usos[numero]!=0)
    {
        x=uso;
        if (y.Submochila[numero].contenedor==00)
        {
            (y.Submochila_usos[numero])-=1;
        }
    }
    else
    {
        sin_usar = false;
    }
    return sin_usar;
} 

void Mostrar_Submochila(estudiante x){
    for (int i=0;i<3;i++) {
        if (x.Submochila[i].nombre!="") {
            cout<<"[ ";
            cout<<x.Submochila[i].nombre;
            cout<<" ]";
        }
    }
}
bool Escoger_accesorio_mochila (accesorio x, estudiante y, int numero)
{
    bool sin_usar = true;
    accesorio uso=y.Mochila.vector_mochila[numero];
    if (y.Mochila.vector_usos[numero]!=0)
    {
        x=uso;
    }
    else
    {
        sin_usar = false;
    }
    return sin_usar;
} 

bool Existe_enMochila(accesorio lista[5],string nombre) {
    bool existe=false;

    for (int i=0;i<5;i++) {
        if (lista[i].nombre==nombre) {
            existe=true;
        }
    }
    return existe;
}

int Posicion_enMochila(accesorio lista[5],string nombre) {
    int posicion;

    for (int i=0;i<5;i++) {
        if (lista[i].nombre==nombre) {
            posicion=i;
        }
    }
    return posicion;
}

bool Existe_enSubMochila(accesorio lista[3],string nombre) {
    bool existe=false;

    for (int i=0;i<3;i++) {
        if (lista[i].nombre==nombre) {
            existe=true;
        }
    }
    return existe;
}

void Detallar_Mochila(estudiante soldado,string nombre) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int num=Posicion_enMochila(soldado.Mochila.vector_mochila,nombre);
    color(hConsole, 13);
    cout<<"- NOMBRE: ";
    color(hConsole, 7);
    cout << soldado.Mochila.vector_mochila[num].nombre;
    cout<<endl;
    color(hConsole, 13);
    cout<<"- TIPO: ";
    color(hConsole, 7);
    cout<< soldado.Mochila.vector_mochila[num].tipo;
    cout<<endl;
    color(hConsole, 13);
    cout<<"- VALOR: ";
    color(hConsole, 7);
    cout<<soldado.Mochila.vector_mochila[num].valor;
    cout<<endl;
    if (soldado.Mochila.vector_mochila[num].tipo=="acondicionamiento") 
        {
            color(hConsole, 13);
            cout<<"- RECUPERACION: ";
            color(hConsole, 7);
            cout<< soldado.Mochila.vector_mochila[num].ambiente;
            cout<<endl;
        }
    else if (soldado.Mochila.vector_mochila[num].tipo=="supervivencia") 
        {
            color(hConsole, 13);
            cout<<"- RECUPERACION: ";
            color(hConsole, 7);
            cout<<soldado.Mochila.vector_mochila[num].recuperacion;
            cout<<endl;
        }
    else{
            cout<<"- RECUPERACION: Ninguna";
            cout<<endl;
        }
    color(hConsole, 13);
    cout<<"- ENERGIA: ";
    color(hConsole, 7);
    cout<<soldado.Mochila.vector_mochila[num].energia_consumida;
    cout<<endl;
    color(hConsole, 13);
    cout<<"- CONTENEDOR (proteccion inicial): ";
    color(hConsole, 7);
    cout<< soldado.Mochila.vector_mochila[num].contenedor;
    cout<<endl;
}

int Posicion_enSubmochila(accesorio lista[3],string nombre) {
    int posicion;

    for (int i=0;i<3;i++) {
        if (lista[i].nombre==nombre) {
            posicion=i;
        }
    }
    return posicion;
}

void Detallar_Submochila(estudiante soldado,string nombre) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int num=Posicion_enSubmochila(soldado.Submochila,nombre);
    color(hConsole, 13);
    cout<<"- NOMBRE: ";
    color(hConsole, 7);
    cout << soldado.Submochila[num].nombre;
    cout<<endl;
    color(hConsole, 13);
    cout<<"- TIPO: ";
    color(hConsole, 7);
    cout<< soldado.Submochila[num].tipo;
    cout<<endl;
    color(hConsole, 13);
    cout<<"- VALOR: ";
    color(hConsole, 7);
    cout<<soldado.Submochila[num].valor;
    cout<<endl;
    if (soldado.Submochila[num].tipo=="acondicionamiento") 
        {
            color(hConsole, 13);
            cout<<"- RECUPERACION: ";
            color(hConsole, 7);
            cout<< soldado.Submochila[num].ambiente;
            cout<<endl;
        }
    else if (soldado.Submochila[num].tipo=="supervivencia") 
        {
            color(hConsole, 13);
            cout<<"- RECUPERACION: ";
            color(hConsole, 7);
            cout<<soldado.Submochila[num].recuperacion;
            cout<<endl;
        }
    else{
            cout<<"- RECUPERACION: Ninguna";
            cout<<endl;
        }
    color(hConsole, 13);
    cout<<"- ENERGIA: ";
    color(hConsole, 7);
    cout<<soldado.Submochila[num].energia_consumida;
    cout<<endl;
    color(hConsole, 13);
    cout<<"- CONTENEDOR (proteccion inicial): ";
    color(hConsole, 7);
    cout<< soldado.Submochila[num].contenedor;
    cout<<endl;
}

void Llenar_Submochila(estudiante soldado,Nodo_accesorio*&lista_accesorios)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    string elegido;
    accesorio accesorio_elegido;
    for (int i = 0; i<3; i++)
    {   
        bool repetir_validacion=true;
        while(repetir_validacion==true) {
            repetir_validacion=false;
            cout<<endl;
            color(hConsole, 13);
            cout << "- NOMBRE: ";//morado :)
            color(hConsole, 7);
            cout<<soldado.nombre <<endl; //blanco :)
            color(hConsole, 13);
            cout << "- SALUD: ";
            color(hConsole, 7);
            cout << soldado.salud <<endl;
            color(hConsole, 13);
            cout << "- ENERGIA: ";
            color(hConsole, 7);
            cout << soldado.energia <<endl;
            color(hConsole, 13);
            cout << "- AMBIENTE: ";
            cout << soldado.ambiente <<endl;
            color(hConsole, 13);
            cout<<endl;
            cout << "- MOCHILA: "<< endl;
            cout<<endl;
            cout << " #1. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[0].nombre << endl;
            color(hConsole, 13);
            cout << " #2. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[1].nombre << endl;
            color(hConsole, 13);
            cout << " #3. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[2].nombre << endl;
            color(hConsole, 13);
            cout << " #4. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[3].nombre << endl;
            color(hConsole, 13);
            cout << " #5. ";
            color(hConsole, 7);
            cout << soldado.Mochila.vector_mochila[4].nombre << endl;

            cout<< "- SUBMOCHILA-"<<endl;
            Mostrar_Submochila(soldado);

            string opcion;
            cout<<"1) Ver detalles de accesorio"<<endl;
            cout<<"2) Ingresar accesorio a submochila (accesorios que usara en batalla)"<<endl;
            getline(cin, opcion);

            if (opcion=="1") {
                bool val2=true;
                while (val2==true) {
                    val2=false;
                    cout<<"Ingrese el nombre del accesorio de su mochila que desea detallar"<<endl;
                    string nombre;
                    getline(cin,nombre);
                    cout<<endl;
                    if (Existe_enMochila(soldado.Mochila.vector_mochila,nombre)==true) {
                        Detallar_Mochila(soldado,nombre);
                        repetir_validacion=true;
                        cout<<endl;
                    }
                    else {
                        cout<<"! Ese accesorio no esta en su mochila. Intente de nuevo."<<endl;
                        cout<<endl;
                        val2=true;
                    }

                }
            }
            else if (opcion=="2") 
            {
                string elegido;
                string elegidos[3];
                bool esta=false;

                cout << "Ingrese el accesorio "<<i+1<<" que desea usar en batalla." << endl;
                getline(cin,elegido);
                cout<<endl;
                for (int j = 0; j<3; j++ )
                    {
                        if (elegidos[j]==elegido)
                        {
                            esta=true;
                        }
                    }
                if (esta==true) {
                        cout<<"! Ya introdujo ese accesorio a su submochila. Seleccione otro"<<endl;
                        cout<<endl;
                        repetir_validacion=true; 
                }
                else {
                    int num=Stoi(elegido);
                    if ((elegido=="1")||(elegido=="2")||(elegido=="3")||(elegido=="4")||(elegido=="5")) {
                        elegidos[i]=elegido;
                        soldado.Submochila[i]=soldado.Mochila.vector_mochila[num-1];
                    }
                    else {
                        cout<<"! Introduzca un numero valido (1 - 5). Intente de nuevo"<<endl;
                        cout<<endl;
                        repetir_validacion=true;
                    }


                }
            }
            else {
                cout<<"! Por favor, introduzca una opcion del menu"<<endl;
                cout<<endl;
                repetir_validacion=true;
            }


        }

     
    }

}

accesorio Usar_Submochila (estudiante soldado)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    accesorio uso;
    cout<<endl;
    bool repetir_validacion=true;
    while(repetir_validacion==true) {
        repetir_validacion=false;
        color(hConsole, 13);
        cout << "- NOMBRE: ";
        color(hConsole, 7);
        cout << soldado.nombre <<endl;
        color(hConsole, 13);
        cout << "- SALUD: ";
        color(hConsole, 7);
        cout << soldado.salud <<endl;
        color(hConsole, 13);
        cout << "- ENERGIA: ";
        color(hConsole, 7);
        cout << soldado.energia <<endl;
        color(hConsole, 13);
        cout << "- AMBIENTE: ";
        color(hConsole, 7);
        cout << soldado.ambiente <<endl;
        color(hConsole, 13);
        cout << "- ACCESORIOS ESCOGIDOS: " << endl;
        cout << " #1. ";
        color(hConsole, 7);
        cout << soldado.Submochila[0].nombre << endl;
        color(hConsole, 13);
        cout << " #2. ";
        color(hConsole, 7);
        cout << soldado.Submochila[1].nombre << endl;
        color(hConsole, 13);
        cout << " #3. ";
        color(hConsole, 7);
        cout << soldado.Submochila[2].nombre << endl; 

        string opcion;
        cout<<"1) Ver detalles de accesorio"<<endl;
        cout<<"2) Ingresar el accesorio que quiere utilizar en el combate."<<endl;
        getline(cin,opcion);
            if (opcion=="1") {
                bool val2=true;
                while (val2==true) {
                    val2=false;
                    cout<<"Ingrese el nombre del accesorio de su mochila que desea detallar"<<endl;
                    string nombre;
                    getline(cin,nombre);
                    cout<<endl;
                    if (Existe_enSubMochila(soldado.Submochila,nombre)==true) {
                        Detallar_Submochila(soldado,nombre);
                        repetir_validacion=true;
                        cout<<endl;
                    }
                    else {
                        cout<<"! Ese accesorio no esta en su mochila. Intente de nuevo."<<endl;
                        cout<<endl;
                        val2=true;
                    }

                }
            }
            else if (opcion=="2") 
            {
                string accesorio;
                cout <<"Ingrese el numero del accesorio a usar" <<endl;
                getline(cin,accesorio);
                cout<<endl;
                if (Validar_enteros(accesorio)==true)        
                    {
                        int accesorio_num=Stoi(accesorio);
                        if ((accesorio_num<=3)&&(accesorio_num>=1))
                        {
                            if(Escoger_accesorio_submochila(uso, soldado, accesorio_num-1)==true)
                            {
                                Escoger_accesorio_submochila(uso, soldado, accesorio_num-1);
                            }
                            else 
                            {
                                color(hConsole, 4);
                                cout<<"! A ese accesorio no le quedan usos, escoga otro."<< endl;
                                cout << endl;
                                color(hConsole, 7);
                                repetir_validacion=true;
                            }
                        }
                        else
                        {
                            color(hConsole, 4);
                            cout<<"! Ingrese un numero entero positivo entre (1-3)"<<endl;
                            cout << endl;
                            color(hConsole, 7);
                            repetir_validacion=true;
                        }
                    }
                else
                    {
                        color(hConsole, 4);
                        cout<<"! Ingrese un numero entero positivo entre (1-3)"<<endl;
                        cout << endl;
                        color(hConsole, 7);
                        repetir_validacion=true;
                    }   
            }
            else {
                cout<<"! Por favor, introduzca una opcion del menu"<<endl;
                cout<<endl;
                repetir_validacion=true;
            }
        }
    return uso;
}


string Randomizar_Turno(int argc, char**argv) {
    string random;

    srand(time(NULL));
    int num;
    num=1 + rand()%(2);

    random=to_string(num);
    
    return random;
}

bool Revisar_SubMochila(accesorio Submochila[3], string ambiente_random) {
    bool encontrado=false;

    for (int i=0;i<3;i++) 
        {
            if ((Submochila[i].tipo=="acondicionamiento")&&(Submochila[i].recuperacion==ambiente_random)) {
                encontrado=true;
            }
        }
    return encontrado;
}

string Asignar_Turno(int argc, char**argv,string ambiente_random,estudiante humano, estudiante andromedano, accesorio Submochila_humano[3],accesorio Submochila_andromedano[3]) {
    string turno;

    if ((humano.ambiente==ambiente_random)&&(andromedano.ambiente==ambiente_random)) {
        turno=Randomizar_Turno(argc,argv);
    }
    else {
        if ((humano.ambiente!=ambiente_random)&&(andromedano.ambiente!=ambiente_random)) {
            turno=Randomizar_Turno(argc,argv);
        }
        else {
            if (humano.ambiente!=ambiente_random) 
                {
                    if (Revisar_SubMochila(humano.Submochila,ambiente_random)==false) {
                        turno="1"; //el humano no tiene con que atacar, se le da la gracia de empezar primero
                    }
                    else {
                        turno=Randomizar_Turno(argc,argv); //si tiene con qué defenderse, se randomiza igual el turno
                    }
                }
            if (andromedano.ambiente!=ambiente_random) 
                {
                if (Revisar_SubMochila(andromedano.Submochila,ambiente_random)==false) {
                    turno="1"; //el andromedano no tiene con que atacar, se le da la gracia de empezar primero
                }
                else {
                    turno=Randomizar_Turno(argc,argv); //si tiene con qué defenderse, se randomiza igual el turno
                }
                }
        }
    }
    return turno;
}

void Consecuencias_Ambiente(estudiante soldado,string ambiente_guerra) {
    if (soldado.ambiente!=ambiente_guerra) {
        if (Revisar_SubMochila(soldado.Submochila,ambiente_guerra)==false) {
            int salud_original=soldado.Raza.salud;
            int energia_original=soldado.Raza.energia;

            int salud_actual= (soldado.salud - (salud_original*0.30));
            int energia_actual= (soldado.energia - (energia_original*0.30));

            if (salud_actual<0) {
                soldado.salud=0;
            }
            else {
                soldado.salud=salud_actual;
            }
            if (energia_actual<0) {
                soldado.energia=0;
            }
            else {
                soldado.energia=energia_actual;
            }
            
        }
    }
}

void Accion(accesorio accesorio, estudiante activo, estudiante inactivo, string ambiente_guerra)
{
    for (int i = 0; i<3; i++)
    {
        if (accesorio.nombre==activo.Submochila[i].nombre)
        {
            activo.Submochila_usos[i]=activo.Submochila_usos[i]-1;

            if (accesorio.contenedor!=0)
            {
                activo.Submochila_usos[i]=activo.Submochila_usos[i]+1;
            }
        }
    }


    if (accesorio.tipo=="ataque")
    {
        if (inactivo.escudo!=0){
            if ((accesorio.valor-inactivo.proteccion)>inactivo.escudo)
            {
                inactivo.salud=(inactivo.salud-(inactivo.escudo-(accesorio.valor-inactivo.proteccion)));
                inactivo.escudo=0;
            }
            else
            {
                inactivo.escudo=inactivo.escudo-(accesorio.valor-inactivo.proteccion);
            }
        }
        else
        {
            inactivo.salud=(inactivo.salud-accesorio.valor);
        }
        Consecuencias_Ambiente(activo,ambiente_guerra);
    }
    if (accesorio.tipo=="defensa")
    {
        activo.escudo=accesorio.contenedor;
        activo.proteccion=accesorio.valor;

    }
    if (accesorio.tipo=="supervivencia")
    {
        if (accesorio.recuperacion=="salud")
        {
            activo.salud=(activo.salud+accesorio.valor);
        }
        else if (accesorio.recuperacion=="energia")
        {
            activo.energia=(activo.energia+accesorio.valor);
        }
    }
    if (accesorio.tipo=="acondicionamiento")
    {
        activo.ambiente=accesorio.ambiente;
    }
    
    activo.energia=(activo.energia-accesorio.energia_consumida);
}

void Devolver_soldado (estudiante soldado, estudiante refugio[3])
{
    for (int i=0;i<3;i++) 
    {
        if (refugio[i].nombre==soldado.nombre) 
        {
            refugio[i].energia =soldado.energia;
            refugio[i].salud = soldado.salud;
            refugio[i].ambiente = soldado.ambiente;
            refugio[i].escudo = soldado.escudo;
            refugio[i].proteccion = soldado.proteccion;
            for (int j = 0; j<3;i++)
            {
                for(int k = 0; k<5; k++)
                {
                    if (soldado.Submochila[j].nombre==refugio[i].Mochila.vector_mochila[k].nombre){
                        refugio[i].Mochila.vector_mochila[k].contenedor=soldado.Submochila[j].contenedor;
                        refugio[i].Mochila.vector_usos[k]=soldado.Submochila_usos[j];
                    }
                }
            }
        }
    }

}

void Combate (estudiante humano, estudiante andromedano, string turno, string ambiente_guerra)
{   
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //randomizar turno
    while ((Revisar_vitalidad(humano)==true)&&(Revisar_vitalidad(andromedano)==true))
    {
        if (turno=="1")
        {
            color(hConsole, 3);
            cout << " |-- Turno Humanos -|" << endl;
            color(hConsole, 7);
            cout << endl;
            Accion(Usar_Submochila(humano), humano, andromedano, ambiente_guerra);


            
            color(hConsole, 10);
            cout << " |-- Turno Andromedanos -|" << endl;
            color(hConsole, 7);
            cout << endl;
            Accion(Usar_Submochila(andromedano), andromedano, humano, ambiente_guerra);

        }
        else 
        {
            color(hConsole, 10);
            cout << " |-- Turno Andromedanos -|" << endl;
            color(hConsole, 7);
            cout << endl;
            Accion(Usar_Submochila(andromedano), andromedano, humano, ambiente_guerra);


            color(hConsole, 3);
            cout << " |- Turno Humanos -|" << endl;
            color(hConsole, 7);
            cout << endl;
            Accion(Usar_Submochila(humano), humano, andromedano, ambiente_guerra);
            
            
        }
    }
    
}



void Descansar(estudiante soldado) 
{
    int salud_original=soldado.Raza.salud;
    int energia_original=soldado.Raza.energia;

    int energia_actual=soldado.energia;
    
    energia_actual=(energia_actual + (energia_original*0.25)); //la energia aumenta en un 25% al descansar

    if (energia_actual>energia_original) {
        soldado.energia=energia_original; //Un soldado al descansar no puede llegar a mas que su energia original
    }
    else {
        soldado.energia=energia_actual;
    }
    
    
    int salud_actual=soldado.salud;

    if (salud_actual>(salud_original*0.60)) {
        salud_actual=(salud_actual+(salud_original*0.15));
    }
    else 
        {
            salud_actual=(salud_actual+(salud_original*0.5));
        }

    if (salud_actual>salud_original) {
        soldado.salud=salud_original; //Un soldado al descansar no puede llegar a mas que su salud original
    }
    else {
        soldado.salud=salud_actual;
    }
}

void Descansos (estudiante Equipo[3], string nombre)
{
    for (int i =0;i<3;i++)
    {
        if (Equipo[i].nombre!=nombre)
        {
            Descansar(Equipo[i]);
        }
    }
}

void Absorber(estudiante ganador, estudiante perdedor) {
    int energia_original=ganador.Raza.energia;
    int energia_perdedor=perdedor.energia;
    int energia_ganador=ganador.energia;
    
    energia_ganador=(energia_ganador+energia_perdedor);

    if (energia_ganador>energia_original) {
        ganador.energia=energia_original; //un soldado no puede tener mas energia que su energia original
    }
    else {
        ganador.energia=energia_ganador;
    }
    //el pepe
}


void Batalla (int argc,char**argv,estudiante Equipo1[3], estudiante Equipo2[3], string ambiente_guerra, Nodo_accesorio*&puntero)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while ((Examinar_vidas(Equipo1)==true)&&(Examinar_vidas(Equipo2)==true))
    {
        estudiante humano;
        estudiante andromedano;

        bool escoger = true;
        while (escoger==true)
        {
            escoger =false;

            cout<<endl;
            color(hConsole, 3);
            cout<<"- () Jugador 1 - Humanos "<<endl;
            color(hConsole, 7);
            Mostrar_Equipo(Equipo1);
            cout<<endl;
            cout<<"  Escoja su combatiente "<<endl;
            cout<<endl;
            string nombre_humano;
            getline(cin,nombre_humano);
            if (Existe_estudiante(nombre_humano, Equipo1)==true)
            {
                if ((Revisar_vitalidad(Escoger_estudiante(nombre_humano,Equipo1)))==true)
                {
                    humano=Escoger_estudiante(nombre_humano,Equipo1);
                }
                else
                {
                    color(hConsole, 4);
                    cout<<"! El soldado ";
                    color(hConsole, 7);
                    cout<<nombre_humano;
                    color(hConsole, 4);
                    cout<<" ha fallecido, escoja otro"<<endl;
                    escoger=true;
                    color(hConsole, 7);
                }
            }
            else
            {
                color(hConsole, 4);
                cout <<"! El soldado ";
                color(hConsole, 7);
                cout<<nombre_humano;
                color(hConsole, 4);
                cout<<" no existe, intente de nuevo"<<endl;
                escoger=true;
                color(hConsole, 7);
            }
        }

            Llenar_Submochila(humano,puntero);

        escoger = true;
        while (escoger==true)
        {
            escoger =false;

            cout<<endl;
            color(hConsole, 10);
            cout<<"- () Jugador 2 - Andromedanos "<<endl;
            color(hConsole, 7);
            Mostrar_Equipo(Equipo2);
            cout<<"  Escoja su combatiente "<<endl;
            cout<<endl;
            string nombre_andromedano;
            getline(cin,nombre_andromedano);
            if (Existe_estudiante(nombre_andromedano, Equipo2)==true)
            {
                if ((Revisar_vitalidad(Escoger_estudiante(nombre_andromedano,Equipo2)))==true)
                {
                    andromedano=Escoger_estudiante(nombre_andromedano,Equipo2);
                }
                else
                {
                    color(hConsole, 4);
                    cout<<"! El soldado ";
                    color(hConsole, 7);
                    cout<<nombre_andromedano;
                    color(hConsole, 4);
                    cout<<" ha fallecido, escoja otro"<<endl;
                    color(hConsole, 7);
                    escoger=true;
                }
            }
            else
            {
                color(hConsole, 4);
                cout <<"! El soldado ";
                color(hConsole, 7);
                cout <<nombre_andromedano;
                color(hConsole, 4);
                cout <<" no existe, intente de nuevo"<<endl;
                escoger=true;
                color(hConsole, 7);
            }
        }
            Llenar_Submochila(andromedano,puntero);
        
            

            //Funcion Roxy turnos
            string turno;
            turno=Asignar_Turno(argc,argv,ambiente_guerra,humano,andromedano,humano.Submochila,andromedano.Submochila);
            
            Combate(humano,andromedano,turno, ambiente_guerra);
            
            if ((Revisar_vitalidad(humano)==true)&&(Revisar_vitalidad(andromedano)==false))
            {
                Absorber(humano, andromedano);
            }
            else if ((Revisar_vitalidad(humano)==false)&&(Revisar_vitalidad(andromedano)==true))
            {
                Absorber(andromedano, humano);
            }
            
            Devolver_soldado(humano, Equipo1);
            Devolver_soldado(andromedano, Equipo2);

            Descansos(Equipo1, humano.nombre);
            Descansos(Equipo2, andromedano.nombre);
            
            
            //descanso


    }
}


bool Guerra (Nodo_ambiente *&puntero1, Nodo_raza *&puntero2, Nodo_accesorio *&puntero3, estudiante Equipo1[3], estudiante Equipo2[3],int argc,char**argv)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Crear_Equipo(puntero1,puntero2,puntero3,Equipo1,Equipo2);
    bool finalizado=false;
    bool menu=true;
    while (menu == true)
    {    
        menu=false;
        Menu_Equipos('1',Equipo1,Equipo2);
        string opcion;
        getline(cin, opcion);
        if (opcion=="1")
            {   
                bool repetir=true;
                while(repetir==true) {
                    repetir=false;
                    Menu_Equipos('4',Equipo1,Equipo2);
                    string opcion1;
                    getline(cin,opcion1);
                    if (opcion1=="a") 
                        {
                            bool submenu=true;
                            while (submenu==true) 
                                {
                                    submenu=false;
                                    cout<<endl;
                                    Menu_Equipos('2',Equipo1,Equipo2);
                                    cout<<endl;
                                    string opcion2;
                                    getline(cin,opcion2);

                                    if (opcion2=="1") 
                                        {   
                                            string nombre_soldado;
                                            bool repetir_validacion=true;
                                            while (repetir_validacion==true) 
                                            {
                                                repetir_validacion=false;
                                                cout<<"Ingrese el nombre del soldado del que desea ver sus detalles"<<endl;
                                                cout<<endl;
                                                getline(cin,nombre_soldado);
                                                cout << endl;
                                                if (Existe_estudiante(nombre_soldado,Equipo1)==true)
                                                    {
                                                        Detallar_Soldado(Equipo1,nombre_soldado);
                                                        submenu=true;
                                                    }
                                                    else
                                                    {
                                                        color(hConsole, 4);
                                                        repetir_validacion=true;
                                                        cout << "! Ese soldado no existe, intente de nuevo" << endl;
                                                        color(hConsole, 7);
                                                    }
                                            }
                                            //Detallar_Soldado(Equipo1,opcion2); hay que validar que el nombre exista dentro de la funcion
                                        }
                                    else if (opcion2=="2") 
                                        {
                                            string nombre_soldado;
                                            bool repetir_validacion=true;
                                            while (repetir_validacion==true)
                                            {
                                                repetir_validacion=false;
                                                cout<<"Ingrese el nombre del soldado al que desea modificar"<<endl;
                                                cout<<endl;
                                                getline(cin,nombre_soldado); 
                                                cout << endl;
                                                if (Existe_estudiante(nombre_soldado,Equipo1)==true)
                                                    {
                                                        Modificar_soldado(nombre_soldado,Equipo1,Equipo2,puntero1,puntero2,puntero3);
                                                        submenu=true;
                                                    }
                                                    else
                                                    {
                                                        color(hConsole, 4);
                                                        repetir_validacion=true;
                                                        cout << "! Ese soldado no existe, intente de nuevo" << endl;
                                                        color(hConsole, 7);
                                                    }
                                            }
                                        }
                                    else if (opcion2=="3") 
                                        {
                                            menu=true;
                                        }
                                    else 
                                        {
                                            color(hConsole, 4);
                                            cout<<"! Por favor, ingrese una opcion del menu.";
                                            cout<<endl;
                                            submenu=true;
                                            color(hConsole, 7);
                                        }  
                                }
                        }
                    else if (opcion1=="b") 
                        {
                            bool submenu=true;
                            while (submenu==true) 
                                {
                                    submenu=false;
                                    Mostrar_Equipo(Equipo2);
                                    cout<<endl;
                                    Menu_Equipos('3',Equipo1,Equipo2);
                                    string opcion2;
                                    cout<<endl;
                                    getline(cin,opcion2);

                                    if (opcion2=="1") 
                                        {
                                            string nombre_soldado;
                                            bool repetir_validacion=true;
                                            while (repetir_validacion==true) 
                                            {
                                                repetir_validacion=false;
                                                cout<<"Ingrese el nombre del soldado del que desea ver sus detalles"<<endl;
                                                cout<<endl;
                                                getline(cin,nombre_soldado);
                                                cout << endl;
                                                if (Existe_estudiante(nombre_soldado,Equipo2)==true)
                                                    {
                                                        Detallar_Soldado(Equipo2,nombre_soldado);
                                                        submenu=true;
                                                    }
                                                else
                                                    {
                                                        color(hConsole, 4);
                                                        repetir_validacion=true;
                                                        cout << "! Ese soldado no existe, intente de nuevo" << endl;
                                                        color(hConsole, 7);
                                                    }
                                            }
                                        }
                                    else if (opcion2=="2") 
                                        {
                                            string nombre_soldado;
                                            bool repetir_validacion=true;
                                            while (repetir_validacion==true)
                                            {
                                                repetir_validacion=false;
                                                cout<<"Ingrese el nombre del soldado al que desea modificar"<<endl;
                                                cout<<endl;
                                                getline(cin,nombre_soldado); 
                                                cout << endl;
                                                if (Existe_estudiante(nombre_soldado,Equipo2)==true)
                                                    {
                                                        Modificar_soldado(nombre_soldado,Equipo2,Equipo1,puntero1,puntero2,puntero3);
                                                        submenu=true;
                                                    }
                                                    else
                                                    {
                                                        repetir_validacion=true;
                                                        color(hConsole, 4);
                                                        cout << "! Ese soldado no existe, intente de nuevo" << endl;
                                                        color(hConsole, 7);
                                                    }
                                            }
                                        }
                                    else if (opcion2=="3") 
                                        {
                                            menu=true;
                                        }
                                    else 
                                        {
                                            color(hConsole, 4);
                                            cout<<"! Por favor, ingrese una opcion del menu.";
                                            cout<<endl;
                                            submenu=true;
                                            color(hConsole, 7);
                                        }  
                                }
                        }
                    else 
                        {
                            color(hConsole, 4);
                            cout<<"! Por favor, ingrese una opcion del menu";
                            cout<<endl;
                            repetir=true;
                            color(hConsole, 7);
                        }

                }
            }
        else if (opcion =="2")
        {
            cout<<"Comenzando Partida..."<<endl;
            cout<<endl;

            estudiante Todos[6];
            int j=0;
            for (int i=0;i<6;i++) {
                if (i<3) {
                    Todos[i]=Equipo1[i];
                }
                else {
                    Todos[i]=Equipo2[j];
                    j+=1;
                }
            }
            

            cout<<endl;
            estudiante Equipo_Humanos[3];
            int posicion_humanos=0;
            estudiante Equipo_Andromedanos[3];
            int posicion_andromedanos=0;

            string fidelidades=Randomizar_Fidelidad(argc,argv);
            
            for (int i=0;i<6;i++) {
                Todos[i].fidelidad=fidelidades[i];
            }

            for (int i=0;i<6;i++) {
                if (Todos[i].fidelidad=='1') {
                    Equipo_Humanos[posicion_humanos]=Todos[i];
                    posicion_humanos+=1;
                }
                else {
                    Equipo_Andromedanos[posicion_andromedanos]=Todos[i];
                    posicion_andromedanos+=1;
                }
            }
            color(hConsole, 4);
            cout<<"! Es posible que hayan ocurrido traiciones"<<endl;
            color(hConsole, 7);
            cout<<"Los nuevos equipos son: "<<endl;
            cout<<endl;
            color(hConsole, 3);
            cout<<"- EQUIPO 1 (HUMANOS) -"<<endl;
            color(hConsole, 7);
            Mostrar_Equipo(Equipo_Humanos);
            cout<<endl;
            color(hConsole, 10);
            cout<<"- EQUIPO 2 (ANDROMEDANOS) -"<<endl;
            color(hConsole, 7);
            Mostrar_Equipo(Equipo_Andromedanos);
            cout<<endl;
            
            //Randomizar ambiente
            string ambiente_random;
            ambiente_random=Randomizar_Ambiente(argc,argv,puntero1);

            cout<<"La guerra tendra lugar en: "<<endl;
            color(hConsole, 13);
            cout<<"     -   "<<ambiente_random<<"   -    "<<endl; 
            color(hConsole, 7);
        
            Batalla(argc,argv,Equipo_Humanos,Equipo_Andromedanos,ambiente_random,puntero3);
            
        }
        else{
            color(hConsole, 4);            
            cout<<"! Ingrese una opcion del menu, intente de nuevo."<<endl;
            cout<<endl;
            menu=true;
            color(hConsole, 7);
        }
        
    }
    return finalizado;
}   


//-----------------------------------------------------------------------------------------------------------
//---------------------------------------------Codigo  Principal--------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
int main(int argc, char**argv){
    //=============================================  Menú principal =============================================
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    color(hConsole, 10);
    cout << endl; 
    cout << "                  .------------.                    " <<endl;
    cout << "               .-                -.                 " <<endl;
    cout << "            .--  ''------------''  --.              " <<endl;
    cout << "          .-         _______         -.             " <<endl;
    cout << "         .-      .adOOOOOOOOOba.      -.            " <<endl;
    cout << "        .-      dOOOOOOOOOOOOOOOb      -.           " <<endl;
    cout << "       .-      dOOOOOOOOOOOOOOOOOb      -.          " <<endl;
    cout << "      .-      dOOOOOOOOOOOOOOOOOOOb      -.         " <<endl;
    cout << "      -      |OOOOOOOOOOOOOOOOOOOOO|      -         " <<endl;
    cout << "      -      OY'~ YOOOOOOOOOOOP ~`YO      -         " <<endl;
    cout << "      -      OO     `YOOOOOP'     OO      -         " <<endl;
    cout << "      '-     OOb      `OOO'      dOO     -'         " <<endl;
    cout << "       '-     OOOo     OOO     oOOO     -'          " <<endl;
    cout << "        '-     OOOb._,dOOOb._,dOOO     -'           " <<endl;
    cout << "         '-    `OOOOOOOOOOOOOOOOO'    -'            " <<endl;
    cout << "          '-     OOOOOOOOOOOOOOO     -'             " <<endl;
    cout << "           '-     YOOPVVVVVYOOY     -'              " <<endl;
    cout << "            '-     OOI=====IOO     -'               " <<endl;
    cout << "             '-    `ObNNNNNdO'    -'                " <<endl;
    cout << "              '-  - `~OOOOO~' -  -'                 " <<endl;
    cout << "               '-'             '-                   " <<endl;
    cout << "               '-               -                   " <<endl;
    cout << "                 '-           -'                    " <<endl;
    cout << "                   ''- - - -''                      " <<endl;
    cout << "--- --- --- --- --- --- --- --- --- --- --- --- --- " <<endl; 
    cout << "- Bienvenido a Invasion Extraterrestre 'El Juego' - " <<endl;
    cout << endl;  

    Nodo_ambiente *lista_ambientes=NULL;
    Nodo_raza *lista_razas=NULL;
    Nodo_accesorio *lista_accesorios=NULL;
    bool menu1 = true;
    string opcion;
    
    while (menu1==true)
        {   
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            color(hConsole, 13);
            menu1=false;
            cout <<"----- -----  ----- -----"<<endl;
            cout <<"()-  MENU PRINCIPAL  -()"<<endl;
            cout <<"----- -----  ----- -----"<<endl;
            
            cout <<endl;
            cout << "- - - - - - - - - - -"<<endl;
            cout << " 1) Jugar"  << endl;
            cout << " 2) Ambientes " << endl;
            cout << " 3) Razas " << endl;
            cout << " 4) Accesorios" << endl;
            cout << " 5) Salir  " << endl;
            cout << "- - - - - - - - - - -"<<endl;
            cout << endl;

            color(hConsole, 7);
            
            getline(cin,opcion);
            
            if (opcion=="1")
                {
                    int cont_accesorios=0;
                    Nodo_accesorio *recorrer = lista_accesorios;
                    while (recorrer!=NULL)
                        {
                            cont_accesorios+=1;
                            recorrer=recorrer->siguiente;
                        }

                    if ((lista_ambientes==NULL)||(lista_razas==NULL)||(cont_accesorios<5))
                        {
                            color(hConsole, 4);
                            cout << "! No puede empezar la partida si no tiene minimo: 1 ambiente, 1 raza y 5 accesorios creados." <<endl;
                            cout << endl;
                            color(hConsole, 7);
                            menu1=true;
                        }    
                    
                    else
                        {   
                            estudiante Equipo1[3];
                            estudiante Equipo2[3];
                            Guerra(lista_ambientes,lista_razas,lista_accesorios,Equipo1,Equipo2,argc,argv);
                            
                        }
                }
            else if (opcion=="2")
                {
                    bool menu_ambientes=true;
                    while (menu_ambientes==(true)) 
                        {
                            color(hConsole, 13);
                            menu_ambientes=false;
                            cout<<endl;
                            cout<<" - AMBIENTES -"<<endl; //color morado
                            cout<<endl;
                            Menu_Ambientes(lista_ambientes);
                            color(hConsole, 7);
                            string opcion1;
                            getline(cin,opcion1);

                            if(opcion1=="1") 
                                {
                                    //AGREGAR AMBIENTES
                                    menu_ambientes=Opcion1Amb(lista_ambientes);        
                                }     
                                        
                            else if (opcion1=="2")
                                { 
                                    //ELIMINAR AMBIENTES
                                    menu_ambientes=Opcion2Amb(lista_ambientes,lista_razas,lista_accesorios);
                                }
                                            
                                        
                            else if (opcion1=="3")
                                {
                                    //MODIFICAR AMBIENTES
                                    menu_ambientes=Opcion3Amb(lista_ambientes,lista_razas,lista_accesorios);
                                }
                                            
                            else if (opcion1=="4")
                                {
                                    //CARGAR ARCHIVO CON AMBIENTES
                                    menu_ambientes=Opcion4Amb(lista_ambientes);
                                }

                            else if (opcion1=="5")
                                {
                                    cout << endl;
                                    menu1=true;
                                }
                                            
                            else 
                                {

                                    color(hConsole, 4);
                                    cout<<"! Por favor, introduzca una opcion del menu."<< endl;
                                    menu_ambientes=true;
                                    cout<<endl;
                                    color(hConsole, 7);
                                }
                                
                        }
                            
                }
            else if (opcion=="3") 
                {   
                    if (lista_ambientes==NULL){
                        color(hConsole, 4);
                        cout<<"! No puede acceder a esta seccion sin crear un ambiente primero.";
                        cout<<endl;
                        menu1=true;
                        color(hConsole, 7);
                    }
                    else {
                        bool menu_razas=true;
                        while (menu_razas==true) {
                            color(hConsole, 13);
                            cout<<" - RAZAS -"<<endl;
                            color(hConsole, 7);
                            cout<<endl;
                            menu_razas=false;
                            if (lista_razas==NULL) {

                                Mostrar_Razas('N',"none",lista_razas);
                            }
                            else {
                                
                                Menu_Razas('2',lista_razas,lista_ambientes);
                            }
                            Menu_Razas('1',lista_razas,lista_ambientes);
                            string opcion2;
                            getline(cin,opcion2);

                            if (opcion2=="1") {
                                menu_razas=Opcion1Raz(lista_razas);
                            }
                            else if (opcion2=="2") {
                                menu_razas=Opcion2Raz(lista_razas,lista_ambientes);
                            }
                            else if (opcion2=="3"){
                                menu_razas=Opcion3Raz(lista_razas);
                            }
                            else if (opcion2=="4"){
                                menu_razas=Opcion4Raz(lista_ambientes,lista_razas);
                            }
                            
                            else if (opcion2=="5") {
                                menu_razas=Opcion5Raz(lista_razas,lista_ambientes);
                            }

                            else if (opcion2=="6") {
                                menu1=true;
                            }
                            else {
                                color(hConsole, 4);
                                menu_razas=true;
                                cout<<"! Introduzca una opcion del menu.";
                                cout<<endl;
                                color(hConsole, 7);
                            }
                        }

                    }
                }

            else if (opcion=="4") 
                {
                    
                    if (lista_ambientes==NULL){
                        color(hConsole, 4);
                        cout<<"! No puede acceder a esta seccion sin crear un ambiente primero.";
                        cout<<endl;
                        menu1=true;
                        color(hConsole, 7);
                    }
                    else {
                        bool menu_accesorios=true;
                        while (menu_accesorios==true) {
                            menu_accesorios=false;
                            color(hConsole, 13);
                            cout<<" - ACCESORIOS -"<<endl;
                            color(hConsole, 7);
                            cout<<endl;
                            if (lista_accesorios==NULL) 
                                {
                                    color(hConsole, 8);
                                    cout<<"[ No hay accesorios ]";
                                    color(hConsole, 7);
                                    cout<<endl;
                                }
                            else 
                                {
                                    Menu_Accesorios('1',lista_accesorios,lista_ambientes);
                                }
                            cout<<endl;
                            Menu_Accesorios('2',lista_accesorios,lista_ambientes);
                            string opcion3;
                            getline(cin,opcion3);

                            if (opcion3=="1") {
                                menu_accesorios=Opcion1Acc(lista_accesorios);
                            }
                            else if (opcion3=="2") {
                                menu_accesorios=Opcion2Acc(lista_accesorios,lista_ambientes);
                            }
                            else if (opcion3=="3"){
                                menu_accesorios=Opcion3Acc(lista_accesorios);
                            }
                            else if (opcion3=="4"){
                                menu_accesorios=Opcion4Acc(lista_ambientes,lista_accesorios);
                            }
                            
                            else if (opcion3=="5") {
                                //cargar archivo
                                menu_accesorios=Opcion5Acc(lista_accesorios,lista_ambientes);

                            }
                            else if (opcion3=="6") {
                                menu1=true;
                            }
                            else {
                                color(hConsole, 4);
                                menu_accesorios=true;
                                cout<<"! Introduzca una opcion del menu.";
                                cout<<endl;
                                color(hConsole, 7);
                            }
                            color(hConsole, 7);
                        }

                    }
                }
            else if (opcion=="5") 
                {
                    menu1=false;
                    cout<<"Gracias por jugar!";
                } 

                    
            else {
                color(hConsole, 4);
                cout<<"! Por favor, introduzca una opcion del menu."<< endl;
                menu1=true;
                color(hConsole, 7);
                }
        }
     
}