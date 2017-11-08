#include "Neuron.hpp"
#include "Simulation.hpp"
#include "gtest/gtest.h"



	/** 
	 * Tests for one neuron and only one step
	 * if membrame potential is correct, and if it can spikes
	 * with first neuron1 : Iext=1.0, Vinitial=0.0;
	 * shouldnt spike, and we can expect V value
	 * then neuron2: Iext=1.0, Vinitial>VTHR;
	 * should spike and V value is 0 
	 */ 
TEST(OneNeuron, OneStep)
{
	Neuron neuron1(1.0,0.0,false);
	bool spiketest;
	spiketest=neuron1.update_state(1);
	EXPECT_NEAR(0.0997504,neuron1.get_V(),0.001);
	
	Neuron neuron2(1.0,neuron2.VTHR+0.1);
	spiketest=neuron2.update_state(1);
	EXPECT_EQ(0, neuron2.get_V());
	EXPECT_TRUE(spiketest);
}

	/** 
	 * Tests for one neuron if it has the correct V before and after the spike
	 * and if it spikes at the correct t
	 */ 

TEST(OneNeuron, CorrectV){
	Neuron neuron(1.01,0.0,false);
	bool spiketest;
	spiketest=neuron.update_state(924);
	EXPECT_FALSE(spiketest);
	spiketest=neuron.update_state(1);
	EXPECT_TRUE(spiketest);
	EXPECT_EQ(0,neuron.get_V());
}
	/** 
	 * Tests the spikes for one neuron (correct number and correct times)
	 */ 

TEST(OneNeuron, SpikeTimes) {
	Neuron neuron(1.01,0.0,false);
	bool spiketest;
	//We know that the spikes times are at 92.4ms, 186.8 ms...
	
	//Waiting for first spike
	spiketest= neuron.update_state(1);
	EXPECT_EQ(0, neuron.get_s());
	EXPECT_FALSE(spiketest);
	
	
	spiketest=neuron.update_state(924);
	EXPECT_EQ(1,neuron.get_s());
	EXPECT_TRUE(spiketest);
	
	//Waiting for second spike
	spiketest=neuron.update_state(1);
	EXPECT_EQ(1,neuron.get_s());
	EXPECT_FALSE(spiketest);
	
	spiketest=neuron.update_state(943);
	EXPECT_EQ(2,neuron.get_s());
	EXPECT_TRUE(spiketest);
	
}

/** 
	 * Tests for two neuron the correct sending of the spike
	 * and if the post connexion neuron receives the J at given delay
	 */ 
TEST(TwoNeuron,SendDelayofJ) {
	Neuron neuron1(1.01,0.0,false), neuron2(0.0,0.0,false);
	int delaytest = 15;
	
	//We wait for the first spike in neuron1 to see the impact on neuron2
	for (int i=0;i<925+delaytest;++i) {
		if (neuron1.update_state(1)){ 
			neuron2.receive(i+delaytest,neuron1.J);
			EXPECT_EQ(0.0, neuron1.get_V());
		}
		neuron2.update_state(1);
	}
	EXPECT_NEAR(0.1, neuron2.get_V(),0.001);
	
}

/** 
	 * Tests if there  is the good amount of connexions with inhibitory
	 * and excitatory neurons for each neuron
	 */ 

TEST(Network, Connexions){
	Simulation sim;
	unsigned int nb_excit(0);
	unsigned int nb_inhibit(0);
	for (auto neuron : sim.neurons){
		if (neuron->isexcitatory)
		++nb_excit;
		else ++nb_inhibit;
	}
	EXPECT_EQ(10000, nb_excit);
	EXPECT_EQ(2500, nb_inhibit);
} 

/** 
	 * Shows the graph for ten step
	 * some neurons should have spiked but only few of them
	 */ 

TEST(Network, Tenstep){
	Simulation sim;
	sim.simule(1);
	sim.save("graphfile.txt");
	system("python ../src/pyscript.py"); 
	
}

/** 
	 * Shows the graph for hundred steps
	 * the pattern shows the randomness of the spikes
	 */ 

TEST(Network, Hundredsteps){
	Simulation sim;
	sim.simule(10);
	sim.save("graphfile.txt");
	system("python ../src/pyscript.py"); 

}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
