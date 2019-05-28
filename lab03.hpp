#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctime>
#include <cstring>

using namespace sf; 
using namespace std;


//void lesson();

#pragma once

#pragma pack(1)
struct tga {
	char  idlength;
	char  colourmaptype;
	char  datatypecode;
	short int colourmaporigin;
	short int colourmaplength;
	char  colourmapdepth;
	short int x_origin;
	short int y_origin;
	short width;
	short height;
	char  bitsperpixel;
	char  imagedescriptor;
};

struct pixel
    {
        char b;
        char g;
        char r;
        char a;
    };

union COL {
	pixel rgba;
	unsigned int p;
};

struct img{
	tga header;
	COL matrix[];
};

struct pool
{
    int size;
    char* begin;
    char* end;
};

struct mem_block_info
{
    int allocated;
    int block_size;
};

tga* create_header(tga *);
COL* create_color(COL *, int );

pool* pool_create();
img* pool_new (pool*, int);
void pool_delete (img*, pool*);
void poolObjdelete(pool*);