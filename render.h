#ifndef RENDER_H
#define RENDER_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "logic.h" // То, что будет рендерить

#define BLOCK_RENDER_SIZE 32
using namespace sf;
//Набор функций для визуального отображения игры
void Render_flag_animated(int i, int j, sf::RenderWindow &window);
void Render_explosion_animated(int i, int j, sf::RenderWindow &window);
void Render_field(sf::RenderWindow &window, Map &map, Gamer gamer);
void Render_win();
#endif // RENDER_H

