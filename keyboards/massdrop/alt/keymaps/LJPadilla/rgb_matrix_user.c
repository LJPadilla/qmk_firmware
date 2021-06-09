//This is where my custom effects will be declared

RGB_MATRIX_EFFECT(sunset)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool sunset(effect_params_t* params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for(uint8_t i = led_min; i<led_max; i++){
        RGB_MATRIX_TEST_LED_FLAGS(); //Not entirely sure what this is for
        rgb_matrix_set_color(i,0,0,255);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif //RGB_MATRIX_CUSTOM_EFFECT_IMPLS
