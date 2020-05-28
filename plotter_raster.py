# -*- coding: UTF-8 -*-
#--------------------------------- RUN WITH PYTHON2
import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import os.path
from os import path

alpha = '1.8'
v_eps = ["0.021"]
N = 525
seed = '1002'
k_mean = '0.03'; sigma = '0.0035'
DIR = "/home/kalel/hoggar/chialvo/"
num_perm = "524"
prefix = "shuffled_uniform_min_" + (k_mean) + "_sigma_" + sigma
for i in range(0, len(v_eps)):
    eps = v_eps[i]
    print(eps)
    fileIn = "results/" +  prefix + "_chialvo_spikeTimes_powerlaw_alpha_" + alpha + "_N_" + str(N) + "_seed_" + seed + "_eps_" + eps + ".dat"
    if(path.exists(fileIn)):
        mTempos = [np.array(map(float, line.split())) for line in open(fileIn)]
    else:
        print('erro, nao achou o arquivo' + fileIn)
        break;

    for j in range(N):
        v_idxNeuron = np.linspace(j, j, len(mTempos[j][:]), dtype=int)
        plt.plot(v_idxNeuron, mTempos[j][:], 'k.', markersize=1)


    plt.ylabel('t', fontsize=8)
    plt.xlim(0, N)
    # plt.ylim(100000, 100300)
    plt.xlabel('Neuron #', fontsize=8)
    eps_2 = ('%.4f' % float(eps))
    plt.savefig('results/' + prefix + '_chialvo_powerlaw_RP_alpha_' + alpha + '_N_' + str(N) + '_seed_' + str(seed) + '_eps_' + eps_2 + '.png')
    plt.clf()
