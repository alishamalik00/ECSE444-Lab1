.syntax unified
.cpu cortex-m4
.fpu fpv4-sp-d16
.thumb

.section .text
.align 2

.global kalman
.type kalman, %function
.thumb_func

kalman:
    /* R0 = address of kalman_state
       S0 = current measurement */

    vldr s1, [r0, #0]      /* S1 = q */
    vldr s4, [r0, #12]     /* S4 = p */
    vadd.f32 s4, s4, s1    /* p = p + q */

    vldr s2, [r0, #4]      /* S2 = r */
    vadd.f32 s5, s4, s2    /* S5 = p + r */
    vdiv.f32 s5, s4, s5    /* k = p / (p + r) */

    vldr s3, [r0, #8]      /* S3 = x */
    vsub.f32 s6, s0, s3    /* measurement - x */
    vmla.f32 s3, s5, s6    /* x = x + k * difference */

    vmov.f32 s6, #1.0      /* S6 = 1.0 */
    vsub.f32 s6, s6, s5    /* 1.0 - k */
    vmul.f32 s4, s6, s4    /* p = (1.0 - k) * p */

    vstr s3, [r0, #8]      /* Save x */
    vstr s4, [r0, #12]     /* Save p */
    vstr s5, [r0, #16]     /* Save k */

    bx lr

.size kalman, .-kalman
