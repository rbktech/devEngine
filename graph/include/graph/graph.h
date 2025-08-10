#pragma once

#include <atomic>
#include <string>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace graph
{
    class CGraph
    {
    private:
        std::atomic<int> mInit;

        glm::vec4 mBackground;

        float mScreenWidth;
        float mScreenHeight;

        float mZoom;

        int mX;
        int mY;

    public:
        CGraph();
        ~CGraph();

        void Init(const float& screenWidth, const float& screenHeight);

        void Draw();

        void SetBackground(const float& r, const float& g, const float& b, const float& a = 1.0f);

        void Set(const std::string& name, const float* data, const int& size);

        void Set(const std::string& name, const glm::vec3& color);

        void Create(const std::string& name);

        void Scroll(const float& xOffset, const float& yOffset);

        void Move(const float& xPosition, const float& yPosition);

        void Cursor(const float& xPos, const float& yPos, float& xReal, float& yReal);

        void SetSize(const float& screenWidth, const float& screenHeight);

        void SetGrid(const int& x, const int& y);
    };
}