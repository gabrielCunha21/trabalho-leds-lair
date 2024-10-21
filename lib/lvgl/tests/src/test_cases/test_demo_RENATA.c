#if LV_BUILD_TEST
#include "../lvgl.h"
#include "../demos/lv_demos.h"

#include "unity/unity.h"

#include "lv_test_helpers.h"
#include "lv_test_indev.h"

void test_demo_RENATA(void)
{
#if LV_USE_DEMO_RENATA
    lv_demo_RENATA();
#endif
}

#endif
