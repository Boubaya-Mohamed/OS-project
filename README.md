# OS-project

We want to simulate the explosion of the Chernobyl nuclear power plant. We will have a

Control center (parent process) and various hazard sensors distributed over the reactors

(Child process). They will communicate via a file for which the father will be a reader and

The sons writers.

The wires, once created, will generate random numbers between 1 and 9 every second, representing

Danger levels, and write these integers to the file with a header containing their

PID. The father, meanwhile, receives all the messages of the file and keeps the account of the total of the numbers

Sent by each of the threads. When this total reaches 100 for a wire (danger potential too high), the

Sends him a signal so that it ends (the sensors signaling a danger are necessarily

defective). If other messages still come from this son, the father continues to keep the total

Does not send a second signal. Of course, when a wire receives the signal, it stops

at once.

Function: 

Srand () and rand () to generate random numbers (be careful: make sure the wires do not generate

Not all the same numbers!);

• fork () and wait () for creating and waiting for threads;

• kill () and signal () for sending and receiving signals;

• open (), close () and write () for writing the log by the parent;
Pipe () for connection between wires and dad

