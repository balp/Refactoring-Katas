#!/bin/bash
#rm -rf build/ ; mkdir build/ ;
if [[ ! -d build ]] ; then
  mkdir build
fi
(cd build/ && cmake .. && make $* && ctest -VV)
