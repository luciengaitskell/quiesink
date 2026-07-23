#include <Arduino.h>
#include <TFT_eSPI.h>

#ifdef EPAPER_ENABLE
EPaper epaper;
#endif

static constexpr uint32_t kHoldMs = 10000;

#ifdef EPAPER_ENABLE
static void draw_color_test()
{
    const int16_t w = epaper.width();
    const int16_t h = epaper.height();

    epaper.fillScreen(TFT_WHITE);

    // Six Spectra 6 swatches across the upper third of the panel.
    static const uint16_t colors[] = {
        TFT_WHITE, TFT_BLACK, TFT_YELLOW, TFT_GREEN, TFT_BLUE, TFT_RED,
    };
    static const char *labels[] = {
        "WHITE", "BLACK", "YELLOW", "GREEN", "BLUE", "RED",
    };
    const int n = 6;
    const int margin = 40;
    const int gap = 20;
    const int sw_w = (w - 2 * margin - (n - 1) * gap) / n;
    const int sw_h = h / 5;
    const int sw_y = h / 6;

    for (int i = 0; i < n; i++) {
        const int x = margin + i * (sw_w + gap);
        epaper.fillRect(x, sw_y, sw_w, sw_h, colors[i]);
        // Outline so the white swatch is visible on a white background.
        epaper.drawRect(x, sw_y, sw_w, sw_h, TFT_BLACK);

        epaper.setTextColor(TFT_BLACK, TFT_WHITE);
        epaper.setTextSize(2);
        epaper.drawCentreString(labels[i], x + sw_w / 2, sw_y + sw_h + 16, 2);
    }

    epaper.setTextColor(TFT_BLACK, TFT_WHITE);
    epaper.setTextSize(5);
    epaper.drawCentreString("quiesink", w / 2, h * 2 / 3, 4);

    epaper.setTextSize(3);
    epaper.drawCentreString("Spectra 6 bring-up", w / 2, h * 2 / 3 + 80, 2);
}
#endif

extern "C" void app_main(void)
{
    initArduino();

    Serial.begin(115200);
    delay(200);

#ifdef EPAPER_ENABLE
    Serial.println("quiesink: Spectra 6 bring-up demo");

    Serial.println("quiesink: begin (power / init)");
    epaper.begin();

    Serial.println("quiesink: draw color test");
    draw_color_test();

    Serial.println("quiesink: refresh (this can take tens of seconds)");
    epaper.update();

    Serial.printf("quiesink: holding for %lu ms\n", (unsigned long)kHoldMs);
    delay(kHoldMs);

    Serial.println("quiesink: white-out for storage");
    epaper.fillScreen(TFT_WHITE);
    epaper.update();

    Serial.println("quiesink: done (panel white and asleep)");
#else
    Serial.println("quiesink: EPAPER_ENABLE not defined — check BOARD_SCREEN_COMBO / EE02 setup");
#endif
}
