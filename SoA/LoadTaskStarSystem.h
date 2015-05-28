#pragma once
#include "LoadMonitor.h"
#include "SpaceSystem.h"

#include "SoaEngine.h"

// Sample Dependency Task
class LoadTaskStarSystem : public ILoadTask {
    friend class LoadScreen;

    LoadTaskStarSystem(vcore::RPCManager* glrpc, const nString& filePath, SoaState* state) :
        soaState(state) {
        this->glrpc = glrpc;
        loadData.filePath = filePath;
    }
    virtual void load() {
        SoaEngine::loadSpaceSystem(soaState, loadData, glrpc);
    }

    vcore::RPCManager* glrpc = nullptr;
    SoaEngine::SpaceSystemLoadData loadData;
    SoaState* soaState;
};