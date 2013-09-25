#pragma once
#include "Dx11Base.h"

class BlankDemo : public Dx11Base
{
public:
	BlankDemo(void);
	virtual ~BlankDemo(void);

	bool LoadContent();
	void UnloadContent();

	void Update(float dt);
	void Render();
};

