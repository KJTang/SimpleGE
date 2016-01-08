#include "SoundController.h"

#include <Windows.h>

SoundController* SoundController::sharedController = nullptr;

SoundController::SoundController() {}

SoundController::~SoundController() {}

SoundController* SoundController::getInstance() {
    if (!sharedController) {
        sharedController = new SoundController();
        sharedController->init();
    }
    return sharedController;
}

bool SoundController::init() {
    /*
    Create a System object and initialize
    */
    result = FMOD::System_Create(&system);
    if (result != FMOD_OK) {
        return false;
    }
    extradriverdata = nullptr;
    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    if (result != FMOD_OK) {
        return false;
    }

    return true;
}

bool SoundController::loadMusic(const std::string &filename, void(*callback)(void *d), void *data) {
    FMOD::Sound *sound = nullptr;
    result = system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
    if (result != FMOD_OK) {
        return false;
    }

    loadedSounds.insert(std::make_pair(filename, sound));
    // start the callback function
    if (callback) {
        callback(data);
    }
}

bool SoundController::playMusic(const std::string &filename, bool loop) {
    auto it = loadedSounds.find(filename);
    if (it == loadedSounds.end()) { // no music has this name
        return false;
    }

    auto it2 = playingSounds.find(filename);
    if (it2 != playingSounds.end()) {
        bool isplaying = true;
        (*it2).second->isPlaying(&isplaying);
        if (isplaying == true) { // already playing
            return false;
        }
    }

    if (loop) {
        (*it).second->setMode(FMOD_LOOP_NORMAL);
    }
    else {
        (*it).second->setMode(FMOD_LOOP_OFF);
    }
    FMOD::Channel *channel;
    system->playSound((*it).second, 0, false, &channel);
    playingSounds.insert(std::make_pair(filename, channel));
    return true;
}

bool SoundController::pauseMusic(const std::string &filename) {
    auto it = playingSounds.find(filename);
    if (it == playingSounds.end()) {
        return false;
    }
    (*it).second->setPaused(true);
    playingSounds.erase(filename);
    return true;
}

bool SoundController::pauseAllMusic() {
    for (auto it = playingSounds.begin(); it != playingSounds.end(); ++it) {
        (*it).second->setPaused(true);
    }
    playingSounds.clear();
    return true;
}

bool SoundController::resumeMusic(const std::string &filename) {
    auto it = playingSounds.find(filename);
    if (it != playingSounds.end()) {
        return false;
    }
    auto it2 = loadedSounds.find(filename);
    if (it2 == loadedSounds.end()) {
        return false;
    }
    playMusic(filename);
    return true;
}

bool SoundController::releaseMusic(const std::string &filename) {
    auto it = loadedSounds.find(filename);
    if (it == loadedSounds.end()) {
        return false;
    }
    auto result = (*it).second->release();
    if (result != FMOD_OK) {
        return false;
    }
    loadedSounds.erase(filename);
    playingSounds.erase(filename);
    return true;
}

bool SoundController::releaseAllMusic() {
    for (auto it = loadedSounds.begin(); it != loadedSounds.end(); ++it) {
        auto result = (*it).second->release();
        if (result != FMOD_OK) {
            return false;
        }
    }
    playingSounds.clear();
}

bool SoundController::setVolume(const std::string &filename, float vol) {
    auto it = playingSounds.find(filename);
    if (it == playingSounds.end()) {
        return false;
    }
    if (vol > 1.0) {
        vol = 1.0;
    }
    if (vol < 0.0) {
        vol = 0.0;
    }
    (*it).second->setVolume(vol);
    return true;
}

void SoundController::setVolume(float vol) {
    if (vol > 1.0) {
        vol = 1.0;
    }
    if (vol < 0.0) {
        vol = 0.0;
    }
    for (auto it = playingSounds.begin(); it != playingSounds.end(); ++it) {
        (*it).second->setVolume(vol);
    }
}