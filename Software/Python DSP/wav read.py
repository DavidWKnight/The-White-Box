import numpy as np
import scipy.io.wavfile
in_data = scipy.io.wavfile.read('guitar.wav')

with open('wav_in.txt', 'w') as f:
    f.write(str(in_data[0]) + ' ')
    f.write(" ".join(map(str, in_data[1])))