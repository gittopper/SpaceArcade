#include <jni.h>
#include <game/spacegame.h>

#include <list>
#include <string>
#include "rendering/androidresourceloader.h"
#include "rendering/rendererfactory.h"


using namespace Game;

SpaceGame* game;

extern "C" {

	JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_init(JNIEnv* env, jobject obj, jint width, jint height, jobject javaAssetManager)
	{
		bool ex = true, t;

		while (!ex)
		{
			t = true;
		}
		game = new SpaceGame;
		game->setRenderer(RendererFactory::getGLESRenderer());
		ResourceLoader* res = dynamic_cast<ResourceLoader*>(new AndroidResourceLoader(AAssetManager_fromJava(env, javaAssetManager)));

        const bool ok = game->getRenderer()->initRenderer(res);
        //game->getRenderer()->createFramebuffer();
        game->getRenderer()->setScreeenSize(width, height);
        //game->getRenderer()->updateInfoAboutWindow();
        game->setupGame();
	}

	JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_step(JNIEnv* env, jobject obj){
        game->renderStep();
	}

	JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_tap(JNIEnv* env, jobject obj, jfloat x, jfloat y){
	}

	JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_actionDown(JNIEnv* env, jobject obj, jfloat x, jfloat y){
        game->tap(x, y);
	}

	JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_actionMove(JNIEnv* env, jobject obj, jfloat x, jfloat y){
		game->drag(x,y);
	}

	JNIEXPORT void JNICALL Java_com_example_arcadegame_GameEngine_actionUp(JNIEnv* env, jobject obj, jfloat x, jfloat y){
	}


	JNIEXPORT jboolean JNICALL Java_com_example_arcadegame_GameEngine_stop(JNIEnv* env, jobject obj){
		return true;
	}

	JNIEXPORT jboolean JNICALL Java_com_example_arcadegame_GameEngine_free(JNIEnv* env, jobject obj){
        //game->getRenderer()->destroyFramebuffer();
		delete game;
		return true;
	}
}
