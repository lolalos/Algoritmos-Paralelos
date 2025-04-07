#include <iostream>
#include <thread>
#include <string>
#include <Windows.h>
using namespace std;
void imprimemensaje(string palabra, long tiempo)
{
    for (int i=1; i <=100; i++)
    {
        cout << palabra << '\n';
        Sleep(tiempo); // pausa de un tiempo  espesifico

    }
}
int main ()
{
// crea y ejecuta el hilo  hilo0 e hilo 1
thread hilo0(imprimemensaje, "holacomoestas pepe",10);
thread hilo1(imprimemensaje, "hola juachos como estas",20);
getchar();
return 0;
}