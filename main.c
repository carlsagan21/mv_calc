#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>


#define SIZE 64
#define TOTAL_SIZE (SIZE+1) * SIZE

typedef union {
    float f;
    unsigned int i;
} foo;

int main(int argc, char **argv) {
    int i, j, k;
    foo container;

    float flat[TOTAL_SIZE];
    float global_mem[SIZE];
    float local_mem[SIZE][SIZE];
    float output_cpu[SIZE];
    float *output_fpga;

    // initialization
    FILE *fd;
    fd = fopen("./input.txt", "r");

    unsigned int a;
    i = 0;
    j = 0;
    k = -1;
    while (!feof(fd)) {
        if (fscanf(fd, "%X", &a) != EOF) {
            container.i = a;

            if (i < SIZE)
                global_mem[i] = container.f;
            else {
                if (j == SIZE) {
                    j = 0;
                    k++;
                }
                local_mem[k][j] = container.f;
            }

            flat[i] = container.f;

            i++;
            j++;
        }
    }
    fclose(fd);

//    output_cpu = 0.0f;

    // computation
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            output_cpu[i] += global_mem[j] * local_mem[i][j];
        }
    }

    // FPGA offloading
    // memory load
    int foo;
    foo = open("/dev/mem", O_RDWR | O_NONBLOCK);
    float *fpga_bram = mmap(NULL, TOTAL_SIZE * sizeof(float), PROT_WRITE, MAP_SHARED, foo, 0x40000000);
    for (i = 0; i < TOTAL_SIZE; i++) {
        *(fpga_bram + i) = flat[i];
    }

    // run
    unsigned int *fpga_ip = mmap(NULL, sizeof(float), PROT_WRITE, MAP_SHARED, foo, 0x43c00000);
    *fpga_ip = 0x5555;

    // wait
    while (*fpga_ip == 0x5555);

    // result
//    output_fpga
//    output_fpga = fpga_bram;//*fpga_bram?


    // display
    printf("%-10s%-10s%-10s%-10s\n", "index", "CPU", "FPGA", "FPGA(hex)");
//    container.f = output_fpga;
    for (i = 0; i < SIZE; i++)
        printf("%-10d%-10f%-10f\n", 0, output_cpu[i], fpga_bram[i]);

    close(foo);

    return 0;
}
