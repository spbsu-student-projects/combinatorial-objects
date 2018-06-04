#!/bin/bash
ls -d ../*/ >somefile
name=score_builder
g++ -O2 -Wall --std=c++11 $name.cpp -o $name
./$name
