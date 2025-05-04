#include <android/androidresourceloader.h>
#include <android/envwrapper.h>
#include <android/glesspacegamerenderer.h>
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
static GLESSpaceGameRenderer renderer;
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
        game->setRenderer(&renderer);
        env_wrapper = std::make_shared<EnvWrapper>(env);
        game->setPlayer(std::make_shared<SoundPlayer>(res_loader));
        game->setResourceLoader(res_loader);
        game->getRenderer()->initRenderer(res_loader.get());
        game->setupGame(width, height);
    }
    game->setResourceLoader(res_loader);
    game->getRenderer()->initRenderer(res_loader.get());
    int w, h;
    game->getRenderer()->getScreeenSize(w, h);
    if (w != width || h != height) {
        game->resize(width, height);
    }
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
    Java_com_example_arcadegame_GameEngine_setup(JNIEnv* env, jobject obj) {}
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
    return true;
}
}
