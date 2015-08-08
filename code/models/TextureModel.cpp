#include "TextureModel.h"


TextureModel::TextureModel(RawModel *rawModel, ModelTexture *texture)
{
    this->rawModel = rawModel;
    this->texture  = texture;
}

TextureModel::~TextureModel()
{
    delete rawModel;
    delete texture;
}
