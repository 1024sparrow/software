#!/bin/bash

tmp=$(pwd)

cp clone_terminal /usr/local/bin/
cd /usr/local/bin && ln -s ${tmp}/projects/80215_desktop_indicator/80215_desktop_indicator ./