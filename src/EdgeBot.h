

#ifndef EdgeBot_H
#define EdgeBot_H

#include "utility/animations.h"

#include "modules/animation_module.h"

#include "data/en.h"
#include "data/anim_defs.h"

AnimationContext WelcomeCtx = {
    Welcome,
    2, 
    11,
    0,
};

AnimationContext WelcomeCtx2 = {
    Welcome,
    2, 
    11,
    0,
};

AnimationContext WelcomeCtx3 = {
    Welcome,
    2, 
    11,
    0,
};

void edgebot_setup() {
    setup_animations();

    Animation welcome = { &ScrollRowsIn, &WelcomeCtx };
    Animation welcome2 = { &CenterBlink, &WelcomeCtx2 };
    Animation welcome3 = { &FlipRows, &WelcomeCtx3 };
    queue_animation(&welcome);
    queue_animation(&welcome2);
    // }
}

void edgebot_loop() {
    update_animations();
}
#endif