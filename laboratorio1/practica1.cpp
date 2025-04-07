#include <iostream>
#include <thread>
using namespace std;
void EscribirMensaje()
{
    // funcion que ejuctara el hilo
    std::cout << "hola como estas .. ) " <<'\n';
}
int main ()
{
    // crea y planiofica  el hilo para ejecutar 
    std::thread hilo0(EscribirMensaje);
    hilo0.join();
    return 0;
}