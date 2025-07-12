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

            const float PI = 3.14159265358979323846f;
            const float radius = 1.0f;
            const int   sectorCount = 64;   // longitude divisions (around Y)
            const int   stackCount = 32;   // latitude  divisions (between the poles)

            const float sectorStep = 2.0f * PI / sectorCount;
            const float stackStep = PI / stackCount;     // 0 … π   (north→south)

            std::vector<Vertex>   vertices;
            std::vector<uint32_t> indices;

            /*-------------------------------------------------
             * 1.  Top pole (one vertex, v = 0)
             *------------------------------------------------*/
            vertices.push_back({
                /*pos*/   {0.0f,  radius, 0.0f},
                /*nrm*/   {0.0f,  1.0f,   0.0f},
                /*uv */   {0.0f,  0.0f}
                });
            const uint32_t topIndex = 0;

            /*-------------------------------------------------
             * 2.  Body (stacks 1 … stackCount‑1)          v: 0–1
             *    θ = stackStep … (π-stackStep)
             *------------------------------------------------*/
            for (int i = 1; i < stackCount; ++i)                     // exclude poles
            {
                float theta = i * stackStep;                         // 0→π
                float y = radius * cosf(theta);                 // pole axis (Y)
                float r_xy = radius * sinf(theta);                 // radius of the ring

                for (int j = 0; j <= sectorCount; ++j)               // <= to wrap seam
                {
                    float phi = j * sectorStep;                      // 0→2π
                    float x = r_xy * cosf(phi);
                    float z = r_xy * sinf(phi);

                    glm::vec3 pos(x, y, -z);
                    glm::vec3 nrm = glm::normalize(pos);

                    float u = static_cast<float>(j) / sectorCount;   // 0 … 1 across seam
                    float v = static_cast<float>(i) / stackCount;    // 0 … 1 down sphere

                    vertices.push_back({ pos, nrm, {u, v} });
                }
            }

            /*-------------------------------------------------
             * 3.  Bottom pole (one vertex, v = 1)
             *------------------------------------------------*/
            uint32_t bottomIndex = static_cast<uint32_t>(vertices.size());
            vertices.push_back({
                /*pos*/   {0.0f, -radius, 0.0f},
                /*nrm*/   {0.0f, -1.0f,   0.0f},
                /*uv */   {0.0f,  1.0f}
                });

            /*-------------------------------------------------
             * 4.  Indices
             *------------------------------------------------*/

             // helper: number of verts in one latitude ring (sectorCount+1)
            const uint32_t ringVerts = sectorCount + 1;

            // --- top cap ---
            for (uint32_t j = 0; j < sectorCount; ++j)
            {
                uint32_t k1 = 1 + j;          // first ring starts at index 1
                uint32_t k2 = 1 + j + 1;

                indices.push_back(topIndex);
                indices.push_back(k1);
                indices.push_back(k2);
            }

            // --- body ---
            for (int i = 0; i < stackCount - 2; ++i)     // rings between the caps
            {
                uint32_t k1 = 1 + i * ringVerts;
                uint32_t k2 = k1 + ringVerts;

                for (uint32_t j = 0; j < sectorCount; ++j, ++k1, ++k2)
                {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);

                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }

            // --- bottom cap ---
            uint32_t base = 1 + (stackCount - 2) * ringVerts;   // first index of last ring
            for (uint32_t j = 0; j < sectorCount; ++j)
            {
                uint32_t k1 = base + j;
                uint32_t k2 = base + j + 1;

                indices.push_back(k1);
                indices.push_back(bottomIndex);
                indices.push_back(k2);
            }

            VertexBuffer::generate(data.vertexBuffer, vertices.size() * sizeof(Vertex), vertices.data());
            IndexBuffer::generate(data.indexBuffer, indices);

            //struct Vertex
            //{
            //    glm::vec3 position;
            //    glm::vec3 normal;
            //    glm::vec2 uv;
            //};

            //const float PI = 3.14159265359;
            //std::vector<Vertex> vertices;
            //std::vector<uint32_t> indices;
            //float radius = 1.0f;
            //int sectorCount = 64;
            //int stackCount = 32;

            //float sectorStep = 2 * PI / sectorCount;
            //float stackStep = PI / stackCount;

            //for (int i = 0; i <= stackCount; ++i) {
            //    float stackAngle = PI / 2 - i * stackStep; // from +pi/2 to -pi/2
            //    float xy = radius * cosf(stackAngle);      // r * cos(u)
            //    float z = radius * sinf(stackAngle);       // r * sin(u)

            //    for (int j = 0; j <= sectorCount; ++j) {
            //        float sectorAngle = j * sectorStep;    // from 0 to 2pi

            //        float x = xy * cosf(sectorAngle);      // x = r * cos(u) * cos(v)
            //        float y = xy * sinf(sectorAngle);      // y = r * cos(u) * sin(v)

            //        glm::vec3 position(x, y, z);

            //        glm::vec3 normal = glm::normalize(position);
            //        glm::vec2 uv(
            //            (float)j / sectorCount,
            //            (float)i / stackCount
            //        );

            //        vertices.push_back({ position, normal, uv });
            //    }
            //}

            //// indices
            //for (int i = 0; i < stackCount; ++i) {
            //    int k1 = i * (sectorCount + 1);     // beginning of current stack
            //    int k2 = k1 + sectorCount + 1;      // beginning of next stack

            //    for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            //        if (i != 0) {
            //            indices.push_back(k1);
            //            indices.push_back(k2);
            //            indices.push_back(k1 + 1);
            //        }
            //        if (i != (stackCount - 1)) {
            //            indices.push_back(k1 + 1);
            //            indices.push_back(k2);
            //            indices.push_back(k2 + 1);
            //        }
            //    }
            //}

            //VertexBuffer::generate(data.vertexBuffer, sizeof(Vertex) * vertices.size(), &vertices[0]);
            //IndexBuffer::generate(data.indexBuffer, indices);
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
