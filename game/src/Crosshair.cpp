#include "Crosshair.h"

Crosshair::Crosshair() : IUserInterfaceBase("resources/Crosshair.png")
{
}

void Crosshair::Update()
{
	constexpr float CROSSHAIR_ALPHA {0.5f};
	const Texture crosshair {UserInterfaceTexture()};

	DrawTexture(crosshair, GetScreenWidth() / 2 - crosshair.width / 2, GetScreenHeight() / 2 - crosshair.height / 2, ColorAlpha(WHITE, CROSSHAIR_ALPHA));
}
