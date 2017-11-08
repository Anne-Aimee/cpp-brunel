#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <array>
#include <cmath>
#include <iostream>
using namespace std;

class Neuron {
	
	public :
	
	Neuron(double Iext_=0.0,double V_=0.0,bool externalnoise_ =true);
	
	//=====CONSTANTES=====//
	
	static constexpr double VTHR=20.0;	//!<spike threshold
	double Vext=2*VTHR; 				//!<potential from external neurons
	static constexpr double Vreset=0.0;	//!<V after refractory time
	const double tau=20.0;				//!<membrane time constant
	static constexpr double h=0.1;		//!<integration stepsize
	const double RT=2.0;				//!<refractory time (ms)
	const double R=20.0;				//!<membrane resistance (Gohm)
	static constexpr double delay=1.5;	//!<delay for sending J between connexions
	static const int delaystep=delay/h;	//!<delay in time steps
	const double JE =0.1; 				//!<current given to neighbours when excitatory neuron spikes
	
	double Iext;						//!<external current
	
	double C1;							//!<constant used in update_V formula
	double C2;							//!<constant used in update_V formula
	unsigned int RTstep;				//!<refractory steps 
	double J; 							//!<current given to neighbours when neuron spikes								
	//===================//
	
	
	//===== GETTERS========//
	int get_t() const;
	double get_V() const;
	int get_s() const;
	double get_h() const;				
	double getexternalnoise();			//!<external noise (in mV)
	//=====================//
	
	//===== SETTERS========//
	void setexcitatory(bool b);
	void setJ(double JI);
	void setVext(double WVEXT_VTHR);
	//=====================//
	
	//== USEFUL SIMULATION FONCTIONS==//
	bool update_state(unsigned int nbsteps);
	void update_V();
	void receive(int td, double J_);
	double readbuffer();
	//===============================//
	
	bool externalnoise;					//!<existence of random external noise (otherwise input current)
	bool spike;							//!<existence of spike
	bool isexcitatory;					//!<type of neuron (excitatory=true, inhibitory=false)
	vector<Neuron*> targets;			//!<contains adresses of neurons that will receive a J if the neuron spikes
	vector<unsigned int> spiketime; 	//!<time of spikes (in steps)


	private :
	
	double V; 							//!<membrane potential
	int s; 								//!<number of spikes, variable used for tests
	unsigned int t; 					//!<times when the spikes occured (duree = t*h)
	array<double,delaystep+1> spikebuff ;//!<buffer where incoming J from neighbours' spikes are stocked to be read after delay 
	
	
};


#endif
