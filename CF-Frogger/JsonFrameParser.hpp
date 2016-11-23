//
//  JsonFrameParser.hpp
//  TextureAtlasSandbox
//
//  Created by Dave Burchill on 2016-11-17.
//  Copyright © 2016 Dave Burchill. All rights reserved.
//

#ifndef JsonFrameParser_hpp
#define JsonFrameParser_hpp

#include <SFML/system.hpp>
#include <SFML/Graphics.hpp>
#include "json.hpp"
#include <vector>


class JsonFrameParser
{
public:
                                    JsonFrameParser(std::string path);
    std::vector<sf::IntRect>        getFramesFor(std::string animationName) const;
    
private:
    nlohmann::json                  _json;
};

 

#endif /* JsonFrameParser_hpp */
