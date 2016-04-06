// SG.2.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "iostream"
#include "random"
#include <cstdlib>
#include <time.h>

#include <fstream>

//#include "System.h"

using namespace std;

#include "GlobalVar.h"

long int neg = 0, pos = 0;
long int negS = 0, posS = 0;

//Local inclusions.
#include "generation.h"

//Deklarerade funktioner
void newSystem();
void writeToFile();


//Main
int main()
{
	int idSystem, idObject, idOrbit, i=0;
	srand(time(NULL));
	for (int n = 0; n < MAXSYSTEM * SYSTEMTOKEN; n++) { s[n] = -1; }
	newSystem();
	writeToFile();
	cout << "Neg: " << neg << ", Pos: " << pos << endl;
	cout << "NegS: " << negS << ", PosS: " << posS << endl;
	//system("pause");

   //*s[idSystem * 10000 + idObject * 1000 + idOrbit * 100];
	return 0;
}
void newSystem() {

	generateCordinates(0);
	newSystemID++;

	int failed = 0;

	for (int n = 0; newSystemID < MAXSYSTEM * 0.9; n++) {
			if (generateCordinates(((n-4)/1.1))) {
				newSystemID++;
				failed = 0;
			}
			else {
				failed++;

			}
		if (n/1.1 > newSystemID)
			n = 0;
	}

	
}

void writeToFile() {
	int star = 0;
	ofstream myfile;
	myfile.open("systemmap.txt");
	while (s[star * SYSTEMTOKEN] != -1) {
		cout << s[star * SYSTEMTOKEN] << "\t" << s[star * SYSTEMTOKEN + 1] << endl;
		myfile << s[star * SYSTEMTOKEN] << "\t" << s[star * SYSTEMTOKEN + 1] << endl;
		star++;
	}
	myfile.close();
}
