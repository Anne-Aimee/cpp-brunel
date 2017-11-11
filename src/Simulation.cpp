#include "Simulation.hpp"
#include <string>
#include <random>
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;



/**
 * A constructor.
 * */


Simulation::Simulation(double WEIGHT_VEXTVTHR_,double WEIGHT_JIJE_){
	WEIGHT_JIJE= WEIGHT_JIJE_;
	assert(WEIGHT_JIJE>0);
	JI=-WEIGHT_JIJE*JE;	
	WEIGHT_VEXTVTHR=WEIGHT_VEXTVTHR_;
	assert(WEIGHT_VEXTVTHR>0);
	for(unsigned int i(0);i<neurons.size();++i){
		neurons[i]=new Neuron;
		neurons[i]->setVext(WEIGHT_VEXTVTHR);
	}
	assert(neurons.size()==nb_excitatory+nb_inhibitory);
	globalclock=0;
	setexcitatoryneurons();
	initialconnexions();
}
	
	
/**
 * simulation : simulates the activity of the neuron network during a certain period
 * @param double : period of simulation (in ms)
 */
void Simulation::simule(double t_stop) {
	while (globalclock<(t_stop/neurons[0]->h)){
		for(unsigned int i(0);i<neurons.size();++i){
			neurons[i]->spike=neurons[i]->update_state(1);
			if (neurons[i]->spike) {
				for (auto& target : neurons[i]->targets){
					target->receive(globalclock+(neurons[i]->delaystep),neurons[i]->J);
				}
			}
		}
		++globalclock;
	}
}

/**
 * creates a new connexion between two identified neurons 
 * @param Neuron* n1 : pointer on preconnexion neuron;
 * @param Neuron* n2 : pointer on postconnexion neuron;
 * @see initialconnexions
 */ 
void Simulation::newconnexion(Neuron* n1, Neuron* n2){
	assert(n1!=nullptr);
	(n1->targets).push_back(n2);
}
		

/**
 * creates random connexions in the neuron network (connexions with excitatory and inhibitory neurons from the network)
 * with defined number of excitatory connexions and inhibitory connexions
 * @see Simulation
 */ 
void Simulation::initialconnexions(){
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis1(0, nb_excitatory-1);
			
	random_device rd2;
	mt19937 gen2(rd2());
	uniform_int_distribution<> dis2(nb_excitatory, neurons.size()-1);
			
for (unsigned int n(0);n<neurons.size();++n){	

	for (unsigned int e(0);e< (CE+CI);++e){
		if(e < CE){
			unsigned int pre_excitatory (0); 
			//pre_excitatory is the index taken randomly in all excitatory neurons indexes from the vector "neurons"
			pre_excitatory = dis1(gen); 
			assert(neurons[pre_excitatory]->isexcitatory);
			assert (pre_excitatory<nb_excitatory);
			newconnexion(neurons[pre_excitatory],neurons[n]);
		}else{
			unsigned int pre_inhibitory (0);
			pre_inhibitory = dis2(gen2);
			assert(! neurons[pre_inhibitory]->isexcitatory);
			assert(pre_inhibitory>= nb_excitatory and pre_inhibitory<neurons.size());
			newconnexion(neurons[pre_inhibitory],neurons[n]);
			}
		}

	}
}
		
/**
 * select which neurons of the network are excitatory and inhibitory
 * @see Simulation
 */ 		
void Simulation::setexcitatoryneurons(){
	for (unsigned int i(0);i<nb_excitatory;++i){
		neurons[i]->setexcitatory(true);
		assert(neurons[i]->J==JE and neurons[i]->isexcitatory);	
	}
	for (unsigned int i(nb_excitatory);i<neurons.size(); ++i){
		neurons[i]->setJ(JI);
		neurons[i]->setexcitatory(false);
		assert(neurons[i]->J==JI and !neurons[i]->isexcitatory);
	}
	
}

/**
 * save all the times and neuron identifier in another file 
 * save date for the graph
 */ 

void Simulation::save(const string& graphfile){
	ofstream out(graphfile);
	if(out.fail()){
		cerr<<"Saving data in graphfile impossible"<<endl;}
	else {
		for(unsigned int i=0; i<neurons.size();++i){
			for(auto spiket : neurons[i]->spiketime){
				out<<spiket<<'\t'<<i<<'\n';}
		}
		out.close();
	}
}



