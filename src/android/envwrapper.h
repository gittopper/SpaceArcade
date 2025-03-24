//
// Created by stanislav on 21.03.2025.
//

#ifndef ANDROIDSTUDIO_ENVWRAPPER_H
#define ANDROIDSTUDIO_ENVWRAPPER_H

#include <jni.h>

class EnvWrapper {
public:
    EnvWrapper(JNIEnv* env):
    env_(env){}
    [[nodiscard]] JNIEnv* getEnv() const {
        return env_;
    }
    void setEnv(JNIEnv* env) {
        env_ = env;
    }
private:
    JNIEnv* env_;
};

#endif //ANDROIDSTUDIO_ENVWRAPPER_H
