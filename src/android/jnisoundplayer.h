//
// Created by stanislav on 21.03.2025.
//

#ifndef ANDROIDSTUDIO_JNISOUNDPLAYER_H
#define ANDROIDSTUDIO_JNISOUNDPLAYER_H

#include <jni.h>

#include <game/isoundplayer.h>
#include <android/envwrapper.h>

class JNISoundPlayer: public ISoundPlayer {
public:
    JNISoundPlayer(std::shared_ptr<EnvWrapper> ew): ew_(ew){}
    void play(const std::string& sound_file_name) override;
private:
    std::shared_ptr<EnvWrapper> ew_;
};


#endif //ANDROIDSTUDIO_JNISOUNDPLAYER_H
