#ifndef TERRAINTEXTUREPACK_H
#define TERRAINTEXTUREPACK_H

class TerrainTexture;
class TerrainTexturePack
{
public:
    TerrainTexturePack(const char* backgroundTextureFile,
                       const char*rTextureFile, const char* gTextureFile, const char* bTextureFile);
    ~TerrainTexturePack();

    TerrainTexture* GetBackgroundTexture() { return backgroundTexture; }
    TerrainTexture* GetrTexture() { return rTexture; }
    TerrainTexture* GetgTexture() { return gTexture; }
    TerrainTexture* GetbTexture() { return bTexture; }

private:
    TerrainTexture *backgroundTexture;
    TerrainTexture *rTexture;
    TerrainTexture *gTexture;
    TerrainTexture *bTexture;

};

#endif // TERRAINTEXTUREPACK_H
