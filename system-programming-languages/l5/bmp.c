#include "bmp.h"
#include "math.h" 
#define M_PI 3.14159265358979323846 


enum read_status from_bmp(FILE* in, struct image_t* const read) //read img
{
    struct bmp_header header;
    struct bmp_header_info header_info;

    fread(&header, sizeof(header), 1, in);
    fread(&header_info, sizeof(header_info), 1, in);

    if(header.bfType!=0x4D42){    
        return READ_INVALID_SIGNATURE;
    }

    if(header_info.biBitCount !=24 && header_info.biBitCount !=8){  
        return READ_INVALID_BITS;
    }

    printf("%s width: %d height: %d deepness: %d\n", "Enter_data ", header_info.biWidth, header_info.biHeight, header_info.biBitCount);

    read->width = header_info.biWidth;
    read->height = header_info.biHeight;
    read->bits_per_pixel = header_info.biBitCount;

    if (header_info.biBitCount == 8){
        read->color_table_size = header.bOffBits - 54;
        read->color_data = malloc((header.bOffBits - 54) * sizeof(struct pixel_t));
        read->pixels_data = malloc(read->width * read->height * (header_info.biBitCount/8));
    }    
    else{
        read->color_table_size = 0;
        read->pixels_data = malloc(read->width * read->height * (header_info.biBitCount/8)); 
    }

    int offset = ((read->width * (header_info.biBitCount/8)) %4 == 0) ? 0 : 4 - ((read->width * (header_info.biBitCount/8)) %4); 
    uint8_t *p_data = read->pixels_data;

    if(header_info.biBitCount == 8){
        struct pixel_t *c_data = read->color_data;

        for (int i = 0; i < (header.bOffBits - 54); i++){
            fread(c_data, sizeof(uint8_t), 1, in);
            c_data++;
        }

    }

    for (int i = 0; i < read->height; i++){      

        for (int j = 0; j < read->width; j++){

            size_t t = fread(p_data, sizeof(uint8_t), header_info.biBitCount/8, in);
                         
            //printf("%x ", *p_data);    
            p_data += header_info.biBitCount/8; 


        
        }
        //printf("\n");

        fseek(in, offset, SEEK_CUR);  

    }          

    return READ_OK;

}

enum write_status to_bmp(FILE* out, struct image_t const* img) {
    struct bmp_header header;
    struct bmp_header_info header_info;

    header.bfType = 19778;  
    header.bfReserved_1 = 0;
    header.bfReserved_2 = 0;

    header_info.biWidth = img->width;
    header_info.biHeight = img->height;   


    int padding = ((img->width * (img->bits_per_pixel/8) %4 == 0) ? 0 : 4 - ((img->width * (img->bits_per_pixel/8)) %4));
    
    header.bOffBits = 54 + img->color_table_size; 

    header_info.biBitCount = img->bits_per_pixel; 
    header_info.biSizeImage = 0; 
    
    header.bfileSize = header.bOffBits + img->width*img->height*(img->bits_per_pixel/8) + padding*img->height;  
    
    header_info.biCompression = 0;   
    header_info.biSize = 40;     
    header_info.biPlanes = 1;    
    header_info.biClrUsed = 0;   
    header_info.biClrImportant = 0;  
    header_info.biXPelsPerMeter = 2834;  
    header_info.biYPelsPerMeter = 2834;  
    
    fwrite(&header, sizeof(struct bmp_header), 1, out);   
    fwrite(&header_info, sizeof(struct bmp_header_info), 1, out);

    if (img->bits_per_pixel == 8) {
        for (size_t i = 0; i < img->color_table_size; i++)
            fwrite(img->color_data + i, sizeof(uint8_t), 1, out);
    }

    printf("%s\n", "Printing pixels");
    for (int i = 0; i < header_info.biHeight; i++){ 


        for (int j = 0; j < header_info.biWidth; j++){

            fwrite(img->pixels_data + (j + i*header_info.biWidth)*(img->bits_per_pixel/8), sizeof(uint8_t), img->bits_per_pixel/8, out);  
        
            //printf("%x ", *(img->pixels_data + (j + i*header_info.biWidth)*(img->bits_per_pixel/8)));
        }

        //printf("\n");


        for (int j = 0; j < padding; j++){

            fputc(0x00, out);  

        }

    }
    return WRITE_OK;
}


struct image_t rotate_right_90(const struct image_t image) {
    struct image_t* rotated_img = malloc(sizeof(struct image_t));     
    rotated_img->width = image.height;
    rotated_img->height = image.width; 
    rotated_img->bits_per_pixel = image.bits_per_pixel;
    rotated_img->color_table_size = image.color_table_size;
    rotated_img->color_data = image.color_data;     
    printf("%d %d\n", rotated_img->width, rotated_img->height);
    uint8_t *rotate = malloc(rotated_img->width * rotated_img->height * image.bits_per_pixel/8); 

    for (int i = 0; i < image.height; i++) 
    {

        for (int j = 0; j < image.width; j++) 
        {
            uint8_t *temp = image.pixels_data + (image.width * i + j)*image.bits_per_pixel/8;

            for (int z = 0; z < image.bits_per_pixel/8; z++)
                rotate[((rotated_img->height - j - 1)*rotated_img->width + i)*(image.bits_per_pixel/8) + z] = *(temp + z);  
        }

    }
    rotated_img->pixels_data = rotate;
    return *rotated_img;
}

struct image_t rotate_left_90(const struct image_t image)  
{
    struct image_t *rotated_img = malloc(sizeof(struct image_t));
    rotated_img->width = image.height;
    rotated_img->height = image.width;
    rotated_img->bits_per_pixel = image.bits_per_pixel;
    rotated_img->color_table_size = image.color_table_size;
    rotated_img->color_data = image.color_data;  

    uint8_t *rotate = malloc(rotated_img->width * rotated_img->height * image.bits_per_pixel/8);

    for (int i = 0; i < image.height; i++) 
    {
        for (int j = 0; j < image.width; j++) 
        {
            //i = 1, j = 2, h = 4, width = 3;
            uint8_t *tmp = image.pixels_data + (image.width * i + j)*image.bits_per_pixel/8;

            for (int z = 0; z < image.bits_per_pixel/8; z++)
                rotate[(j*rotated_img->width + (rotated_img->width - i - 1))*image.bits_per_pixel/8 + z] = *(tmp + z);
        }
    }
    rotated_img->pixels_data = rotate;
    return *rotated_img;
}

struct image_t rotate_any(const struct image_t img, const int dgr){

    int degree = dgr;
    struct image_t image = img;

    degree = degree % 360;

    while(degree < 0){
        degree += 360; 
    }


    while(degree >= 90){
        const struct image_t temp_img = image;
        image = rotate_left_90(temp_img);
        degree -= 90;    
    }

    double angle = degree * M_PI / 180;

    struct image_t *rotated_img = malloc(sizeof(struct image_t));

    rotated_img->width = ceil(image.width*cos(angle) + image.height*(cos(angle-M_PI/2)));
    rotated_img->height = ceil(sqrt(image.width*image.width + image.height*image.height) * sin(angle + atan((double)image.height/image.width))); 
    rotated_img->bits_per_pixel = image.bits_per_pixel;
    rotated_img->color_table_size = image.color_table_size;
    rotated_img->color_data = image.color_data;  

    double x_offset = image.height*(cos(angle-M_PI/2));

    uint8_t *rotate = malloc(rotated_img->width * rotated_img->height * image.bits_per_pixel/8);

    int rotate_x;
    int rotate_y;

    printf("Output_data: Width: %d Height: %d\n", rotated_img->width, rotated_img->height);

    for (int i = 0; i < image.height; i++) 
    {
        for (int j = 0; j < image.width; j++) 
        {
            
            uint8_t *tmp = image.pixels_data + (image.width * i + j)*image.bits_per_pixel/8;

            rotate_x = rint(j*cos(angle) - i*sin(angle) + x_offset);
            rotate_y = rint(j*sin(angle) + i*cos(angle));

            for (int z = 0; z < image.bits_per_pixel/8; z++)
                rotate[(rotated_img->width*rotate_y + rotate_x)*image.bits_per_pixel/8 + z] = *(tmp + z);
        }
    }
    rotated_img->pixels_data = rotate;
    return *rotated_img;

}


    
