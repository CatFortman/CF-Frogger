/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Graphical components. This class is in it's own namespace GUI

*/

#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <memory>

namespace sf
{
	class Event;
}

namespace GEX
{
	namespace GUI
	{
		class Component : public sf::Drawable, public sf::Transformable 
		{
		public:
			typedef std::shared_ptr<Component> Ptr;

		public:
								Component();
			virtual				~Component();

								Component(const Component&) = delete;    ///< non-copyable 
			Component&			operator =(const Component&) = delete;	 ///< non-copyable 

			virtual bool		isSelectable() const = 0;
			bool				isSelected() const;
			virtual void		select();
			virtual void		deselect();

			virtual bool		isActive() const;
			virtual void		activate();
			virtual void		deactivate();

			virtual void		handleEvent(const sf::Event& event) = 0;


		private:
			bool				_isSelected;
			bool				_isActive;
		};
	}
}

