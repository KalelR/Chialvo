#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "to_string.h"

using namespace std;

//==========INPUT: program.cpp alpha N seed sigma_meido sigma_ruido eps


void shuffle(vector<double> & noise, int N, int seed, int num_perm)
{
    int i, j;
	double aux;
    srand(seed);
    for (i = 0; i < num_perm; i++)
    {
      j = i + rand() / (RAND_MAX / (N - i) + 1);
      aux = noise[j];
      noise[j] = noise[i];
      noise[i] = aux;
    }
}

int main(int argc, char ** argv)
{
    double xn, x, yn, y, a, b, c, xn_th, alpha, k, k_inicial, k_desvio, eta, x_coup, eps;
    int t, t_exec, t_trans, i, N, seed, N_p, j, i_1, i_2, num_perm;
    ofstream outfile, outfile2;
    ifstream inFile;
    string outName, inName;
    
    //==paramatros do modelo
    k_inicial = 0.03;//strtod(argv[4], NULL); //0.03;
    k_desvio =  0.0035; //strtod(argv[5], NULL); //0.005;
    seed = 1019;// strtod(argv[3], NULL); 
    N = 525;
    num_perm = N - 1; //default
    // num_perm  = 100;
    vector<double> v_k(N, k_inicial);
    srand(seed);

    for(i = 0; i < N; i++){
      v_k[i] = k_inicial + (k_desvio / N) * i;
    }

    shuffle(v_k, N, seed, num_perm);


    outName = "data/noises/shuffled_uniforme_num_perm_" + toString(num_perm) + "_mean_" + toString(k_inicial) + "_sigma_" + toString(k_desvio) +  "_N_" + toString(N) + "_seed_" + toString(seed)  + ".dat";
    outfile2.open(outName.c_str());


    for (int i = 0; i < N; ++i)
    {
        // cout << v_k[i] << endl;
        outfile2 << v_k[i] << endl;
    }
    outfile2.close();

    return 0;
}