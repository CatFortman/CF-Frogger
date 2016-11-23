/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/

#include "Component.h"

namespace GEX
{

	namespace GUI
	{

		Component::Component() : 
			_isSelected(false), 
			_isActive(false)
		{}

		Component::~Component()
		{}

		bool Component::isSelected() const
		{
			return _isSelected;
		}

		void Component::select()
		{
			_isSelected = true;
		}

		void Component::deselect()
		{
			_isSelected = false;
		}

		bool Component::isActive() const
		{
			return _isActive;
		}

		void Component::activate()
		{
			_isActive = true;
		}

		void Component::deactivate()
		{
			_isActive = false;
		}

	}
}
