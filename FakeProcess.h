// Emulates a PCB (Process Control Block)

#ifndef FAKEPROCESS_H
#define FAKEPROCESS_H

class FakeProcess {
private:
	int PID;
	int ARRIVAL_TIME;
	int CPU_BURST;

public:
	FakeProcess();
	FakeProcess(int*);

	int getPID();
	int getArrivalTime();
	int getCPUBurst();
	void setCPUBurst(int);
	void progress();

	int num_context_switch;
	int original_CPU_BURST;
	bool waiting;
	bool finished;
	bool preempted;
	float time_of_completion;
	float waiting_time;
	float turnaround_time;
	float response_time;
};

#endif