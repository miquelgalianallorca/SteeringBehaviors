#pragma once

#include "steering.h"

class SteeringAlign : public Steering {
public:
    SteeringAlign()  {}
    ~SteeringAlign() {}

    void GetAcceleration(
        Character &character,
        Params &params,
        USVec2D &outLinearAcceleration,
        float &outAngularAcceleration);

    void DrawDebug();

private:
    USVec2D characterLocation;
    float characterRotation;
    float desiredAngularVelocity;
    float desiredAngularAcceleration;
};