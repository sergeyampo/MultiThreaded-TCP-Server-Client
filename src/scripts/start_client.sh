#!/bin/bash
for i in {1..21}
do
  ../build/client/client --factorial 20 --server 127.0.0.1:20001 &
done

sleep 1