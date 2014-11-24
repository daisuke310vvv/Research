#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
import os

#node側の実行ファイルをApp/mainとしてコピー
os.system('cp bin/node .')
os.system('mv ./node ./main')

#node_list内のnodeに~/workspace_satoディレクトリを転送
#workspace_sato は各自workspace_yournameで。
for line in open('node_list.txt','r'):
	print line
	os.system('scp -r ~/workspace_sato root@%s:~/' % line[:-1])

#server側の実行ファイルをApp/mainとしてコピー
os.system('cp bin/server .')
os.system('rm main')
os.system('mv ./server ./main')
