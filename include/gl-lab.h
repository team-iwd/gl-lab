/* ========================================================================= */

#ifndef GL_LAB_H
#define GL_LAB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ================================================================ */

#include <limits.h>

/* Macros ================================================================== */

#define INVERSE_UCHAR_MAX  (1.0f / UCHAR_MAX)

#define TO_RGB01(r_, g_, b_, a_)        \
    (g1Color) {                         \
        .r = (r_) * INVERSE_UCHAR_MAX,  \
        .g = (g_) * INVERSE_UCHAR_MAX,  \
        .b = (b_) * INVERSE_UCHAR_MAX,  \
        .a = (a_) * INVERSE_UCHAR_MAX   \
    }

/* Typedefs ================================================================ */

/* 색상을 나타내는 구조체. */
typedef struct g1Color_ {
    // 빨간색 (red), 초록색 (green), 파란색 (blue)과 색상 투명도 (alpha)
    float r, g, b, a; 
} g1Color;

/* ========================================================================= */

#ifdef __cplusplus
}
#endif

#endif // `GL_LAB_H`