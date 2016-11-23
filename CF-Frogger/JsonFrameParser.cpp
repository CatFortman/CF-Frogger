//
//  JsonFrameParser.cpp
//  TextureAtlasSandbox
//
//  Created by Dave Burchill on 2016-11-17.
//  Copyright © 2016 Dave Burchill. All rights reserved.
//

#include "JsonFrameParser.hpp"
#include <fstream>

#include "json.hpp"
// for convenience
using json = nlohmann::json;


JsonFrameParser::JsonFrameParser(std::string path)
{
    std::ifstream ifs(path);
    _json= json::parse(ifs);
}

std::vector<sf::IntRect>  JsonFrameParser::getFramesFor(std::string animationName) const
{
    std::vector<sf::IntRect> data;
    
    json k = _json["frames"];
    for (auto i : k) {
        
        std::string tmpStr = i["filename"]; // needs to be a string, use implicit conversion
        
        if ( tmpStr.compare(0,animationName.size(), animationName) == 0)  {
            std::cout << i["frame"]["x"] << ", ";
            std::cout << i["frame"]["y"] << ", ";
            std::cout << i["frame"]["w"] << ", ";
            std::cout << i["frame"]["h"] << "\n";
            
            data.push_back(sf::IntRect( i["frame"]["x"],
                                       i["frame"]["y"],
                                       i["frame"]["w"],
                                       i["frame"]["h"]));
        }
    }
    return data;
}
