#!/bin/bash
g++ -std=c++11 "effects.cpp" -o "effects"
"/home/david/Projects/Python DSP/"effects
python "/home/david/Projects/Python DSP/wav write.py"
play ex\ edit.wav
