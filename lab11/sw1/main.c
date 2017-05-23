#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define BIT_LENGTH 6
#define WIDTH_SIZE (1 << BIT_LENGTH)

#define RAND_RANGE 16.0f

int main(int argc, char **argv) {
    float global_mem[WIDTH_SIZE], global_mem_rand[WIDTH_SIZE];
    float local_mem[WIDTH_SIZE][WIDTH_SIZE], local_mem_rand[WIDTH_SIZE][WIDTH_SIZE];
    float result[WIDTH_SIZE], result_rand[WIDTH_SIZE];
    int i, j;
    FILE *fp, *fp_readable, *fp_rand, *fp_rand_readable;

    fp = fopen("./input.txt", "w+");
    fp_readable = fopen("./input_readable.txt", "w+");
    fp_rand = fopen("./input_rand.txt", "w+");
    fp_rand_readable = fopen("./input_rand_readable.txt", "w+");

    for (i = 0; i < WIDTH_SIZE; i++) {
        global_mem[i] = 1.0f;
        global_mem_rand[i] = (float)rand()/(float)(RAND_MAX) * RAND_RANGE;
        fprintf(fp, "%08X\n", *( (int*) &global_mem[i] ));
        fprintf(fp_readable, "%08f\n", global_mem[i]);
        fprintf(fp_rand, "%08X\n", *( (int*) &global_mem_rand[i] ));
        fprintf(fp_rand_readable, "%08f\n", global_mem_rand[i]);
    }

    for (i = 0; i < WIDTH_SIZE; i++) {
        for (j = 0; j < WIDTH_SIZE; j++) {
            local_mem[i][j] = (float)(i + 2);
            local_mem_rand[i][j] = (float)rand()/(float)(RAND_MAX) * RAND_RANGE;
            fprintf(fp, "%08X\n", *( (int*) &local_mem[i][j] ));
            fprintf(fp_readable, "%08f\n", local_mem[i][j]);
            fprintf(fp_rand, "%08X\n", *( (int*) &local_mem_rand[i][j] ));
            fprintf(fp_rand_readable, "%08f\n", local_mem_rand[i][j]);
        }
    }

    fclose(fp);
    fclose(fp_readable);
    fclose(fp_rand);
    fclose(fp_rand_readable);

    fp = fopen("./output.txt", "w+");
    fp_readable = fopen("./output_readable.txt", "w+");
    fp_rand = fopen("./output_rand.txt", "w+");
    fp_rand_readable = fopen("./output_rand_readable.txt", "w+");

    for (i = 0; i < WIDTH_SIZE; i++) {
        result[i] = 0.0f;
        for (j = 0; j < WIDTH_SIZE; j++) {
            result[i] += global_mem[j] * local_mem[i][j];
            result_rand[i] += global_mem_rand[j] * local_mem_rand[i][j];
        }
        fprintf(fp, "%08X\n", *( (int*) &result[i] ));
        fprintf(fp_readable, "%08f\n", result[i]);
        fprintf(fp_rand, "%08X\n", *( (int*) &result_rand[i] ));
        fprintf(fp_rand_readable, "%08f\n", result_rand[i]);
    }

    fclose(fp);
    fclose(fp_readable);
    fclose(fp_rand);
    fclose(fp_rand_readable);

    return 0;
}