#include "Grid.hpp"

Cell::Cell(unsigned int CellSize, sf::Vector2i pos) : cellSize(CellSize), state(0)
{
	this->setSize(sf::Vector2f(CellSize, CellSize));
	//this->setOrigin(this->getSize() / 2.0f);
	this->setPosition(sf::Vector2f(pos));
	//this->setFillColor(sf::Color::White);
	this->setFillColor(sf::Color(255, 242, 166));
	this->update();
}

Cell::Cell(unsigned int CellSize, sf::Vector2i pos, bool State) : cellSize(CellSize), state(State)
{
	this->setSize(sf::Vector2f(CellSize, CellSize));
	this->setOrigin(this->getSize() / 2.0f);
	this->setPosition(sf::Vector2f(pos));
	this->update();
}

void Cell::updateCell()
{
	//this->setFillColor(sf::Color::White);
}

Grid::Grid(unsigned int CellSize)
{
	cellSize = { CellSize, CellSize };
	cellNum = sf::Vector2u(windowSize.x / CellSize, windowSize.y / CellSize);
	//sf::Vector2i pos = sf::Vector2i(cellSize.x / 2, cellSize.y / 2);
	sf::Vector2i pos = { 0,0 };

	grid.resize(cellNum.x);
	backGrid.resize(cellNum.x);

	float increment = 255 / cellNum.y, curr = 0;

	for (int i = 0; i < cellNum.x; ++i) {
		grid[i].resize(cellNum.y);
		backGrid[i].resize(cellNum.y);

		for (int j = 0; j < cellNum.y; ++j) {
			grid[i][j] = new Cell(CellSize, pos);
			backGrid[i][j] = new Cell(CellSize, pos);

			pos.y += CellSize;
		}

		pos.x += CellSize;
		pos.y = 0;
	}
}

void Grid::update()
{
	mouseDrag();
	gravity();
	swapGrids();
}

void Grid::draw()
{
	for (auto cells : grid) {
		for (Cell* c : cells) {
			if (c->state) {
				//c->updateCell();
				window->draw(*c);
			}
		}
	}
}

void Grid::resetGrid(std::vector<std::vector<Cell>>* g)
{
	for (auto cells : *g) {
		for (Cell c : cells) {
			c.state = 0;
		}
	}
}

void Grid::swapGrids()
{
	for (int i = 0; i < cellNum.x ; ++i) {
		for (int j = 0; j < cellNum.y; ++j) {
			grid[i][j]->state = backGrid[i][j]->state;
			backGrid[i][j]->state = 0;
		}
	}
}

void Grid::gravity()
{
	for (int i = 0; i < cellNum.x; ++i) {
		for (int j = 0; j < cellNum.y; ++j) {
			if (grid[i][j]->state) {
				if (inBoundsY(j + 1)) {
					if (!grid[i][j + 1]->state) {
						backGrid[i][j + 1]->state = 1;
					}
					else {
						int dir = (rand50() == 0) ? -1 : 1;

						if (inBoundsX(i + dir) && !grid[i + dir][j + 1]->state) backGrid[i + dir][j + 1]->state = 1;
						else if (inBoundsX(i - dir) && !grid[i - dir][j + 1]->state) backGrid[i - dir][j + 1]->state = 1;
						else backGrid[i][j]->state = 1;
					}
				}
				else backGrid[i][j]->state = 1;
			}
		}
	}
}

bool Grid::inBoundsX(unsigned int i)
{
	return i < cellNum.x && i > 0;
}

bool Grid::inBoundsY(unsigned int j)
{
	return j < cellNum.y && j > 0;
}

void Grid::mouseDrag()
{
	bool left = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	//if (left && !lastLeft) {
	if (left) {
		if (!lastFrame) {
			if (mousePos.x > 0 && mousePos.x < windowSize.x && mousePos.y > 0 && mousePos.y < windowSize.y) {
				const sf::Vector2i pos = sf::Vector2i(mousePos.x / cellSize.x, mousePos.y / cellSize.y);
				grid[pos.x][pos.y]->state = 1;
			}
		}
		lastFrame = !lastFrame;
	}
	lastLeft = left;
}
