#pragma once

#include <Component/SimpleScene.h>
#include <Projects/BrickBreaker/Levels/Level.h>

#include <iostream>

class BrickBreaker : public SimpleScene {
public:
    BrickBreaker();
    ~BrickBreaker();
    void Init() override;

private:
    float totalTime = 0;
    Level *currentLevel;

    void FrameStart() override;
    void Update(float deltaTimeSeconds) override;
    void FrameEnd() override;

    void GenerateMeshes();
    void DrawScene();

    void OnInputUpdate(float deltaTime, int mods) override;
    void OnKeyPress(int key, int mods) override;
    void OnKeyRelease(int key, int mods) override;
    void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
    void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;


protected:
    float length;
    glm::mat3 modelMatrix;
};