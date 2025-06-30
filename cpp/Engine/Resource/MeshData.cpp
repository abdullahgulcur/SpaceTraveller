#include "pch.h"
#include "MeshData.h"
#include "tiny_obj_loader.h"
#include "glm.hpp"
#include "AssetManager.h"

namespace Engine {

    namespace MeshData {

        void loadStaticMesh(MeshData& data, std::string path) {

            struct Vertex {
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

            AssetManager assetManager;
            std::string objStr;
            assetManager.readBytesFromAsset(path.c_str(), objStr);
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

            struct Vertex {
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

            AssetManager assetManager;
            std::string objStr;
            assetManager.readBytesFromAsset(path.c_str(), objStr);
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

        void generateQuadSphereMeshTextured(MeshData& data) {

            struct Vertex
            {
                glm::vec3 position;
                glm::vec3 normal;
                glm::vec2 uv;
            };

            const float PI = 3.14159265359;
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;
            float radius = 1.0f;
            int sectorCount = 64;
            int stackCount = 32;

            float sectorStep = 2 * PI / sectorCount;
            float stackStep = PI / stackCount;

            for (int i = 0; i <= stackCount; ++i) {
                float stackAngle = PI / 2 - i * stackStep; // from +pi/2 to -pi/2
                float xy = radius * cosf(stackAngle);      // r * cos(u)
                float z = radius * sinf(stackAngle);       // r * sin(u)

                for (int j = 0; j <= sectorCount; ++j) {
                    float sectorAngle = j * sectorStep;    // from 0 to 2pi

                    float x = xy * cosf(sectorAngle);      // x = r * cos(u) * cos(v)
                    float y = xy * sinf(sectorAngle);      // y = r * cos(u) * sin(v)

                    glm::vec3 position(x, y, z);

                    glm::vec3 normal = glm::normalize(position);
                    glm::vec2 uv(
                        (float)j / sectorCount,
                        (float)i / stackCount
                    );

                    vertices.push_back({ position, normal, uv });
                }
            }

            // indices
            for (int i = 0; i < stackCount; ++i) {
                int k1 = i * (sectorCount + 1);     // beginning of current stack
                int k2 = k1 + sectorCount + 1;      // beginning of next stack

                for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
                    if (i != 0) {
                        indices.push_back(k1);
                        indices.push_back(k2);
                        indices.push_back(k1 + 1);
                    }
                    if (i != (stackCount - 1)) {
                        indices.push_back(k1 + 1);
                        indices.push_back(k2);
                        indices.push_back(k2 + 1);
                    }
                }
            }

            VertexBuffer::generate(data.vertexBuffer, sizeof(Vertex) * vertices.size(), &vertices[0]);
            IndexBuffer::generate(data.indexBuffer, indices);
        }


        void generateTerrainBlockMesh(MeshData& data, unsigned int blockResolution) {

            std::vector<glm::u8vec2> vertices;
            std::vector<unsigned int> indices;

            for (int i = 0; i <= blockResolution; i++)
                for (int j = 0; j <= blockResolution; j++)
                    vertices.push_back(glm::u8vec2(j, i));

            for (int i = 0; i < blockResolution; i++) {
                for (int j = 0; j < blockResolution; j++) {

                    indices.push_back(j + i * (blockResolution + 1));
                    indices.push_back(j + (i + 1) * (blockResolution + 1));
                    indices.push_back(j + i * (blockResolution + 1) + 1);

                    indices.push_back(j + i * (blockResolution + 1) + 1);
                    indices.push_back(j + (i + 1) * (blockResolution + 1));
                    indices.push_back(j + (i + 1) * (blockResolution + 1) + 1);
                }
            }

            VertexBuffer::generate(data.vertexBuffer, sizeof(glm::u8vec2) * vertices.size(), &vertices[0]);
            IndexBuffer::generate(data.indexBuffer, indices);
        }

        void generateTerrainOuterDegenerateMesh(MeshData& data, unsigned int blockResolution) {

            std::vector<glm::u8vec2> vertices;
            std::vector<unsigned int> indices;

            for (int i = 0; i < blockResolution * 6; i++)
                vertices.push_back(glm::u8vec2(i, 0));
            for (int i = 0; i < blockResolution * 6; i++)
                vertices.push_back(glm::u8vec2(blockResolution * 6, i));
            for (int i = 0; i < blockResolution * 6; i++)
                vertices.push_back(glm::u8vec2(blockResolution * 6 - i, blockResolution * 6));
            for (int i = 0; i < blockResolution * 6; i++)
                vertices.push_back(glm::u8vec2(0, blockResolution * 6 - i));

            int triCount = blockResolution * 12;
            for (int i = 0; i < triCount; i++) {
                int index0 = i * 2;
                int index1 = ((i + 1) % triCount) * 2;
                int index2 = i * 2 + 1;

                indices.push_back(index0);
                indices.push_back(index1);
                indices.push_back(index2);

                indices.push_back(index0);
                indices.push_back(index2);
                indices.push_back(index1);
            }

            VertexBuffer::generate(data.vertexBuffer, sizeof(glm::u8vec2) * vertices.size(), &vertices[0]);
            IndexBuffer::generate(data.indexBuffer, indices);
        }

    }

}
