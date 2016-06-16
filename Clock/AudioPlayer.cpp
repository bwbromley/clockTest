/*
 * AudioPlayer.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: bromley
 */

#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() {
}

AudioPlayer::~AudioPlayer() {
	player.closeAudioDevice();
}
bool AudioPlayer::isPlaying() {
	return player.isPlaying();
}

/**
 * Pure virtual implementation.
 */
void AudioPlayer::threadBody() {
	while (whatToDo != -1) {
		if (whatToDo != 0) {
			mutex.lock();
			int temp = whatToDo;
			whatToDo = 0;
			mutex.unlock();
		if (temp)
			performCommand(temp);
		usleep(1000000);
		}
	}
}
/**
 * Pure virtual implementation.
 */
void AudioPlayer::start() {
	//player.openAudioDevice();
	thread = std::thread(&ClockPart::threadBody, this);
}
/**
 * Pure virtual implementation.
 */
void AudioPlayer::performCommand(int command) {

}
void AudioPlayer::setFilePath(string path) {
	player.setFilePath(path);
}

void AudioPlayer::setVolume(int volume) {
	player.setVolume(volume);
}

void AudioPlayer::play() {
	cout << "Player playing" << endl;
	player.play();
	cout << "Player done playing " << endl;
}
