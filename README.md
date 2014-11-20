スポーツビジョン班
========

##MPI
MPIの使い方の説明を書いていく。
MPIを用いて複数PCでの同期処理を行う。

##MPICH2実行方法

* MPICH2でのMPIデーモンの実行方法  

	```mpdの立ち上げ
	$ mpdboot -n 2 -f mpd.hosts //オプション-n は同期するPC台数
	```

	```mpdの起動確認
	$ mpdtrace
	```

	```終了
	$ mpdallexit
	```


##MPIでHello world

```helloworld.c
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

```
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

```
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

##コンパイル

```
$ mpicc -o hello hello.c
```

```
$ mpiexec -n 2 ./hello
```


































