#! /bin/bash
cd pbPlot/
g++ pbPlots.cpp -o pbPlots.o
g++ supportLib.cpp -o supportLib.o
cd ..
g++ Graph.cpp -o Graph.o
g++ Graph.o pb\ Plot/pbPlots.o pb\ Plot/supportLib.o -lm -o GraphExecute.o
strip GraphExecute.o
./GraphExecute.o