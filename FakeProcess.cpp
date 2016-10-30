#include "FakeProcess.h"

FakeProcess::FakeProcess() {
	PID = 0;
	ARRIVAL_TIME = 0;
	CPU_BURST = 0;
	original_CPU_BURST = 0;
	time_of_completion = 0;
	waiting_time = 0;
	turnaround_time = 0;
	response_time = 0;
	num_context_switch = 0;
	waiting = false;
	finished = false;
	preempted = false;
}

FakeProcess::FakeProcess(int* p_data) {
	PID = p_data[0];
	ARRIVAL_TIME = p_data[1];
	CPU_BURST = p_data[2];
	original_CPU_BURST = CPU_BURST;
	time_of_completion = 0;
	waiting_time = 0;
	turnaround_time = 0;
	response_time = 0;
	num_context_switch = 0;
	waiting = false;
	finished = false;
	preempted = false;
}

int FakeProcess::getPID() {
	return PID;
}

int FakeProcess::getArrivalTime() {
	return ARRIVAL_TIME;
}

int FakeProcess::getCPUBurst() {
	return CPU_BURST;
}

void FakeProcess::setCPUBurst(int burst) {
	CPU_BURST = burst;
}

void FakeProcess::progress() {
	--CPU_BURST;
}