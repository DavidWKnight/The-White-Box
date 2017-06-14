import numpy as np
import scipy.io.wavfile

in_data = scipy.io.wavfile.read('guitar.wav')

#print(in_data[1])
with open('wav_out.txt', 'r') as f:
    iterator = 0
    for line in f:
        in_data[1][iterator] = int(line.strip('\n'))
        iterator += 1
    
    scipy.io.wavfile.write('ex edit.wav', in_data[0], in_data[1])