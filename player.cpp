#include "player.h"
#include <iostream>

Player::Player()
	: GameObject(__FUNCTION__)
{
	
}

Player::~Player()
{

}
void Player::input(int x, int y)
{
	std::cout << x << " " << y << std::endl;
	glm::vec3 a = { x,y,0 };
	m_position += a;
}
