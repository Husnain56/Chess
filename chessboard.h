#pragma once

#include<SFML/Graphics.hpp>
using namespace sf;

class Chessboard {

private:
	Texture GameBgtxt;
	Sprite GameBg;
	Texture boardbgTexture;
	Sprite chessboard;

public:

	Chessboard();

	void DrawBg(RenderWindow& Window);

};


