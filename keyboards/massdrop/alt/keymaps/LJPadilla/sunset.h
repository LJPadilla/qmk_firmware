RGB_MATRIX_EFFECT(sunset)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool sunset(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);


    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
            rgb_matrix_set_color(i, 255, 70, 0);
        } else {
            rgb_matrix_set_color(i, 0, 0, 255);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
