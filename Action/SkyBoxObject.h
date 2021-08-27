#pragma once
#include "GameObject.h"

class SkyBoxObject : public GameObject
{
public:

	SkyBoxObject(bool _reUseGameObject, const Tag _objectTag);
	~SkyBoxObject();

	void UpdateGameObject(float _deltaTime)override;

	class CubeMapComponent* GetCubeMapComp() { return cubeMapComp; }

private:

	class CubeMapComponent* cubeMapComp;

	class Environment* environmnet;
};

