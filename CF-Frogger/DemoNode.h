#pragma once
#include "Entity.h"
#include <string>
#include <iostream>
namespace GEX {
	class DemoNode : public Entity
	{
	public:
		DemoNode(std::string name) : _name(name) {};
		virtual ~DemoNode() {};
	private:
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override 
		{
			std::cout << "draw " << _name << std::endl;
		}
	private:
		std::string _name;
	};

}