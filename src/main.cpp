
#include <array>
#include "Neuron.hpp"
#include "Simulation.hpp"
#include <vector>
using namespace std;

int set_sim_duration(){
	int t(0);
	while(t<=0){
		cout<<"Set time of neuron activity simulation (in ms) :"<<flush;
		cin>>t;
	}
	return t;
}


//Useful to create other graphs (chosen by the user)
/*double set_sim_g(){
	double g(0.0);
	while(g<=0){
		cout<<"Set weight between currents from inhibitory and excitatory (weight = -JI/JE) :"<<flush;
		cin>>g;
	}
	return g;
}

double set_sim_VextVthr(){
	double VextVthr(0.0);
	while(VextVthr<=0){
		cout<<"Set weight between potential from external neurons and threshold potential :"<<flush;
		cin>>VextVthr;
	}
	return VextVthr;
}*/

int main(){
	
	int t_sim(0);
	t_sim=set_sim_duration();
	cerr<<"Graph 1"<<endl;
	Simulation sim1(2,3);
	cerr<<"creation ok"<<endl;
	sim1.simule(t_sim);
	cerr<<"simulation ok"<<endl;
	sim1.save("graphfile.txt");
	system("python ../src/pyscript.py");
	
	cerr<<"Graph 2"<<endl;
	Simulation sim2(4,6);
	cerr<<"creation ok"<<endl;
	sim2.simule(t_sim);
	cerr<<"simulation ok"<<endl;
	sim2.save("graphfile.txt");
	system("python ../src/pyscript.py");
	
	cerr<<"Graph 3"<<endl;
	Simulation sim3;
	cerr<<"creation ok"<<endl;
	sim3.simule(t_sim);
	cerr<<"simulation ok"<<endl;
	sim3.save("graphfile.txt");
	system("python ../src/pyscript.py");
	
	cerr<<"Graph 4"<<endl;
	Simulation sim4(0.9,4.5);
	cerr<<"creation ok"<<endl;
	sim4.simule(t_sim);
	cerr<<"simulation ok"<<endl;
	sim4.save("graphfile.txt");
	system("python ../src/pyscript.py");
	
	return 0;
}



