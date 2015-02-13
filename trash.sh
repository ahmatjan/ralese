#!/bin/bash

rote=/home/mp3/rls
cur=`pwd`
cd $rote && ./bin/rls_control stop 
sleep 3
rm -rf log
cd ${cur}
cp rls ${rote}/bin
cd $rote && ./bin/rls_control start
