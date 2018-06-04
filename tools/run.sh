#!/bin/bash
ls -d ../*/ >somefile
make
./score_builder
./log_builder
