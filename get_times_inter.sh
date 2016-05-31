#!/bin/bash
sample_size=50

for (( seq_num=1; seq_num <= $sample_size; ++seq_num ))
do
  time -p  ./large_interchange 
done
