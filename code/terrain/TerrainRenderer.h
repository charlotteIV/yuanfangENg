#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include <list>
using namespace std;

class Terrain;
class TerrainShader;
class MasterRenderer;

class TerrainRenderer
{
public:
    TerrainRenderer(MasterRenderer *masterRender = NULL);
    ~TerrainRenderer();

    void Rendering();

    // Add one entity into entity list
    void AddTerrain(Terrain *terrain);

    // Bind VAO and VBO
    void PrepareTerrain(const Terrain *terrain);

    // Bind texture
    void BindTexture(const Terrain *terrain);

    // Unbind
    void UnbindTextureModel();

    // Create transformation matrix
    void LoadModelMatrix(const Terrain *terrain);

private:
    // Terrain shader
    TerrainShader *shader;

    // Master renderer pointer
    MasterRenderer *masterRender;

    // Terrain list
    list<Terrain*> terrains;
};

#endif // TERRAINRENDERER_H
