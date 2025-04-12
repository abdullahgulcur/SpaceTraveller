#pragma once

namespace Engine {

    namespace Vao{

        struct Vao{
            unsigned int vao;
        };

        void generate(unsigned int& vao);
        void bind(unsigned int vao);
        void unbind();
        void enableVertexAttributeArray(unsigned int index);
        void vertexAttributePointer(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset);
        void vertexAttributeIntegerPointer(unsigned int index, unsigned int size, unsigned int type, unsigned int stride, unsigned int offset);
        void vertexAttributePointerInstanced(unsigned int index, unsigned int size, unsigned int type, int stride, unsigned int offset);
        void vertexAttributeIntegerPointerInstanced(unsigned int index, unsigned int size, unsigned int type, int stride, unsigned int offset);
        void createMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId, bool textured = false);
        void createMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int indexBufferId, unsigned int instanceBufferId, bool textured = false);
        void createBillboardMeshVao(unsigned int& vao, unsigned int vertexBufferId);
        void createBillboardMeshVao(unsigned int& vao, unsigned int vertexBufferId, unsigned int instanceBufferId);

    }
}