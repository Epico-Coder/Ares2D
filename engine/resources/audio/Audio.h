#pragma once

#include "dependancies/fmod/inc/fmod.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

class AudioHandler {
public:
    AudioHandler();
    ~AudioHandler();

    void add(const std::string& filePath, int audioID);
    void remove(int audioID);

    void play(int audioID, bool loop=false);
    void pause(int audioID);
    void resume(int audioID);
    bool isPlaying(int audioID);

    void fadeOut(int audioID, int fadeTimeMs = 2000);
    void setTime(int audioID, unsigned int timeMs);
    unsigned int getTime(int audioID);
public:
    class Audio {
    public:
        Audio(FMOD::System* system, const std::string& filePath);
        ~Audio();
        void play();
        void pause();
        void resume();
        bool isPlaying();
        void fadeOut(int fadeTimeMs = 2000);
        void setTime(unsigned int timeMs);
        unsigned int getTime();

    private:
        FMOD::System* m_system = nullptr;
        FMOD::Sound* m_sound = nullptr;
        FMOD::Channel* m_channel = nullptr;
        unsigned int m_length = 0;
        bool m_isPaused = false;
        bool m_isFadingOut = false;
    };
private:
    FMOD::System* m_system = nullptr;
    std::unordered_map<int, Audio*> m_audios;
    FMOD_RESULT result;
};