#!/bin/bash

apt install -y qt4-dev-tools
xx="dev core gui script help declarative assistant network sql xml test webkit svg opengl xmlpatterns dbg"
for i in $xx
do
    apt install -y libqt4-$i
done
