スポーツビジョン班
========

##MPI
MPIの使い方の説明を書いていく。
スポーツビジョン班では、1台のサーバPCと15台のノードPCを用いて同期処理を行う。
なるべく汎用性のあるように説明していく。

##前提条件
前提条件として、各PCに以下のものが揃っているとする。(OSはCentOS6.5)

* opencv/opencv2
* mpich2
* python
* C/C++
* gcc/g++

##MPIの基本

##MPICH2実行方法

### mpd立ち上げに必要なもの  

### server PC

* mpd.hosts  
	同期するPCのリスト。このファイル内に記述してあるPCで同期処理が行われる。
	Server01は必須。ClientXXはLANケーブルで繋いであるPCのみを指定する。コメントアウトしたPCは同期処理されない。
	mpd.hostsファイルはコマンドラインで実行する時に、そのディレクトリになくてはならない。

``` mpd.hosts
Server01 //サーバーは必須.一台.
Client01 //クライアント(ノード)は1~n台
Client02
.
.
.
ClientN
```

* /etc/mpd.conf  
	上記のmpd.hostsファイル内で指定してある名前(Server01やClientXX)は/etc/直下にあるmpd.confというファイル内で定義されてある。
	名前とそのPCのIPアドレスを指定する。もしPCを増やしたりなど、新しいPCを追加する場合はこのファイル内に追加する必要がある。

```
192.XXX.XX.XX Server01
192.XXX.XX.XX Client01
.
.
.
```

###MPIの基本的な実行方法  

mpdの立ち上げ

```
$ mpdboot -n 2 -f mpd.hosts //オプション-n は同期するPC台数
```

mpdの起動確認(同期されているPCの名前が返ってくる)

```
$ mpdtrace
```

コンパイル

```
$ mpicc -o hello hello.c
```

実行

```
$ mpiexec -n 2 ./hello //-nは同期するPCの台数
```

終了

```
$ mpdallexit
```

##構築した環境の説明
スポーツビジョン班の実験のために作成した環境について説明する。この環境は、Appというディレクトリ内に構成されてある。
以下に簡単な概要を示す。

* bin/	: 実行ファイル(node/server)を格納するディレクトリ
* src/	: 実験に用いられるすべてのソースコードを格納するディレクトリ
* include/	: src/内のソースコードのヘッダーファイルを格納するディレクトリ
* data/	: 実験用の画像データを格納するディレクトリ
* main	: 実行ファイル(MPIを用いて同期処理をする場合に用いる。bin/直下のファイルがnode/serverPCでこの実行ファイルとなる)
* distribute.py	: serverPCからそれぞれのnodePCに配布する用のスクリプト。またmainファイルをnode/server用に書き換える
* node_list.txt	: distribute.pyで転送するPCのIPアドレスの一覧
* mpd.hosts		: mpdを実行するPCの一覧

開発時は、ヘッダーファイル(*.h)と実装ファイル(*.cpp)をそれぞれ適当なディレクトリに入れる。
src内にあるmakefileを用いてコンパイルする。
以下に簡単なmakefileの概要(流れ)を説明する。

makeすると、まずsrc内のすべてのプログラムをコンパイルする(include内のヘッダーファイルも含めて)。
その後、binディレクリ内にnodeとserverという名前の実行ファイルを２つ生成する。
(それぞれ個別にコンパイル等する必要はない。)

makefileを用いてコンパイルすると、nodeとserverそれぞれの実行ファイルができあがるので、この時点で同期処理が可能となる。

次に、MPIを用いて同期処理をするための流れを説明する。

まずは、作成した実行ファイルをそれぞれのPCに配布する。
Appディレクトリ直下で、distribute.pyを実行する。

```
$python distribute.py
```

すると、binディレクトリ内のnode実行ファイルをコピーし、Appディレクトリ内にmainという実行ファイルを作る。
その後、Appディレクトリが格納されているworkspace_satoというディレクトリをそれぞれのnodePCのrootのhome直下に配布する。
すべてのnodePCに配布がおわると、App/mainファイルを一度消し、今度はbin/serverをApp/mainとしてコピーする。

これによって、serverPCには、server用の実行ファイルmain、nodePCにはnode用の実行ファイルmainが配布されたことになる。

あとは、MPIのコマンドを打つことで同期処理を実行する。

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
