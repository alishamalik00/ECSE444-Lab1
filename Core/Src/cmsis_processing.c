#include "cmsis_processing.h"
#include "arm_math.h"

void cmsis_vector_difference(const float *input, const float *filtered, float *difference, int length) {
    if (length <= 0) {
        return;
    }

    arm_sub_f32(input, filtered, difference, (uint32_t)length);
}

void cmsis_mean_and_standard_deviation(const float *data, int length, float *mean, float *standard_deviation){
    if (length <= 0) {
        *mean = 0.0f;
        *standard_deviation = 0.0f;
        return;
    }

    arm_mean_f32(data, (uint32_t)length, mean);

    if (length == 1){
        *standard_deviation = 0.0f;
    } else {
        arm_std_f32(data, (uint32_t)length, standard_deviation);
    }
}

void cmsis_vector_correlation(const float *input, const float *filtered, float *output, int length) {
    if (length <= 0){
        return;
    }

    int output_length = (2 * length) - 1;

    for (int i = 0; i < output_length; i++) {
        output[i] = 0.0f;
    }

    arm_correlate_f32(input, (uint32_t)length, filtered, (uint32_t)length, output);
}

void cmsis_vector_convolution(const float *input, const float *filtered, float *output, int length) {
    if (length <= 0) {
        return;
    }

    arm_conv_f32(input, (uint32_t)length, filtered, (uint32_t)length, output);
}
