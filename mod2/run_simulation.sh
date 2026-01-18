#!/bin/bash

# Run the Ising model simulation and analysis

echo "Compiling Ising model simulation..."
make

echo "Running simulation..."
./bin/ising

echo "Running analysis..."
cd scripts


echo "Creating animations..."
python animation.py

echo "All done! Results are in the data/ and plots/ directories."