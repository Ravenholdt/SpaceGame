#include "random"
#include <cstdlib>

int generateSystemobj(int i)	// stavens generator
{
	int u = 0, a = 0;
	u = rand() % 100 + 1;
	if (u < 31)
	{
		a = 0;	// ringen f�r inget tilldelat
	}
	else if (i < 6)	//de inre ringarna
	{
		if ((50 < u) && (u < 53))	//2% den f�r asteroidf�lt
			a = 3;
		else if ((52 < u) && (u < 54))	//1% gasplnet
			a = 2;
		else if (53 < u)
			a = 1;			//57% planet
		else
			a = 0;			//40% inget
	}
	else if (i < 11)	//mellanringarna
	{
		if (i < 8)	// de inre mellanreingarna
		{
			if ((40 < u) && (u < 51))
				a = 3;		//10% asteroid
			else if ((50 < u) && (u < 54))	//3% gasplnet
				a = 2;
			else if (53 < u)
				a = 1;		//47% planet
			else
				a = 0;		//40% inget
		}
		if (i > 7)	//de yttre mellanringarna
		{
			if ((40 < u) && (u < 71))
				a = 3;		//30% asteroid
			else if ((70 < u) && (u < 76))	//5% gasplnet
				a = 2;
			else if (75 < u)
				a = 1;		//25% planet
			else
				a = 0;	//40% inget
		}
	}
	else if (i > 10)	// yttre ringarna
	{
		if (i < 12)		// inre yttre ringarna
		{
			if ((60 < u) && (u < 91))	//30% asteroid
				a = 3;
			else if ((90 < u) && (u < 96)) //5% gasplanet
				a = 2;
			else if (95 < u)	//5% planet
				a = 1;
			else
				a = 0;		//60% inget
		}
		if (11 < i < 24)		// de mellersta yttre ringarna
		{
			if ((70 < u) && (u < 81))	//10% asteroid
				a = 3;
			else if ((80 < u) && (u < 96)) //15% gasplanet
				a = 2;
			else if (95 < u)	//5% planet
				a = 1;
			else
				a = 0;		//70% inget
		}
		if (i > 23)		// de yttersta yttre ringarna
		{
			if ((60 < u) && (u < 91))	//30% asteroid
				a = 3;
			else if ((90 < u) && (u < 96)) //5% gasplanet
				a = 2;
			else if (95 < u)	//10% planet
				a = 1;
			else
				a = 0;		//55% inget
		}
	}
	i++;
	return a;
}

int generateCordinates(int parent) {
	int placed = 0, u, systemDistX, systemDistY, collisionCheck, timesFailed = 0;

	//Debug
	if (parent < 0)
		parent = 0;

	//Place first system.
	if (newSystemID == 0)
	{
		s[0] = 0;
		s[1] = 0;
		placed = 1;
	}
	while (!placed) {
		//Make example placement.
		u =rand() % 2;
		if (u == 0) { u = -1; }
		s[(newSystemID * SYSTEMTOKEN) + 0] = u*(rand() % 1900 + 101) + s[(parent * SYSTEMTOKEN) + 0];
		u = rand() % 2;
		if (u == 0) { u = -1; neg++; } else { pos++; }
		s[(newSystemID * SYSTEMTOKEN) + 1] = u*(rand() % 1900 + 101) + s[(parent * SYSTEMTOKEN) + 1];

		//Check all systems for collisions.
		collisionCheck = 0;
		for (int n = 0; n < newSystemID; n++) { 

			systemDistX = (s[(n * SYSTEMTOKEN) + 0]) - (s[(newSystemID * SYSTEMTOKEN) + 0]);
			systemDistY = (s[(n * SYSTEMTOKEN) + 1]) - (s[(newSystemID * SYSTEMTOKEN) + 1]);

			if ((systemDistX < 500 && systemDistX > -500) && (systemDistY < 500 && systemDistY > -500)) {
				 collisionCheck = 1;
				 n = newSystemID; //If collision, end for loop.
			}
		}

		// If no collission, place system.
		if (!collisionCheck) {
			placed = 1;
			timesFailed = 0;
			if (u > 0)
				posS++;
			else
				negS++;
		}
		else {
			cout << "Failed, " << newSystemID << endl;
			timesFailed++;

			if (timesFailed > 10) {
				return 0;
			}
		}

	}
	return 1;
}
int generateConnections(int system) {
	int placed, u, i = 2, jumpLengt = 500, systemDistX, systemDistY;

	u = rand() % 5 + 1;
	while(jumpLengt < 2101) {
		jumpLengt = jumpLengt + 200;
		for (int n = 0; n < newSystemID; n++) {
			systemDistX = (s[(n * SYSTEMTOKEN) + 0]) - (s[(system * SYSTEMTOKEN) + 0]);
			systemDistY = (s[(n * SYSTEMTOKEN) + 1]) - (s[(system * SYSTEMTOKEN) + 1]);
			if ((systemDistX < jumpLengt && systemDistX > -jumpLengt) && (systemDistY < jumpLengt && systemDistY > -jumpLengt)) {
				s[(system * SYSTEMTOKEN) + i] = n;
				i++;
				u--;
			}

		}
		
	}
	if (i == 2) {
		return 0;
	}
	return 1;
}
