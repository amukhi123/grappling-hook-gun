#include "Crosshair.h"

Crosshair::Crosshair() : IUserInterfaceBase("resources/Crosshair.png")
{
}

void Crosshair::Update()
{
	constexpr float CROSSHAIR_ALPHA {1.f};
	const Texture crosshairTexture {UserInterfaceTexture()};

	DrawTexture(crosshairTexture, GetScreenWidth() / 2 - crosshairTexture.width / 2, GetScreenHeight() / 2 - crosshairTexture.height / 2, ColorAlpha(WHITE, CROSSHAIR_ALPHA));
}
