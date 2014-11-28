/****************************************
 このクラスは通信をするためのクラスである．
 通信関係の処理はできるだけココにまとめて書くこと
 ****************************************/

#include "Communication.h"
#include<iostream>
#include<stdlib.h>

using namespace std;

Communication::Communication(int argc, char *argv[]) {
	tag = 0;
	receivedata = NULL;

	MPI_Init(&argc, &argv);
	/*MPI ランクを取得 */
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	/*クラスタの台数取得 */
	MPI_Comm_size(MPI_COMM_WORLD, &nodenum);
	/*プロセッサ名取得 */
	MPI_Get_processor_name(processor_name, &name_len);
receivelist = new  int[HEIGHT * 5];
}

Communication::~Communication() {
	//cout << "(Comunication::~Communication): test!" << endl;
	delete[] receivedata;
	receivedata = NULL;
	MPI_Finalize();
	//cout << "Communication::~Communication()\n";
}

int Communication::getMyrank() {
	return myrank;
}

int Communication::getNodenum() {
	return nodenum;
}

string Communication::getProcessorname() {
	return processor_name;
}

int Communication::getProcessorname(char *name_array, int numberofelement) {
	if (name_len > numberofelement) {
		fprintf(stderr,
				"(Communication) getProcessorname: lack of array length.\n");
		exit(EXIT_FAILURE);
	}
	//strcpy(name_array, processor_name);

	return 0;
}

/*MPIを使ってデータを転送する*/
int Communication::send(char *send_data) {
	//TODO: send
	//MPI_Send(send_data.getPixels(), HEIGHT * WIDTH, MPI_CHAR, myrank, tag, MPI_COMM_WORLD ); //メッセージ送信

	// test用
	//cout << processor_name << ": sending..." << endl;
	MPI_Send(send_data, HEIGHT * WIDTH * 3, MPI_CHAR, 0,
			tag, MPI_COMM_WORLD);
	return 0;
}


/*MPIを使ってデータを受け取る*/
char *Communication::receive(int pcunum) {
	//TODO:receive
	MPI_Status recv_status;

	// test用
	//cout << processor_name << ": receiving..." << endl;
	receivedata = new  char[HEIGHT * WIDTH * 3];
	MPI_Recv(receivedata, HEIGHT * WIDTH * 3, MPI_CHAR, pcunum,
			tag, MPI_COMM_WORLD, &recv_status);

	return receivedata;
}

/*MPIを使ってデータを転送する*/
int Communication::procnameSend(int send_data) {
	//TODO: send
	//MPI_Send(send_data.getPixels(), HEIGHT * WIDTH, MPI_CHAR, myrank, tag, MPI_COMM_WORLD ); //メッセージ送信

	// test用
	//cout << processor_name << ": sending..." << endl;
	MPI_Send(&send_data, 1, MPI_INT, 0,tag, MPI_COMM_WORLD);
	return 0;
}

/*MPIを使ってデータを受け取る*/
int Communication::procnameReceive(int rank) {
	//TODO:receive
	MPI_Status recv_status;

	// test用
	//cout << processor_name << ": receiving..." << endl;
	int receivedata;
	MPI_Recv(&receivedata, 1, MPI_INT, rank,tag, MPI_COMM_WORLD, &recv_status);

	return receivedata;
}

/*MPIを使ってデータを転送する*/
int Communication::procrankSend(int rank) {
	//TODO: send
	//MPI_Send(send_data.getPixels(), HEIGHT * WIDTH, MPI_CHAR, myrank, tag, MPI_COMM_WORLD ); //メッセージ送信

	// test用
	//cout << processor_name << ": sending..." << endl;
	MPI_Send(&rank, 1, MPI_INT, 0,tag, MPI_COMM_WORLD);
	return 0;
}

/*MPIを使ってデータを受け取る*/
int Communication::procrankReceive() {
	//TODO:receive
	MPI_Status recv_status;

	// test用
	//cout << processor_name << ": receiving..." << endl;
	int receivedata;
	MPI_Recv(&receivedata, 1, MPI_INT, MPI_ANY_SOURCE,tag, MPI_COMM_WORLD, &recv_status);

	return receivedata;
}

/*MPIを使ってMONOCHROデータを転送する*/
int Communication::monosend(char *send_data) {
	//TODO: send
	//MPI_Send(send_data.getPixels(), HEIGHT * WIDTH, MPI_CHAR, myrank, tag, MPI_COMM_WORLD ); //メッセージ送信

	// test用
	//cout << processor_name << ": sending..." << endl;
	MPI_Send(send_data, HEIGHT * WIDTH, MPI_CHAR, 0,
			tag, MPI_COMM_WORLD);
	return 0;
}


/*MPIを使ってMONOCHROデータを受け取る*/
char *Communication::monoreceive(int pcunum) {
	//TODO:receive
	MPI_Status recv_status;

	// test用
	//cout << processor_name << ": receiving..." << endl;
	receivedata = new  char[HEIGHT * WIDTH];
	MPI_Recv(receivedata, HEIGHT * WIDTH, MPI_CHAR, pcunum,
			tag, MPI_COMM_WORLD, &recv_status);

	return receivedata;
}

/*MPIを使ってMONOCHROデータを転送する*/
int Communication::testsend(int *send_data) {
	//TODO: send
	//MPI_Send(send_data.getPixels(), HEIGHT * WIDTH, MPI_CHAR, myrank, tag, MPI_COMM_WORLD ); //メッセージ送信

	// test用
	//cout << processor_name << ": sending..." << endl;
	MPI_Send(send_data, HEIGHT * 5, MPI_INT, 0,
			tag, MPI_COMM_WORLD);
	return 0;
}


/*MPIを使ってMONOCHROデータを受け取る*/
int *Communication::testreceive(int pcunum) {
	//TODO:receive
	MPI_Status recv_status;

	// test用
	//cout << processor_name << ": receiving..." << endl;
	
	MPI_Recv(receivelist, HEIGHT * 5, MPI_INT, pcunum,
			tag, MPI_COMM_WORLD, &recv_status);

	return receivelist;
}

void barrier(){



}
