#include "Audio.h"

namespace Ares2D
{
    Audio::Audio()
    {
        result = FMOD::System_Create(&m_system);

        if (result != FMOD_OK) 
        {
            std::cout << "FMOD error! " << result << ": " << FMOD_RESULT(result) << std::endl;
        }

        result = m_system->init(32, FMOD_INIT_NORMAL, 0);

        if (result != FMOD_OK)
        {
            std::cout << "FMOD error! " << result << ": " << FMOD_RESULT(result) << std::endl;
        }
    }

    Audio::~Audio()
    {
        result = m_system->release();

        if (result != FMOD_OK)
        {
            std::cout << "FMOD error! " << result << ": " << FMOD_RESULT(result) << std::endl;
        }
    }

    /*-------------------------- Public Functions --------------------------*/

    Audio& Audio::Instance()
    {
        static Audio instance;
        return instance;
    }

    void Audio::add(const std::string& filePath, int audioID)
    {
        Instance().i_add(filePath, audioID);
    }

    void Audio::remove(int audioID)
    {
        Instance().i_remove(audioID);
    }

    void Audio::play(int audioID, bool loop)
    {
        Instance().i_play(audioID, loop);
    }

    void Audio::pause(int audioID)
    {
        Instance().i_pause(audioID);
    }

    void Audio::resume(int audioID)
    {
        Instance().i_resume(audioID);
    }

    bool Audio::isPlaying(int audioID)
    {
        return Instance().i_isPlaying(audioID);
    }

    void Audio::fadeOut(int audioID, int fadeTimeMs)
    {
        Instance().i_fadeOut(audioID, fadeTimeMs);
    }

    void Audio::setTime(int audioID, unsigned int timeMs)
    {
        Instance().i_setTime(audioID, timeMs);
    }

    unsigned int Audio::getTime(int audioID)
    {
        return Instance().i_getTime(audioID);
    }

    /*-------------------------- Internal Functions --------------------------*/

    void Audio::i_add(const std::string& filePath, int audioID)
    {
        m_audios[audioID] = new Audio_Element(m_system, filePath);
    }

    void Audio::i_remove(int audioID)
    {
        auto iter = m_audios.find(audioID);
        if (iter == m_audios.end()) {
            std::cout << "Audio with ID " << audioID << " does not exist" << std::endl;
        }
        else
        {
            m_audios.erase(iter);
        }
    }

    void Audio::i_play(int audioID, bool loop)
    {
        auto audio = m_audios.find(audioID);
        if (audio != m_audios.end()) {
            audio->second->play();
        }
    }

    void Audio::i_pause(int audioID)
    {
        auto audio = m_audios.find(audioID);
        if (audio != m_audios.end()) {
            audio->second->pause();
        }
    }

    void Audio::i_resume(int audioID)
    {
        auto audio = m_audios.find(audioID);
        if (audio != m_audios.end()) {
            audio->second->resume();
        }
    }

    bool Audio::i_isPlaying(int audioID)
    {
        auto audio = m_audios.find(audioID);
        if (audio != m_audios.end()) {
            return audio->second->isPlaying();
        }
        return false;
    }

    void Audio::i_fadeOut(int audioID, int fadeTimeMs)
    {
        auto audio = m_audios.find(audioID);
        if (audio != m_audios.end()) {
            audio->second->fadeOut();
        }
    }

    void Audio::i_setTime(int audioID, unsigned int timeMs)
    {
        auto audio = m_audios.find(audioID);
        if (audio != m_audios.end()) {
            audio->second->setTime(timeMs);
        }
    }

    unsigned int Audio::i_getTime(int audioID)
    {
        auto audio = m_audios.find(audioID);
        if (audio != m_audios.end()) {
            return audio->second->getTime();
        }
    }

    /*-------------------------- Child Functions --------------------------*/

    Audio::Audio_Element::Audio_Element(FMOD::System* system, const std::string& filePath) {
        m_system = system;
        m_system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &m_sound);
        m_sound->getLength(&m_length, FMOD_TIMEUNIT_MS);
    }

    Audio::Audio_Element::~Audio_Element()
    {
        m_sound->release();
        m_channel->stop();
    }

    void Audio::Audio_Element::play()
    {
        if (m_channel == nullptr) {
            FMOD_RESULT result = m_sound->setMode(FMOD_LOOP_NORMAL);
            result = m_system->playSound(m_sound, 0, false, &m_channel);

            // temporary set volume to retain ears
            //m_channel->setVolume(0.1f);
        }
        else {
            m_channel->setPaused(false);
            m_isPaused = false;
        }
    }

    void Audio::Audio_Element::pause()
    {
        if (m_channel != nullptr) {
            m_channel->setPaused(true);
            m_isPaused = true;
        }
    }

    void Audio::Audio_Element::resume()
    {
        if (m_channel != nullptr) {
            m_channel->setPaused(false);
            m_isPaused = false;
        }
    }

    bool Audio::Audio_Element::isPlaying()
    {
        if (m_channel != nullptr) {
            bool isPlaying = false;
            m_channel->isPlaying(&isPlaying);
            return isPlaying && !m_isPaused;
        }
        return false;
    }

    void Audio::Audio_Element::fadeOut(int fadeTimeMs)
    {
        if (m_channel != nullptr && !m_isFadingOut) {
            m_isFadingOut = true;
            unsigned int position;
            m_channel->setFadePointRamp(0, 0.0f);
            m_channel->setDelay(m_channel->getPosition(&position, FMOD_TIMEUNIT_MS), fadeTimeMs, true);
            m_channel->setPaused(true);
        }
    }

    void Audio::Audio_Element::setTime(unsigned int timeMs)
    {
        if (m_channel != nullptr) {
            FMOD_RESULT result = m_channel->setPosition(timeMs, FMOD_TIMEUNIT_MS);
        }
    }

    unsigned int Audio::Audio_Element::getTime()
    {
        if (m_channel != nullptr) {
            unsigned int timeMs = 0;
            m_channel->getPosition(&timeMs, FMOD_TIMEUNIT_MS);
            return timeMs;
        }
        return 0;
    }
};