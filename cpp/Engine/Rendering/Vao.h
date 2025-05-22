#pragma once

namespace Engine {

    namespace Vao{

        void generate(unsigned int& vao);
        void bind(unsigned int vao);
        void unbind();
        void deleteVao(unsigned int& vao);
        void enableVertexAttributeArray(unsigned int index);
        void vertexAttributePointer(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset);
        void vertexAttributePointerNormalized(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset);
        void vertexAttributeIntegerPointer(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset);
        void vertexAttributePointerInstanced(unsigned int index, unsigned int size, unsigned int type, int stride, unsigned int offset);
        void vertexAttributePointerInstancedNormalized(unsigned int index, unsigned int size, unsigned int type, int stride, unsigned int offset);
        void vertexAttributeIntegerPointerInstanced(unsigned int index, unsigned int size, unsigned int type, int stride, unsigned int offset);
        void createLitMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId);
        void createLitMeshTexturedVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId);
        void createMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId, bool textured = false);
        void createMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId, unsigned int instanceBufferId, bool textured = false);
        void createBillboardMeshVao(unsigned int& vao, unsigned int vertexBufferId);
        void createParticleMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId);
        void createGalaxyMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId);
        void createQuadMeshVao(unsigned int& vao, unsigned int vertexBufferId);
        void createGridVao(unsigned int& vao, unsigned int vertexBufferId);
    }
}