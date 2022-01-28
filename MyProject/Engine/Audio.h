#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "Default.h"

#if !DISABLE_AUDIO

#include <QSound>
#include <string>
#include <vector>

#include "Ref.h"

class Sound : public Ref {
public:
    static Sound *create(const std::string &file);
    Sound(const std::string &file);
    virtual ~Sound();

    void play();
    void pause();
    //将音乐设置为从头播放
    void toBegin();
    // 0.0~1.0 音量大小
    void setVolume(float volume);

private:
    QSound *player = nullptr;

};

#endif

#endif