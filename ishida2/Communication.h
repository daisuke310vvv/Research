#ifndef ONCE
#define ONCE
//２重インクルード防止
#include "Image.h"
#include "init.h"
#include <cstdio>
#include <cstdlib>
#include <string>


#endif

#include <mpi.h>

class Communication {
private:
	//Image data;
	int myrank;
	int nodenum;
	int name_len;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int tag;
	//unsigned char *receivedata;
	char *receivedata;
	int *receivelist;

public:
	Communication(int argc, char *argv[]);
	~Communication();

	int getMyrank();
	int getNodenum();
	int getProcessorname(char *, int);
	string getProcessorname();
	int send(char * send_data);
	int procnameSend(int send_data);
	char *receive(int pcnum);
	int procnameReceive(int rank);
	int procrankSend(int rank);
	int procrankReceive();
	int monosend(char * send_data);
	char *monoreceive(int pcnum);
	int testsend(int * send_data);
	int *testreceive(int pcnum);

};

