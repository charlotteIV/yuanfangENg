///////////////////////////////////////////////////////////////////////////////
//! Generally include all neccessary header file
///////////////////////////////////////////////////////////////////////////////

#ifndef HEUENGINE_H
#define HEUENGINE_H

#include "models/RawModel.h"
#include "models/ModelData.h"
#include "models/TextureModel.h"

#include "camera/Camera.h"
#include "entities/Entity.h"
#include "camera/FreeCamera.h"
#include "graphic/Light.h"
#include "entities/Actor.h"
#include "camera/ActorCamera.h"

#include "toolbox/Maths.h"
#include "toolbox/Random.h"

#include "Terrain/Terrain.h"
#include "Terrain/TerrainShader.h"

#include "textures/ModelTexture.h"
#include "textures/TerrainTexture.h"
#include "textures/TerrainTexturePack.h"

#include "shaders/ShaderProgram.h"
#include "static/StaticShader.h"


#include "toolbox/Loader.h"
#include "static/StaticRenderer.h"
#include "toolbox/MeshLoader.h"
#include "renderEngine/MasterRenderer.h"
#include "renderEngine/DisplayManager.h"

#endif // HEUENGINE_H
