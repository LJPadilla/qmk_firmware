RGB_MATRIX_EFFECT(sunset_function)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

    bool sunset_function(effect_params_t* params) {
        RGB_MATRIX_USE_LIMITS(led_min, led_max);


        for (uint8_t i = led_min; i < led_max; i++) {
            RGB_MATRIX_TEST_LED_FLAGS();
            if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
                if((i<=12 && i>=1)||i==55){
                    rgb_matrix_set_color(i, 255, 0, 0);
                }
                else if(i==13){
                    rgb_matrix_set_color(i, 255,255,255);
                }
                else{
                    rgb_matrix_set_color(i,255,70,0);
                }
            } else {
                if(i==0||i==14||i==29||i==43||i==56||i==57||i==61||i==64||i==65||i==66){
                    rgb_matrix_set_color(i,255,0,0);
                }
                else{
                    rgb_matrix_set_color(i, 0, 0, 255);
                }
            }
        }
        return led_max < DRIVER_LED_TOTAL;
    }

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
