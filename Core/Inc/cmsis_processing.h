#ifndef CMSIS_PROCESSING_H_
#define CMSIS_PROCESSING_H_

void cmsis_vector_difference(const float *input,const float *filtered, float *difference, int length);

void cmsis_mean_and_standard_deviation(const float *data, int length, float *mean, float *standard_deviation);

void cmsis_vector_correlation(const float *input, const float *filtered, float *output, int length);

void cmsis_vector_convolution(const float *input, const float *filtered, float *output, int length);

#endif
