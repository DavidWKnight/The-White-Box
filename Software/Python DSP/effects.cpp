#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
using namespace std;

#define max_sample_size 32767
#define one_third .33333
#define two_thirds .66666
#define __PI__ 3.14159

void delay_sample(int);
int delay(int, unsigned int, unsigned int, float);
int flange(int, float, float, unsigned int);
int reverb(int, float, unsigned int, float);
int tanh_OD(int, float, float);
int distortion(int, float, float);
int tremolo(int, float, float, float);

unsigned int samplerate;
float samplerate_float;
int delayed_sig[110250];
unsigned int delay_sig_it = sizeof(delayed_sig)/sizeof(delayed_sig[0]) - 1;

int main(){
    ifstream data_in;
    data_in.open("wav_in.txt");
    ofstream data_out;
    data_out.open("wav_out.txt");

    data_in >> samplerate;
    samplerate_float = float(samplerate);
    
    
    int sample;
    int sample_temp;
    while(!data_in.eof()){
        data_in >> sample;
        delay_sample(sample);

        //sample = flange(sample, 1, .005, 1);
        //sample = delay(sample, (unsigned int)(samplerate*.05), 1, 1);   
        //sample = distortion(sample, 100, .3);
        //sample = tanh_OD(sample, 25, .2);
        sample = tremolo(sample, 2500, 1, 2);
        sample *= .6;

        data_out << sample << '\n';
    }

    data_in.close();
    data_out.close();

    return 0;
}
/* puts copy of sample into memory for time based effects*/
void delay_sample(int sample){
    delayed_sig[delay_sig_it] = sample;
    delay_sig_it--;
    if(delay_sig_it >= sizeof(delayed_sig)/sizeof(delayed_sig[0])) {
        delay_sig_it = sizeof(delayed_sig)/sizeof(delayed_sig[0]) - 1;
    }
}

/*
 * time_delay = number of frames to delay by, .2-2.25 
 * (note max delay is always sizeof(delayedsig)/samplerate)
 */
int delay(int sample_in, unsigned int time_delay, unsigned int repeats, float decay){
    float sample = sample_in;
    float decay_ref = 1;
    unsigned int delay_ref = delay_sig_it;
    //cout << sizeof(delayed_sig)/sizeof(delayed_sig[0]) << endl;
    
    while (repeats > 0){
        delay_ref += time_delay;
        decay_ref *= decay;

        if(delay_ref >= sizeof(delayed_sig)/sizeof(delayed_sig[0])){
            delay_ref -= sizeof(delayed_sig)/sizeof(delayed_sig[0]);
        }
        
        sample += float(delayed_sig[delay_ref]) * decay_ref;
        
        if (abs(sample) > max_sample_size){
            sample *= .8;
        }
        
        repeats--;
    }

    return int(sample);
}

/*
 * speed = frequency of oscillation, 2-5
 * depth = range of delay in seconds, .001-.01
 */
int flange(int sample_in, float speed, float depth, unsigned int mode){
    static float ref = 0;
    unsigned int time_delay;
    if (mode == 1){
        ref += 1/float(samplerate);
        //cout << ref << '\n';
        
        time_delay = samplerate*depth*abs(sin(__PI__*ref*speed)) + 88;
        //cout << time_delay << '\n';
        return delay(sample_in, time_delay, 1, 1);
    }


    return sample_in;
}

int reverb(int sample_in, float reverb_time, unsigned int feedback, float decay){
    return delay(sample_in, (unsigned int)(samplerate*reverb_time), feedback, decay);
}

int tanh_OD(int sample_in, float gain, float mix){
    float sample = float(sample_in)/max_sample_size;
    float clean_sample = sample;
    sample = (exp(sample*gain) - exp(sample*-gain)) / (exp(sample*gain) + exp(sample*-gain));
    
    sample *= (1-mix);
    sample += (clean_sample * mix);

    return int(sample*max_sample_size);
}

/*
 * gain = amount of gain/distortion to add, 1-11
 * mix = ration of wet to clean signal, 0-1 (0 is wet, 1 is clean)
 */
int distortion(int sample_in, float gain, float mix){
    if(sample_in == 0){
        return 0;
    }
    float sample = float(abs(sample_in))/max_sample_size;
    float clean_sample = sample;

    sample = (1-pow(2.718, -abs(gain*sample)));

    sample *= (1-mix);
    sample += (clean_sample * mix);

    return (sample*max_sample_size*(sample_in/abs(sample_in)));
}

int tremolo(int sample_in, float rate, float depth, float wave){
    float sample = float(sample_in)/max_sample_size;
    static float trem_it = 1-depth;

    if (wave = 1){ //sawtooth
        trem_it += 2*depth*rate/samplerate_float;
        if(trem_it > 1+depth){
            trem_it = 1-depth;
        }
        sample *= 1-depth+trem_it;
    }
    else if(wave = 2){ //triangle wave
        float direction_mult = 1;
        trem_it += direction_mult*2*depth*rate/samplerate_float;
        if(trem_it > 1+depth){
            direction_mult = -1;
        }
        else if (trem_it < 1-depth){
            direction_mult = 1;
        }
    }

    return int(sample*44100);
}