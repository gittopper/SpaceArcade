//
//  androidresourceloader.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 09/12/14.
//
//

#ifndef Shader_androidresourceloader_h
#define Shader_androidresourceloader_h

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <jni.h>

#include "game/resourceloader.h"

using namespace std;

class AndroidResourceLoader : public ResourceLoader {
  public:
    AndroidResourceLoader(AAssetManager* manager);
    virtual std::vector<char> readFile(string filename);
    virtual void setResourcesPath(string path);

  private:
    string resPath_;
    AAssetManager* assetManager_;
};

#endif
