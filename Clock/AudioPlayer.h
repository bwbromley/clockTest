/*
 * AudioPlayer.h
 *
 *  Created on: Feb 19, 2016
 *      Author: bromley
 */

#ifndef AUDIOPLAYER_H_
#define AUDIOPLAYER_H_

#include "ClockPart.h"
#include <vector>
#include <string>
#include "Player.h"

using std::vector;
using std::string;

class AudioPlayer: public ClockPart {
public:
	AudioPlayer();
	virtual ~AudioPlayer();
	virtual void threadBody();
	virtual void start();
	virtual void performCommand(int command);
	void setVolume(int volume);
	Player player;
	void setAudio(vector<unsigned char>* data);
	void setFilePath(string fileName);
	void play();
	bool isPlaying();
private:
	vector<unsigned char>* audio;

};

#endif /* AUDIOPLAYER_H_ */
