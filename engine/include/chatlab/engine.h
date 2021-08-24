#pragma once

struct Engine {
public:
    static void init();
    static float getDeltaTime();
    inline static float prevTime = 0.0f;

private:
};
