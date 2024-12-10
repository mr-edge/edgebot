#ifndef ANIMATIONDEFINTIONS_H
#define ANIMATIONDEFINTIONS_H
#include  "../utility/animations.h"

anim_def_t NoAnimation = {
    100,
    5,
    &noop
};

anim_def_t WrapScroll = {
    100,
    5,
    &wrap_scroll_animation
};

anim_def_t FlipRows = {
    500,
    5,
    &flip_row_animation
};

anim_def_t ScrollRowsIn = {
    100,
    0,
    &scroll_rows_in_animation
};

anim_def_t CenterBlink = {
    1000,
    2,
    &center_blink_animation
};

#endif
