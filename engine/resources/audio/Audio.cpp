#include "Audio.h"

AudioHandler::AudioHandler()
{
    result = FMOD::System_Create(&m_system);
    result = m_system->init(32, FMOD_INIT_NORMAL, 0);
}

AudioHandler::~AudioHandler()
{
}

void AudioHandler::add(const std::string& filePath, int audioID)
{
    m_audios[audioID] = new Audio(m_system, filePath);
}

void AudioHandler::remove(int audioID)
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

void AudioHandler::play(int audioID, bool loop)
{
    auto audio = m_audios.find(audioID);
    if (audio != m_audios.end()) {
        audio->second->play();
    }
}

void AudioHandler::pause(int audioID)
{
    auto audio = m_audios.find(audioID);
    if (audio != m_audios.end()) {
        audio->second->pause();
    }
}

void AudioHandler::resume(int audioID)
{
    auto audio = m_audios.find(audioID);
    if (audio != m_audios.end()) {
        audio->second->resume();
    }
}

bool AudioHandler::isPlaying(int audioID)
{
    auto audio = m_audios.find(audioID);
    if (audio != m_audios.end()) {
        return audio->second->isPlaying();
    }
    return false;
}

void AudioHandler::fadeOut(int audioID, int fadeTimeMs)
{
    auto audio = m_audios.find(audioID);
    if (audio != m_audios.end()) {
        audio->second->fadeOut();
    }
}

void AudioHandler::setTime(int audioID, unsigned int timeMs)
{
    auto audio = m_audios.find(audioID);
    if (audio != m_audios.end()) {
        audio->second->setTime(timeMs);
    }
}

unsigned int AudioHandler::getTime(int audioID)
{
    auto audio = m_audios.find(audioID);
    if (audio != m_audios.end()) {
        return audio->second->getTime();
    }
}


AudioHandler::Audio::Audio(FMOD::System* system, const std::string& filePath) {
    m_system = system;
    m_system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &m_sound);
    m_sound->getLength(&m_length, FMOD_TIMEUNIT_MS);
}

AudioHandler::Audio::~Audio()
{
    m_sound->release();
    m_channel->stop();
}

void AudioHandler::Audio::play() {
    if (m_channel == nullptr) {
        FMOD_RESULT result = m_sound->setMode(FMOD_LOOP_NORMAL);
        result = m_system->playSound(m_sound, 0, false, &m_channel);
    }
    else {
        m_channel->setPaused(false);
        m_isPaused = false;
    }
}

void AudioHandler::Audio::pause() {
    if (m_channel != nullptr) {
        m_channel->setPaused(true);
        m_isPaused = true;
    }
}

void AudioHandler::Audio::resume() {
    if (m_channel != nullptr) {
        m_channel->setPaused(false);
        m_isPaused = false;
    }
}

bool AudioHandler::Audio::isPlaying() {
    if (m_channel != nullptr) {
        bool isPlaying = false;
        m_channel->isPlaying(&isPlaying);
        return isPlaying && !m_isPaused;
    }
    return false;
}

void AudioHandler::Audio::fadeOut(int fadeTimeMs) {
    if (m_channel != nullptr && !m_isFadingOut) {
        m_isFadingOut = true;
        unsigned int position;
        m_channel->setFadePointRamp(0, 0.0f);
        m_channel->setDelay(m_channel->getPosition(&position, FMOD_TIMEUNIT_MS), fadeTimeMs, true);
        m_channel->setPaused(true);
    }
}

void AudioHandler::Audio::setTime(unsigned int timeMs) {
    if (m_channel != nullptr) {
        FMOD_RESULT result = m_channel->setPosition(timeMs, FMOD_TIMEUNIT_MS);
    }
}

unsigned int AudioHandler::Audio::getTime() {
    if (m_channel != nullptr) {
        unsigned int timeMs = 0;
        m_channel->getPosition(&timeMs, FMOD_TIMEUNIT_MS);
        return timeMs;
    }
    return 0;
}
