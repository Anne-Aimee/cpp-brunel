#ifndef SIMULATION_H
#define SIMULATION_H

#include "Neuron.hpp"
#include <vector>
#include <array>

using namespace std;


class Simulation{
	
	public :
	Simulation(double WEIGHT_VEXTVTHR_=2,double WEIGHT_JIJE_=5) ;
	
	void simule (double t_stop);
	void newconnexion(Neuron* n1, Neuron* n2);
	void setexcitatoryneurons();
	void initialconnexions();
	void save(const string&);
	
	
	//=====CONSTANTES=====//
	const size_t nb_excitatory =10000;			//!<amount of excitatory neurons in the simulation
	const size_t nb_inhibitory =2500;			//!<amount of inhibitory neurons in the simulation
	const unsigned int CE =1000;				//!<amount of excitatory neurons linked to each neuron
	const unsigned int CI=250 ;					//!<amount of inhibitory neurons linked to each neuron
	const double JE =0.1; 						//!<current given to neighbours when excitatory neuron spikes
	double WEIGHT_JIJE;							//!< weight between currents from inhibitory and excitatory (weight = -JI/JE)
	double WEIGHT_VEXTVTHR;						//!< weight between potential from external neurons and threshold potential
	double JI;									//!<current given to neighbours when inhibitory neuron spikes
	//===================//
	
	
	
	array<Neuron*,12500> neurons;				//!<array to access to  all the neurons of the simulation
	int globalclock ;							//!<equivalent of timestep from class Neuron but for global scale
	
	private :

};


#endif

