CFLAGS=-O3 
COMPILER=g++# icpc

all:  powerlaw
powerlaw:
	$(COMPILER) $(CFLAGS) src/chialvo_powerlaw.cpp -o chialvo_power

