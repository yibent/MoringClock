#include "Audio.h"

#include "Default.h"
#include "Director.h"

#if !DISABLE_AUDIO

using namespace std;

#include <QMediaContent>
#include <QUrl>

//**********************************************************************

Sound *Sound::create(const string &file)
{
    auto s = new (std::nothrow) Sound{file};
    if (s) {
        s->autorelease();
        return s;
    }
    return nullptr;
}

Sound::Sound(const string &file)
{
    auto ins = Director::instance;
    player = new QSound{str2qstr(file)};
    //auto status = player->mediaStatus();
    //qDebug() << (int)status << endl;
}

Sound::~Sound()
{
    delete player;
    //delete videoWidget;
}

void Sound::play() { player->play(); }

void Sound::pause() {
    
     //player->pause();
     player->stop();
     
      }

void Sound::toBegin() { 
    
    //player->setPosition(0);
     }

void Sound::setVolume(float volume) { 
    //player->setProperty()
    //player->setVolume(volume * 100);
     }

#endif
