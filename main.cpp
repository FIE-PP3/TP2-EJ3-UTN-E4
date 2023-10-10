#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>
#include "ctime"
#include <string.h>
#include <iomanip>

using namespace std;

const char* const n = "\033[0m";
const char* const negrita = "\033[1m";
const char* const subrayado = "\033[4m";

const char* const naranja = "\033[38;5;208m";
const char* const rosa = "\033[38;5;200m";
const char* const rojo = "\033[31m";
const char* const verde =" \033[32m";
const char* const amarillo = "\033[33m";
const char* const azul = "\033[36m";
const char* const blanco = "\033[37m";
const char* const magenta = "\033[35m";




class BonoPresentismo {
public:
    float calcularBonoPresentismo(int diasAusente) {
        float bono = 100.0;

        if(diasAusente == 1){
            bono = 50;
        } else if(diasAusente > 1) {
            bono = 0;
        }

        return bono;
    }

    int ingresarDiasAusente(){
        int diasA;
        while (true) {
            cout<<"....................................................................."<<endl;
            cout <<amarillo<< "\n-Cantidad de dias ausentes del empleado: "<<n;
            cin >> diasA;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout <<rojo<< "\nPor favor, ingrese un numero valido." <<n<< endl;
            } else {
                break;
            }
        }
        return diasA;
    }
};



class BonoResultados {
public:
    float calcularBonoResultado(int tipoBono, float sueldoNeto) {
        // 1: 10% del sueldo neto
        // 2: $80 fijos
        // 3: nada
        float bono = 0;

        if(tipoBono == 1) {
            bono = 0.1f * sueldoNeto;
        } else if(tipoBono == 2) {
            bono = 80.0;
        }

        return bono;
    }

    int ingresarBonoResultados () {
        int tipoBonoR;

        while (true) {
            cout<<"....................................................................."<<endl;
            cout <<amarillo<< "\nBonos por rendimientos:\n"<<n<<endl;
            cout << "1 - 10 porciento sobre el neto\n2 - $80 fijos\n3 - Sin Bono\n\nRespuesta: ";
            cin >> tipoBonoR;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout <<rojo<<"\nPor favor, ingrese un numero valido." <<n<< endl;
            } else if (tipoBonoR < 1 || tipoBonoR > 3) {
                cout <<rojo<< "Opción no válida. Por favor, elija 1, 2 o 3." <<n<< endl;
            } else {
                cout<<azul<<"\n\nCredenciales cargadas correctamente."<<n<<endl;
                cout<<azul<<"Para visualizar recibo.   "<<n;
                break;
            }
        }

        return tipoBonoR;
    }
};



class Categoria {
private:
    string denominacionCategoria;
    float sueldoBase;
public:
    Categoria(string denominacionCategoria, float sueldoBase) {
        this->denominacionCategoria = denominacionCategoria;
        this->sueldoBase = sueldoBase;
    }

    string getDenominacionCategoria() {
        return this->denominacionCategoria;
    }

    float getSueldoBase() {
        return this->sueldoBase;
    }
};



class Persona {
private:
    string nombre;
    Categoria *categoriaTrabajador;
    float sueldo;
public:
    Persona(string nombre, Categoria *categoriaTrabajador) {
        this->nombre = nombre;
        this->categoriaTrabajador = categoriaTrabajador;
        this->sueldo = categoriaTrabajador->getSueldoBase();
    }

    void calcularSueldo(int diasAusente, int tipoBonoResultados, Persona *persona, int response) {             //PARA LA IMPRESION DEL RECIBO PODEMOS TRABAJAR ESTA FUNCION PARA QUE DEVUEVLA VALORES DE BONOS Y SUELDO, Y DESDE OTRO METODO USAMOS E IMPRIMIMOS.
        BonoPresentismo bp;
        BonoResultados br;

        float extraPresentismo = bp.calcularBonoPresentismo(bp.ingresarDiasAusente());
        float extraResultados = br.calcularBonoResultado(br.ingresarBonoResultados(), categoriaTrabajador->getSueldoBase());

        sueldo = categoriaTrabajador->getSueldoBase() + extraPresentismo + extraResultados;
        system("Pause");
        impresion_sueldo(persona->getNombre(),persona->getCategoriaTrabajador()->getDenominacionCategoria(),persona->getCategoriaTrabajador()->getSueldoBase(),extraPresentismo,extraResultados,sueldo);
    }

    string getNombre() {
        return this->nombre;
    }

    Categoria* getCategoriaTrabajador() {
        return this->categoriaTrabajador;
    }


    void impresion_sueldo(string name, string cargo, int neto, int bp, int br, int bruto){         //TOMAR PARAMETROS COMO NOMBRE, CARGO, BONO 1, BONO 2, NETO, SUELDO TOTAL.
        hash<string> hashFun;
        size_t id = hashFun(name)%1000;

    void impresion_sueldo(string name, string cargo, int neto, int bp, int br, int bruto){         //CLASE QUE TOMA LOS PARAMETROS DEL USUARIO CREADO Y GENERA LA IMPRESION DEL SUELDO.
        //FUNCION HASH QUE UTILIZA EL NOMBRE DEL USER PARA GENERAR UN ID ALEATORIO Y ASIGNARSELO AL RECIBO
        hash<string> hashFun;
        size_t id = hashFun(name)%1000;
        //OBTENGO FECHA ACTUAL PARA ADJUNTAR EN EL RECIBO
        time_t fechaActual = time(0);
        char* datetime = ctime(&fechaActual);

        system("cls");cout<<naranja;
        cout<<setw(40)<<"************************************************************************************************************************"<<n<<endl;
        gotoxy(50,1);cout<<rojo<<negrita<<subrayado<<"RECIBO DE SUELDO"<<n<<endl;

        gotoxy(14,3);cout<<azul<<"Empleado: "<<n<<name<<endl;
        gotoxy(17,4);cout<<azul<<"Cargo: "<<n<<cargo<<endl;
        gotoxy(70,3);cout<<azul<<"Fecha de emision: "<<n<<datetime<<endl;
        gotoxy(70,4);cout<<azul<<"Numero de recibo: "<<n<<id<<naranja<<endl;
        cout<<setw(40)<<"************************************************************************************************************************"<<n<<endl;
        gotoxy(41,6); cout<<verde<<"Sueldo Neto:   "<<n<<"$"<<neto<<endl<<endl;
        gotoxy(47,8);cout<<verde<<"Bonos: "<<n<<endl;
        gotoxy(37,9);cout<<verde<<"Por Presentismo:   "<<n<<"$"<<bp<<endl;
        gotoxy(36,10);cout<<verde<<"Por Rendimientos:   "<<n<<"$"<<br<<endl;
        gotoxy(33,11);cout<<naranja<<negrita<<"-------------------------------------"<<n<<endl;
        gotoxy(41,12);cout<<magenta<<"Sueldo Bruto:   "<<n<<"$"<<bruto<<endl<<naranja<<endl;
        cout<<setw(40)<<"************************************************************************************************************************"<<n<<endl<<endl;

        system("Pause");
    }

    static void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
};





 class Interfaz {

class Interfaz {

public:
    static void mostrarPantallaDeCarga() {
        system("cls");
        cout<<setw(40)<<"************************************************************************************************************************"<<n;
        gotoxy(45,1);cout<<rojo<<negrita<<subrayado<<"SISTEMA LIQUIDACION SUELDOS:"<<n<<endl;
        cout<<setw(40)<<"************************************************************************************************************************"<<n<<endl;
        gotoxy(50,3);cout <<amarillo<< "Cargando" <<n<< endl;
        for (int i = 58; i < 64; i++) {
            gotoxy(i,3);cout <<amarillo<< "." << " "<<n;
            this_thread::sleep_for(std::chrono::seconds(1)); // Pausa durante 1 segundo
        }

        gotoxy(40,5);

        system("pause");

        cout << endl;
        system("cls");
    }

    static void gotoxy(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    static void Menu_Principal(){


        while(true){
            system("cls");
            Interfaz::mostrarPantallaDeCarga();
        system("cls");
        Interfaz::mostrarPantallaDeCarga();

        while(true){
            system("cls");
            int respuesta;
            cout <<azul<< "\n------------------------------------------------------------------------------------------------------------------------"<<n<<endl;
            gotoxy(45,2);cout<<verde<<negrita<<subrayado<<"CATEGORIAS DEL SISTEMA"<<n<<endl;
            cout <<azul<< "------------------------------------------------------------------------------------------------------------------------"<<n<<endl;
            gotoxy(40,5);cout<<azul<<"Presione 0 para salir."<<n;
            gotoxy(1,5);cout<<amarillo<<"Ingrese categoria del usuario: "<<n<<"\n\n1 - Gerente \n2 - Cadete\n\n\nRespuesta: "<<n;
            cin>>respuesta;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar la entrada no válida
                cout << "\nPor favor, ingrese un numero" << endl;
                continue;
            }


            if (respuesta==1){

                system("cls");
                cout <<azul<< "\n------------------------------------------------------------------------------------------------------------------------"<<n<<endl;
                gotoxy(45,2);cout<<verde<<negrita<<subrayado<<"GESTOR DE CREDENCIALES DE USUARIO"<<n<<endl;
                cout <<azul<< "------------------------------------------------------------------------------------------------------------------------"<<n<<endl;
                int diasA, tipoBonoR;
                float sueldo;
                string nombre;
                cout<<amarillo<<"\n-Ingrese nombre del empleado: "<<n;
                cin>>nombre;

                Categoria *gerente = new Categoria("Gerente", 1500);
                Persona persona(nombre, gerente);


                persona.calcularSueldo(diasA, tipoBonoR, &persona, respuesta);
            }

            else if (respuesta==2){

                system("cls");
                cout <<azul<< "\n------------------------------------------------------------------------------------------------------------------------"<<n<<endl;
                gotoxy(45,2);cout<<verde<<negrita<<subrayado<<"GESTOR DE CREDENCIALES DE USUARIO"<<n<<endl;
                cout <<azul<< "------------------------------------------------------------------------------------------------------------------------"<<n<<endl;
                int diasA, tipoBonoR;
                float sueldo;
                string nombre;
                cout<<amarillo<<"\n-Ingrese nombre del empleado: "<<n;
                cin>>nombre;

                Categoria *cadete = new Categoria("Cadete", 1000);
                Persona persona(nombre, cadete);

                persona.calcularSueldo(diasA, tipoBonoR, &persona, respuesta);
            }

            else if(respuesta==0){
                break;
            }

            else{
                cout<<"Numero no valido\n";
            }

            system("cls");
        }
    }
};





int main() {
    Interfaz::Menu_Principal();
    return 0;
}