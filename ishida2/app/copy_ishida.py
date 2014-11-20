#!/usr/bin/env python

# writen by Ishida (2013) 

import sys
import os
print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
print "This program copy and rename files(node, server)"
print "  Rename node & server to Main_test and send each Client."
print "  Client01, 02, 03, 04, 07, 08, 09, 10, 12, 13"
print "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

print     "cp /home/user/ishida2/node /home/user/ishida2/app/Main_test"
os.system("cp /home/user/ishida2/node /home/user/ishida2/app/Main_test")

print "------start copying file to each node.------"
print     "scp /home/user/ishida2/app/Main_test root@Client01:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client01:~/")

print     "scp /home/user/ishida2/app/Main_test root@Client02:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client02:~/")

print     "scp /home/user/ishida2/app/Main_test root@Client03:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client03:~/")

print     "scp /home/user/ishida2/app/Main_test root@Client04:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client04:~/")

print     "scp /home/user/ishida2/app/Main_test root@Client07:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client07:~/")

print     "scp /home/user/ishida2/app/Main_test root@Client08:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client08:~/")

print     "scp /home/user/ishida2/app/Main_test root@Client09:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client09:~/")

print     "scp /home/user/ishida2/app/Main_test root@Client10:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client10:~/")

print     "scp /home/user/ishida2/app/Main_test root@Client12:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client12:~/")

print     "scp /home/user/ishida2/app/Main_test root@Client13:~/"
os.system("scp /home/user/ishida2/app/Main_test root@Client13:~/")

print "------copying file to each node done.------"
print     "cp /home/user/ishida2/server ~/Main_test"
os.system("cp /home/user/ishida2/server ~/Main_test")
print "~~~~~~~~~~~exit this program.~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
