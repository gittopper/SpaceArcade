#include <android/androidresourceloader.h>
#include <android/envwrapper.h>
#include <rendering//glesspacegamerenderer.h>
#include <game/soundplayer.h>
#include <game/spacegame.h>

#include <jni.h>
#include <list>
#include <memory>
#include <mutex>
#include <string>

using namespace Game;

std::shared_ptr<SpaceGame> game;
std::shared_ptr<EnvWrapper> env_wrapper;
std::mutex m;

extern "C" {

JNIEXPORT void JNICALL
    Java_com_example_arcadegame_GameEngine_init(JNIEnv* env,
                                                jobject obj,
                                                jint width,
                                                jint height,
                                                jobject javaAssetManager) {
    std::lock_guard<std::mutex> lock(m);
    std::shared_ptr<ResourceLoader> res_loader(new AndroidResourceLoader(
        AAssetManager_fromJava(env, javaAssetManager)));
    if (nullptr == game) {
        game = std::make_shared<SpaceGame>();
        auto renderer = std::make_shared<GLESSpaceGameRenderer>();
        renderer->initRenderer(res_loader.get());
        game->setRenderer(renderer);
        env_wrapper = std::make_shared<EnvWrapper>(env);
        game->game_state_.player_ = std::make_shared<SoundPlayer>(res_loader);
        game->game_state_.resource_loader_ = res_loader;
        game->setupGame(width, height);
    }
    game->game_state_.resource_loader_ = res_loader;
    game->getRenderer()->initRenderer(res_loader.get());
    game->resize(width, height);
}

JNIEXPORT void JNICALL
    Java_com_example_arcadegame_GameEngine_step(JNIEnv* env, jobject obj) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->renderStep();
}

JNIEXPORT void JNICALL
    Java_com_example_arcadegame_GameEngine_onPause(JNIEnv* env, jobject obj) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->pause();
}

JNIEXPORT void JNICALL
    Java_com_example_arcadegame_GameEngine_onResume(JNIEnv* env, jobject obj) {
    std::lock_guard<std::mutex> lock(m);
    if (game) {
        env_wrapper->setEnv(env);
        game->resume();
    }
}

JNIEXPORT void JNICALL
    Java_com_example_arcadegame_GameEngine_showFrame(JNIEnv* env, jobject obj) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->showFrame();
}

JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_tap(JNIEnv* env,
                                                                  jobject obj,
                                                                  jfloat x,
                                                                  jfloat y) {}

JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_dragStart(
    JNIEnv* env, jobject obj, jfloat x1, jfloat y1, jfloat x2, jfloat y2) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->dragStart(x1, y1, x2, y2);
}

JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_drag(
    JNIEnv* env, jobject obj, jfloat x1, jfloat y1, jfloat x2, jfloat y2) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->drag(x1, y1, x2, y2);
}

JNIEXPORT void JNICALL
    Java_com_example_arcadegame_GameEngine_dragStop(JNIEnv* env, jobject obj) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->dragStop();
}

JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_actionDown(
    JNIEnv* env, jobject obj, jfloat x, jfloat y) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->tap(x, y);
}

JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_actionMove(
    JNIEnv* env, jobject obj, jfloat x, jfloat y) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->drag(x, y);
}

JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_actionUp(
    JNIEnv* env, jobject obj, jfloat x, jfloat y) {}

JNIEXPORT jboolean JNICALL
    Java_com_example_arcadegame_GameEngine_stop(JNIEnv* env, jobject obj) {
    return true;
}

JNIEXPORT jboolean JNICALL
    Java_com_example_arcadegame_GameEngine_free(JNIEnv* env, jobject obj) {
    return true;
}
}
