#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "to_string.h"

using namespace std;

//==========INPUT: program.cpp alpha N seed K_min sigma eps


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
    double xn, x, yn, y, a, b, c, xn_th, alpha, k, k_inicial, k_desvio, eta, x_coup, eps, num_eps, x_mean;
    int t, t_exec, t_trans, i, N, seed, N_p, j, i_1, i_2, num_perm;
    ofstream outfile, outfile2, outfile3;
    ifstream inFile;
    string outName, inName;
    

    //==network parameters
    alpha = strtod(argv[1], NULL);
    N = strtod(argv[2], NULL);  //dados.N = N; 
    N_p = (N-1)/2; //N^\prime
    eta = 0;
    for (int j = 1; j < N_p; j++)
        eta += 1/pow(j, alpha);
    eta *= 2;


    //==model parameters
    a = 0.89; b = 0.6; c = 0.28;
    k_inicial = strtod(argv[4], NULL); //
    k_desvio =  strtod(argv[5], NULL); //
    vector<double> v_k(N, k_inicial); //
    seed = strtod(argv[3], NULL); 
    num_perm = N-1; //number of permutaions (always N-1 in the paper)
    srand(seed);
    for (i = 0; i < N; i++)
    {
        v_k[i] = k_inicial + (k_desvio / N) * i;
    }
    shuffle(v_k, N, seed, num_perm);

    

    //=================simulation parameters
    // t_exec = 200000; t_trans = 100000; //used in the paper
    t_exec = 1000; t_trans = 100; //used for a quick example
    xn_th = 0.5;
    num_eps = argc - 6;

    //====initial conditions
    vector<double> v_x(N, 0), v_y(N, 0), v_x0(N,0), v_y0(N,0), v_xn(N,0), v_yn(N,0); //vetores com os valores antigos (precisam ser salvos para iterarmos o mapa)
    inName = "inputs/ci_N_525_exp_1.80_seed_1000.dat";
    inFile.open(inName.c_str());
    for(i = 0; i < N; i++){
        inFile >> t >> x >> y;
        v_x0[i] = x;
        v_y0[i] = y;
    }
    inFile.close();

    vector<vector<int> > m_spikeTimes(N, vector<int>(0)); //N rows, 0 cols

    for (int idx_e = 0; idx_e < num_eps; idx_e++)
    {
        eps = strtod(argv[6+idx_e], NULL);  //dados.N = N; 
        //output file
        outName = "results/shuffled_uniform_min_" + toString(k_inicial) + "_sigma_" + toString(k_desvio) + "_chialvo_spikeTimes_powerlaw_alpha_" + toString(alpha) + "_N_" + toString(N) + "_seed_" + toString(seed) + "_eps_" + toString(eps) + ".dat";
        outfile2.open(outName.c_str());


        for (i = 0; i < N; ++i){v_x[i] = v_x0[i]; v_y[i] = v_y0[i]; }//setting inicial conditions
        vector<vector<int> > m_spikeTimes(N, vector<int>(0)); //N rows, 0 cols

        for (t = 1; t < t_exec + t_trans; t++)
        {
            x_mean = 0;
            for (i = 1; i <= N; i++) //COMEÇO OS LOOPS EM 1, para acessar os vetores tem que subtrair os indices por 1 sempre; começo em 1 para facilitar as equaçoes para a powerlaw
            {
                x = v_x[i-1]; y = v_y[i-1]; k = v_k[i-1];
                
                //calcular o x_coup, que é daquele jeito de powerlaw
                x_coup = 0;
                for (j = 1; j <= N_p; j++){
                        i_1 = i - j;
                        i_2 = i + j;
                        if (i_1 <= 0) i_1 += (N);
                        if (i_2 > N) i_2 -= N;
                        x_coup += (1/pow(j, alpha))*(v_x[i_1-1] + v_x[i_2-1]); //i_1 = i+j; i_2 = i-j
                }
                

                xn = x*x*exp(y - x) + k + (eps/eta)*x_coup;
                yn = a*y - b*x + c;
                
                v_xn[i-1] = xn; v_yn[i-1] = yn;
                //salva os dados
                if (t >= t_trans){
                    x_mean += xn;

                    //Acha os tempos dos spikes e salva na matriz
                    if (xn > xn_th && x < xn_th){
                        m_spikeTimes[i-1].push_back(t); //nao eh mto eficiente, poderia ser melhor
                    }
                    
                }
            }
            if (t > t_trans) outfile3 << t << " " << (x_mean/N) << endl;
            //update neuron variables
            for (i = 1; i <= N; i++){ v_x[i-1] = v_xn[i-1]; v_y[i-1] = v_yn[i-1]; }


        }   
        
        //printa tempos
        for (i = 0; i < N; i++)
        {
            for (t = 0; t < m_spikeTimes[i].size(); t++)
                outfile2 << m_spikeTimes[i][t] << " ";
            outfile2 << endl;   
        }
        
        if(outfile2.is_open())
            outfile2.close();   
    }    
    
    
    return 0;
}