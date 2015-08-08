#include "TerrainTexturePack.h"
#include "TerrainTexture.h"
#include "../toolbox/Loader.h"

TerrainTexturePack::TerrainTexturePack(const char *backgroundTextureFile,
                                       const char *rTextureFile, const char *gTextureFile, const char *bTextureFile)
{
    backgroundTexture = new TerrainTexture(Loader::LoadTexture(backgroundTextureFile,2));
    rTexture = new TerrainTexture(Loader::LoadTexture(rTextureFile,2));
    gTexture = new TerrainTexture(Loader::LoadTexture(gTextureFile,2));
    bTexture = new TerrainTexture(Loader::LoadTexture(bTextureFile,2));
}

TerrainTexturePack::~TerrainTexturePack()
{
    delete backgroundTexture;
    delete rTexture;
    delete gTexture;
    delete bTexture;
}
