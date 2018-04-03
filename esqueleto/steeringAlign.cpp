#include "stdafx.h"
#include "steeringAlign.h"
#include "character.h"

void SteeringAlign::GetAcceleration(
    Character &character,
    const Params &params,
    USVec2D &outLinearAcceleration,
    float &outAngularAcceleration)
{
    characterLocation = character.GetLoc();

    desiredLinearVelocity = params.targetPosition - character.GetLoc();
    float length = desiredLinearVelocity.Length();
    desiredLinearVelocity.NormSafe();
    if (length > params.arrive_radius) {
        desiredLinearVelocity.Scale(character.GetMaxVelocity());
    }
    else {
        // Reduce speed
        float factor = length / params.arrive_radius;
        desiredLinearVelocity.Scale(character.GetMaxVelocity() * factor);
    }
    desiredLinearAcceleration = desiredLinearVelocity - character.GetLinearVelocity();
    desiredLinearAcceleration.NormSafe();
    desiredLinearAcceleration.Scale(character.GetMaxAcceleration());

    outLinearAcceleration = desiredLinearAcceleration;
}

void SteeringAlign::DrawDebug() {
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 0.5f);
    MOAIDraw::DrawLine(characterLocation,
        characterLocation + desiredLinearVelocity);

    gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);
    MOAIDraw::DrawLine(characterLocation,
        characterLocation + desiredLinearAcceleration);

}