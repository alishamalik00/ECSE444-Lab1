#include "kalman.h"
#include <math.h>
#include <stddef.h>

int Kalmanfilter(float *InputArray, float *OutputArray, kalman_state *kstate, int Length) {
    if ((InputArray == NULL) || (OutputArray == NULL) || (kstate == NULL) || (Length < 0)) {
        return 1;
    }

    for (int i = 0; i < Length; i++)
    {
        /* Reject invalid inputs or an invalid incoming state. */
        if (!isfinite(InputArray[i]) || !isfinite(kstate->q) || !isfinite(kstate->r) || !isfinite(kstate->x) || !isfinite(kstate->p)) {
            return 1;
        }

        /* Call the ARM assembly subroutine. */
        kalman(kstate, InputArray[i]);

        /* Detect overflow, infinity, or NaN produced by the calculation. */
        if (!isfinite(kstate->x) || !isfinite(kstate->p) || !isfinite(kstate->k)){
            return 1;
        }

        OutputArray[i] = kstate->x;
    }

    return 0;
}
