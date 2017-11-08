#include "Neuron.hpp"
#include <cassert>
#include <random>
#include <iomanip>



	/**
	 * A constructor.
	 */
Neuron::Neuron(double Iext_,double V_, bool externalnoise_) {
	
	C1=exp(-h/tau);
	C2=R*(1.0-C1);
	V=V_;
	J=JE;
	RTstep=RT/h;
	Iext=Iext_;
	externalnoise=externalnoise_;
	spike=false;
	isexcitatory=true;
	assert(spikebuff.size()==delaystep+1);
	t=0;
	s=0;
	
	for(auto& element: spikebuff){element=0;}
}

	/** 
	 * A getter
	 * @return t corresponds to the local steptime
	 * 
	 */ 
int Neuron::get_t() const {
	return t;
}
	/** 
	 * A getter
	 * @return s corresponds to the number of spikes
	 */ 
int Neuron::get_s() const { 
	return s;
}
	/** 
	 * A getter
	 * @return V corresponds to membrane potential 
	 */ 
double Neuron::get_V() const {
	return V;
}
	/** 
	 * A getter
	 * @return h corresponds to the integration stepsize 
	 */ 
double Neuron::get_h() const {
	return h;
}
	/** 
	 * A getter
	 * a neuron is connected to a number(generated with Poisson distribution)
	 * of excitatory neurons outside of the simulation 
	 * @see update_V()
	 * @return external noise (due to spikes coming from neurons outside the simulation)
	 */ 	
	

double Neuron::getexternalnoise(){
	if(!externalnoise)
		{return 0;}
	static random_device rd;
	static mt19937 gen(rd());
	static poisson_distribution<> poisson_gen(Vext*h/(JE*tau));
	return JE*poisson_gen(gen);
	} 

	/**
	 * reads the current coming from neighbours' spikes and clean the buffer after reading
	 * @return  the value of total current coming from neighbours' spikes 
	 */

double Neuron::readbuffer(){
	double buffert = spikebuff[t%(delaystep+1)];
	spikebuff[t%(delaystep+1)]=0;
	return buffert;
}

	/**
	 * update the membrane tension value associated with :
	 * the last tension value, spikes of neighbours and external current
	 * @see update_state()
	 */
void Neuron::update_V(){
	double S(readbuffer()+getexternalnoise());
	if (spiketime.size()>0){
		if ((t-spiketime.back())<RTstep){
			V=0.0;}
		else { V=C1*V+Iext*C2+S;}
	}
	else { V=C1*V+Iext*C2+S;} 
}

	/**
	 * update the state of the neuron a certain number of times (to make it spike or not)
	 * @param unsigned int : number of steps for updating
	 * @see Simulation::simule()
	 * @return spike (true if there is the spike at the last step of update and false otherwise)
	 */
bool Neuron::update_state(unsigned int nbsteps){
	spike=false;
	for (unsigned int i(0);i<nbsteps;++i){
		if (V>=VTHR){
			spike=true;
			spiketime.push_back(t);
			++s;
		}
		update_V();
		++t;
	}
	return spike;
}

	/**
	 * receives the spike from neighbours and put it (write it) in the corresponding place in the buffer
	 * (with the delay)
	 * @param int : time step of neighbours' spike+delay (td will be the time of reading)
	 * @param double : current given from neighbours'spike
	 * @see Simulation::simule()
	 */
void Neuron::receive(int td, double J_){
	const unsigned int tout = td%(delaystep+1);
	assert(tout<spikebuff.size());
	spikebuff[tout]+=J_;
}
	/**
	 * A setter.
	 * modifies the boolean isexcitatory
	 * @param bool : true to set the neuron as excitatory and false to set it as inhibitory
	 * @see Simulation::setexcitatoryneurons()
	 */

void Neuron::setexcitatory(bool b){
	isexcitatory=b;
}

	/**
	 * A setter.
	 * modifies the value of J for the neuron
	 * @param JI : new value for J
	 * @see Simulation::setexcitatoryneurons()
	 */
	 
void Neuron::setJ(double JI){
	J=JI;
}

	/**
	 * A setter.
	 * modifies the value of Vext (given the weight between Vext and VTHR)
	 * @param double weight between Vext and VTHR
	 * @see Simulation::Simulation()
	 */
void Neuron::setVext(double WVEXT_VTHR){
	Vext=WVEXT_VTHR*VTHR;
}
