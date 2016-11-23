/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once


#include "Component.h"

#include <vector>
#include <memory>


namespace GEX
{
	namespace GUI
	{
		class Container : public Component
		{
		public:
			typedef std::shared_ptr<Container> Ptr;

		public:
								Container();

			void				pack(Component::Ptr component);

			virtual bool		isSelectable() const;
			virtual void		handleEvent(const sf::Event& event);


		private:
			virtual void		draw(sf::RenderTarget& target, sf::RenderStates states) const;

			bool				hasSelectableChildren() const;
			void				select(std::size_t index); ///< change selected child to index
			void				selectNext();
			void				selectPrevious();


		private:
			std::vector<Component::Ptr>		_children;
			int								_selectedChild; ///< index of selected or -1 for no selection
		};
	}
}