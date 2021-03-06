//Autor: Mauricio Cortes
//Fecha: 15/11/2016
//Version 0.1
//Contacto: abmaury97@hotmail.com

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>
#define M 8 // Renglones
#define N 8 // Columnas
#define Bombas 10

using namespace std;
int iIntentos=0;

void InicializarMatrices(int iMatBuscaminas[M][N], char iMatJugador[M][N], bool iMatRecorridos[M][N])
{
    for(int i=0; i<M; i++)
        for(int j=0; j<N; j++)
            iMatBuscaminas[i][j] = 0;
    for(int i=0; i<M; i++)
        for(int j=0; j<N; j++)
            iMatJugador[i][j] = '-';
    for(int i=0; i<M; i++)
        for(int j=0; j<N; j++)
            iMatRecorridos[i][j] = false;
}

void SumarAlrededor(int iMatBuscaminas[M][N], int iRandomRow, int iRandomCol)
{
    for(int i = iRandomRow-1; i <= iRandomRow+1; i++)
        for(int j = iRandomCol-1; j <= iRandomCol+1; j++)
            if(i >= 0 && i < M && j >= 0 && j < N)
                if(iMatBuscaminas[i][j] != -1)
                    iMatBuscaminas[i][j] += 1;
}

void GenerarMinasRandom(int iMatBuscaminas[M][N])
{
    srand(time(NULL));
    int iRandomRow, iRandomCol;
    int iMinas = Bombas;
    while(iMinas>0)
    {
        iRandomRow = rand()%M; // Rango de 0 a 7
        iRandomCol = rand()%N; // Rango de 0 a 7
        if(iMatBuscaminas[iRandomRow][iRandomCol] == 0) // Verificar que no haya una mina ya en esa posicion
        {
            iMatBuscaminas[iRandomRow][iRandomCol] = -1; //Agrega la mina a la matriz
            SumarAlrededor(iMatBuscaminas, iRandomRow, iRandomCol); // Suma 1 a las ocho casillas alrededor de la mina
            iMinas--;
        }
    }
}

template<typename T>
void ImprimirMatriz(T iMat[M][N])
{
    string linea="--", numerosArriba=" X |    ";
    for(int i=0; i<N; i++)
        linea += "--------";

    cout << "                             TABLERO" << endl;
    cout << linea << endl;
    cout << numerosArriba;
    for(int i=1; i<=N; i++)
        cout << i << "       ";
    cout << endl << linea << endl;
    for(int i=0; i<M; i++)
    {
        cout << " " << i+1 << " |    ";
        for(int j=0; j<N; j++)
            cout << iMat[i][j] << "\t";
        cout << endl << endl;
    }
}

void Ataque(char iMatJugador[M][N], int iMatBuscaminas[M][N], bool iRecorridos[M][N], int &iIntentos, int iRenAtaque, int iColAtaque)
{
    if(iRenAtaque>=0 && iRenAtaque<M && iColAtaque>=0 && iColAtaque<N && iRecorridos[iRenAtaque][iColAtaque] == false)
    {
        if(iMatBuscaminas[iRenAtaque][iColAtaque] == 0)
        {
            iMatJugador[iRenAtaque][iColAtaque] = ' ';//opcional con el cambio
            iIntentos++;
            iRecorridos[iRenAtaque][iColAtaque] = true;

            for(int i = iRenAtaque-1; i <= iRenAtaque+1; i++)
                for(int j = iColAtaque-1; j <= iColAtaque+1; j++)
                    if(i >= 0 && i < M && j >= 0 && j < N)
                        Ataque(iMatJugador, iMatBuscaminas, iRecorridos, iIntentos, i, j);
        }
        else
        {
            iMatJugador[iRenAtaque][iColAtaque] = iMatBuscaminas[iRenAtaque][iColAtaque] + '0';
            iIntentos++;
            iRecorridos[iRenAtaque][iColAtaque] = true;
        }
    }
}

void Marcar(char iMatJugador[M][N], bool iRecorridos[M][N], int iRenMarca, int iColMarca)
{
    if(iRecorridos[iRenMarca][iColMarca] == false)
    {
        if(iMatJugador[iRenMarca][iColMarca] == '?')
            iMatJugador[iRenMarca][iColMarca] = '-';
        else
            iMatJugador[iRenMarca][iColMarca] = '?';
    }
    system("cls");
}

void MostrarSolucion(char iMatJugador[M][N], int iMatBuscaminas[M][N], int iRen, int iCol, string sNombreJugador, int iIntentos)
{
    iMatJugador[iRen][iCol] = 'X';
    ImprimirMatriz(iMatJugador);
    cout << endl << endl;
    cout << "Perdiste " << sNombreJugador << " en " << iIntentos << " intentos." << endl << endl;
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(iMatBuscaminas[i][j] == -1)
                iMatJugador[i][j] = 'X';
           // else if(iMatBuscaminas[i][j] == 0)
             //   iMatJugador[i][j] = ' ';
            //else
              //  iMatJugador[i][j] = iMatBuscaminas[i][j] + '0';
        }
    }
    cout << "SOLUCION" << endl << endl;
    ImprimirMatriz(iMatJugador);
}

void Juego()
{
    string sNombreJugador;
    int iPassword = 12345;
    int iMatBuscaminas[M][N];
    char iMatJugador[M][N];
    int iRenAtaque, iColAtaque, iRenMarca, iColMarca;
    char cDecision = 'X', cMovimiento;
    bool bSalir = true, iRecorridos[M][N];;

    InicializarMatrices(iMatBuscaminas, iMatJugador, iRecorridos);
    GenerarMinasRandom(iMatBuscaminas);

    cout << "Bienvenido al juego BUSCAMINAS!" << endl << endl;
    cout << "Nombre del jugador:" << endl;
    cin >> sNombreJugador;
    system("cls");

    while(bSalir)
    {
        if(cDecision == 'S')
        {
            InicializarMatrices(iMatBuscaminas, iMatJugador, iRecorridos);
            GenerarMinasRandom(iMatBuscaminas);
            iIntentos = 0;
            cDecision = 'X';
            system("cls");//Limpiar consola
        }
        ImprimirMatriz(iMatJugador);
        cout << endl << endl;
        if(iIntentos == (M*N)-Bombas) //64 casillas - 10 bombas = todas las casillas visitadas
        {
            cout << endl << "Ganaste " << sNombreJugador << " en " << iIntentos << " intentos." << endl << endl;
            do{
                cout << "Deseas jugar otra vez? (S/N)" << endl;
                cin >> cDecision;
            }while(cDecision != 'N' && cDecision != 'S');
        }
        else
        {
            do{
            cout << "Quieres destapar o marcar? (D/M)" << endl;
            cin >> cMovimiento;
            }while(cMovimiento != 'D' && cMovimiento != 'M');
            if(cMovimiento == 'M')
            {
                do{
                    cout << "Renglon: ";
                    cin >> iRenMarca;
                    if(iRenMarca == iPassword)
                    {
                        system("cls");
                        ImprimirMatriz(iMatBuscaminas);
                    }
                }while(iRenMarca < 1 || iRenMarca > M);
                do{
                    cout << "Columna: ";
                    cin >> iColMarca;
                    if(iColMarca == iPassword)
                    {
                        system("cls");
                        ImprimirMatriz(iMatBuscaminas);
                    }
                }while(iColMarca < 1 || iColMarca > N);
                iRenMarca--;
                iColMarca--;
                Marcar(iMatJugador, iRecorridos, iRenMarca, iColMarca);//Marcar o desmarcar casilla
                if(iRecorridos[iRenMarca][iColMarca] == true)
                    cout << endl << "No puedes marcar o desmarcar una casilla visitada." << endl << endl;
            }
            else
            {
                do{
                    cout << "Renglon: ";
                    cin >> iRenAtaque;
                    if(iRenAtaque == iPassword)
                    {
                        system("cls");
                        ImprimirMatriz(iMatBuscaminas);
                    }
                }while(iRenAtaque < 1 || iRenAtaque > M);
                do{
                    cout << "Columna: ";
                    cin >> iColAtaque;
                    if(iColAtaque == iPassword)
                    {
                        system("cls");
                        ImprimirMatriz(iMatBuscaminas);
                    }
                }while(iColAtaque < 1 || iColAtaque > N);

                iRenAtaque--;//Se resta para que sea en numeros de computadora de la matriz
                iColAtaque--;
                system("cls");//Limpiar consola
                if(iRecorridos[iRenAtaque][iColAtaque] == true)
                    cout << endl << "No puedes destapar una casilla destapada." << endl << endl;
                else
                {
                    if(iMatBuscaminas[iRenAtaque][iColAtaque] == -1)//En caso de que ataque una mina(perdiste)
                    {
                        iIntentos++;
                        iRecorridos[iRenAtaque][iColAtaque] = true;
                        MostrarSolucion(iMatJugador, iMatBuscaminas, iRenAtaque, iColAtaque, sNombreJugador, iIntentos);
                        do{
                            cout << "Deseas jugar otra vez? (S/N)" << endl;
                            cin >> cDecision;
                        }while(cDecision != 'N' && cDecision != 'S');
                    }
                    else // Desplegar numeros o ceros recursivamente
                        Ataque(iMatJugador, iMatBuscaminas, iRecorridos, iIntentos, iRenAtaque, iColAtaque);
                }
            }
        }
        if(cDecision == 'N')//Salir del juego
        {
            bSalir = false;
            system("cls");
        }
    }
}

void Informacion()
{
    string sBack = "";
    while(sBack != "back")
    {
        cout << "Bienvenido a la informacion para jugar este buscaminas." << endl << endl;
        cout << "1. Para ver la solucion del juego teclea el password cuanto te pide renglon o columna." << endl;
        cout << "2. Los - en el tablero son casillas que aun no visitas." << endl;
        cout << "3. Las X significan MINAS." << endl;
        cout << "4. Los ? significan una casilla marcada." << endl;
        cout << "5. Si eliges marcar una casilla ya marcada, se desmarca." << endl << endl;
        cout << "Teclea 'back' para regresar al menu..." << endl;
        cin >> sBack;
        system("cls");
    }
}

void Buscaminas()
{
    int iBuscaminas = 0;
    while(iBuscaminas != 3)
    {
        do{
            cout << "1. Ir directo al juego" << endl;
            cout << "2. Ver informacion del juego" << endl;
            cout << "3. Salir" << endl;
            cin >> iBuscaminas;
            system("cls");
        }while(iBuscaminas > 3 || iBuscaminas < 1);

        switch(iBuscaminas)
        {
            case 1: Juego();
                break;
            case 2: Informacion();
                break;
        }
    }
}

int main()
{
    Buscaminas();
    return 0;
}
