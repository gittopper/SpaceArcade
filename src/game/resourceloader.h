//
//  resourceloader.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 08/12/14.
//
//

#ifndef Shader_resourceloader_h
#define Shader_resourceloader_h

#include <memory>
#include <string>
#include <vector>

using namespace std;

class ResourceLoader {
  public:
    virtual std::vector<char> readFile(string filename) = 0;
    virtual void setResourcesPath(string path) = 0;

    virtual ~ResourceLoader() {}
};
using ResourceLoaderPtr = std::shared_ptr<ResourceLoader>;

#endif
