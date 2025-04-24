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
    }

//    class MeshData{
//
//    private:
//    public:
//
//        VertexBuffer::VertexBuffer vertexBuffer;
//        IndexBuffer::IndexBuffer indexBuffer;
//
//        MeshData(){}
//        ~MeshData(){}
//        void loadStaticMesh(std::string& path);
//        void loadStaticMeshTextured(std::string& path);
//        void loadSkinnedMesh(std::string& path);
//        void loadSkinnedMeshTextured(std::string& path);
//    };
}
