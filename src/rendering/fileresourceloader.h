//
//  fileresourceloader.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 08/12/14.
//
//

#ifndef Shader_fileresourceloader_h
#define Shader_fileresourceloader_h

#include "rendering/resourceloader.h"

class FileResourceLoader : public ResourceLoader {
   public:
    virtual char* readFile(std::string filename);
    virtual void setResourcesPath(std::string path);

   private:
    std::string resourcesPath_;
};

#endif
