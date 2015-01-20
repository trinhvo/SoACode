///
/// SphericalTerrainComponent.h
/// Seed of Andromeda
///
/// Created by Benjamin Arnold on 3 Dec 2014
/// Copyright 2014 Regrowth Studios
/// All Rights Reserved
///
/// Summary:
/// Defines the component for creating spherical terrain
/// for planets and stuff.
///

#pragma once

#ifndef SphericalTerrainComponent_h__
#define SphericalTerrainComponent_h__

#include "SphericalTerrainPatch.h"
#include "SphericalTerrainGenerator.h"

#include <Vorb/RPC.h>
#include <Vorb/ecs/Entity.h>
#include <deque>

class Camera;
class NamePositionComponent;
class AxisRotationComponent;
class PlanetGenData;
class SphericalTerrainMeshManager;

#define LOAD_DIST 80000.0
// Should be even
#define PATCH_ROW 2  
#define NUM_FACES 6
const int PATCHES_PER_FACE = (PATCH_ROW * PATCH_ROW);
const int TOTAL_PATCHES = PATCHES_PER_FACE * NUM_FACES;

class TerrainGenDelegate : public IDelegate<void*> {
public:
    virtual void invoke(Sender sender, void* userData) override;
    volatile bool inUse = false;

    vcore::RPC rpc;

    f32v3 startPos;
    i32v3 coordMapping;
    float width;

    SphericalTerrainMesh* mesh = nullptr;
    SphericalTerrainGenerator* generator = nullptr;
};

class TerrainRpcDispatcher {
public:
    TerrainRpcDispatcher(SphericalTerrainGenerator* generator) :
        m_generator(generator) {
        for (int i = 0; i < NUM_GENERATORS; i++) {
            m_generators[i].generator = m_generator;
        }
    }
    /// @return a new mesh on success, nullptr on failure
    SphericalTerrainMesh* dispatchTerrainGen(const f32v3& startPos,
                                             const i32v3& coordMapping,
                                             float width,
                                             int lod,
                                             CubeFace cubeFace);
private:
    static const int NUM_GENERATORS = 1024;
    int counter = 0;

    SphericalTerrainGenerator* m_generator = nullptr;

    TerrainGenDelegate m_generators[NUM_GENERATORS];
};

class SphericalTerrainComponent {
public:
    /// Initialize the spherical terrain
    /// @param radius: Radius of the planet, must be multiple of 32.
    void init(vcore::ComponentID npComp, 
              vcore::ComponentID arComp,
              f64 radius, PlanetGenData* planetGenData,
              vg::GLProgram* normalProgram,
              vg::TextureRecycler* normalMapRecycler);

    vcore::ComponentID namePositionComponent = 0;
    vcore::ComponentID axisRotationComponent = 0;

    TerrainRpcDispatcher* rpcDispatcher = nullptr;

    SphericalTerrainPatch* patches = nullptr; ///< Buffer for top level patches
    SphericalTerrainData* sphericalTerrainData = nullptr;

    SphericalTerrainMeshManager* meshManager = nullptr;
    SphericalTerrainGenerator* generator = nullptr;

    PlanetGenData* planetGenData = nullptr;
};

#endif // SphericalTerrainComponent_h__