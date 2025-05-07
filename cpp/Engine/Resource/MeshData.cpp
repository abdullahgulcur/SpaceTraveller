#include "pch.h"
#include "MeshData.h"
#include "tiny_obj_loader.h"
#include "glm.hpp"
#include "AssetManager.h"

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

        void generateQuadSphereVertexBuffer(MeshData& data) {

            //// Helper to hash glm::ivec3 for unordered_map
            //struct ivec3_hash
            //{
            //    size_t operator()(const glm::ivec3& v) const noexcept
            //    {
            //        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1) ^ (std::hash<int>()(v.z) << 2);
            //    }
            //};

            //int subdivision = 16;
            //std::vector<Vertex> outVertices;
            //std::vector<uint32_t> outIndices;

            //// Maps grid position to vertex index
            //std::unordered_map<glm::ivec3, uint32_t, ivec3_hash> vertexMap;

            //auto getVertexIndex = [&](const glm::ivec3& gridPos) -> uint32_t
            //{
            //    auto it = vertexMap.find(gridPos);
            //    if (it != vertexMap.end())
            //        return it->second;

            //    glm::vec3 p = glm::normalize(glm::vec3(gridPos));
            //    Vertex v;
            //    v.position = p;
            //    v.normal = p;
            //    uint32_t idx = static_cast<uint32_t>(outVertices.size());
            //    outVertices.push_back(v);
            //    vertexMap[gridPos] = idx;
            //    return idx;
            //};

            //auto buildFace = [&](const glm::vec3& axisU, const glm::vec3& axisV, const glm::vec3& faceNormal)
            //{
            //    glm::vec3 origin = faceNormal;

            //    for (int y = 0; y < subdivision; ++y)
            //    {
            //        for (int x = 0; x < subdivision; ++x)
            //        {
            //            float fx0 = float(x) / subdivision;
            //            float fy0 = float(y) / subdivision;
            //            float fx1 = float(x + 1) / subdivision;
            //            float fy1 = float(y + 1) / subdivision;

            //            glm::vec3 p00 = origin + (fx0 - 0.5f) * 2.0f * axisU + (fy0 - 0.5f) * 2.0f * axisV;
            //            glm::vec3 p10 = origin + (fx1 - 0.5f) * 2.0f * axisU + (fy0 - 0.5f) * 2.0f * axisV;
            //            glm::vec3 p11 = origin + (fx1 - 0.5f) * 2.0f * axisU + (fy1 - 0.5f) * 2.0f * axisV;
            //            glm::vec3 p01 = origin + (fx0 - 0.5f) * 2.0f * axisU + (fy1 - 0.5f) * 2.0f * axisV;

            //            glm::ivec3 i00 = glm::round(p00 * float(subdivision));
            //            glm::ivec3 i10 = glm::round(p10 * float(subdivision));
            //            glm::ivec3 i11 = glm::round(p11 * float(subdivision));
            //            glm::ivec3 i01 = glm::round(p01 * float(subdivision));

            //            uint32_t idx00 = getVertexIndex(i00);
            //            uint32_t idx10 = getVertexIndex(i10);
            //            uint32_t idx11 = getVertexIndex(i11);
            //            uint32_t idx01 = getVertexIndex(i01);

            //            outIndices.push_back(idx00);
            //            outIndices.push_back(idx10);
            //            outIndices.push_back(idx11);

            //            outIndices.push_back(idx00);
            //            outIndices.push_back(idx11);
            //            outIndices.push_back(idx01);
            //        }
            //    }
            //};

            //// Build 6 faces
            //buildFace({ 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 });  // Front
            //buildFace({ -1, 0, 0 }, { 0, 1, 0 }, { 0, 0, -1 }); // Back
            //buildFace({ 1, 0, 0 }, { 0, 0, -1 }, { 0, 1, 0 }); // Top
            //buildFace({ 1, 0, 0 }, { 0, 0, 1 }, { 0, -1, 0 }); // Bottom
            //buildFace({ 0, 0, -1 }, { 0, 1, 0 }, { 1, 0, 0 }); // Right
            //buildFace({ 0, 0, 1 }, { 0, 1, 0 }, { -1, 0, 0 });  // Left


            struct Vertex
            {
                glm::vec3 position;
                glm::vec3 normal;
            };

            const float PI = 3.14159265359;
            int latitudeSegments = 32;
            int longitudeSegments = 64;
            std::vector<Vertex> outVertices;
            std::vector<uint32_t> outIndices;


            // Top vertex
            Vertex topVertex;
            topVertex.position = glm::vec3(0, 1, 0);
            topVertex.normal = glm::vec3(0, 1, 0);
            outVertices.push_back(topVertex);

            // Generate vertices
            for (int lat = 1; lat < latitudeSegments; ++lat)
            {
                float v = float(lat) / latitudeSegments;
                float theta = v * PI;

                float sinTheta = std::sin(theta);
                float cosTheta = std::cos(theta);

                for (int lon = 0; lon <= longitudeSegments; ++lon)
                {
                    float u = float(lon) / longitudeSegments;
                    float phi = u * PI * 2;

                    float sinPhi = std::sin(phi);
                    float cosPhi = std::cos(phi);

                    glm::vec3 pos;
                    pos.x = sinTheta * cosPhi;
                    pos.y = cosTheta;
                    pos.z = sinTheta * sinPhi;

                    Vertex vtx;
                    vtx.position = pos;
                    vtx.normal = glm::normalize(pos);

                    outVertices.push_back(vtx);
                }
            }

            // Bottom vertex
            Vertex bottomVertex;
            bottomVertex.position = glm::vec3(0, -1, 0);
            bottomVertex.normal = glm::vec3(0, -1, 0);
            outVertices.push_back(bottomVertex);

            int topIndex = 0;
            int bottomIndex = int(outVertices.size()) - 1;

            // Top cap
            for (int lon = 0; lon < longitudeSegments; ++lon)
            {
                outIndices.push_back(topIndex);
                outIndices.push_back(1 + lon + 1);
                outIndices.push_back(1 + lon);
            }

            // Middle
            for (int lat = 0; lat < latitudeSegments - 2; ++lat)
            {
                for (int lon = 0; lon < longitudeSegments; ++lon)
                {
                    int current = 1 + lat * (longitudeSegments + 1) + lon;
                    int next = current + longitudeSegments + 1;

                    outIndices.push_back(current);
                    outIndices.push_back(current + 1);
                    outIndices.push_back(next);

                    outIndices.push_back(current + 1);
                    outIndices.push_back(next + 1);
                    outIndices.push_back(next);
                }
            }

            // Bottom cap
            int baseIndex = 1 + (latitudeSegments - 2) * (longitudeSegments + 1);
            for (int lon = 0; lon < longitudeSegments; ++lon)
            {
                outIndices.push_back(bottomIndex);
                outIndices.push_back(baseIndex + lon);
                outIndices.push_back(baseIndex + lon + 1);
            }

            VertexBuffer::generate(data.vertexBuffer, sizeof(Vertex) * outVertices.size(), &outVertices[0]);
            IndexBuffer::generate(data.indexBuffer, outIndices);
        }
    }


}
