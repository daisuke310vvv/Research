#ifndef ONCE
#define ONCE
//２重インクルード防止
#include "./Image.h"
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

	/**
	 * Communication() 
	 * コンストラクタ(初期化してインスタンスを返す)
	 */
	Communication(int argc, char *argv[]);

	/**
	 * ~Communication()
	 * デストラクタ(終了時に呼ぶ)
	 */
	~Communication();

	/**
	 * getMyrank()
	 * クラスタのランクを返す
	 * 0	: サーバ
	 * !0	: ノード
	 */
	int getMyrank();

	/**
	 * getNodenum()
	 * ノードの番号を返す
	 */
	int getNodenum();

	/**
	 * getProcessorname
	 * ???
	 * @param name_array 名前の格納された配列
	 * @param numberofelement (該当する？)要素番号
	 **/
	int getProcessorname(char *name_array, int numberofelement);

	/**
	 * getProcessorname
	 * プロセッサの名前を返す
	 **/
	string getProcessorname();

	/**
	 * send
	 * データを送る
	 * @param send_data これはデータのアドレス?
	 */
	int send(char * send_data);

	/**
	 * procnameSend()
	 * データを送る
	 * @param send_data int型でデータ?
	 */
	int procnameSend(int send_data);

	/**
	 * receive()
	 * データを受け取る
	 * @param pcnum クラスタの番号(nodenum)？
	 */
	char *receive(int pcnum);
	int procnameReceive(int rank);
	int procrankSend(int rank);
	int procrankReceive();
	int monosend(char * send_data);
	char *monoreceive(int pcnum);
	int testsend(int * send_data);
	int *testreceive(int pcnum);

};

