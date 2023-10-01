#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust trinagulation. Requires C++11
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"
#include "MeshLoader.h"

void LoadMeshFromFile(std::string inputfile, std::vector<Triangle>& mTriangles)
{
    //tinyObj stuff
    std::string warn;
    std::string err;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }
    //this is a boolean to check if the input file has only given use vertices without any normal and uv coordinates
    bool MoreVertexInfo = true;

    // Loop over shapes/Meshes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            //this will store the vertices in the face as they come up
            glm::vec3 verts[3];
            //this stores the normals as they come up
            glm::vec3 normals[3];
            //this will store the UVs of the face vertices as they come up
            glm::vec2 uvs[3];
            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++)
            {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                tinyobj::real_t vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                tinyobj::real_t vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                tinyobj::real_t vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
                verts[v].x = vx;
                verts[v].y = vy;
                verts[v].z = vz;

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
                    tinyobj::real_t ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
                    tinyobj::real_t nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
                    normals[v].x = nx;
                    normals[v].y = ny;
                    normals[v].z = nz;
                }
                else
                {
                    normals[v].x = 0.0f;
                    normals[v].y = 0.0f;
                    normals[v].z = 0.0f;
                    MoreVertexInfo = false;

                }
                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                    tinyobj::real_t ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    uvs[v].x = tx;
                    uvs[v].y = ty;
                }
                else
                {
                    uvs[v].x = 1.0f;
                    uvs[v].y = 1.0f;
                    MoreVertexInfo = false;
                }
            }
            index_offset += fv;
            Vertex iv0 = Vertex(verts[0], normals[0], uvs[0]);
            Vertex iv1 = Vertex(verts[1], normals[1], uvs[1]);
            Vertex iv2 = Vertex(verts[2], normals[2], uvs[2]);
            //Vertex(glm::vec3 iposition, glm::vec3 inormal, glm::vec2 itexUV) 
            Triangle currentT;
            if (MoreVertexInfo)
            {
                currentT = Triangle(iv0, iv1, iv2);
            }
            else
            {
                currentT = Triangle(iv0, iv1, iv2, MoreVertexInfo, glm::vec2(1.0f, 1.0f));
            }
            mTriangles.push_back(currentT);

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }
}