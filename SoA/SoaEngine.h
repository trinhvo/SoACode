///
/// SoAEngine.h
/// Seed of Andromeda
///
/// Created by Benjamin Arnold on 10 Jan 2015
/// Copyright 2014 Regrowth Studios
/// All Rights Reserved
///
/// Summary:
/// Handles initialization and destruction of SoAState
///

#pragma once

#ifndef SoAEngine_h__
#define SoAEngine_h__

class GameSystem;
class SpaceSystem;
class SoaState;

#pragma once
class SoaEngine {
public:
    struct SpaceSystemLoadData {
        nString filePath;
    };
    struct GameSystemLoadData {
        // More stuff here
    };
    static bool initState(OUT SoaState* state);

    static bool loadSpaceSystem(OUT SoaState* state, const SpaceSystemLoadData& loadData);

    static bool loadGameSystem(OUT SoaState* state, const GameSystemLoadData& loadData);

    static void destroyAll(OUT SoaState* state);

    static void destroyGameSystem(OUT SoaState* state);

private:
    static void destroySpaceSystem(OUT SoaState* state);
};

#endif // SoAEngine_h__