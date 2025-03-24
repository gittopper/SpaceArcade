#include <game/spacegame.h>
#include <jni.h>

#include <list>
#include <memory>
#include <string>
#include <mutex>

#include "rendering/androidresourceloader.h"
#include <android/jnisoundplayer.h>
#include "rendering/rendererfactory.h"

using namespace Game;

std::shared_ptr<SpaceGame> game;
std::shared_ptr<EnvWrapper> env_wrapper;
std::mutex m;
extern "C" {

JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_init(
    JNIEnv* env, jobject obj, jint width, jint height,
    jobject javaAssetManager) {
    std::lock_guard<std::mutex> lock(m);
    if (nullptr == game) {
        game = std::make_shared<SpaceGame>();
        game->setRenderer(RendererFactory::getGLESRenderer());
        env_wrapper = std::make_shared<EnvWrapper>(env);
        game->setPlayer(std::make_shared<JNISoundPlayer>(env_wrapper));
    }
    ResourceLoader* res =
        dynamic_cast<ResourceLoader*>(new AndroidResourceLoader(
            AAssetManager_fromJava(env, javaAssetManager)));
    const bool ok = game->getRenderer()->initRenderer(res);
    int w, h;
    game->getRenderer()->getScreeenSize(w, h);
    if (w != width || h != height) {
        game->getRenderer()->setScreeenSize(width, height);
        game->setupGame();
    }
    // game->getRenderer()->createFramebuffer();
    // game->getRenderer()->updateInfoAboutWindow();
}

JNIEXPORT void JNICALL
Java_com_example_arcadegame_GameEngine_step(JNIEnv* env, jobject obj) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->renderStep();
}

JNIEXPORT void JNICALL
Java_com_example_arcadegame_GameEngine_showFrame(JNIEnv* env, jobject obj) {
    std::lock_guard<std::mutex> lock(m);
    env_wrapper->setEnv(env);
    game->showFrame();
}

JNIEXPORT void JNICALL
Java_com_example_arcadegame_GameEngine_setup(JNIEnv* env, jobject obj) {
}
JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_tap(JNIEnv* env,
                                                                  jobject obj,
                                                                  jfloat x,
                                                                  jfloat y) {}

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
    // game->getRenderer()->destroyFramebuffer();
    return true;
}
}
