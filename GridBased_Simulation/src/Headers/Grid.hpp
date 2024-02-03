#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Useful.hpp"
#include "Common.hpp"

class Cell : public sf::RectangleShape
{
public:
	Cell() = default;
	~Cell() = default;
	Cell(unsigned int CellSize, sf::Vector2i pos);
	Cell(unsigned int CellSize, sf::Vector2i pos, bool State);

	void updateCell();

	bool state = false;
private:
	unsigned int cellSize;
};



class Grid
{
public:
	Grid() = default;
	~Grid() = default;
	Grid(unsigned int CellSize);

	void update();
	void draw();
	void resetGrid(std::vector<std::vector<Cell>>* g);
	void swapGrids();
	void gravity();
	bool inBoundsX(unsigned int i);
	bool inBoundsY(unsigned int j);
private:
	std::vector<std::vector<Cell*>> grid;
	std::vector<std::vector<Cell*>> backGrid;
	sf::Vector2u cellSize;
	sf::Vector2u gridSize;
	sf::Vector2u cellNum;

	bool lastLeft = false, lastFrame = false;

	void mouseDrag();
};
