#ifndef KALMAN_H_
#define KALMAN_H_

typedef struct
{
    float q;  // Process-noise covariance
    float r;  // Measurement-noise covariance
    float x;  // Estimated value
    float p;  // Estimation-error covariance
    float k;  // Kalman gain
} kalman_state;


void kalman(kalman_state *state, float measurement);

int Kalmanfilter(float *InputArray, float *OutputArray, kalman_state *kstate, int Length);

void kalman_c(kalman_state *state, float measurement);
void kalman_cmsis(kalman_state *state, float measurement);

int Kalmanfilter_c(float *InputArray, float *OutputArray, kalman_state *kstate, int Length);
int Kalmanfilter_cmsis(float *InputArray, float *OutputArray, kalman_state *kstate, int Length);

#endif /* KALMAN_H_ */
