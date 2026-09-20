#include "kalman.h"
#include "arm_math.h"
#include <math.h>
#include <stddef.h>

void kalman_c(kalman_state *state, float measurement)
{
    state->p = state->p + state->q;
    state->k = state->p / (state->p + state->r);
    state->x = state->x + state->k * (measurement - state->x);
    state->p = (1.0f - state->k) * state->p;
}

void kalman_cmsis(kalman_state *state, float measurement)
{
    float predicted_p;
    float denominator;
    float innovation;
    float correction;
    float new_x;
    float one = 1.0f;
    float one_minus_k;

    arm_add_f32(&state->p, &state->q, &predicted_p, 1U);
    arm_add_f32(&predicted_p, &state->r, &denominator, 1U);

    state->k = predicted_p / denominator;

    arm_sub_f32(&measurement, &state->x, &innovation, 1U);
    arm_mult_f32(&state->k, &innovation, &correction, 1U);
    arm_add_f32(&state->x, &correction, &new_x, 1U);
    arm_sub_f32(&one, &state->k, &one_minus_k, 1U);
    arm_mult_f32(&one_minus_k, &predicted_p, &state->p, 1U);

    state->x = new_x;
}

int Kalmanfilter_c(float *InputArray, float *OutputArray, kalman_state *kstate, int Length)
{
    if ((InputArray == NULL) || (OutputArray == NULL) || (kstate == NULL) || (Length < 0)) {
        return 1;
    }

    for (int i = 0; i < Length; i++) {
        if (!isfinite(InputArray[i]) || !isfinite(kstate->q) || !isfinite(kstate->r) || !isfinite(kstate->x) || !isfinite(kstate->p))
        {
            return 1;
        }

        kalman_c(kstate, InputArray[i]);

        if (!isfinite(kstate->x) || !isfinite(kstate->p) || !isfinite(kstate->k))
        {
            return 1;
        }

        OutputArray[i] = kstate->x;
    }

    return 0;
}

int Kalmanfilter_cmsis(float *InputArray, float *OutputArray, kalman_state *kstate, int Length)
{
    if ((InputArray == NULL) || (OutputArray == NULL) || (kstate == NULL) || (Length < 0))
    {
        return 1;
    }

    for (int i = 0; i < Length; i++)
    {
        if (!isfinite(InputArray[i]) || !isfinite(kstate->q) || !isfinite(kstate->r) || !isfinite(kstate->x) || !isfinite(kstate->p))
        {
            return 1;
        }

        kalman_cmsis(kstate, InputArray[i]);

        if (!isfinite(kstate->x) || !isfinite(kstate->p) || !isfinite(kstate->k))
        {
            return 1;
        }

        OutputArray[i] = kstate->x;
    }

    return 0;
}
