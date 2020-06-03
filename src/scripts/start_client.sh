#!/bin/bash
for i in {1..5}
do
  ../build/client/client --k 1 --mod 5 --servers ../server/server
done
