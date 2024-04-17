#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "layerparser.h"
#include "serial.h"
#include "hasher.h"
#include "headergen.h"

#define WORDSIZE 4
#define IS_ALIGNED(x) (!(x % WORDSIZE))
#define ALIGN(x) ((x + (WORDSIZE -1)) & -WORDSIZE)


void calculate_offsets(struct layer **layers, size_t n){
    for(size_t i = 0; i < n; ++i){
        layers[i]->offsets = malloc(sizeof (struct layer_offset));

        if(i == 0){
            /* always start the first layer at 0x0 */
            layers[i]->offsets->kernel = 0x0;
            layers[i]->offsets->bias = layers[i]->weights->klen * sizeof(_Float16);
            layers[i]->offsets->kernel = ALIGN(layers[i]->offsets->kernel);
            layers[i]->offsets->bias = ALIGN(layers[i]->offsets->bias);
            continue;
        }

        /* This looks quite ugly but all it's doing is checking where the previous layers weights end
         * and then setting the weights to start at that 
         * Note: this does always assume that the bias weights are written after the kernel weights */
        layers[i]->offsets->kernel = layers[i - 1]->offsets->bias + (layers[i - 1]->weights->blen * sizeof(_Float16));
        layers[i]->offsets->bias = layers[i]->offsets->kernel + (layers[i]->weights->klen * sizeof(_Float16));

        /* and round up to next aligned address if required */
        layers[i]->offsets->kernel = ALIGN(layers[i]->offsets->kernel);
        layers[i]->offsets->bias = ALIGN(layers[i]->offsets->bias);
    }

}

void print_offsets(struct layer *l){
    printf("Layer %s\n", l->name);
    printf("\tKernel offset: %#x\n", l->offsets->kernel);
    printf("\tKernel len: %#x\n", (l->weights->klen) * sizeof(_Float16));
    printf("\tBias offset: %#x\n", l->offsets->bias);
    printf("\tBias len: %#x\n", (l->weights->blen) * sizeof(_Float16));
    putchar('\n');
}

int main(int argc, char *argv[]){
    /* usage: ./main filename [offsets|header|write|all][headername]  */

    if(argc < 3){
        printf("Usage: %s filename offsets | header | write [headername | port]\n", argv[0]);
        return 0;
    }

    struct layer **layers = NULL;
    size_t n_layers = get_layers(argv[1], &layers);

    if(layers == NULL){
        return 0;
    }

    for(size_t i = 0; i < n_layers; ++i){
        get_weights(layers[i]);
    }

    calculate_offsets(layers, n_layers);


    if(strcmp(argv[2], "header") == 0){
        if(argc > 3){
            write_header(argv[3], layers, n_layers);
        }else{
            puts("Provide a filename");
        }
    }

    if(strcmp(argv[2], "offsets") == 0){
        for(size_t i = 0; i < n_layers; ++i){
            print_offsets(layers[i]);
        }
    }

    if(strcmp(argv[2], "write") == 0){

        if(argc >3){
            int fd = open_port(argv[3]);

            if(fd >= 0){
                for(size_t i = 0; i < n_layers; ++i){
                    write_weights(fd, layers[i]);
                }
                close_port(fd);
            }
        }else{
            puts("Provide a port");
        }


    }

    free_layers(layers, n_layers);
    free(layers);


}
