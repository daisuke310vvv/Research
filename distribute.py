#!/usr/bin/env python
import sys
import os
#print "cp  ../node ./Main_kato"
#os.system("cp  ../node ./Main_kato")
#for line in sys.stdin:
#	print "scp ./dist.txt root@%s:~/" % line[:-1]
#	os.system("scp ./dist.txt root@%s:~/" % line[:-1])
#os.system("cp  ../server ~/Main_kato")
#print "cp  ../server ~/Main_kato"

for line in open('node_list.txt','r'):
	print line
	os.system('scp ./hoge.txt root@%s:~/' % line[:-1])
