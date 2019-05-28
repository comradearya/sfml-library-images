#include "lab03.hpp"


pool* pool_create()
{
	 pool* pool1;
    pool1 = new pool;
    int block = sizeof(img) + 256 * 256 * sizeof(COL) + sizeof(mem_block_info);
    int mem_block = sizeof(img) + 256 * 256 * sizeof(COL); 
    pool1->size = 11 * block;
    pool1->begin = new char[pool1->size];
    pool1->end = pool1->begin + pool1->size;
    for(int i = 0; i < pool1->size; i++)
    {
        pool1->begin[i] = 0;
    }
	return pool1;
}

void poolObjdelete(pool* pool1)
{
	delete[] pool1->begin;
	delete pool1;
}

img* pool_new(pool* pool1, int size)
{
    char* ptr = pool1->begin;
    while((ptr + sizeof(mem_block_info) + size) < pool1->end)
    {
        if(reinterpret_cast<mem_block_info*>(ptr)->allocated == 1)
        {
            int curr_block_size = reinterpret_cast<mem_block_info*>(ptr)->block_size;
            ptr = ptr + sizeof(mem_block_info) + curr_block_size;
        }
        else if(reinterpret_cast<mem_block_info*>(ptr)->allocated == 0)
        {
            reinterpret_cast<mem_block_info*>(ptr)->allocated = 1;
            reinterpret_cast<mem_block_info*>(ptr)->block_size = size;
            return(reinterpret_cast<img*>(ptr + sizeof(mem_block_info)));   
        }
        else
        {
            return(nullptr);
        }
    }
    return(nullptr);
}

void pool_delete(img* image, pool* pool1)
{
    if((reinterpret_cast<char*>(image) <= pool1->end) && (reinterpret_cast<char*>(image) >= pool1->begin))
    {
        char* ptr = reinterpret_cast<char*>(image);
        mem_block_info* mem = reinterpret_cast<mem_block_info*>(ptr - sizeof(mem_block_info));
        int mem_size = mem->block_size + sizeof(mem_block_info);
        mem->allocated = 0;
        mem->block_size = 0;
        ptr = reinterpret_cast<char*>(mem);
        for(int i = 0; i < mem_size; i++)
        {
            ptr[i] = 0;
        }
    }
    else
    {
        cout<<"the image is not in pool, can't delete it"<<endl;
    }
}

tga* create_header(tga *h)
{
	
	h->datatypecode = 2;
	h->bitsperpixel = 32;
	h->width = 256;
	h->height = 256;
	h->colourmapdepth = 0;
	h->colourmaplength = 0;
	h->colourmaporigin = 0;
	h->x_origin = 0;
	h->y_origin = 0;
	h->colourmaptype = 0;
	h->idlength = 0;
	h->imagedescriptor = 8;
	return h;	
}

COL* create_color(COL *pointer, int choice) 
{
switch (choice)
        {
            case 0:
			{
				for (int i = 0; i < 256; i++) 
				{
					for (int j = 0; j < 256; j++) 
					{
						pointer[j*256 + i].rgba.r = 0 + rand() % 255;
						pointer[j*256 + i].rgba.g = 0 + rand() % 255;
						pointer[j*256 + i].rgba.b = 0 + rand() % 255;
						pointer[j*256 + i].rgba.a = 0 + rand() % 255;
					}
				}
                break;
			}
            case 1:
			{
                int col1 = 0;
				for (int i = 0; i < 256; i++) 
				{
					for (int j = 0; j < 256; j++)
					{
						col1 = (j*256+i)%256;
						pointer[j*256 + i].rgba.r = col1;
						pointer[j*256 + i].rgba.g = col1;
						pointer[j*256 + i].rgba.b = col1;
						pointer[j*256 + i].rgba.a = col1;
					}
				}
                break;
			}
            case 2:
			{
                int col2 = 0;
				for (int i = 0; i < 256; i++)
				{
					for (int j = 0; j < 256; j++)
					{
						col2 = (i*j);
						pointer[j*256 + i].rgba.r = col2;
						pointer[j*256 + i].rgba.g = col2;
						pointer[j*256 + i].rgba.b = col2;
						pointer[j*256 + i].rgba.a = col2;
					}
				}
                break;
			}
            case 3:
			{
                int col3 = 0;
				for (int i = 0; i < 256; i++)
				{
					for (int j = 0; j < 256; j++)
					{
						col3 = (i+j)%256;
						pointer[j*256 + i].rgba.r = col3;
						pointer[j*256 + i].rgba.g = col3;
						pointer[j*256 + i].rgba.b = col3;
						pointer[j*256 + i].rgba.a = col3;
					}
				}
                break;
			}
            case 4:
			{
                int col4 = 0;
				for (int i = 0; i < 256; i++)
				{
					for (int j = 0; j < 256; j++)
					{
						col4 = fabs(i-j);
						pointer[j*256 + i].rgba.r = col4;
						pointer[j*256 + i].rgba.g = col4;
						pointer[j*256 + i].rgba.b = col4;
						pointer[j*256 + i].rgba.a = col4;
					}
				}
                break;
			}
            case 5:
			{
                int col5 = 0;
				for (int i = 0; i < 256; i++)
				{
					for (int j = 0; j < 256; j++)
					{
						col5 = static_cast<int>(sqrt(i*j));
						pointer[j*256 + i].rgba.r = col5;
						pointer[j*256 + i].rgba.g = col5;
						pointer[j*256 + i].rgba.b = col5;
						pointer[j*256 + i].rgba.a = col5;
					}
				}
                break;
			}
            case 6:
			{
                double diag1 = (sqrt(256*256*2)) / 2;
				int distance1 = 0;
				for (int i = 0; i < 256; i++)
				{
					for (int j = 0; j < 256; j++)
					{
						distance1 = static_cast<int>((sqrt((256 / 2 - i)*(256/ 2 - i) + (256/ 2 - j)*(256/ 2 - j))/diag1)*255);
						pointer[j*256 + i].rgba.r = distance1;
						pointer[j*256 + i].rgba.g = distance1;
						pointer[j*256 + i].rgba.b = distance1;
						pointer[j*256 + i].rgba.a = distance1;
					}
				}
                break;
			}
            case 7:
			{
				int distance2 = 0;
				for (int i = 0; i < 256; i++)
				{
					for (int j = 0; j < 256; j++)
					{
						distance2 = static_cast<int>((sqrt((256/ 2 - i)*(256/ 2 - i) + (256 / 2 - j)*(256/ 2 - j))/(255/2))*255);
						pointer[j*256 + i].rgba.r = distance2;
						pointer[j*256 + i].rgba.g = distance2;
						pointer[j*256 + i].rgba.b = distance2;
						pointer[j*256 + i].rgba.a = distance2;
					}
				}
                break;
			}
            case 8:
			{
                int col8 = 0;
				for (int i = 0; i < 256; i++)
				{
					for (int j = 0; j < 256; j++)
					{
						col8 = static_cast<int>(fabs((cos((i+j)*3.14/180))*255));
						pointer[j*256 + i].rgba.r = col8;
						pointer[j*256 + i].rgba.g = col8;
						pointer[j*256 + i].rgba.b = col8;
						pointer[j*256 + i].rgba.a = col8;
					}
				}
                break;
			}
            case 9:
			{
                int col9 = 0;
				for (int i = 0; i < 256; i++)
				{
					for (int j = 0; j < 256; j++)
					{
						col9 = static_cast<int>(fabs((sin((i+j)*3.14/180)*255)));
						pointer[j*256 + i].rgba.r = col9;
						pointer[j*256 + i].rgba.g = col9;
						pointer[j*256 + i].rgba.b = col9;
						pointer[j*256 + i].rgba.a = col9;
					}
				}
                break;
			}
            default:
                break;
        }
		return pointer;
}


