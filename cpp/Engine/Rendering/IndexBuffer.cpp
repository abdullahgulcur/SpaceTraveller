#include "pch.h"
#include "IndexBuffer.h"
#include <GLES3/gl32.h>

namespace Engine {

    namespace IndexBuffer {

        void generate(unsigned int& bufferId){
            glGenBuffers(1, &bufferId);
        }

        void bind(unsigned int bufferId){
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
        }

        void unbind(){
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        void clear(unsigned int& bufferId){
            glDeleteBuffers(1, &bufferId);
        }

        unsigned int getIndexElementType(unsigned int maxIndex){
            if(maxIndex < 256)
                return GL_UNSIGNED_BYTE;
            if(maxIndex < 65536)
                return GL_UNSIGNED_SHORT;
            return GL_UNSIGNED_INT;
        }

        void bufferData(unsigned int bufferId, unsigned int size, void* ptr){
            bind(bufferId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, ptr, GL_STATIC_DRAW);
        }

        void bufferData(IndexBuffer& indexBuffer, std::vector<unsigned int>& indices){
            unsigned int maxIndex = *std::max_element(indices.begin(), indices.end());
            indexBuffer.indexElementType = getIndexElementType(maxIndex);
            indexBuffer.totalIndices = indices.size();
            switch(indexBuffer.indexElementType){
                case GL_UNSIGNED_BYTE:{
                    std::vector<unsigned char> newIndices(indexBuffer.totalIndices);
                    for(int i = 0; i < indexBuffer.totalIndices; i++)
                        newIndices[i] = static_cast<unsigned char>(indices[i]);

                    bufferData(indexBuffer.bufferId, indexBuffer.totalIndices, &newIndices[0]);
                    break;
                }
                case GL_UNSIGNED_SHORT:{
                    std::vector<unsigned short> newIndices(indexBuffer.totalIndices);
                    for(int i = 0; i < indexBuffer.totalIndices; i++)
                        newIndices[i] = static_cast<unsigned short>(indices[i]);

                    bufferData(indexBuffer.bufferId, indexBuffer.totalIndices * 2, &newIndices[0]);
                    break;
                }
                case GL_UNSIGNED_INT:{
                    bufferData(indexBuffer.bufferId, indexBuffer.totalIndices * 4, &indices[0]);
                    break;
                }
            };
        }

        void draw(unsigned int totalIndices, unsigned int indexElementType){
            glDrawElements(GL_TRIANGLES, totalIndices, indexElementType, (void*)0);
        }

        void drawInstanced(unsigned int totalIndices, unsigned int indexElementType, unsigned int instanceCount){
            glDrawElementsInstanced(GL_TRIANGLES, totalIndices, indexElementType, (void*)0, instanceCount);
        }

    }

    /*IndexBuffer::IndexBuffer(){
        glGenBuffers(1, &bufferId);
    }*/

    /*void IndexBuffer::bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
    }

    void IndexBuffer::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void IndexBuffer::clear() {
        IndexBuffer::bind();
        glDeleteBuffers(1, &bufferId);
    }

    unsigned int IndexBuffer::getIndexElementType(unsigned int maxIndex){
        if(maxIndex < 256)
            return GL_UNSIGNED_BYTE;
        if(maxIndex < 65536)
            return GL_UNSIGNED_SHORT;
        return GL_UNSIGNED_INT;
    }

    void IndexBuffer::bufferData(unsigned int size, void* ptr){
        IndexBuffer::bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, ptr, GL_STATIC_DRAW);
    }

    void IndexBuffer::bufferData(std::vector<unsigned int>& indices){

        unsigned int maxIndex = *std::max_element(indices.begin(), indices.end());
        this->indexElementType = IndexBuffer::getIndexElementType(maxIndex);
        totalIndices = indices.size();
        switch(this->indexElementType){
            case GL_UNSIGNED_BYTE:{
                std::vector<unsigned char> newIndices(totalIndices);
                for(int i = 0; i < totalIndices; i++)
                    newIndices[i] = static_cast<unsigned char>(indices[i]);

                IndexBuffer::bufferData(totalIndices, &newIndices[0]);
                break;
            }
            case GL_UNSIGNED_SHORT:{
                std::vector<unsigned short> newIndices(totalIndices);
                for(int i = 0; i < totalIndices; i++)
                    newIndices[i] = static_cast<unsigned short>(indices[i]);

                IndexBuffer::bufferData(totalIndices * 2, &newIndices[0]);
                break;
            }
            case GL_UNSIGNED_INT:{
                IndexBuffer::bufferData(totalIndices * 4, &indices[0]);
                break;
            }
        };
    }

    void IndexBuffer::draw(){
        glDrawElements(GL_TRIANGLES, totalIndices, indexElementType, (void*)0);

*//*        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            printf("OpenGL Error in draw(): 0x%x\n", error);
        }*//*
    }

    void IndexBuffer::drawInstanced(unsigned int instanceCount){
        glDrawElementsInstanced(GL_TRIANGLES, totalIndices, indexElementType, (void*)0, instanceCount);
    }*/

}