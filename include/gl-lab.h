/* ========================================================================= */

#ifndef GL_LAB_H
#define GL_LAB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ================================================================ */

#include <assert.h>
#include <limits.h>

/* Macros ================================================================== */

#define INVERSE_UCHAR_MAX  (1.0f / UCHAR_MAX)

#define GLAB_TO_RGB01(r, g, b, a)  \
    (r) * INVERSE_UCHAR_MAX,       \
    (g) * INVERSE_UCHAR_MAX,       \
    (b) * INVERSE_UCHAR_MAX,       \
    (a) * INVERSE_UCHAR_MAX        \

/* ========================================================================= */

#ifdef __cplusplus
}
#endif

#endif // `GL_LAB_H`