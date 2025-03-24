//
// Created by stanislav on 21.03.2025.
//

#include "jnisoundplayer.h"

void JNISoundPlayer::play(const std::string& sound_file_name) {
    jclass sound_class = ew_->getEnv()->FindClass("com/example/arcadegame/Sound");
    jmethodID play = ew_->getEnv()->GetStaticMethodID(sound_class, "play",
                                                      "(Ljava/lang/String;)V");
    jstring jsound_file_name = ew_->getEnv()->NewStringUTF(sound_file_name.c_str());
    ew_->getEnv()->CallStaticVoidMethod(sound_class, play, jsound_file_name);
}
