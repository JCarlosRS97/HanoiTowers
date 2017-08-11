#include <iostream>
#include <cstring>
#define TAM 4
#define TAMSOLS 3
#define TAMJUGADAS 1000
using namespace std;

/*
respuestas[TAMSOLS=3]
para mover: disco*10+dst

*/

int getArriba(int lista[], int torre); // si no hay nada en la torre devuelve TAM+1
bool fin(int lista[]);
void inicializarLista(int lista[], int n);
void moverDisco(int lista[], int disco, int dst);
void posiblesJugadas(int lista[], int respuestas[]); // no validas devuelve -1
float valorarJugada(int lista[], int jugada, int ant1[], int ant2[]);//si repite pos devuelve 2
																	//A valor mas alto menos adecuado
void imprimir(int lista[], int respuestas[], float valoraciones[]);


int getArriba(int lista[], int torre) {
	int pos = 0;
	while (pos < TAM && lista[pos] != torre) {
		pos++;
	}
	if (lista[pos] != torre) {
		return TAM + 1;
	}
	return pos + 1;
}

bool fin(int lista[]) {
	bool fin = true;
	for (int i = 0; i < TAM; i++) {
		if (lista[i] != 3) {
			fin = false;
		}
	}
	return fin;
}

void inicializarLista(int lista[], int n) {
	for (int i = 0; i < n; i++) {
		lista[i] = 1;
	}
}

void moverDisco(int lista[], int disco, int dst) {
	lista[disco - 1] = dst;
}

void imprimir(int lista[], int respuesta[], float valoraciones[], int mov) {
	cout << "Torre 1: ";
	for (int i = 0; i < TAM; i++) {
		if (lista[i] == 1) {
			cout << i + 1 << " ";
		}
	}
	cout << endl;
	cout << "Torre 2: ";
	for (int i = 0; i < TAM; i++) {
		if (lista[i] == 2) {
			cout << i + 1 << " ";
		}
	}
	cout << endl;
	cout << "Torre 3: ";
	for (int i = 0; i < TAM; i++) {
		if (lista[i] == 3) {
			cout << i + 1 << " ";
		}
	}
	cout << endl;

	cout << "Posibilidades :" << endl;
	if (respuesta[0] > 0)
		cout << "1- " << respuesta[0] << ": " << valoraciones[0] << endl;
	if (respuesta[1] > 0)
		cout << "2- " << respuesta[1] << ": " << valoraciones[1] << endl;
	if (respuesta[2] > 0)
		cout << "3- " << respuesta[2] << ": " << valoraciones[2] << endl;
	cout << "Siguiente movimiento: " << mov << endl;
}

void posiblesJugadas(int lista[], int respuesta[]) {
	int disc1 = getArriba(lista, 1);
	int disc2 = getArriba(lista, 2);
	int disc3 = getArriba(lista, 3);
	for (int i = 0; i < TAMSOLS; i++) {
		respuesta[i] = -1;
	}
	int n = 0;
	if (disc1 < disc2) {
		respuesta[n] = disc1 * 10 + 2;
		n++;
	}
	if (disc1 < disc3) {
		respuesta[n] = disc1 * 10 + 3;
		n++;
	}

	if (disc2 < disc1) {
		respuesta[n] = disc2 * 10 + 1;
		n++;
	}
	if (disc2 < disc3) {
		respuesta[n] = disc2 * 10 + 3;
		n++;
	}

	if (disc3 < disc1) {
		respuesta[n] = disc3 * 10 + 1;
		n++;
	}
	if (disc3 < disc2) {
		respuesta[n] = disc3 * 10 + 2;
		n++;
	}
}

float valorarJugada(int lista[], int jugada, int ant1[], int ant2[]) {
	int copialista[TAM];
	memcpy(copialista, lista, sizeof(int)*TAM);
	moverDisco(copialista, jugada / 10, jugada % 10);
	if (memcmp(copialista, ant1, sizeof(int) * 3) == 0 || memcmp(copialista, ant2, sizeof(int) * 3) == 0) {
		return 2;
	}
	float puntuacion = 0;
	for (int i = 0; i < TAM; i++) {
		if (copialista[i] == 1) {
			puntuacion += 1 / (float(i + 1));
		}
	}
	return puntuacion;
}
int main() {
	int lista[TAM], ant1[TAM], ant2[TAM];
	int respuesta[TAMSOLS];
	float valoraciones[TAMSOLS];
	int jugadas[TAMJUGADAS];
	int numJug = 0;
	int cont = 0;
	int indiceMejor;
	inicializarLista(lista, TAM);
	inicializarLista(ant1, TAM);
	inicializarLista(ant2, TAM);
	inicializarLista(jugadas, TAMJUGADAS);
	memset(valoraciones, 0, sizeof(float) * 3);
	memset(ant1, 0, sizeof(int) * 3);
	memset(ant2, 0, sizeof(int) * 3);
	while (!fin(lista)) {
		posiblesJugadas(lista, respuesta);
		cont = 0;
		indiceMejor = 0;
		while (cont < TAMSOLS && respuesta[cont] > 0) {
			valoraciones[cont] = valorarJugada(lista, respuesta[cont], ant1, ant2);
			if (valoraciones[indiceMejor] > valoraciones[cont]) {
				indiceMejor = cont;
			}
			cont++;
		}
		imprimir(lista, respuesta, valoraciones, respuesta[indiceMejor]);
		memcpy(ant2, ant1, sizeof(int)*TAM);
		memcpy(ant1, lista, sizeof(int)*TAM);
		moverDisco(lista, respuesta[indiceMejor] / 10, respuesta[indiceMejor] % 10);
		jugadas[numJug] = respuesta[indiceMejor];
	}

	return 0;
}