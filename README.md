スポーツビジョン班
========

##MPI
MPIの使い方の説明を書いていく。
MPIを用いて複数PCでの同期処理を行う。

##MPICH2実行方法

### mpd立ち上げに必要なもの  

* mpd.hosts  
	同期するPCのリスト

```
Server01 //サーバーは必須.一台.
Client01 //クライアント(ノード)は1~n台
Client02
.
.
.
ClientN
```

* /etc/mpd.conf  
	IPAdressと名前を指定
	(権限注意)

```
192.XXX.XX.XX Server01
192.XXX.XX.XX Client01
.
.
.
```

###MPICH2でのMPIデーモンの実行方法  

mpdの立ち上げ

```
$ mpdboot -n 2 -f mpd.hosts //オプション-n は同期するPC台数
```

mpdの起動確認

```
$ mpdtrace
```

終了

```
$ mpdallexit
```

コンパイル

```
$ mpicc -o hello hello.c
```

実行

```
$ mpiexec -n 2 ./hello
```

##同期処理の流れ

0. 作成したプログラムをすべてのPCのroot以下に置く。(パスはすべてのPCで同じにする)
1. サーバPCでmpdboot.
2. サーバPCでmpiexec.

##MPIでHello world

```c
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

int main(int argc, char *argv[]){

	MPI_Init(&argc,&argv); //MPI初期化

	printf("Hello world\n");

	MPI_Finalize();	//MPI終了


	return EXIT_SUCCESS;
}
```

##Rank/Size

```c
#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"

int main(int argc,char *argv[]){

	int myrank;
	int nodenum;

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nodenum);

	printf("my node rank: %d. size of node: %d\n",myrank,nodenum);

	MPI_Finalize();



	return EXIT_SUCCESS;
}
```

##Send/Recv

```c

#include <stdio.h>
#include <stdlib.h>

#include "mpi.h"
int main(int argc,char *argv[]){

	int myrank;
	int nodenum;
	int tag = 0;
	char message[256] = {0};

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	MPI_Comm_size(MPI_COMM_WORLD,&nodenum);

	if(myrank ==0){
		int source;	
		MPI_Status recv_status;

		for(source = 1;source<nodenum,source++){
			MPI_Recv(message,256,MPI_CHAR,source,tag,MPI_COMM_WORLD,&recv_status);
			printf("%s",message);
		}
	}else{
		strcat(message, "Helloworld\n");
		MPI_Send(message,strlen(message)+1,MPI_CHAR,0,tag,MPI_COMM_WORLD);
	}

	MPI_Finalize();


	return EXIT_SUCCESS;
}

```




































## workspace_sato

* workspace_sato
	- app
		- src
			- Server
				- server.c
			- Client
				- client.c
			- etc
	- mpd.hosts
	- README.md
