//#pragma once
#ifndef SOUND_CONTROLLER_H
#define SOUND_CONTROLLER_H

#include <map>
//#include <thread>

#include "fmod.hpp"

class SoundController {
private:
    static SoundController* sharedController;
    //std::thread *musicThread;
    //std::function<void()> *_callbackFunc;

    FMOD::System *system;
    void *extradriverdata;
    FMOD_RESULT result;

    std::map<std::string, FMOD::Sound*> loadedSounds;
    std::map<std::string, FMOD::Channel*> playingSounds;

    //void mainLoop();
public:
    SoundController();
    ~SoundController();

    static SoundController* getInstance();
    bool init();

    bool loadMusic(const std::string &filename, void (*callback)(void *d) = nullptr, void *data = nullptr);
    bool playMusic(const std::string &filename, bool loop = false);
    bool pauseMusic(const std::string &filename);
    bool pauseAllMusic();
    bool resumeMusic(const std::string &filename);

    bool releaseMusic(const std::string &filename);
    bool releaseAllMusic();

    bool setVolume(const std::string &filename, float vol);
    void setVolume(float vol); // set all sounds' volume
};

#endif