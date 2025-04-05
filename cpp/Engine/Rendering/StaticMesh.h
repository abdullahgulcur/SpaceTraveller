#pragma once

#include "Vao.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Engine{

    namespace Mesh {

        // bu sekilde olmasina gerek yok. her sahne icin gerekli olan degerleri cek.
        // generic birsey yapmak zorunda degilsin.
        // performance onemli.

        struct StaticMeshRenderer {

            unsigned int vao0, vao1, vao2;
            unsigned int indexElementType0, indexElementType1, indexElementType2;
            unsigned int totalIndices0, totalIndices1, totalIndices2;
            unsigned int shaderProgramId;
            unsigned int albedoTextureId;
            unsigned int uniformLocationProjectionView;
            unsigned int uniformLocationCameraPosition;

        };

    }
}
