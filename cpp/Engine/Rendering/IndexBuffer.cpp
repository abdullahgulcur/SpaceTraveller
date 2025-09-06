#include "pch.h"
#include "IndexBuffer.h"
#include "GraphicsApi.h"

namespace Engine {

    namespace IndexBuffer {

        void generate(unsigned int& bufferId){
            glGenBuffers(1, &bufferId);
        }

        void generate(IndexBuffer& indexBuffer, std::vector<unsigned int>& indices){
            generate(indexBuffer.bufferId);
            bufferData(indexBuffer, indices);
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

        // not tested yet
        void bufferData(IndexBuffer& indexBuffer, unsigned char* indices, unsigned int totalIndices){

            indexBuffer.indexElementType = GL_UNSIGNED_BYTE;
            indexBuffer.totalIndices = totalIndices;
            bufferData(indexBuffer.bufferId, indexBuffer.totalIndices, indices);
        }

    }

}