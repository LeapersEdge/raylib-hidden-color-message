#pragma once

#include <fstream>
#include "VectorD.h"

namespace popo
{
    unsigned char* read_BMP(char* filename)
    {
        int i;
        FILE* f = fopen(filename, "rb");
        unsigned char info[54];

        // read the 54-byte header
        fread(info, sizeof(unsigned char), 54, f); 

        // extract image height and width from header
        int width = *(int*)&info[18];
        int height = *(int*)&info[22];

        // allocate 3 bytes per pixel
        int size = 3 * width * height;
        unsigned char* data = new unsigned char[size];

        // read the rest of the data at once
        fread(data, sizeof(unsigned char), size, f); 
        fclose(f);

        for(i = 0; i < size; i += 3)
        {
            // flip the order of every 3 bytes
            unsigned char tmp = data[i];
            data[i] = data[i+2];
            data[i+2] = tmp;
        }

        return data;
    }

    popo::Vector2D size_BMP(char* filename)
    {
	    FILE* f = fopen(filename, "rb");
	    unsigned char info[54];

	    // read the 54-byte header
	    fread(info, sizeof(unsigned char), 54, f); 

	    // extract image height and width from header
	    int width = *(int*)&info[18];
	    int height = *(int*)&info[22];

	    fclose(f);

	    return popo::Vector2D(width, height);
    }
   
}
