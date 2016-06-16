#!/bin/bash
# convert all .wav files in this directory to 44100 Hz stereo
for f in *.wav
do
	sox -S $f $f channels 2 rate -L -s 44100
done

