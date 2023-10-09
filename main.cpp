
#include <iostream>
#include <string>
#include <limits>

using namespace std;

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

    float calcularSueldo(int diasAusente, int tipoBonoResultados) {
        BonoPresentismo bp;
        BonoResultados br;

        float extraPresentismo = bp.calcularBonoPresentismo(diasAusente);
        float extraResultados = br.calcularBonoResultado(tipoBonoResultados, categoriaTrabajador->getSueldoBase());

        sueldo = categoriaTrabajador->getSueldoBase() + extraPresentismo + extraResultados;

        return sueldo;
    }

    string getNombre() {
        return this->nombre;
    }

    Categoria* getCategoriaTrabajador() {
        return this->categoriaTrabajador;
    }

};


int ingresarBonos(){
    int diasA, tipoBonoR;
    while (true) {
        cout << "\nIngrese cantidad de dias ausentes: ";
        cin >> diasA;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPor favor, ingrese un numero valido." << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "\nIngrese tipo de bono por resultados:\n";
        cout << "1 - 10 porciento sobre el neto\n2 - $80 fijos\n3 - nada\n\nRespuesta: ";
        cin >> tipoBonoR;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPor favor, ingrese un numero valido." << endl;
        } else if (tipoBonoR < 1 || tipoBonoR > 3) {
            cout << "Opción no válida. Por favor, elija 1, 2 o 3." << endl;
        } else {
            break;
        }
    }
    return diasA, tipoBonoR;
}

void menu(){
    int respuesta, diasA, tipoBonoR;
    float sueldo;
    string nombre;
    cout << "\n--------------------------------------------------------------" <<endl;
    cout<<"Bienvenido a calcular sueldos. "<<endl;
    cout << "--------------------------------------------------------------" <<endl;
    cout<<"Ingrese categoria del usuario:\n1 - Gerente \n2 - Cadete\n3 - Salir\n\nRespuesta:"<<" ";
    cin>>respuesta;
    while (respuesta!=3) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignorar la entrada no válida
            cout << "\nPor favor, ingrese un numero" << endl;
            continue;
        }
        if (respuesta == 1 || respuesta == 2){
        cout<<"\nIngrese nombre del empleado: ";
        cin>>nombre;}
        if (respuesta==1)
        {
            Categoria *gerente = new Categoria("Gerente", 1000);
            Persona persona(nombre, gerente);
            diasA, tipoBonoR = ingresarBonos();
            sueldo = persona.calcularSueldo(diasA, tipoBonoR);
            cout<<"\n"<<nombre<< " cobra  $" << sueldo << endl;

        }else if (respuesta==2){
            Categoria *cadete = new Categoria("Cadete", 1500);
            Persona persona(nombre, cadete);
            diasA, tipoBonoR = ingresarBonos();
            sueldo = persona.calcularSueldo(diasA, tipoBonoR);
            cout<<"\n"<<nombre<< " cobra  $" << sueldo << endl;
        }else if(respuesta==3){
            break;
        } else{
            cout<<"Numero no valido\n";
        }
        cout << "\n--------------------------------------------------------------" <<endl;
        cout<<"Bienvenido a calcular sueldos. "<<endl;
        cout << "--------------------------------------------------------------" <<endl;
        cout<<"Ingrese categoria del usuario:\n1 - Gerente \n2 - Cadete\n3 - Salir\n\nRespuesta:"<<" ";
        cin>>respuesta;
    }
};

int main() {

    menu ();

    return 0;
}

