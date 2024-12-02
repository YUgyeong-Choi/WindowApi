#pragma once
#include "StageScene.h"
class StageHero :
    public StageScene
{
public:
    virtual void SpawnMonster();
public:
    virtual void Initialize(Obj* _pPlayer) override;
    virtual int	 Update();
};

