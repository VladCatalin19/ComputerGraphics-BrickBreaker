#include <Projects/BrickBreaker/BrickBreaker.h>
#include <Core/Engine.h>
#include <iostream>
using namespace std;

#include <Projects/BrickBreaker/ShapeCreator/Transform2D.h>
#include <Projects/BrickBreaker/ShapeCreator/ShapeCreator2D.h>
#include <Projects/BrickBreaker/Levels/Level.h>
#include <Projects/BrickBreaker/Levels/Level1.h>
#include <Projects/BrickBreaker/Levels/Level2.h>
#include <Projects/BrickBreaker/Levels/Level3.h>
#include "BrickBreaker.h"

BrickBreaker::BrickBreaker() {
    currentLevel = NULL;
}

BrickBreaker::~BrickBreaker() {
    delete currentLevel;
}

void BrickBreaker::Init() {
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    currentLevel = new Level1(resolution);
    currentLevel->InitLevel();

    GenerateMeshes();
}

void BrickBreaker::GenerateMeshes() {
    // Walls
    for (int i = 0; i < 3; ++i) {
        Wall *wall = currentLevel->GetWalls()[i];
        Mesh *wallMesh = ShapeCreator2D::CreateRectangle("wall" + i, 
                                                          wall->GetPosition(),
                                                          wall->GetWidth(),
                                                          wall->GetHeight(), 
                                                          wall->GetColor(), 
                                                          true);
        AddMeshToList(wallMesh);
    }

    // Platform
    Platform *platform = currentLevel->GetPlatform();
    Mesh *platformMesh = ShapeCreator2D::CreateRectangle("platform",
                                                          glm::vec3(0.0f, 0.0f, 0.0f), 
                                                          platform->GetWidth(),
                                                          platform->GetHeight(), 
                                                          platform->GetColor(),
                                                          true);
    AddMeshToList(platformMesh);

    // Ball
    Ball *ball = currentLevel->GetBall();
    Mesh *ballMesh = ShapeCreator2D::CreateCircle("ball", glm::vec3(0.0f, 0.0f, 0.0f), 
                                                   ball->GetRadius(), ball->GetColor(),
                                                   true);
    AddMeshToList(ballMesh);

    // Bricks
    Brick *brick = currentLevel->GetBricks()[0][0];
    Mesh *brickMesh = ShapeCreator2D::CreateRectangle("brick_normal",
                                                       glm::vec3(0.0f, 0.0f, 0.0f),
                                                       brick->GetWidth(),
                                                       brick->GetHeight(),
                                                       currentLevel->GetBrickColors()[0],
                                                       true);
    AddMeshToList(brickMesh);

    brickMesh = ShapeCreator2D::CreateRectangle("brick_double",
                                                glm::vec3(0.0f, 0.0f, 0.0f),
                                                brick->GetWidth(),
                                                brick->GetHeight(),
                                                currentLevel->GetBrickColors()[1],
                                                true);
    AddMeshToList(brickMesh);

    brickMesh = ShapeCreator2D::CreateRectangle("brick_triple",
                                                glm::vec3(0.0f, 0.0f, 0.0f),
                                                brick->GetWidth(),
                                                brick->GetHeight(),
                                                currentLevel->GetBrickColors()[2],
                                                true);
    AddMeshToList(brickMesh);

    brickMesh = ShapeCreator2D::CreateRectangle("brick_last",
                                                glm::vec3(0.0f, 0.0f, 0.0f),
                                                brick->GetWidth(),
                                                brick->GetHeight(),
                                                currentLevel->GetBrickColors()[3],
                                                true);
    AddMeshToList(brickMesh);

    // PowerUps
    for (int i = 0; i < 3; ++i) {
        PowerUp *powerUp = currentLevel->GetPowerUps()[i];
        Mesh *powerUpMesh = ShapeCreator2D::CreateSquare("powerup" + i,
                                                          glm::vec3(0.0f, 0.0f, 0.0f),
                                                          powerUp->GetLength(),
                                                          powerUp->GetColor(),
                                                          true);
        AddMeshToList(powerUpMesh);
    }

}

void BrickBreaker::FrameStart() {
    // clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void BrickBreaker::Update(float deltaTimeSeconds) {
    totalTime += deltaTimeSeconds;
    glm::ivec2 resolution = window->GetResolution();

    if (currentLevel->HasLost()) {
        delete currentLevel;
        currentLevel = new Level1(window->GetResolution());
        currentLevel->InitLevel();
        return;
    }

    if (currentLevel->HasWon()) {
        int levelNumber = currentLevel->GetLevelNumber();
        delete currentLevel;
        currentLevel = NULL;

        switch (levelNumber) {
        case 1:
            currentLevel = new Level2(window->GetResolution());
            break;

        case 2:
            currentLevel = new Level3(window->GetResolution());
            break;

        case 3:
            currentLevel = new Level1(window->GetResolution());
            break;
        }

        currentLevel->InitLevel();
        return;
    }

    currentLevel->Update(deltaTimeSeconds);

    DrawScene();
}

void BrickBreaker::FrameEnd() {

}

void BrickBreaker::DrawScene() {
    // Draw walls
    Wall **walls = currentLevel->GetWalls();
    for (int i = 0; i < 3; ++i) {
        Mesh *wallMesh = meshes.at("wall" + i);
        modelMatrix = glm::mat3(1);
        RenderMesh2D(wallMesh, shaders.at("VertexColor"), modelMatrix);
    }

    // Draw ball
    Ball *ball = currentLevel->GetBall();
    Mesh *ballMesh = meshes.at("ball");
    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform2D::Translate(ball->GetPosition().x, ball->GetPosition().y);
    if (currentLevel->GetPowerUps()[0]->IsActive()) {
        modelMatrix *= Transform2D::Scale(currentLevel->GetBallIncreasingSize(),
                                          currentLevel->GetBallIncreasingSize());
    }
    RenderMesh2D(ballMesh, shaders.at("VertexColor"), modelMatrix);

    // Draw platform
    Platform *platform = currentLevel->GetPlatform();
    Mesh *platformMesh = meshes.at("platform");
    modelMatrix = glm::mat3(1) * Transform2D::Translate(platform->GetPosition().x,
                                                     platform->GetPosition().y);
    if (currentLevel->GetPowerUps()[1]->IsActive()) {
        modelMatrix *= Transform2D::Scale(currentLevel->GetPlatformIncreasingSize(), 1.0f);
    }
    RenderMesh2D(platformMesh, shaders.at("VertexColor"), modelMatrix);

    // Draw Bricks
    Mesh *brickMesh = NULL;
    for (int i = 0; i < currentLevel->GetBricksRows(); ++i) {
        for (int j = 0; j < currentLevel->GetBricksColumns(); ++j) {

            glm::vec3 pos;
            modelMatrix = glm::mat3(1);
            Brick *brick = currentLevel->GetBricks()[i][j];

            switch (brick->GetHealth()) {
            case 0:
            case 1:
                brickMesh = meshes.at("brick_normal");
                break;

            case 2:
                brickMesh = meshes.at("brick_double");
                break;

            case 3:
                brickMesh = meshes.at("brick_triple");
                break;

            case -1:
                brickMesh = meshes.at("brick_last");
                break;
            }

            switch (currentLevel->GetBricks()[i][j]->GetDestroyStatus()) {
            case Brick::destroyed :
                continue;

            case Brick::destroying: {
                float time = brick->GetDestroyingTimeRemaining();
                pos.x = brick->GetPosition().x + (1.0f - time) / 2.0f * brick->GetWidth();
                pos.y = brick->GetPosition().y + (1.0f - time) / 2.0f * brick->GetHeight();

                modelMatrix = glm::mat3(1) * Transform2D::Translate(pos.x, pos.y)
                                           * Transform2D::Scale(time, time);
                break;
            }

            case Brick::notDestroyed :
                pos = currentLevel->GetBricks()[i][j]->GetPosition();
                modelMatrix = glm::mat3(1) * Transform2D::Translate(pos.x, pos.y);
                break;
            }

            RenderMesh2D(brickMesh, shaders.at("VertexColor"), modelMatrix);
        }
    }

    // Draw falling PowerUps
    for (BrickBreakerObjects::PowerUp* it : currentLevel->GetFallingPowerUp()) {
        Mesh *powerUpMesh = meshes.at("powerup" + it->GetType());
        float x = it->GetPosition().x + it->GetLength() / 2.0f;
        float y = it->GetPosition().y + it->GetLength() / 2.0f;
        modelMatrix = glm::mat3(1) * Transform2D::Translate(x, y)
                                   * Transform2D::Rotate(totalTime);
        RenderMesh2D(powerUpMesh, shaders.at("VertexColor"), modelMatrix);
    }

    // Draw lives
    for (int i = 0; i < currentLevel->GetLives()->GetLives(); ++i) {
        glm::vec3 pos = currentLevel->GetLives()->GetPosition();
        pos.x = pos.x + currentLevel->GetLives()->GetSpaceBetweenLives() * i;
        modelMatrix = glm::mat3(1) * Transform2D::Translate(pos.x, pos.y);
        RenderMesh2D(ballMesh, shaders.at("VertexColor"), modelMatrix);
    }
    
}

void BrickBreaker::OnInputUpdate(float deltaTime, int mods) {

}


void BrickBreaker::OnKeyPress(int key, int mods) {

}

void BrickBreaker::OnKeyRelease(int key, int mods) {

}

void BrickBreaker::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    Platform *platform = currentLevel->GetPlatform();
    glm::vec3 newPosition = glm::vec3(mouseX - platform->GetWidth() / 2.0f,
                                     platform->GetPosition().y, 0.0f);
    platform->SetPosition(newPosition, currentLevel->GetWalls()[0]->GetWidth(),
                         (float)(window->GetResolution().x));

    Ball *ball = currentLevel->GetBall();
    if (!ball->IsLaunched()) {
        float ballX = platform->GetPosition().x + platform->GetWidth() / 2.0f;
        float ballY = ball->GetPosition().y;
        glm::vec3 ballNewPossition = glm::vec3(ballX, ballY, 0.0f);
        ball->SetPosition(ballNewPossition);
    }
}

void BrickBreaker::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT) && 
            !currentLevel->GetBall()->IsLaunched()) {

        currentLevel->GetBall()->Launch();
    }
}

void BrickBreaker::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {

}

void BrickBreaker::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {

}