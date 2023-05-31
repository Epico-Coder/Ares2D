#pragma once

#include "dependancies/fmod/inc/fmod.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

namespace Ares2D
{
    class Audio {
    public:
        static Audio& Instance();

        static void add(const std::string& filePath, int audioID);
        static void remove(int audioID);

        static void play(int audioID, bool loop = false);
        static void pause(int audioID);
        static void resume(int audioID);
        static bool isPlaying(int audioID);

        static void fadeOut(int audioID, int fadeTimeMs = 2000);
        static void setTime(int audioID, unsigned int timeMs);
        static unsigned int getTime(int audioID);
    private:
        Audio();
        ~Audio();
    private:
        void i_add(const std::string& filePath, int audioID);
        void i_remove(int audioID);

        void i_play(int audioID, bool loop = false);
        void i_pause(int audioID);
        void i_resume(int audioID);
        bool i_isPlaying(int audioID);

        void i_fadeOut(int audioID, int fadeTimeMs = 2000);
        void i_setTime(int audioID, unsigned int timeMs);
        unsigned int i_getTime(int audioID);
    public:
        class Audio_Element {
        public:
            Audio_Element(FMOD::System* system, const std::string& filePath);
            ~Audio_Element();
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
        std::unordered_map<int, Audio_Element*> m_audios;
        FMOD_RESULT result;
    };
};