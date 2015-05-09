#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include <ctime>
#include <math.h>
#include <cmath>
#include <time.h>
using namespace std;


//para leer archivo de texto

ifstream File;
string FileRead;

//Timer para LRU

int marcosrealtimestamps[256] = {-1}; //(para calcular tiempo en el que se modifico)
int cputime = 0;

//variables que manejan marcos

int marcosreal[256] = {-1}; //(numero de proceso que utiliza el marco)
int marcosrealmodificado[256] = {0}; //(0 o 1, modificado o no)
int marcosvirtual[512] = {-1}; //(apunta al proceso del marco real que tenia la memoria real)
int cantMarcos = 0;


void cargarProceso()
{
//Formato (P n p)
double n = 0;
int p = 0;
int residuo = 0; //utilizado para saber cuantos marcos de paginaci�n hay que reemplazar cuando se llene la memoria
int lleno = 0; // cuando se pase de 256 paginas/marcos, este estara arriba de 1


//leer n
File>>FileRead;
istringstream (FileRead) >>n;

//leer p
File>>FileRead;
istringstream (FileRead) >>p;

//Debug de direcciones
//cout << "Proceso: " << p << " Direcciones: " << n << endl;

//Empezar a meter datos

int paginas = cantMarcos + ceil (n/8);
lleno = paginas/256;
residuo = paginas % 256;

int ultimoMarco = 0;

//Si hay espacio
if(lleno == 0)
{
    ultimoMarco = residuo + cantMarcos - 1;
    for(int i = cantMarcos; i < ultimoMarco; i++)
    {marcosrealtimestamps[i] = cputime;
    marcosreal[i] = p;
    }
    cantMarcos += residuo;

}
else
{
    //checar si quedan espacios libres
    int faltantes;
    if (cantMarcos < 256)
    {
        ultimoMarco = 256;
        int restanteMarcos = 255-cantMarcos;
        for(int i = cantMarcos; i < ultimoMarco; i++)
        {
          marcosrealtimestamps[i] = cputime;
          marcosreal[i] = p;

        }
        cantMarcos += residuo;
    }
}

cputime++;


//Ver si se superaron los 256 marcos con texto
cout << "Lleno: " << lleno << " Paginas: " << residuo << " hecho por el proceso: " << marcosreal[ultimoMarco-1]<< " tiempo entrada: " << marcosrealtimestamps[ultimoMarco-1] << endl;

}

int main()
{
    //Cargar archivo de texto
    File.open("texto.txt");
    while (!File.eof()) {

        File>>FileRead; //agarra cada caracter separado por un espacio.

        if(FileRead == "P" || FileRead == "p"){cargarProceso();}
        //else if(FileRead == "A" || FileRead == "a"){A();}
        //else if(FileRead == "L" || FileRead == "l"){L();}
        //else if(FileRead == "E" || FileRead == "e"){E();}
        //else if(FileRead == "F" || FileRead == "f"){F();}
        else{}//cout<<FileRead<<endl;}

}//while
    File.close();
    cout << "Hello world!" << endl;
    return 0;
}
