#include "../matrix/matrix-operations.h"

#include "neural-network.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAXCHAR 1000

NeuralNetwork *network_create(int input, int hidden, int output, double lr)
{
    NeuralNetwork *net = malloc(sizeof(NeuralNetwork));
    net->input = input;
    net->hidden = hidden;
    net->output = output;
    net->learning_rate = lr;

    Matrix *hidden_layer = matrix_create(hidden, input);
    Matrix *output_layer = matrix_create(output, hidden);

    matrix_randomize(hidden_layer, hidden);
    matrix_randomize(output_layer, output);

    net->hidden_weights = hidden_layer;
    net->output_weights = output_layer;
    return net;
}

Matrix *network_predict_img(NeuralNetwork *net, Img *img)
{
    Matrix *img_data = matrix_flatten(img->img_data, 0);
    Matrix *res = network_predict(net, img_data);
    matrix_free(img_data);
    return res;
}

double network_predict_imgs(NeuralNetwork *net, Img **imgs, int n)
{
    int n_correct = 0;
    for (int i = 0; i < n; i++)
    {
        Matrix *prediction = network_predict_img(net, imgs[i]);
        if (matrix_argmax(prediction) == imgs[i]->label)
        {
            n_correct++;
        }
        matrix_free(prediction);
    }
    return 1.0 * n_correct / n;
}

Matrix *network_predict(NeuralNetwork *net, Matrix *input_data)
{
    Matrix *hidden_inputs = dot(net->hidden_weights, input_data);
    Matrix *hidden_outputs = apply(sigmoid, hidden_inputs);
    Matrix *final_inputs = dot(net->hidden_weights, hidden_outputs);
    Matrix *final_outputs = apply(sigmoid, final_inputs);
    Matrix *result = softMax(final_outputs);
    return result;
}

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