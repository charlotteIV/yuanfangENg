#ifndef OBJLOADER_H
#define OBJLOADER_H

#include "Loader.h"
#include "../models/RawModel.h"
#include <string>
using namespace std;

class MeshLoader
{
public:
    MeshLoader(){}

    static RawModel *LoadObjModel(string fileName);
};

#endif // OBJLOADER_H
