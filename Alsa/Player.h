/*
 * player.h
 *
 *  Created on: Feb 15, 2016
 *      Author: bromley
 *  Modified from:
 *    http://www.linuxquestions.org/questions/programming-9/c-playing-a-wav-file-with-lib-asound-4175467877/
 *
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <alsa/asoundlib.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

class Player {

public:
	Player();
	virtual ~Player();
	int waveLoad(char* fileName);
	void playAudio();
	void freeWaveData();
	int openAudioDevice();
	void closeAudioDevice();
	void play(vector<unsigned char>* data);
	void copyData(vector<unsigned char>* data);
	void play();
	void setFilePath(string path);
	bool isPlaying();
	void setVolume(int percent);
private:
	struct FileHead {
		unsigned char	id[4];	// could be {'R', 'I', 'F', 'F'} or {'F', 'O', 'R', 'M'}
		unsigned int	length;
		unsigned char	type[4];	// {'W', 'A', 'V', 'E'} or {'A', 'I', 'F', 'F'}
	} ;
	struct ChunkHead {
		unsigned char id[4];
		unsigned int	length;
	} ;
	struct WavFormat {
		short				formatTag;
		unsigned short	channels;
		unsigned int	samplesPerSec;
		unsigned int	avgBytesPerSec;
		unsigned short	blockAlign;
		unsigned short	bitsPerSample;
	} ;
	bool playing;
	string filePath;
	int getPcmFormat(unsigned char nBits);
	int compareId(const unsigned char * id, unsigned char * ptr);
	unsigned int	 waveSize;
	snd_pcm_t* playbackHandle;
	unsigned char* wavData;
	unsigned short waveRate;
	unsigned char waveBits;
	unsigned char waveChannels;
	static const char SoundCardPortName[];
	static unsigned char riff[4];
	static unsigned char wave[4];
	static unsigned char fmt[4];
	static unsigned char data[4];
};

#endif /* PLAYER_H_ */
