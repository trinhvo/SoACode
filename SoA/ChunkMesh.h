#pragma once
#include "stdafx.h"
#include "OpenGLStructs.h"

#include <vector>

enum class MeshType { NONE, BLOCK, LEAVES, FLORA, CROSSFLORA, LIQUID };

enum class MeshJobType;

class RenderTask;
class Chunk;

// Stores Chunk Mesh Information
struct MesherInfo {
public:
    i32 index, topIndex, leftIndex, rightIndex, botIndex, backIndex, frontIndex, liquidIndex;
    i32 pLayerFrontIndex, pLayerBackIndex, pLayerLeftIndex, pLayerRightIndex;
    i32 wsize;
    i32 pyVboSize, nxVboSize, pxVboSize, nzVboSize, pzVboSize, nyVboSize, transparentIndex, cutoutIndex;
    i32 y, z, x;
    i32 y2, z2, x2; //used for transparent positions. == y*2,z*2,x*2
    i32 c, wc;
    i32 btype;
    i32 pbtype;
    i32 pupIndex, pfrontIndex, pbackIndex, pbotIndex;
    i32 temperature, rainfall;
    MeshType meshType;
    bool mergeUp, mergeBot, mergeFront, mergeBack;

    RenderTask* task;
};

struct ChunkMeshRenderData {
    ChunkMeshRenderData() : indexSize(0), waterIndexSize(0) {}
    i32 pxVboOff, pxVboSize, nxVboOff, nxVboSize, pzVboOff, pzVboSize, nzVboOff, nzVboSize;
    i32 pyVboOff, pyVboSize, nyVboOff, nyVboSize, transVboSize, cutoutVboSize;
    i32 highestY, lowestY, highestX, lowestX, highestZ, lowestZ;
    ui32 indexSize;
    ui32 waterIndexSize;
};

struct ChunkMeshData
{
    ChunkMeshData(Chunk *ch);
    ChunkMeshData(RenderTask *task);

    void addTransQuad(const i8v3& pos);

    ChunkMeshRenderData meshInfo;

    std::vector <BlockVertex> vertices;
    std::vector <BlockVertex> transVertices;
    std::vector <BlockVertex> cutoutVertices;
    std::vector <LiquidVertex> waterVertices;
    Chunk *chunk;
    struct ChunkMesh *chunkMesh;
    MeshJobType type;
    int debugCode;

    //*** Transparency info for sorting ***
    ui32 transVertIndex;
    std::vector <i8v3> transQuadPositions;
    std::vector <ui32> transQuadIndices;
};

struct ChunkMesh
{
    ChunkMesh(Chunk *ch);

    ChunkMeshRenderData meshInfo;

    GLuint vboID;
    GLuint vaoID;
    GLuint transVboID;
    GLuint transVaoID;
    GLuint cutoutVboID;
    GLuint cutoutVaoID;
    GLuint waterVboID;
    float distance;
    glm::ivec3 position;
    int vecIndex;
    bool inFrustum;
    bool needsSort;

    //*** Transparency info for sorting ***
    GLuint transIndexID;
    std::vector <i8v3> transQuadPositions;
    std::vector <ui32> transQuadIndices;

};