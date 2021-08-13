#include "Audio.h"

#include "Default.h"

#if !DISABLE_AUDIO

using namespace std;

#include <QMediaContent>
#include <QUrl>

//**********************************************************************

Sound *Sound::create(const string &file) {
    auto s = new (std::nothrow) Sound{file};
    if (s) {
        s->autorelease();
        return s;
    }
    return nullptr;
}

Sound::Sound(const string &file) {
    player = new QMediaPlayer{};
    player->setMedia(QUrl::fromLocalFile(file.c_str()));
}

Sound::~Sound() { delete player; }

void Sound::play() { player->play(); }

void Sound::pause() { player->pause(); }

void Sound::toBegin() { player->setPosition(0); }

void Sound::setVolume(float volume) { player->setVolume(volume * 100); }

#endif
