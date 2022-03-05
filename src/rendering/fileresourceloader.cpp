#include "fileresourceloader.h"



char* FileResourceLoader::readFile(string filename)
{
    
    string filePath = resourcesPath + filename;
    FILE* fin = fopen(filePath.c_str(), "ra");
    if (fin == NULL)
    {
        return NULL;
    }

    fseek(fin, 0L, SEEK_END);
    long sz = ftell(fin);
    fseek(fin, 0L, SEEK_SET);

    char* buffer = new char[sz+1];

    memset(buffer, 0, sz);

    fread(buffer, 1, sz, fin);
    
    fclose(fin);
    return buffer;
}

void FileResourceLoader::setResourcesPath(string path)
{
    resourcesPath = path;
}
