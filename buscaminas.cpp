#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_FILAS = 30;
const int MAX_COLUMNAS = 30;
const int MINA = -1;

void generar_tablero(int tablero[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas, int minas) {
    int colocadas = 0;
    while (colocadas < minas) {
        int fi=rand()%filas;
        int co= rand()%columnas;
        if (tablero[fi][co]!= MINA) {
            tablero[fi][co]= MINA;
            colocadas++;
        }
    }
}


void contar_adyacentes(int tablero[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (tablero[i][j] == MINA) continue;
            int conteo=0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0&& ni <filas && nj >= 0 && nj< columnas &&tablero[ni][nj]==MINA)
                        conteo++;
                }
            }
            tablero[i][j]=conteo;
        }
    }
}


void mostrar_tablero(int tablero[MAX_FILAS][MAX_COLUMNAS], bool visible[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas) {
    cout<<"\n   ";
    for (int j = 0; j < columnas; ++j) cout<<j<<" ";
    cout<<"\n";

    for (int i = 0; i < filas; ++i) {
        cout<<i<<"  ";
        for (int j = 0; j < columnas; ++j) {
            if (visible[i][j]) {
                if (tablero[i][j] == MINA)
                    cout<<"* ";
                else
                    cout<<tablero[i][j]<<" ";
            } else {
                cout<<"- ";
            }
        }
        cout<<"\n";
    }
}


void destapar(int tablero[MAX_FILAS][MAX_COLUMNAS], bool visible[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas, int fi, int co) {
    if (fi < 0 || fi >= filas || co < 0 || co >= columnas || visible[fi][co])
        return;

    visible[fi][co]=true;

    if (tablero[fi][co] == 0) {
        for (int di = -1; di <= 1; ++di)
            for (int dj = -1; dj <= 1; ++dj)
                if (di != 0 || dj != 0)
                    destapar(tablero, visible, filas, columnas, fi + di, co + dj);
    }
}


bool victoria(int tablero[MAX_FILAS][MAX_COLUMNAS], bool visible[MAX_FILAS][MAX_COLUMNAS], int filas, int columnas) {
    for (int i = 0; i < filas; ++i)
        for (int j = 0; j < columnas; ++j)
            if (tablero[i][j] != MINA && !visible[i][j])
                return false;
    return true;
}


int main() {
    srand(time(NULL));
    int filas, columnas;

    cout<<"ingrese las dimensiones del tablero (filas columnas): ";
    cin>>filas>>columnas;

    int minas=columnas+ 1;

    int tablero[MAX_FILAS][MAX_COLUMNAS]={0};
    bool visible[MAX_FILAS][MAX_COLUMNAS]={false};

    generar_tablero(tablero, filas, columnas, minas);
    contar_adyacentes(tablero, filas, columnas);

       
    system("cls"); 

    bool gameover=false;

    while (!gameover) {
        mostrar_tablero(tablero, visible, filas, columnas);

        int fi, co;
        cout<<"\ningrese fila y columna ";
        cin>>fi>>co;

        if (fi < 0 || fi >= filas || co < 0 || co >= columnas) {
            cout<<"coordenadas invalidas\n";
            continue;
        }

        if (tablero[fi][co] == MINA) {
            cout<<"\nGAME OVER\n";
            for (int i = 0; i < filas; ++i)
                for (int j = 0; j < columnas; ++j)
                    visible[i][j] =true;
            mostrar_tablero(tablero, visible, filas, columnas);
            break;
        }

        destapar(tablero, visible, filas, columnas, fi, co);

        if (victoria(tablero, visible, filas, columnas)) {
            cout<<"\nfelicidades\n";
            mostrar_tablero(tablero, visible, filas, columnas);
            break;
        }

        system("cls");
    }

    
}


