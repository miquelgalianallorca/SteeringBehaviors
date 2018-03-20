#pragma once

#include "steering.h"

class SteeringSeek : public Steering {
public:
    SteeringSeek()  {}
    ~SteeringSeek() {}

    void GetAcceleration(
        Character &character,
        const USVec2D &targetLocation,
        USVec2D &outLinearAcceleration,
        float &outAngularAcceleration);

    void DrawDebug();

private:
    USVec2D characterLocation;
    USVec2D desiredLinearVelocity;
    USVec2D desiredLinearAcceleration;
};