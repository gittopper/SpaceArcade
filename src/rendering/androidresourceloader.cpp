#include "rendering/androidresourceloader.h"


AndroidResourceLoader::AndroidResourceLoader(AAssetManager* manager):
assetManager(manager)
{

}
char* AndroidResourceLoader::readFile(string filename)
{
	char* buffer = NULL;
	AAssetDir* assetDir = AAssetManager_openDir(assetManager, resPath.c_str());
	if (!assetDir)
	{
		return buffer;
	}

	AAsset* asset = AAssetManager_open(assetManager, filename.c_str(),AASSET_MODE_BUFFER);
	if(asset)
	{
		long length = AAsset_getLength(asset);

		buffer = new char[length+1];
		long offset = 0;
		long readed = 0;
		while((readed = AAsset_read(asset, buffer + offset, length - offset)) > 0){
			offset += readed;
		}

		AAsset_close(asset);

		buffer[length] = '\0';
	}

	AAssetDir_close(assetDir);

	return buffer;
}
void AndroidResourceLoader::setResourcesPath(string path)
{
	resPath = path;
}
