#ifndef MAPREADER_HPP_INCLUDED
#define MAPREADER_HPP_INCLUDED

#include <vector>
#include <string>

class MapReader {
public:
    //Constructor
    MapReader() {}
    //Reads a lvl file and returns the map data in a vector
    std::vector< std::vector< std::vector< int > > > readMapFile( std::string fileName );

private:
    //Read a row/line of map data
    std::vector< std::vector< int > > readMapRow( std::string line );

    //Read and return information about a single tile
    std::vector< int > readMapTile( std::string tile );
};

#endif // MAPREADER_HPP_INCLUDED
