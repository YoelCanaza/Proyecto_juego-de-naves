#include <iostream>
#include <stdio.h>
// se usa la librer�a stdio.h de c nos pide el formato de las variables que queremos imprimir
//eso nos permitir� usar m�s caracteres para imprimir nuestra nave en pantalla
#include <windows.h>
/* La biblioteca windows.h incluye la funci�n SetConsoleCursorPosition(), que nos permite darle una posici�n al cursor,
    ya teniendo esa posici�n podremos mandar a imprimir lo que queramos en dichas coordenadas
*/
#include <conio.h>
/*La biblioteca conio.h nos facilitar� detectar si se van presionando las teclas*/
#include <stdlib.h> // para poder usar la funci�n rand()
#include<list>
#include <cstdlib> // necesitamos la cabecera cstdlib para usar system

using namespace std;

/*La siguiente funci�n nos permitir� darle nuevas coordenadas al cursor poniendo las coordenadas como par�metros, para
luego imprimir en esas coordenadas*/
void gotoxy(int cordx, int cordy) {
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD posicion;
    posicion.X = cordx;
    posicion.Y = cordy;

    // la siguiente funci�n nos permite asignarle una nueva posici�n al cursor
    SetConsoleCursorPosition(consola, posicion);
}

void ocultarCursor(){
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO aparienciaCursor;
    aparienciaCursor.dwSize = 50;
    aparienciaCursor.bVisible = FALSE;

    // La siguiente funci�n nos permite cambiar las caracter�sticas del cursor que se muestra en pantalla
    SetConsoleCursorInfo(consola, &aparienciaCursor);
}

void bordes() {
    for (int i = 2; i < 118; i++) {
        gotoxy(i, 2);
        cout << "_";
        gotoxy(i, 28);
        cout << "_";
    }

    for (int i = 3; i < 29; i++) {
        gotoxy(2, i);
        cout << "|";
        gotoxy(117, i);
        cout << "|";
    }
}

class NAVE {
    int cordx, cordy; // atributos privados
    int salud;
    int vidas;
public:
    NAVE(int _cordx, int _cordy, int _salud, int _vidas) {
        cordx = _cordx;
        cordy = _cordy;
        salud = _salud;
        vidas = _vidas;
    }

    void restSalud(){salud -= 1;}
    void aumentarSalud() {salud += 1;}
    int CORDX() {return cordx;}
    int CORDY() {return cordy;}
    int vid() {return vidas;}

    void pintar();
    void borrar();
    void mover();
    void drawSalud();
    void explotar();
};

void NAVE::pintar() { // el operador :: nos permite acceder a los m�todos(funciones) de la clase
    gotoxy(cordx, cordy);
    cout << " /A\\ ";
    gotoxy(cordx, cordy + 1);
    cout << "/. .\\";
    gotoxy(cordx, cordy + 2);
    cout << "\\_O_/";
}

void NAVE::borrar() {
    gotoxy(cordx, cordy);
    cout << "     ";
    gotoxy(cordx, cordy + 1);
    cout << "     ";
    gotoxy(cordx, cordy + 2);
    cout << "     ";
}

void NAVE::mover() {
        if ( kbhit() ) {
        // la funci�n kbhit() detecta si se ha presionado una tecla
            char tecla = getch();
            /* la funci�n getch() guarda la letra que se presion�, entonces le estamos pasando el valor de
             la tecla que se presion� a la variable de nombre tecla */

            borrar();

            /* Cada una de las teclas est�n asociadas con un n�mero que podemos usar para referirnos a ellas,
            y cuando el compilardor se ve en la situaci�n de comparar algo que deber�a ser un caracter con un n�mero entero
            toma el n�mero como un c�digo que hace referencia a un caracter
            en el caso de las flechas arriba, abajo, izquierda y derecha, los n�meros son: 72, 80, 75 y 77 respectivamente */
            if (tecla == 75) {
                cordx -= 1;
                if (cordx < 3) {
                    cordx +=1;
                }
            } else if (tecla == 77) {
                cordx += 1;
                if (cordx + 4 > 116) {
                    cordx -=1;
                }
            } else if (tecla == 72) {
                cordy -= 1;
                if (cordy < 3) {
                    cordy += 1;
                }
            } else if (tecla == 80) {
                cordy += 1;
                if (cordy + 2 > 27) {
                    cordy -= 1;
                }
            }
        pintar();
        drawSalud();
        }
}

void NAVE::drawSalud() {
    gotoxy(88, 1);
    cout << "VIDAS: " << vidas;
    gotoxy(104, 1);
    cout << "Salud:";
    gotoxy(110, 1);
    cout << "      ";
    for (int i = 0; i < salud; i++) {
        gotoxy(110 + i, 1);
        char corazon = 3;
        cout << corazon;
    }
}

void NAVE::explotar() {
    if (salud == 0) {
        borrar();
        gotoxy(cordx, cordy);
        cout << "  *  ";
        gotoxy(cordx, cordy + 1);
        cout << " *** ";
        gotoxy(cordx, cordy + 2);
        cout << "  *  ";
        Sleep(200);

        borrar();

        gotoxy(cordx, cordy);
        cout << "* * *";
        gotoxy(cordx, cordy + 1);
        cout << " *** ";
        gotoxy(cordx, cordy + 2);
        cout << "* * *";
        Sleep(200);

        borrar();
        vidas -= 1;
        salud = 3;
        drawSalud();

        pintar();
    }
}

class ASTEROIDE{
    int cordx, cordy;
public:
    ASTEROIDE(int _cordx, int _cordy) {
        cordx = _cordx;
        cordy = _cordy;
    }
    int CORDX(){return cordx;}
    int CORDY(){return cordy;}
    void pintar() {
        gotoxy(cordx, cordy); cout << "O";
    }
    void pintarCura() {
        char botiquin = 3;
        gotoxy(cordx, cordy); cout << botiquin;
    }
    void mover() {
        gotoxy(cordx, cordy); cout << " ";
        cordy += 1;
        if (cordy > 27) {
            cordx = (rand()%110) + 5;
            cordy = 4;
        }
        pintar();

    }
    void movCura() {
        gotoxy(cordx, cordy); cout << " ";
        cordy += 1;
        if (cordy > 27) {
            cordx = (rand()%110) + 5;
            cordy = 4;
        }
        pintarCura();
    }
    void colision(class NAVE &voyager) {
        if(cordx >= voyager.CORDX() && cordx < voyager.CORDX()+5 && cordy >= voyager.CORDY() &&cordy <= voyager.CORDY()+ 2) {
            voyager.restSalud();
            voyager.pintar();
            voyager.drawSalud();
            cordx = (rand()%110) + 5;
            cordy = 4;
        }
    }
    void cura(class NAVE &voyager) {
        if(cordx >= voyager.CORDX() && cordx < voyager.CORDX()+5 && cordy >= voyager.CORDY() &&cordy <= voyager.CORDY()+ 2) {
            voyager.aumentarSalud();
            voyager.pintar();
            voyager.drawSalud();
            cordx = (rand()%110) + 5;
            cordy = 4;
        }
    }
};

class DISPARO {

    int cordx, cordy;
public:
    DISPARO(int _cordx, int _cordy) {
        cordx = _cordx;
        cordy = _cordy;
    }
    int CORDX(){return cordx;}
    int CORDY(){return cordy;}

    void mover(){
        gotoxy(cordx, cordy); cout << " ";

        cordy -= 1;

        gotoxy(cordx, cordy); cout << "*";
    }

    bool fuera() {
        if(cordy == 3) {
            return true;
        } else {
            return false;
        }
    }
};

int main()
{
    ocultarCursor();
    bordes();
    NAVE voyager(47, 20, 3, 3);
    voyager.pintar();
    voyager.drawSalud();


    list<ASTEROIDE*> A;
    list<ASTEROIDE*>::iterator itAST;
    for(int i=0; i < 5; i++) {
        A.push_back(new ASTEROIDE(rand()%110 +5, rand()%5 + 4) );
    }

    ASTEROIDE cura1(60, 4);

    list<DISPARO*> D;
    list<DISPARO*>::iterator it;

    bool gameOver = false;
    bool cerrarJuego = false;

    int score= 0;
    bool win = false;


    while (!gameOver) {

        gotoxy(3,1); cout << "SCORE: " << score;

        if (kbhit()) {
            char tecla = getch();
            if (tecla == 'j' || tecla == 'J') {
                D.push_back(new DISPARO(voyager.CORDX()+2, voyager.CORDY()-1));
            }
        }
        for (it=D.begin(); it != D.end(); it++) {
            (*it)-> mover();
            if((*it)->fuera() ) {
                gotoxy((*it)->CORDX(), (*it)->CORDY()); cout << " ";
                delete(*it);
                it = D.erase(it);

            }
        }

        for(itAST = A.begin(); itAST != A.end(); itAST++) {
            (*itAST)->mover();
            (*itAST)->colision(voyager);
        }
        cura1.movCura(); cura1.cura(voyager);

        for(itAST = A.begin(); itAST != A.end(); itAST++) {
            for (it=D.begin(); it != D.end(); it++) {
                if( (*itAST)->CORDX() == (*it)->CORDX() && ( (*itAST)->CORDY() + 1 == (*it)->CORDY() || (*itAST)->CORDY() == (*it)->CORDY() )) {
                    gotoxy((*it)->CORDX(), (*it)->CORDY()); cout << " ";
                    delete(*it);
                    it = D.erase(it);

                    A.push_back(new ASTEROIDE(rand()%110 +5, 5) );
                    gotoxy((*itAST)->CORDX(), (*itAST)->CORDY()); cout << " ";
                    delete(*itAST);
                    itAST = A.erase(itAST);

                    score += 5;
                }
            }
        }

        if(voyager.vid()==0) {
            gameOver = true;
        }
        if(score==20){
            win = true;
            gameOver = true;
        }

        voyager.explotar();
        voyager.mover();
        Sleep(40);
        // la funci�n sleep(30) detiene la ejecuci�n del programa por 30 milisegudnos cuando se llega a esta sentencia
        //Eso lo hacemos con el fin de no saturar el procesador
    }
    if(win) {
        system("cls");// limpia la pantalla en Windows. Llamar a la funci�n system es
        //una mala pr�ctica ya que puede ser inseguro en algunos casos
        cout << "                           *     .--." << endl;
        cout << "                                / /  `" << endl;
        cout << "               +               | |" << endl;
        cout << "                      '         \\ \\__," << endl;
        cout << "                  *          +   '--'  *" << endl;
        cout << "                      +   /\\" << endl;
        cout << "         +              .'  '.   *" << endl;
        cout << "                *      /======\\      +" << endl;
        cout << "                      ;:.  _   ;" << endl;
        cout << "                      |:. (_)  |" << endl;
        cout << "                      |:.  _   |" << endl;
        cout << "            +         |:. (_)  |          *" << endl;
        cout << "                      ;:.      ;" << endl;
        cout << "                    .' \\:.    / `." << endl;
        cout << "                   / .-'':._.'`-. \\" << endl;
        cout << "                   I    /||\\    I" << endl;
        cout << "   	        FELICIDADES, HAS GANADO" << endl;

        Sleep(5000);
    } else{
        system("cls");
        cout << "     .    " << endl;
        cout << "    / \\   " << endl;
        cout << "   /   \\  " << endl;
        cout << "  /     \\ " << endl;
        cout << " /       \\" << endl;
        cout << "/   HAZ   \\" << endl;
        cout << "\\PERDIDO  /" << endl;
        cout << " \\       / " << endl;
        cout << "  \\     /  " << endl;
        cout << "   \\   /   " << endl;
        cout << "    \\ /    " << endl;
        cout << "     v     " << endl;

        Sleep(5000);
    }

    return 0;
}
