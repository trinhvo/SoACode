///
/// StarComponentRenderer.h
/// Seed of Andromeda
///
/// Created by Benjamin Arnold on 9 Apr 2015
/// Copyright 2014 Regrowth Studios
/// All Rights Reserved
///
/// Summary:
/// Renderer for StarComponents
///

#pragma once

#ifndef StarComponentRenderer_h__
#define StarComponentRenderer_h__

#include <Vorb/ecs/ECS.h>
#include <Vorb/ecs/ComponentTable.hpp>
#include <Vorb/VorbPreDecl.inl>
#include <Vorb/graphics/gtypes.h>
#include <Vorb/graphics/ImageIO.h>
#include <Vorb/script/Function.h>
#include <Vorb/script/Environment.h>

DECL_VG(class GLProgram)
class ModPathResolver;

struct StarComponent;

class StarComponentRenderer {
public:
    StarComponentRenderer(const ModPathResolver* textureResolver);
    ~StarComponentRenderer();

    void drawStar(const StarComponent& sCmp,
                  const f32m4& VP,
                  const f64q& orientation,
                  const f32v3& relCamPos);
    void drawCorona(StarComponent& sCmp,
                    const f32m4& VP,
                    const f32m4& V,
                    const f32v3& relCamPos);
    void drawGlow(const StarComponent& sCmp,
                  const f32m4& VP,
                  const f64v3& relCamPos,
                  float aspectRatio,
                  const f32v3& viewDirW,
                  const f32v3& viewRightW,
                  const f32v3& colorMult = f32v3(1.0f));
    void updateOcclusionQuery(StarComponent& sCmp,
                              const f32m4& VP,
                              const f64v3& relCamPos);

    void dispose();
    void disposeShaders();
    void disposeBuffers();

    f32v3 calculateStarColor(const StarComponent& sCmp);
    f64 calculateGlowSize(const StarComponent& sCmp, const f64v3& relCamPos);

private:
    void checkLazyLoad();
    void buildShaders();
    void buildMesh();
    void loadTempColorMap();
    void loadGlowTextures();
    f32v3 getColor(int index);
    f32v3 getTempColorShift(const StarComponent& sCmp);

    vg::GLProgram* m_starProgram = nullptr;
    vg::GLProgram* m_coronaProgram = nullptr;
    vg::GLProgram* m_glowProgram = nullptr;
    vg::GLProgram* m_occlusionProgram = nullptr;
    // Star
    VGBuffer m_sVbo = 0;
    VGIndexBuffer m_sIbo = 0;
    VGVertexArray m_sVao = 0;
    // Corona
    VGBuffer m_cVbo = 0;
    VGIndexBuffer m_cIbo = 0;
    VGVertexArray m_cVao = 0;
    // Glow
    VGVertexArray m_gVao = 0;
    // Occlusion
    VGVertexArray m_oVao = 0;
    
    vg::BitmapResource m_tempColorMap;
    VGTexture m_glowColorMap = 0;
    int m_numIndices = 0;

    // TODO(Ben): UBO
    VGUniform unWVP;
    VGUniform unDT;

    const ModPathResolver* m_textureResolver = nullptr;
};

#endif // StarComponentRenderer_h__