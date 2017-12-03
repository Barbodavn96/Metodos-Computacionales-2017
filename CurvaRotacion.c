#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h>

float v_circ(float r, float Mb, float bb, float Md, float bd, float ad, float Mh, float ah);
float compute_likelihood(float *R, float *V, int n_datos, float Mb, float bb, float Md, float bd, float ad, float Mh, float ah);
float get_random_number(float min, float max);

int main(void)
{
	printf("Iniciando Programa \n\n");

	char filename[100] = "RadialVelocities.dat";
	char e1[300], e2[300];
	int test;
	FILE *in;
	int n_datos=300;
	in = fopen(filename, "r");
	float *R = malloc(n_datos*sizeof(float));	
	float *V = malloc(n_datos*sizeof(float));



	// Cargamos los datos que nos dan para resolver el ejercicio. 
	// Recoerdemos que vamos a usar el metodo de montecarlo, tirando numeros aleatorios para encontrar asi los parametros del modelo
	test = fscanf(in, "%s %s\n", e1, e2);
	printf("Los datos son\n%s %s\n", e1, e2);
	for (int i = 0; i < n_datos; ++i)
	{
		fscanf(in, "%f %f\n", &R[i], &V[i]);
		printf("%f %f\n", R[i], V[i]);
	}
	fclose(in);


	int n_iteraciones = 100000;
	float bb=0.2497, bd=5.16, ad=0.3105, ah=64.3;
	float Mgal=2.325e7;
	float G=1;
	float Mb=3000.0, Md=3000.0, Mh=3000.0;
	float dM = 5;
	float new_Mb, new_Md, new_Mh;
	float likelihood0 = compute_likelihood(R, V, n_datos, Mb, bb, Md, bd, ad, Mh, ah);
	float likelihood1;
	srand(time(NULL));

	char filename2[100] = "caminata_aleatoria.tarea";
	FILE *out = fopen(filename2, "w");
	fprintf(out, "Mb,Md,Mh,likelihood\n");
	fprintf(out, "%f,%f,%f,%f\n", Mb,Md,Mh,likelihood0);

	printf("\n\nIterando con método de Monte Carlo\n");

	for (int i = 0; i < n_iteraciones; ++i)
	{
		new_Mb = Mb + get_random_number(-dM,dM);
		new_Md = Md + get_random_number(-dM,dM);
		new_Mh = Mh + get_random_number(-dM,dM);

		likelihood1 = compute_likelihood(R, V, n_datos, new_Mb, bb, new_Md, bd, ad, new_Mh, ah);

		//printf("%f---%f\n", likelihood0, likelihood1);
		if (likelihood1 < likelihood0)
		{
			Mb = new_Mb;
			Md = new_Md;
			Mh = new_Mh;
			likelihood0 = likelihood1;
		}

		fprintf(out, "%f,%f,%f,%f\n", Mb,Md,Mh,likelihood0);
		if (i%500==0)
		{
			printf("%d...", i);
		}
		
	}
	
	printf("\n\n\nMasa-bulbo ### Masa-disco ### Masa-halo\n");
	printf("%f ### %f ### %f\n", Mb, Md, Mh);

	fclose(out);
	printf("\n\nPrograma Finalizado \n\n");
	return 0;


}


float v_circ(float r, float Mb, float bb, float Md, float bd, float ad, float Mh, float ah)
{	
	// Calcular velocidad circular teniendo en cuenta 
	// modelo de bulbo, disco y halo
	float bulbo = pow(Mb,0.5)*r/pow(pow(r,2)+pow(bb,2),0.75);
	float disco = pow(Md,0.5)*r/pow( pow(r,2)+pow(bd+ad,2) ,0.75);
	float halo = pow(Mh,0.5)/pow(pow(r,2)+pow(ah,2),0.25);

	float Vcirc = bulbo + disco + halo;

	return Vcirc;
}


float compute_likelihood(float *R, float *V, int n_datos, float Mb, float bb, float Md, float bd, float ad, float Mh, float ah)
{
	float likelihood=0;
	float v_modelo;
	float l;

	for (int i = 0; i < n_datos; ++i)
	{
		v_modelo = v_circ(R[i], Mb, bb, Md, bd, ad, Mh, ah);
		l = fabs(v_modelo - V[i]);
		likelihood = likelihood + l;
	}

	return likelihood;

}

float get_random_number(float min, float max)
{
	float numero_aleatorio;
	float delta = max-min;
	numero_aleatorio = (float)rand()/RAND_MAX;

	numero_aleatorio = delta - numero_aleatorio*2.0*delta;

	return numero_aleatorio;

}