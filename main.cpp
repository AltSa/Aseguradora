#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define TAMANIO 9999
#define E "Error al intentar abrir el archivo o el archivo no existe."
#define C "Los datos se han cargado correctamente."
#define A "Asegurados.BAK"

using namespace std;


struct Incidente {
    int incidenteID;
    char fechahora[14];
    char dniasegurado[11];
    char patente [15];
    char dniotro [11];
    char calle[50];
    int altura;
};

struct asegurado{
    int nroPoliza;
    char dni [11];
    char nombre [11];
    char apellido[15];
    bool CuotaAlDia;
    char PatenteAuto [15];
    bool Activa;
    int CantIncidentes;

};

// Declaracion de los prototipos de las funciones utilizadas.

void LevantarAsegurados(asegurado v[]);
void inicializarVector(asegurado v[]);
int cantElementos(asegurado v[]);
int numeroDePolizaMayor(asegurado v[]);
void cargarNuevaPoliza(asegurado v[]);
int BuscarPoliza(asegurado v[], int);
void BuscarPolizaV2(asegurado v[]);
void BuscarPolizaPorDNI(asegurado v[]);
void ListarPolizas(asegurado v[]);
void ordenar_polizas(asegurado v[]);
void desactivarPoliza(asegurado v[]);
int BuscarPatente(asegurado v[], char*);
void ProcesarLote(asegurado v[]);
void FinalizarJornada(asegurado v[]);
bool datos_prueba();
bool inc_prueba();
void menu_ordenar(asegurado v[]);
void menu_buscar(asegurado v[]);
void menu_prueba();
char menu(asegurado v[]);

// Se cargan los asegurados a un vector
void LevantarAsegurados(asegurado v[]){
    FILE *arch;
    int i =0;

    if (arch=fopen(A,"rb")){
    while (!feof(arch)){
        fread(&v[i],sizeof(asegurado),1,arch);

          if(v[i].nroPoliza)
        {
            cout<<endl;
            cout<<"*****************************************************************************"<<endl<<endl;
            cout<<"Numero de Poliza: "<<v[i].nroPoliza<<endl;
            cout<<"DNI: "<<v[i].dni<<endl;
            cout<<"Nombre: "<<v[i].nombre<<endl;
            cout<<"Apellido: "<<v[i].apellido<<endl;
            if(v[i].CuotaAlDia){
                cout<<"Cuota al dia: Si"<<endl;
            }else{
                cout<<"Cuota al dia: No"<<endl;
            }

            cout<<"Patente: "<<v[i].PatenteAuto<<endl;
            if(v[i].Activa){
                cout<<"Poliza activa: Si"<<endl;
            }else{
                cout<<"Poliza activa: No"<<endl;
            }
            cout<<"Cantidad de incidentes: "<<v[i].CantIncidentes<<endl;
        }


        i++;
     }
    fclose(arch);
        cout <<endl;
        cout<<"*****************************************************************************"<<endl;
        cout<<"********** Los "<< i-1 <<" registros se cargaron al vector correctamente ***************"<<endl;
        cout<<"*****************************************************************************"<<endl;

    }else{
       // cout<<"*******************************************************************************"<<endl;
        cout<<"*************** No se pudieron cargar los registros al vector *****************"<<endl;
        cout<<"*************** El archivo Asegurados.BAK no existe o esta daniado ************"<<endl;
        //cout<<"*******************************************************************************"<<endl;
    }

}
// Se Inicializa el vector
void inicializarVector(asegurado v[]){
    for(int i=0;i<TAMANIO; i++){
        v[i].nroPoliza=0;
    }
}
//Se obtiene la cantidad de registros no vacios dentro del vector
int cantElementos(asegurado v[]){
    int i = 0;
    while(v[i].nroPoliza !=0 && i<TAMANIO){
        i++;

    }
    return i;
}
/*Obtengo el numero de la poliza mas grande para poder asignar el
siguiente a una nueva poliza */
int numeroDePolizaMayor(asegurado v[]){
    int i =0;
    int mayor= v[i].nroPoliza;
    int numElementos = cantElementos(v);
    for(i=0; i<numElementos; i++){
        if(v[i].nroPoliza> mayor){
            mayor = v[i].nroPoliza;
        }
    }
    return mayor;
}
//Cargo los datos de una nueva poliza
void cargarNuevaPoliza(asegurado v[]){
    int i=0;
    while (v[i].nroPoliza != 0 && i < TAMANIO){
        i++;
    }

    if(i<TAMANIO){
        v[i].nroPoliza = numeroDePolizaMayor(v)+1;
        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"Ingrese DNI"<<endl;
        cin.getline (v[i].dni,11,'\n');
        cout<<"Ingrese Nombre"<<endl;
        cin.getline (v[i].nombre,11,'\n');
        cout<<"Ingrese apellido"<<endl;
        cin.getline (v[i].apellido,15,'\n');
        cout<<"Ingrese Patente del auto"<<endl;
        cin.getline (v[i].PatenteAuto,15,'\n');
        v[i].CuotaAlDia=true;
        v[i].Activa=true;
        v[i].CantIncidentes=0;

        cout<<""<<endl;
        cout<<"*****************************************************************************"<<endl<<endl;
        cout<<" Se agrego la nueva poliza de forma exitosa "<<endl<<endl;
        cout<<"*****************************************************************************"<<endl;
        cout<<"Numero de Poliza: "<<v[i].nroPoliza<<endl;
        cout<<"DNI: "<<v[i].dni<<endl;
        cout<<"Nombre: "<<v[i].nombre<<endl;
        cout<<"Apellido: "<<v[i].apellido<<endl;
        cout<<"Cuota al dia: SI"<<endl;
        cout<<"Patente de Auto: " << v[i].PatenteAuto<<endl;
        cout<<"Poliza Activa: SI"<<endl;
        cout<<"Cantidad de incidentes: "<<v[i].CantIncidentes<<endl;
        cout<<"*****************************************************************************"<<endl;

    }else{
        cout<<"*****************************************************************************"<<endl;
        cout<<"**El vector esta lleno**"<<endl;
        cout<<"*****************************************************************************"<<endl;
    }
}
//Devuelvo la posicion del numero de poliza
int BuscarPoliza(asegurado v[], int numero){
    int i = 0;
    while (v[i].nroPoliza != numero && i < TAMANIO ){
        i++;
    }
    if(i<TAMANIO ){
        return i;
    }else{
        return -1;
    }
}
//Devuelvo los datos de la poliza si es que se encontro
void BuscarPolizaV2(asegurado v[]){
    cout<<"ingrese el numero de poliza que busca"<<endl;
    int numero;
    cin>>numero;
    int posicion = BuscarPoliza(v,numero);
    if (posicion!=-1){
            cout<<""<<endl;
            cout<<"*****************************************************************************"<<endl;
            cout << "************* DATOS DE LA PERONSA BUSCADA *****************" << endl << endl;
            cout<<"Numero de Poliza: "<<v[posicion].nroPoliza<<endl;
            cout<<"DNI: "<<v[posicion].dni<<endl;
            cout<<"Nombre: "<<v[posicion].nombre<<endl;
            cout<<"Apellido: "<<v[posicion].apellido<<endl;
            if(v[posicion].CuotaAlDia){
                cout<<"Cuota al dia: Si"<<endl;
            }else{
                cout<<"Cuota al dia: No"<<endl;
            }

            cout<<"Patente: "<<v[posicion].PatenteAuto<<endl;
            if(v[posicion].Activa){
                cout<<"Poliza activa: Si"<<endl;
            }else{
                cout<<"Poliza activa: No"<<endl;
            }
            cout<<"Cantidad de incidentes: "<<v[posicion].CantIncidentes<<endl;
            cout<<"*****************************************************************************"<<endl;
    }else{
        cout<<"No se encontro el numero de poliza solicitado.";
    }


}
//Devuelvo los datos de la poliza si es que se encontro el DNI
void BuscarPolizaPorDNI(asegurado v[]){
    char dni [11];
    cout<<"ingrese un DNI"<<endl;
    cin.getline (dni,11,'\n');

    int numElementos = cantElementos(v);

    for(int i = 0; i <numElementos; i++){


        if (strcmp(v[i].dni,dni)==0){
            cout<<""<<endl;
            cout<<"*****************************************************************************"<<endl;
            cout << "************* DATOS DE LA PERONSA BUSCADA *****************" << endl << endl;
            cout<<"Numero de Poliza: "<<v[i].nroPoliza<<endl;
            cout<<"DNI: "<<v[i].dni<<endl;
            cout<<"Nombre: "<<v[i].nombre<<endl;
            cout<<"Apellido: "<<v[i].apellido<<endl;
            if(v[i].CuotaAlDia){
                cout<<"Cuota al dia: Si"<<endl;
            }else{
                cout<<"Cuota al dia: No"<<endl;
            }

            cout<<"Patente: "<<v[i].PatenteAuto<<endl;
            if(v[i].Activa){
                cout<<"Poliza activa: Si"<<endl;
            }else{
                cout<<"Poliza activa: No"<<endl;
            }
            cout<<"Cantidad de incidentes: "<<v[i].CantIncidentes<<endl;
            cout<<"*****************************************************************************"<<endl;

        }

    }
}
/*Ordeno las polizas por cantidad de incidentes descendente
  y luego muestro todas */
void ListarPolizas(asegurado v[]){
    asegurado aux;
    int NumElementos = cantElementos(v);
    for (int i = 0 ; i<NumElementos-1; i++){
        for(int j = 0; j < NumElementos-1 -i; j++){
            if(v[j+1].CantIncidentes<v[j].CantIncidentes){
                aux = v[j];
                v[j]= v[j+1];
                v[j+1]= aux;
            }
        }
    }
    for(int i=0; i< NumElementos; i++){
        if(v[i].Activa){
            cout<<""<<endl;
            cout<<"*****************************************************************************"<<endl;
            cout<<"Numero de Poliza: "<<v[i].nroPoliza<<endl;
            cout<<"DNI: "<<v[i].dni<<endl;
            cout<<"Nombre: "<<v[i].nombre<<endl;
            cout<<"Apellido: "<<v[i].apellido<<endl;
            if(v[i].CuotaAlDia){
                cout<<"Cuota al dia: Si"<<endl;
            }else{
                cout<<"Cuota al dia: No"<<endl;
            }

            cout<<"Patente: "<<v[i].PatenteAuto<<endl;
            if(v[i].Activa){
                cout<<"Poliza activa: Si"<<endl;
            }else{
                cout<<"Poliza activa: No"<<endl;
            }
            cout<<"Cantidad de incidentes: "<<v[i].CantIncidentes<<endl;
            cout<<"*****************************************************************************"<<endl;
        }
    }
}
/*Ordeno las polizas por el Nro. de Poliza descendente
  y luego muestro todas */
void ordenar_polizas(asegurado v[]){
    asegurado aux;
    int NumElementos = cantElementos(v);
    for (int i = 0 ; i<NumElementos-1; i++){
        for(int j = 0; j < NumElementos-1 -i; j++){
            if(v[j+1].nroPoliza<v[j].nroPoliza){
                aux = v[j];
                v[j]= v[j+1];
                v[j+1]= aux;
            }
        }
    }
    for(int i=0; i< NumElementos; i++){
        if(v[i].Activa){
            cout<<""<<endl;
            cout<<"*****************************************************************************"<<endl;
            cout<<"Numero de Poliza: "<<v[i].nroPoliza<<endl;
            cout<<"DNI: "<<v[i].dni<<endl;
            cout<<"Nombre: "<<v[i].nombre<<endl;
            cout<<"Apellido: "<<v[i].apellido<<endl;
            if(v[i].CuotaAlDia){
                cout<<"Cuota al dia: Si"<<endl;
            }else{
                cout<<"Cuota al dia: No"<<endl;
            }

            cout<<"Patente: "<<v[i].PatenteAuto<<endl;
            if(v[i].Activa){
                cout<<"Poliza activa: Si"<<endl;
            }else{
                cout<<"Poliza activa: No"<<endl;
            }
            cout<<"Cantidad de incidentes: "<<v[i].CantIncidentes<<endl;
            cout<<"*****************************************************************************"<<endl;
        }
    }
}
//Desactivo el numero de la poliza ingresada
void desactivarPoliza(asegurado v[]){
    cout<<"Ingrese el numero de poliza a desactivar"<<endl;
    int numero;
    cin>>numero;

    int posicion = BuscarPoliza(v,numero);
    if (posicion !=-1){
        v[posicion].Activa=false;
        cout<<"*****************************************************************************"<<endl;
        cout<<"************** Se desactivo la poliza de forma exitosa. ************************"<<endl;
        cout<<"*****************************************************************************"<<endl;

    }else{
        cout<<"*****************************************************************************"<<endl;
        cout<<"**************** No se encontro el numero de Poliza. ***************************"<<endl;
        cout<<"*****************************************************************************"<<endl;
    }
}
//Busco una patente en el vector de asegurados
int BuscarPatente(asegurado v[], char* patente){
    int i = 0;
    while(strcmp(v[i].PatenteAuto,patente)!=0 ){
        i++;
    }
    if(i<TAMANIO){
        return i;
    }else{
        return -1;
    }

}
//Sumo la cantidad de incidentes en las pòlizas correspondientes
void ProcesarLote(asegurado v[]){
    FILE *lote, *procesados;
    int posicion;
    Incidente r,z;
    lote=fopen("Incidentes.BAK","rb");
    if(lote){
    procesados=fopen("procesados.BAK","ab");
    while (!feof(lote)){
        fread(&r,sizeof(Incidente),1,lote);
        posicion = BuscarPatente(v, r.patente);

        if (posicion!=-1){
            v[posicion].CantIncidentes = v[posicion].CantIncidentes +1;

        }else{
            cout<<"*****************************************************************************"<<endl;
            cout<<"*********************** No se encontro la patente. **************************"<<endl;
            cout<<"*****************************************************************************"<<endl;
        }
        z = r;
        fseek(procesados,-1,SEEK_END);
        fwrite(&z,sizeof(Incidente),1,procesados);

     }
    cout<<"*****************************************************************************"<<endl;
    cout<<"******* Se terminaron de Procesar los incidentes de este lote ***************"<<endl;
    cout<<"*****************************************************************************"<<endl;
    fclose(lote);
    fclose(procesados);
    }else{
    cout<<E<<endl;
    }

}
//Sobreescribo el archivo de asegurados
void FinalizarJornada(asegurado v[]){
    FILE *finalizado;
    finalizado=fopen("Asegurados.BAK","wb+");
    int NumElementos = cantElementos(v);
    asegurado copiar;
    for(int i=0;i<NumElementos;i++){
        if(v[i].Activa){

            copiar = v[i];
            fwrite(&copiar,sizeof(asegurado),1,finalizado);

        }

    }
    cout<<"********************* Se actualizo el archivo Asegurados. **********************"<<endl;
    fclose(finalizado);
}
// Genero un archivo con Polizas de prueba
bool datos_prueba(){
    FILE* f=fopen(A,"ab");
    asegurado z;
    if(f)
    {

    z.nroPoliza=1;
    strcpy(z.dni,"39645602");
    strcpy(z.nombre,"Julio");
    strcpy(z.apellido,"Ichiki");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"FF01CC");
    z.Activa=1;
    z.CantIncidentes=5;
    fwrite(&z,sizeof(asegurado),1,f);


    z.nroPoliza=2;
    strcpy(z.dni,"39645602");
    strcpy(z.nombre,"Julio");
    strcpy(z.apellido,"Ichiki");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"XX11WW");
    z.Activa=1;
    z.CantIncidentes=19;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=3;
    strcpy(z.dni,"39645603");
    strcpy(z.nombre,"Hernan");
    strcpy(z.apellido,"viudez");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"KK12XX");
    z.Activa=1;
    z.CantIncidentes=20;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=4;
    strcpy(z.dni,"39645604");
    strcpy(z.nombre,"Romina");
    strcpy(z.apellido,"Marini");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"UU99WW");
    z.Activa=1;
    z.CantIncidentes=2;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=5;
    strcpy(z.dni,"39645205");
    strcpy(z.nombre,"Carla");
    strcpy(z.apellido,"varada");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"XX92TT");
    z.Activa=1;
    z.CantIncidentes=1000;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=6;
    strcpy(z.dni,"39645205");
    strcpy(z.nombre,"Carla");
    strcpy(z.apellido,"varada");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"ZZ24JS");
    z.Activa=1;
    z.CantIncidentes=12;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=7;
    strcpy(z.dni,"39645205");
    strcpy(z.nombre,"Carla");
    strcpy(z.apellido,"varada");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"WWII00");
    z.Activa=0;
    z.CantIncidentes=17;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=8;
    strcpy(z.dni,"39645606");
    strcpy(z.nombre,"Fernando");
    strcpy(z.apellido,"Martinez");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"JJ92LL");
    z.Activa=1;
    z.CantIncidentes=0;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=9;
    strcpy(z.dni,"39645606");
    strcpy(z.nombre,"Fernando");
    strcpy(z.apellido,"Martinez");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"WW14II");
    z.Activa=1;
    z.CantIncidentes=10;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=10;
    strcpy(z.dni,"39645607");
    strcpy(z.nombre,"Juan");
    strcpy(z.apellido,"Garcia");
    z.CuotaAlDia=0;
    strcpy(z.PatenteAuto,"BB91JJ");
    z.Activa=1;
    z.CantIncidentes=2;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=11;
    strcpy(z.dni,"39645608");
    strcpy(z.nombre,"Omar");
    strcpy(z.apellido,"lopez");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"RR18OO");
    z.Activa=1;
    z.CantIncidentes=4;
    fwrite(&z,sizeof(asegurado),1,f);

    z.nroPoliza=12;
    strcpy(z.dni,"39645609");
    strcpy(z.nombre,"Emilia");
    strcpy(z.apellido,"Diaz");
    z.CuotaAlDia=1;
    strcpy(z.PatenteAuto,"JJ12TT");
    z.Activa=0;
    z.CantIncidentes=54;
    fwrite(&z,sizeof(asegurado),1,f);

    fclose(f);
    return true;
    }
    else{
            cout << E<<endl;
        return false;
    }
}
// Genero un archivo con Incidentes de prueba
bool inc_prueba(){
    Incidente inc;
    FILE *f=fopen("Incidentes.BAK","ab");
    if (f)
    {
        inc.incidenteID=200;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645602");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"av medrano");
        inc.altura=8232;
        strcpy(inc.patente,"XX11WW");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=200;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645602");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"av medrano");
        inc.altura=8232;
        strcpy(inc.patente,"XX11WW");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=200;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645602");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"av medrano");
        inc.altura=8232;
        strcpy(inc.patente,"XX11WW");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=200;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645602");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"av medrano");
        inc.altura=8232;
        strcpy(inc.patente,"XX11WW");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=200;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645602");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"av medrano");
        inc.altura=8232;
        strcpy(inc.patente,"XX11WW");
        fwrite(&inc,sizeof(Incidente),1,f);


        inc.incidenteID=201;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645603");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"THOMSON");
        inc.altura=1984;
        strcpy(inc.patente,"KK12XX");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=202;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645604");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"CHILAVERT");
        inc.altura=5232;
        strcpy(inc.patente,"UU99WW");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=203;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645605");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"alcorta");
        inc.altura=8329;
        strcpy(inc.patente,"XX92TT");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=210;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645605");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"pueyredon");
        inc.altura=1921;
        strcpy(inc.patente,"XX92TT");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=201;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645605");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"olvarria");
        inc.altura=1229;
        strcpy(inc.patente,"XX92TT");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=204;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645606");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"rivadavia");
        inc.altura=1432;
        strcpy(inc.patente,"JJ92LL");
        fwrite(&inc,sizeof(Incidente),1,f);

        inc.incidenteID=205;
        strcpy(inc.fechahora,"2017053114:23");
        strcpy(inc.dniasegurado,"39645606");
        strcpy(inc.dniotro,"1428492");
        strcpy(inc.calle,"benavidez");
        inc.altura=1312;
        strcpy(inc.patente,"WW14II");
        fwrite(&inc,sizeof(Incidente),1,f);

        fclose(f);
      return true;
    }
    else{
        return false;
    }


}
// menu ordenar , ordena por cantidad de incidentes y por nro de poliza.
void menu_ordenar(asegurado v[]){
    char i;
    cout << "Ingrese una opcion: "<<endl<<endl;
    cout << "1-Ordenar registros Activos por cantidad de incidentes Descendentemente."<<endl<<endl;
    cout << "2-Ordenar por nro. de Poliza Descendentemente."<<endl<<endl;
    cin >> i;
    switch(i)
    {
    case '1':
        ListarPolizas(v);
        break;
    case '2':
        ordenar_polizas(v);
        break;
    }
}
// menu buscar , busca una poliza por dni o por Nro de Poliza.
void menu_buscar(asegurado v[]){
    char i;
    cout << "Ingrese una opcion: "<<endl<<endl;
    cout << "1-Buscar registro por Nro. de Poliza."<<endl<<endl;
    cout << "2-Buscar registro por DNI."<<endl<<endl;
    cin >> i;
    switch(i)
    {
    case '1':
        BuscarPolizaV2(v);
        break;
    case '2':
        BuscarPolizaPorDNI(v);
        break;
    }
}
// menu prueba da la opcion de generar los archivos de Polizas y Incidentes
void menu_prueba(){
    char i;
    cout << "Ingrese una opcion. "<<endl<<endl;
    cout << "1-Generar datos de prueba de clientes."<<endl<<endl;
    cout << "2-Generar archivo de lote de incidentes."<<endl<<endl;
    cin >> i;
    switch(i)
    {
    case '1':
        datos_prueba()?cout<<C:cout<<E;
        break;
    case '2':
        inc_prueba()?cout<<C:cout<<E;
        break;
    }
}

char menu(asegurado v[]){

    char opcion;

    cout << endl;
    cout<<"*****************************************************************************"<<endl<<endl;
    cout<<"Seleccione una opcion: "<<endl<<endl;
    cout<<"1 - Levantar Asegurados. "<<endl<<endl;
    cout<<"2 - Cargar nueva poliza. "<<endl<<endl;
    cout<<"3 - Desactivar una poliza existente. "<<endl<<endl;
    cout<<"4 - Buscar Registro. "<<endl<<endl;
    cout<<"5 - Ordenar Registros."<<endl<<endl;
    cout<<"6 - Procesar un lote de incidentes. "<<endl<<endl;
    cout<<"7 - Finalizar jornada. "<<endl<<endl;
    cout<<"8 - Cargar datos de prueba."<<endl<<endl;
    cout<<"Presione ESC para salir"<<endl<<endl;
    cout<<"*****************************************************************************"<<endl<<endl;
    do
         opcion=getch();

    while (opcion !='1' && opcion !='2' && opcion !='3' && opcion !='4' && opcion !='5' && opcion !='6' && opcion !='7' && opcion !='8' && opcion !=27);

    switch(opcion)
    {
    case '1':
        LevantarAsegurados(v);
        break;
    case '2':
        cargarNuevaPoliza(v);
        break;
    case '3':
        desactivarPoliza(v);
        break;
    case '4':
        menu_buscar(v);
        break;
    case '5':
       menu_ordenar(v);
        break;
    case '6':
        ProcesarLote(v);
        break;
    case '7':
        FinalizarJornada(v);
        break;
    case '8':
        menu_prueba();
        break;
    }
    return opcion;
}

int main(){
    asegurado v[TAMANIO];

    inicializarVector(v);


    char out;

    do

        out = menu(v);
    while (out !=27);

    return 0;
}


