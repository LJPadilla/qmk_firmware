#ifndef DISABLE_RGB_MATRIX_ALPHAS_MODS
RGB_MATRIX_EFFECT(ALPHAS_MODS)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// alphas = color1, mods = color2
bool ALPHAS_MODS(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

//    HSV hsv  = rgb_matrix_config.hsv;
//    RGB rgb1 = rgb_matrix_hsv_to_rgb(hsv);
//    hsv.h += rgb_matrix_config.speed;
//    RGB rgb2 = rgb_matrix_hsv_to_rgb(hsv);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, 0, 0, 255);
        } else {
            rgb_matrix_set_color(i, 255, 40, 0);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // DISABLE_RGB_MATRIX_ALPHAS_MODS
