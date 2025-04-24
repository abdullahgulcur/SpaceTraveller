#include "pch.h"
#include "MeshData.h"
#include "tiny_obj_loader.h"
#include "glm.hpp"
#include "AndroidAssetManager.h"

namespace Engine{

    namespace MeshData{

        void loadStaticMesh(MeshData& data, std::string path){

            struct Vertex{
                glm::vec3 position;
                glm::vec3 normal;

                bool operator==(const Vertex& other) const {
                    return position[0] == other.position[0] && position[1] == other.position[1] && position[2] == other.position[2] &&
                           normal[0] == other.normal[0] && normal[1] == other.normal[1] && normal[2] == other.normal[2];
                }
            };

            struct VertexHash {
                std::size_t operator()(const Vertex& vertex) const {
                    std::size_t h1 = std::hash<float>()(vertex.position[0]) ^ std::hash<float>()(vertex.position[1]) ^ std::hash<float>()(vertex.position[2]);
                    std::size_t h2 = std::hash<float>()(vertex.normal[0]) ^ std::hash<float>()(vertex.normal[1]) ^ std::hash<float>()(vertex.normal[2]);
                    return h1 ^ h2;
                }
            };

            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            std::string warn, err;

            AndroidAssetManager androidAssetManager;
            std::string objStr;
            androidAssetManager.readBytesFromAsset(path.c_str(), objStr);
            std::stringstream ss(objStr);

            bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &ss);

            if (!warn.empty()) std::cout << "Warning: " << warn << std::endl;
            if (!err.empty()) std::cerr << "Error: " << err << std::endl;
            if (!ret) throw std::runtime_error("Failed to load .obj file.");

            std::unordered_map<Vertex, unsigned int, VertexHash> uniqueVertices;

            for (const auto& shape : shapes) {
                for (const auto& index : shape.mesh.indices) {
                    Vertex vertex = {};

                    // Position
                    vertex.position[0] = attrib.vertices[3 * index.vertex_index + 0];
                    vertex.position[1] = attrib.vertices[3 * index.vertex_index + 1];
                    vertex.position[2] = attrib.vertices[3 * index.vertex_index + 2];

                    // Normal
                    if (index.normal_index >= 0) {
                        vertex.normal[0] = attrib.normals[3 * index.normal_index + 0];
                        vertex.normal[1] = attrib.normals[3 * index.normal_index + 1];
                        vertex.normal[2] = attrib.normals[3 * index.normal_index + 2];
                    }

                    // Check if the vertex is already in the list of unique vertices
                    if (uniqueVertices.count(vertex) == 0) {
                        uniqueVertices[vertex] = static_cast<unsigned int>(vertices.size());
                        vertices.push_back(vertex);
                    }

                    // Add the corresponding index
                    indices.push_back(uniqueVertices[vertex]);
                }
            }

            VertexBuffer::generate(data.vertexBuffer, vertices.size() * sizeof(Vertex), &vertices[0]);
            IndexBuffer::generate(data.indexBuffer, indices);
        }

        void loadStaticMeshTextured(MeshData& data, std::string path) {

            struct Vertex{
                glm::vec3 position;
                glm::vec3 normal;
                glm::vec2 uv;

                bool operator==(const Vertex& other) const {
                    return position[0] == other.position[0] && position[1] == other.position[1] && position[2] == other.position[2] &&
                           normal[0] == other.normal[0] && normal[1] == other.normal[1] && normal[2] == other.normal[2] &&
                           uv[0] == other.uv[0] && uv[1] == other.uv[1];
                }
            };

            struct VertexHash {
                std::size_t operator()(const Vertex& vertex) const {
                    std::size_t h1 = std::hash<float>()(vertex.position[0]) ^ std::hash<float>()(vertex.position[1]) ^ std::hash<float>()(vertex.position[2]);
                    std::size_t h2 = std::hash<float>()(vertex.normal[0]) ^ std::hash<float>()(vertex.normal[1]) ^ std::hash<float>()(vertex.normal[2]);
                    std::size_t h3 = std::hash<float>()(vertex.uv[0]) ^ std::hash<float>()(vertex.uv[1]);
                    return h1 ^ h2 ^ h3;
                }
            };

            std::vector<Vertex> vertices;
            std::vector<unsigned int> indices;

            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            std::string warn, err;

            AndroidAssetManager androidAssetManager;
            std::string objStr;
            androidAssetManager.readBytesFromAsset(path.c_str(), objStr);
            std::stringstream ss(objStr);

            bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &ss);

            if (!warn.empty()) std::cout << "Warning: " << warn << std::endl;
            if (!err.empty()) std::cerr << "Error: " << err << std::endl;
            if (!ret) throw std::runtime_error("Failed to load .obj file.");

            std::unordered_map<Vertex, unsigned int, VertexHash> uniqueVertices;

            for (const auto& shape : shapes) {
                for (const auto& index : shape.mesh.indices) {
                    Vertex vertex = {};

                    // Position
                    vertex.position[0] = attrib.vertices[3 * index.vertex_index + 0];
                    vertex.position[1] = attrib.vertices[3 * index.vertex_index + 1];
                    vertex.position[2] = attrib.vertices[3 * index.vertex_index + 2];

                    // Normal
                    if (index.normal_index >= 0) {
                        vertex.normal[0] = attrib.normals[3 * index.normal_index + 0];
                        vertex.normal[1] = attrib.normals[3 * index.normal_index + 1];
                        vertex.normal[2] = attrib.normals[3 * index.normal_index + 2];
                    }

                    // Texture coordinate
                    if (index.texcoord_index >= 0) {
                        vertex.uv[0] = attrib.texcoords[2 * index.texcoord_index + 0];
                        vertex.uv[1] = attrib.texcoords[2 * index.texcoord_index + 1];
                    }

                    // Check if the vertex is already in the list of unique vertices
                    if (uniqueVertices.count(vertex) == 0) {
                        uniqueVertices[vertex] = static_cast<unsigned int>(vertices.size());
                        vertices.push_back(vertex);
                    }

                    // Add the corresponding index
                    indices.push_back(uniqueVertices[vertex]);
                }
            }

            VertexBuffer::generate(data.vertexBuffer, vertices.size() * sizeof(Vertex), &vertices[0]);
            IndexBuffer::generate(data.indexBuffer, indices);
        }
    }



//
//    void MeshData::loadStaticMesh(std::string& path){
//
//        struct Vertex{
//            glm::vec3 position;
//            glm::vec3 normal;
//
//            bool operator==(const Vertex& other) const {
//                return position[0] == other.position[0] && position[1] == other.position[1] && position[2] == other.position[2] &&
//                       normal[0] == other.normal[0] && normal[1] == other.normal[1] && normal[2] == other.normal[2];
//            }
//        };
//
//        struct VertexHash {
//            std::size_t operator()(const Vertex& vertex) const {
//                std::size_t h1 = std::hash<float>()(vertex.position[0]) ^ std::hash<float>()(vertex.position[1]) ^ std::hash<float>()(vertex.position[2]);
//                std::size_t h2 = std::hash<float>()(vertex.normal[0]) ^ std::hash<float>()(vertex.normal[1]) ^ std::hash<float>()(vertex.normal[2]);
//                return h1 ^ h2;
//            }
//        };
//
//        std::vector<Vertex> vertices;
//        std::vector<unsigned int> indices;
//
//        tinyobj::attrib_t attrib;
//        std::vector<tinyobj::shape_t> shapes;
//        std::vector<tinyobj::material_t> materials;
//        std::string warn, err;
//
//        AndroidAssetManager androidAssetManager;
//        std::string objStr;
//        androidAssetManager.readBytesFromAsset(path.c_str(), objStr);
//        std::stringstream ss(objStr);
//
//        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &ss);
//
//        if (!warn.empty()) std::cout << "Warning: " << warn << std::endl;
//        if (!err.empty()) std::cerr << "Error: " << err << std::endl;
//        if (!ret) throw std::runtime_error("Failed to load .obj file.");
//
//        std::unordered_map<Vertex, unsigned int, VertexHash> uniqueVertices;
//
//        for (const auto& shape : shapes) {
//            for (const auto& index : shape.mesh.indices) {
//                Vertex vertex = {};
//
//                // Position
//                vertex.position[0] = attrib.vertices[3 * index.vertex_index + 0];
//                vertex.position[1] = attrib.vertices[3 * index.vertex_index + 1];
//                vertex.position[2] = attrib.vertices[3 * index.vertex_index + 2];
//
//                // Normal
//                if (index.normal_index >= 0) {
//                    vertex.normal[0] = attrib.normals[3 * index.normal_index + 0];
//                    vertex.normal[1] = attrib.normals[3 * index.normal_index + 1];
//                    vertex.normal[2] = attrib.normals[3 * index.normal_index + 2];
//                }
//
//                // Check if the vertex is already in the list of unique vertices
//                if (uniqueVertices.count(vertex) == 0) {
//                    uniqueVertices[vertex] = static_cast<unsigned int>(vertices.size());
//                    vertices.push_back(vertex);
//                }
//
//                // Add the corresponding index
//                indices.push_back(uniqueVertices[vertex]);
//            }
//        }
//
//        VertexBuffer::generate(vertexBuffer.bufferId);
//        IndexBuffer::generate(indexBuffer.bufferId);
//        VertexBuffer::bufferData(vertexBuffer.bufferId, vertices.size() * sizeof(Vertex), &vertices[0]);
//        IndexBuffer::bufferData(indexBuffer, indices);
//    }
//
//    void MeshData::loadStaticMeshTextured(std::string &path) {
//
//        struct Vertex{
//            glm::vec3 position;
//            glm::vec3 normal;
//            glm::vec2 uv;
//
//            bool operator==(const Vertex& other) const {
//                return position[0] == other.position[0] && position[1] == other.position[1] && position[2] == other.position[2] &&
//                       normal[0] == other.normal[0] && normal[1] == other.normal[1] && normal[2] == other.normal[2] &&
//                       uv[0] == other.uv[0] && uv[1] == other.uv[1];
//            }
//        };
//
//        struct VertexHash {
//            std::size_t operator()(const Vertex& vertex) const {
//                std::size_t h1 = std::hash<float>()(vertex.position[0]) ^ std::hash<float>()(vertex.position[1]) ^ std::hash<float>()(vertex.position[2]);
//                std::size_t h2 = std::hash<float>()(vertex.normal[0]) ^ std::hash<float>()(vertex.normal[1]) ^ std::hash<float>()(vertex.normal[2]);
//                std::size_t h3 = std::hash<float>()(vertex.uv[0]) ^ std::hash<float>()(vertex.uv[1]);
//                return h1 ^ h2 ^ h3;
//            }
//        };
//
//        std::vector<Vertex> vertices;
//        std::vector<unsigned int> indices;
//
//        tinyobj::attrib_t attrib;
//        std::vector<tinyobj::shape_t> shapes;
//        std::vector<tinyobj::material_t> materials;
//        std::string warn, err;
//
//        AndroidAssetManager androidAssetManager;
//        std::string objStr;
//        androidAssetManager.readBytesFromAsset(path.c_str(), objStr);
//        std::stringstream ss(objStr);
//
//        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &ss);
//
//        if (!warn.empty()) std::cout << "Warning: " << warn << std::endl;
//        if (!err.empty()) std::cerr << "Error: " << err << std::endl;
//        if (!ret) throw std::runtime_error("Failed to load .obj file.");
//
//        std::unordered_map<Vertex, unsigned int, VertexHash> uniqueVertices;
//
//        for (const auto& shape : shapes) {
//            for (const auto& index : shape.mesh.indices) {
//                Vertex vertex = {};
//
//                // Position
//                vertex.position[0] = attrib.vertices[3 * index.vertex_index + 0];
//                vertex.position[1] = attrib.vertices[3 * index.vertex_index + 1];
//                vertex.position[2] = attrib.vertices[3 * index.vertex_index + 2];
//
//                // Normal
//                if (index.normal_index >= 0) {
//                    vertex.normal[0] = attrib.normals[3 * index.normal_index + 0];
//                    vertex.normal[1] = attrib.normals[3 * index.normal_index + 1];
//                    vertex.normal[2] = attrib.normals[3 * index.normal_index + 2];
//                }
//
//                // Texture coordinate
//                if (index.texcoord_index >= 0) {
//                    vertex.uv[0] = attrib.texcoords[2 * index.texcoord_index + 0];
//                    vertex.uv[1] = attrib.texcoords[2 * index.texcoord_index + 1];
//                }
//
//                // Check if the vertex is already in the list of unique vertices
//                if (uniqueVertices.count(vertex) == 0) {
//                    uniqueVertices[vertex] = static_cast<unsigned int>(vertices.size());
//                    vertices.push_back(vertex);
//                }
//
//                // Add the corresponding index
//                indices.push_back(uniqueVertices[vertex]);
//            }
//        }
//
//        VertexBuffer::generate(vertexBuffer.bufferId);
//        IndexBuffer::generate(indexBuffer.bufferId);
//        VertexBuffer::bufferData(vertexBuffer.bufferId, vertices.size() * sizeof(Vertex), &vertices[0]);
//        IndexBuffer::bufferData(indexBuffer, indices);
//    }
//
//    void MeshData::loadSkinnedMesh(std::string& path){
//
//    }
//
//    void MeshData::loadSkinnedMeshTextured(std::string& path){
//
//    }

}
