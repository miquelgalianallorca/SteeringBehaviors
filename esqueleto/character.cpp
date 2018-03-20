#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>

#include <params.h>

Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND (MOAIEntity2D)
	RTTI_END
}

Character::~Character()
{

}

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
    // Update acceleration with steering
    USVec2D linearAcceleration(0.f, 0.f);
    float   angularAcceleration = 0.f;
    steeringArrive.GetAcceleration(*this, mParams.targetPosition,
        linearAcceleration, angularAcceleration);

    // Update velocity with acceleration
    USVec2D newLinearVel = GetLinearVelocity() +
        linearAcceleration * step;
    if (newLinearVel.Length() > mParams.max_velocity) {
        newLinearVel.NormSafe();
        newLinearVel.Scale(mParams.max_velocity);
    }
    SetLinearVelocity(newLinearVel.mX, newLinearVel.mY);
    
    // Update location and rotation
    SetLoc(GetLoc() + GetLinearVelocity() * step);
    SetRot(GetRot() + GetAngularVelocity() * step);
}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);
    gfxDevice.SetPenWidth(3.f);
    // Draw origin
	MOAIDraw::DrawPoint(0.0f, 0.0f);

    // Draw steering
    MOAIDraw::DrawEllipseFill(mParams.targetPosition.mX, mParams.targetPosition.mY,
        10.f, 10.f, 3);
    steeringArrive.DrawDebug();
}





// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
	