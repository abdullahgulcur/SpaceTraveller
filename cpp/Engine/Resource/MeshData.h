#pragma once

#include "glm.hpp"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Engine{

    namespace MeshData{

        struct MeshData{
            unsigned int vertexBuffer;
            IndexBuffer::IndexBuffer indexBuffer;
        };

        void loadStaticMesh(MeshData& data, std::string path);
        void loadStaticMeshTextured(MeshData& data, std::string path);
        void generateQuadSphereMeshTextured(MeshData& data);
        void generateTerrainBlockMesh(MeshData& data, unsigned int blockResolution);
        void generateTerrainOuterDegenerateMesh(MeshData& data, unsigned int blockResolution);

    }
}