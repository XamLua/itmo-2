#include <string.h>
#include "bmp.h"

int main(int argc, char *argv[]){

    FILE *f_in = fopen(argv[1], "rb");  

    struct image_t* const in_image = malloc(sizeof(struct image_t));

    enum read_status read_result = from_bmp(f_in, in_image);

    FILE *f_out = fopen(argv[2], "wb");

    if(!f_in)
    {
        puts("Can't find input file.\n");
        return 2;
    }

    if(!f_out){
        puts("Can't create output file.\n");
    }

    switch (read_result)
    {
            case READ_INVALID_HEADER: 
            {
                printf("Invailid header.\n");
                return 2;
            }
            case READ_INVALID_BITS: 
            {
                printf("Invailid deep img\n");
                return 2;
            }
            case READ_OK:
            {
                printf("Reading is successfull\n");
                break;
            }
        }

        struct image_t rotated;
           
        if(strcmp(argv[3], "left") == 0){
            rotated = rotate_left_90(*in_image);
            printf("Left rotation\n");
        } 

        else if(strcmp(argv[3], "right") == 0){
            printf("Right rotation\n");
            rotated = rotate_right_90(*in_image);
        }
        else if(strcmp(argv[3], "custom") == 0){
            int dgr = atoi(argv[4]);
            if (dgr >= 0)
                printf("%s %d %s\n", "Custom rotation:", dgr, "degree anticlockwise.");
            if (dgr < 0)
                printf("%s %d %s\n", "Custom rotation:", -dgr, "degree clockwise.");

            rotated = rotate_any(*in_image, dgr);
        }
        else if(strcmp(argv[3], "no") == 0){
            printf("%s\n", "God bless you");
            rotated = *in_image;
        }

        else{
            printf("Error: choose way of rotation\n");
            return 2;
        }

    enum write_status result_write = to_bmp(f_out, &rotated);  

    if(result_write != WRITE_OK){

        printf("Error: error with write\n");
    } 
    else 
        printf("Write successfull\n");

    free(rotated.pixels_data);
    free(rotated.color_data);
    free(in_image->pixels_data);
    free(in_image);
}