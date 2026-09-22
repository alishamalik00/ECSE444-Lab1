#include "signal_processing.h"
#include <math.h>

void vector_difference(const float *input, const float *filtered, float *difference, int length) {
    for (int i = 0; i < length; i++)
    {
        difference[i] = input[i] - filtered[i];
    }
}

float vector_mean(const float *data, int length)
{
    if (length <= 0) {
        return 0.0f;
    }

    float sum = 0.0f;

    for (int i = 0; i < length; i++) {
        sum += data[i];
    }

    return sum / (float)length;
}

float vector_standard_deviation(const float *data, int length, float mean)
{
    if (length <= 1)
    {
        return 0.0f;
    }

    float squared_sum = 0.0f;

    for (int i = 0; i < length; i++)
    {
        float deviation = data[i] - mean;
        squared_sum += deviation * deviation;
    }

    return sqrtf(squared_sum / (float)(length - 1));
}

void vector_correlation(const float *input, const float *filtered, float *output, int length) {
    for (int lag = -(length - 1); lag <= length - 1; lag++) {
        float sum = 0.0f;

        for (int i = 0; i < length; i++) {
            int j = i - lag;

            if ((j >= 0) && (j < length))
            {
                sum += input[i] * filtered[j];
            }
        }

        output[lag + length - 1] = sum;
    }
}

void vector_convolution(const float *input, const float *filtered, float *output, int length) {
    int output_length = (2 * length) - 1;

    for (int n = 0; n < output_length; n++)
    {
        float sum = 0.0f;

        for (int i = 0; i < length; i++)
        {
            int j = n - i;

            if ((j >= 0) && (j < length))
            {
                sum += input[i] * filtered[j];
            }
        }

        output[n] = sum;
    }
}
