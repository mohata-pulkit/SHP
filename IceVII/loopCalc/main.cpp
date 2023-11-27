#include <stdio.h>
#include <math.h>
#include <omp.h>
#define NUM_ATOMS 6000

void readFile(char filename[], double x[], double y[], double z[]);
void distanceGraph(double x[], double y[], double z[], double dist[NUM_ATOMS][NUM_ATOMS]);
void bondingGraph(double bondLength, double dist[NUM_ATOMS][NUM_ATOMS], bool bonded[NUM_ATOMS][NUM_ATOMS]);
void loopSearch(bool bonded[NUM_ATOMS][NUM_ATOMS], int loopSize);

int main(int argc, char *argv[])
{
	double x[NUM_ATOMS];
	double y[NUM_ATOMS];
	double z[NUM_ATOMS];
	double dist[NUM_ATOMS][NUM_ATOMS];
	bool bonded[NUM_ATOMS][NUM_ATOMS];

	readFile("coordinates.txt", x, y, z);
	distanceGraph(x, y, z, dist);
	bondingGraph(1.5, dist, bonded);

	return 0;
}

void readFile(char filename[], double x[], double y[], double z[])
{
	FILE *fp;
	fp = fopen(filename, "r");
	int i;
	for (i = 0; i < NUM_ATOMS; i++)
	{
		fscanf(fp, "%lf %lf %lf", &x[i], &y[i], &z[i]);
	}
	fclose(fp);
}

void distanceGraph(double x[], double y[], double z[], double dist[NUM_ATOMS][NUM_ATOMS])
{
	int i;
	int j;
	for (i = 0; i < NUM_ATOMS; i++)
	{
		for (j = i + 1; j < NUM_ATOMS; j++)
		{
			dist[i][j] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2) + pow(z[i] - z[j], 2));
			dist[j][i] = dist[i][j];
		}
	}
}

void bondingGraph(double bondLength, double dist[NUM_ATOMS][NUM_ATOMS], bool bonded[NUM_ATOMS][NUM_ATOMS])
{
	int i;
	int j;
	for (i = 0; i < NUM_ATOMS; i++)
	{
		for (j = i + 1; j < (NUM_ATOMS - i); j++)
		{
			if (dist[i][j] <= bondLength)
			{
				bonded[i][j] = true;
				bonded[j][i] = true;
			}
			else
			{
				bonded[i][j] = false;
				bonded[j][i] = false;
			}
		}
	}
}

void loopSearch(bool bonded[NUM_ATOMS][NUM_ATOMS], int loopSize)
{
}