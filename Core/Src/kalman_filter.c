#include "kalman.h"
#include <math.h>
#include <stddef.h>

/* A function that updates one state using one measurement. */
typedef void (*kalman_method)(kalman_state *state, float measurement);

/* Shared validation, iteration, and output storage. */
static int Kalmanfilter_run(float *input, float *output, kalman_state *state, int length, kalman_method method)
{
    if ((input == NULL) || (output == NULL) || (state == NULL) || (method == NULL) || (length < 0))
    {
        return 1;
    }

    for (int i = 0; i < length; i++)
    {
        if (!isfinite(input[i]) || !isfinite(state->q) || !isfinite(state->r) || !isfinite(state->x) || !isfinite(state->p))
        {
            return 1;
        }

        //calls the assembly, C, or CMSIS routine
        method(state, input[i]);

        if (!isfinite(state->x) || !isfinite(state->p) || !isfinite(state->k))
        {
            return 1;
        }

        output[i] = state->x;
    }

    return 0;
}

int Kalmanfilter(float *InputArray, float *OutputArray, kalman_state *kstate, int Length)
{
    return Kalmanfilter_run(InputArray, OutputArray, kstate, Length, kalman);
}

int Kalmanfilter_c(float *InputArray, float *OutputArray, kalman_state *kstate, int Length)
{
    return Kalmanfilter_run(InputArray, OutputArray, kstate, Length, kalman_c);
}

int Kalmanfilter_cmsis(float *InputArray, float *OutputArray, kalman_state *kstate, int Length)
{
    return Kalmanfilter_run(InputArray, OutputArray, kstate, Length, kalman_cmsis);
}
