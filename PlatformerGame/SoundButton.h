#pragma once

#include "PauseButton.h"
#include "LoadSave.h"

class SoundButton : public PauseButton
{
private:
	sf::Texture* soundTexture;
	sf::Sprite* soundSprites[2][3];
	bool mouseOver, mousePressed;
	bool muted;
	int rowIndex, colIndex;

	void LoadSoundTextures();

public:
	SoundButton(float x, float y, float width, float height);
	~SoundButton();

	void ResetBools();

	bool IsMouseOver();
	bool IsMousePressed();
	bool IsMuted();

	void SetMouseOver(bool mouseOver);
	void SetMousePressed(bool mousePressed);
	void SetMuted(bool muted);

	void UpdateProperties();

	void Render(sf::RenderTarget* renderTarget);
};

