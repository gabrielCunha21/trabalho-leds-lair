// #include <lvgl.h>                // Inclui a biblioteca LVGL
// #include <Wire.h>
// #include "SensorPCF85063.hpp"    // Inclui a biblioteca do sensor PCF85063
// #include "TFT_eSPI.h"            // Inclui a biblioteca TFT_eSPI para interface com o display

// TFT_eSPI tft = TFT_eSPI();       // Inicializa o display TFT_eSPI
// SensorPCF85063 rtc;              // Instancia o RTC

// lv_obj_t *label;                 // Cria um objeto label global para exibir a hora

// void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
// void updateTime();

// void setup() {
//   Serial.begin(115200);

//   // Inicializa o display e LVGL
//   tft.begin();
//   tft.setRotation(1);            // Define a rotação do display, se necessário
//   lv_init();

//   // Inicializa o buffer de exibição LVGL
//   static lv_color_t buf[240 * 10];
//   static lv_disp_draw_buf_t draw_buf;
//   lv_disp_draw_buf_init(&draw_buf, buf, NULL, 280 * 10);

//   // Configuração do driver de exibição LVGL
//   static lv_disp_drv_t disp_drv;
//   lv_disp_drv_init(&disp_drv);
//   disp_drv.flush_cb = my_disp_flush;
//   disp_drv.draw_buf = &draw_buf;
//   disp_drv.hor_res = 240;
//   disp_drv.ver_res = 320;
//   lv_disp_drv_register(&disp_drv);

//   // Inicializa o RTC
//   if (!rtc.begin(Wire, PCF85063_SLAVE_ADDRESS, 11, 10)) {
//     Serial.println("Erro ao encontrar o PCF85063. Verifique a conexão.");
//     while (1) {
//       delay(1000);
//     }
//   }

//   // Cria o label e o centraliza na tela
//   label = lv_label_create(lv_scr_act());
//   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
//   lv_label_set_text(label, "Inicializando...");

//   // Configura um timer para atualizar o relógio
//   const esp_timer_create_args_t lvgl_tick_timer_args = {
//     .callback = &updateTime,
//     .name = "update_time"
//   };
  
//   esp_timer_handle_t lvgl_tick_timer = NULL;
//   esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer);
//   esp_timer_start_periodic(lvgl_tick_timer, 1000 * 1000);  // Atualiza a cada segundo
// }

// void loop() {
//   lv_timer_handler();  // Mantém a interface gráfica funcionando
//   delay(5);
// }

// // Função de exibição para LVGL
// void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
//   tft.startWrite();
//   tft.setAddrWindow(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
//   tft.pushColors(&color_p->full, (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1), true);
//   tft.endWrite();
//   lv_disp_flush_ready(disp);
// }

// // Função para atualizar a hora no display
// void updateTime() {
//   RTC_DateTime datetime = rtc.getDateTime();

//   // Formata a hora como uma string
//   char buf[16];
//   snprintf(buf, sizeof(buf), "%02d:%02d:%02d", datetime.hour, datetime.minute, datetime.second);

//   // Atualiza o texto do label com a hora atual
//   lv_label_set_text(label, buf);
// }
