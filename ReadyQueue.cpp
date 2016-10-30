#include "ReadyQueue.h"
#include "FakeProcess.h"
#include <cstring>

int HEAD = 0;
int TAIL = 1;
int INCREASE = 1;
int DECREASE = -1;

ReadyQueue::ReadyQueue() {
	queue = new FakeProcess[0];
	size = 0;
}

ReadyQueue::~ReadyQueue() {
	delete[] queue;
}

void ReadyQueue::sort() {
	FakeProcess temp;
	bool swapped = true;
	int idx = 0;

	while (swapped) {
		swapped = false;
		++idx;
		for (int i = 0; i < size - idx; ++i) {
			if (queue[i].getCPUBurst() > queue[i + 1].getCPUBurst()) {
				temp = queue[i];
				queue[i] = queue[i + 1];
				queue[i + 1] = temp;
				swapped = true;
			}
		}
	}
}

void ReadyQueue::push(FakeProcess& p) {
	queue = resize_arr(INCREASE, TAIL);
	queue[size - 1] = p;
}

FakeProcess& ReadyQueue::pop(FakeProcess* p, int num_processes) {
	FakeProcess fp = queue[0];
	for (int i = 0; i < num_processes; ++i) {
		if (queue[0].getPID() == p[i].getPID()) {
			p[i].setCPUBurst(queue[0].getCPUBurst());
			p[i].finished = queue[0].finished;
			p[i].num_context_switch = queue[0].num_context_switch;
			p[i].response_time = queue[0].response_time;
			p[i].time_of_completion = queue[0].time_of_completion;
			p[i].turnaround_time = queue[0].turnaround_time;
			p[i].waiting = queue[0].waiting;
			p[i].waiting_time = queue[0].waiting_time;
			break;
		}
	}
	//queue[0].~FakeProcess();
	queue = resize_arr(DECREASE, HEAD);

	return fp;
}

FakeProcess& ReadyQueue::remove(int pos, FakeProcess* p, int num_processes) {
	FakeProcess fp = queue[pos];
	for (int i = 0; i < num_processes; ++i) {
		if (queue[pos].getPID() == p[i].getPID()) {
			p[i].setCPUBurst(queue[pos].getCPUBurst());
			p[i].finished = queue[pos].finished;
			p[i].num_context_switch = queue[pos].num_context_switch;
			p[i].response_time = queue[pos].response_time;
			p[i].time_of_completion = queue[pos].time_of_completion;
			p[i].turnaround_time = queue[pos].turnaround_time;
			p[i].waiting = queue[pos].waiting;
			p[i].waiting_time = queue[pos].waiting_time;
			break;
		}
	}

	//queue[pos].~FakeProcess();

	for (int i = pos; i < size - 1; ++i)
		queue[i] = queue[i + 1];

	queue = resize_arr(DECREASE, TAIL);

	return fp;
}

FakeProcess* ReadyQueue::resize_arr(int mode, int from) {
	size += mode;
	FakeProcess* new_queue = new FakeProcess[size];

	for (int i = 0; i < size; ++i) {
		if ((mode == INCREASE && from == TAIL) || (mode == DECREASE && from == TAIL))
			new_queue[i] = queue[i];
		else
			new_queue[i] = queue[i + 1];
	}

	return new_queue;
}

FakeProcess* ReadyQueue::get(int i) {
	return &queue[i];
}

int ReadyQueue::length() {
	return size;
}

bool ReadyQueue::empty() {
	bool empty = false;
	if (size == 0)
		empty = true;

	return empty;
}