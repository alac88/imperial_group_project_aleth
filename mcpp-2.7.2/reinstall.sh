#!/bin/bash

./configure --prefix=/var/tmp/mcpp --exec-prefix=/var/tmp/mcpp

make install

export PATH=$PATH:/var/tmp/mcpp/bin
