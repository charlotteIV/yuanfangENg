#ifndef TEXTUREMODEL_H
#define TEXTUREMODEL_H

#include "RawModel.h"
#include "../textures/ModelTexture.h"

class TextureModel
{
public:
    TextureModel(RawModel *rawModel, ModelTexture *texture);
    ~TextureModel();

    // Retrieve raw model
    RawModel* GetRawModel() const { return rawModel; }

    // Retrieve texture
    ModelTexture* GetTexture() const { return texture; }

private:
    RawModel *rawModel;
    ModelTexture *texture;
};

#endif // TEXTUREMODEL_H
