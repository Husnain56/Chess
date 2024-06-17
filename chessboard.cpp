#include"chessboard.h"
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Chessboard::Chessboard() {
    if (!GameBgtxt.loadFromFile("Backgrounds/GameBg.jpg")) {}
    GameBg.setTexture(GameBgtxt);
    if (!boardbgTexture.loadFromFile("Backgrounds/chessboard.png")) {}
    chessboard.setTexture(boardbgTexture);
    chessboard.setPosition(0, 140);
}


void Chessboard::DrawBg(RenderWindow& Window) {
    Window.clear();
    Window.draw(GameBg);
    Window.draw(chessboard);
}

