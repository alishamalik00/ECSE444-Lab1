#include "kalman.h"
#include "arm_math.h"

/* Plain-C update for one measurement. */
void kalman_c(kalman_state *state, float measurement)
{
    state->p = state->p + state->q;
    state->k = state->p / (state->p + state->r);
    state->x = state->x + state->k * (measurement - state->x);
    state->p = (1.0f - state->k) * state->p;
}

/* CMSIS-DSP update for one measurement. */
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
