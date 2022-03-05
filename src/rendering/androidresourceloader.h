//
//  androidresourceloader.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 09/12/14.
//
//

#ifndef Shader_androidresourceloader_h
#define Shader_androidresourceloader_h

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "rendering/resourceloader.h"

using namespace std;

class AndroidResourceLoader: public ResourceLoader
{
public:
	AndroidResourceLoader(AAssetManager* manager);
    virtual char* readFile(string filename);
    virtual void setResourcesPath(string path);
private:
    string resPath;
    AAssetManager* assetManager;
};


#endif
