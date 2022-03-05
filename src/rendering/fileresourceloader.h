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

using namespace std;

class FileResourceLoader: public ResourceLoader
{
public:
    
    virtual char* readFile(string filename);
    virtual void setResourcesPath(string path);
private:
    string resourcesPath;
};


#endif
