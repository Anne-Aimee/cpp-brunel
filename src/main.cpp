
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



void simgraph(int t_sim,int graphid=3, double param1=2,double param2=5){
	cerr<<"Graph "<<graphid<<endl;
	Simulation sim(param1,param2);
	cerr<<"creation ok"<<endl;
	sim.simule(t_sim);
	cerr<<"simulation ok"<<endl;
	sim.save("graphfile.txt");
	system("python ../src/pyscript.py");
}

void choose_graph(int t_sim){
	int g(0);
	while (g<=0 or g>4){
		cout <<"Which graph do you want to see (choose 1, 2, 3 or 4) ? "<<flush;
		cin>>g;
	}
	switch(g){
	case 1 : simgraph(t_sim,1,2,3);
			break;
	case 2 : simgraph(t_sim,2,4);
			break;
	case 3 : simgraph(t_sim);
			break;
	case 4 : simgraph(t_sim,4,0.9,4.5) ;
	}	
}

//May be useful to create other graphs (chosen by the user)
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
	choose_graph(t_sim);
	return 0;
}



