//#pragma once
#ifndef SOUND_CONTROLLER_H
#define SOUND_CONTROLLER_H

#include <map>
#include <thread>

#include "fmod.hpp"

class SoundController {
private:
    static SoundController* sharedController;
    std::thread *musicThread;
    FMOD::System *system;
    void *extradriverdata;
    FMOD_RESULT result;
    //std::map<std::string, std::pair<FMOD::Sound*, bool> > sounds;

    std::map<std::string, FMOD::Sound*> loadedSounds;
    std::map<std::string, FMOD::Channel*> playingSounds;

    void mainLoop();
public:
    SoundController();
    ~SoundController();

    static SoundController* getInstance();
    bool init();

    bool loadMusic(const std::string &filename);
    bool playMusic(const std::string &filename, bool loop = false);
    bool pauseMusic(const std::string &filename);
    bool resumeMusic(const std::string &filename);

    bool releaseMusic(const std::string &filename);
    bool releaseAllMusic();

    bool setVolume(const std::string &filename, float vol);
    void setVolume(float vol); // set all sounds' volume

    bool quit; /// temp
};

#endif