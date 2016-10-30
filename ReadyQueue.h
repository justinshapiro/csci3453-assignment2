// Creates and maintains an array-based FIFO queue

#ifndef READYQUEUE_H
#define READYQUEUE_H

#include "FakeProcess.h"

class ReadyQueue {
private:
	FakeProcess* resize_arr(int, int);
	FakeProcess* queue;
	int size;
	
public:
	ReadyQueue();
	~ReadyQueue();

	int length();
	bool empty();
	void sort();
	void push(FakeProcess&);
	FakeProcess& pop(FakeProcess*, int);
	FakeProcess& remove(int, FakeProcess*, int);
	FakeProcess* get(int);
};

#endif