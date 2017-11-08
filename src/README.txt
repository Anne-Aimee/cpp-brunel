Anne-Aimée Bernard (SCIPER : 271148)

Project based on Brunel paper to modelise the activity of neurons with different parameters

There is two classes : 
Neuron and Simulation.
Neurons are by default excitatory neurons which means that when they spike, they give a positive current
to all of their neighbours. Inhibitory neurons give a negative current to their neighbours when they spike.
Simulation corresponds to the network of Neuron.

Tests are done in Neur_unittest.cpp

Display of graphs is done in main.cpp

To do the tests or show the graphs, be in directory called : build 
And write the following lines in the terminal :
	cmake ../src
	make
	./Neur_unittest		or			./Neuron
	


As I have too many spikes, the generation of a graph takes quite a long time
(around 6 minutes for 1seconde simulation with g=5 and Vext/Vthr=2).
The machines didn't work for the last 2 weeks so I couldn't see my graphs.
