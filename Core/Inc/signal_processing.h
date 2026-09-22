#ifndef SIGNAL_PROCESSING_H_
#define SIGNAL_PROCESSING_H_

void vector_difference(const float *input, const float *filtered, float *difference, int length);

float vector_mean(const float *data, int length);

float vector_standard_deviation(const float *data, int length, float mean);

void vector_correlation(const float *input, const float *filtered, float *output, int length);

void vector_convolution(const float *input, const float *filtered, float *output, int length);

#endif
