#include "../matrix/matrix-operations.h"

#include "neural-network.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXCHAR 1000

void network_save(NeuralNetwork *net, char *file_string)
{
    mkdir(file_string);
    // write the descriptor file
    chdir(file_string);

    FILE *descriptor = fopen("descriptor", "w");

    fprintf(descriptor, "%d\n", net->input);
    fprintf(descriptor, "%d\n", net->hidden);
    fprintf(descriptor, "%d\n", net->output);
    fclose(descriptor);

    matrix_save(net->hidden_weights, "hidden");
    matrix_save(net->output_weights, "output");
    printf("Successfully written network to '%s'\n", file_string);
    chdir("-"); // go back to project dir
}

NeuralNetwork *network_load(char *file_string)
{
    NeuralNetwork *net = malloc(sizeof(NeuralNetwork));
    char entry[MAXCHAR];

    chdir(file_string);

    FILE *descriptor = fopen("descriptor", "r");

    fgets(entry, MAXCHAR, descriptor);
    net->input = atoi(entry);
    fgets(entry, MAXCHAR, descriptor);
    net->hidden = atoi(entry);
    fgets(entry, MAXCHAR, descriptor);
    net->output = atoi(entry);

    fclose(descriptor);

    net->hidden_weights = matrix_load("hidden");
    net->output_weights = matrix_load("output");

    printf("Successfully loaded network from '%s'\n", file_string);

    chdir("-"); // go back to project dir
    return net;
}

void network_print(NeuralNetwork *net)
{
    printf("# of Inputs: %d\n", net->input);
    printf("# of Hidden: %d\n", net->hidden);
    printf("# of Outputs: %d\n", net->output);
    printf("Hidden Weights:\n");
    matrix_print(net->hidden_weights);
    printf("Output Weights:\n");
    matrix_print(net->output_weights);
}

void network_free(NeuralNetwork *net)
{
    matrix_free(net->hidden_weights);
    matrix_free(net->output_weights);
    free(net);
    net = NULL;
}