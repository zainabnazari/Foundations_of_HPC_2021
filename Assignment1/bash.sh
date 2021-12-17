#!/bin/bash
for y in {2..36}

do
 for x in {1..10} 
 do
 sum=0
 mpicc check_ring.c 
 tim=$(mpirun -np $y a.out 2>/dev/null)
 sum=$(echo "$sum + $tim"| bc -l)
 done
 ave=$(echo "$sum / $x" | bc -l)
 echo $y, $ave >> time.txt
done
