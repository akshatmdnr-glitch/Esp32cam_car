
#include <Arduino.h>
#include "esp_camera.h"

/* Edge Impulse library */
#include <your_model_inferencing.h>

#define LED_PIN 4

/* Camera Pins (AI Thinker ESP32-CAM) */
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

static bool debug_nn = false;

void setup_camera()
{
    camera_config_t config;

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;

    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;

    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;

    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;

    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_RGB565;

    config.frame_size = FRAMESIZE_QQVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    esp_camera_init(&config);
}

void setup()
{
    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);

    setup_camera();

    Serial.println("YOLO Interaction System Started");
}

void loop()
{
    camera_fb_t *fb = esp_camera_fb_get();

    if (!fb)
    {
        Serial.println("Camera capture failed");
        return;
    }

    signal_t signal;
    ei_impulse_result_t result = { 0 };

    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;

    signal.get_data = [](size_t offset, size_t length, float *out_ptr)
    {
        /* Edge Impulse image conversion */
        return numpy::int8_to_float(offset, length, out_ptr);
    };

    EI_IMPULSE_ERROR res = run_classifier(&signal, &result, debug_nn);

    if (res != EI_IMPULSE_OK)
    {
        Serial.println("Inference failed");
        esp_camera_fb_return(fb);
        return;
    }

    bool personDetected = false;

    for (size_t i = 0; i < result.bounding_boxes_count; i++)
    {
        ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];

        if (bb.value > 0)
        {
            Serial.print("Detected: ");
            Serial.println(bb.label);

            if (String(bb.label) == "person")
            {
                personDetected = true;
            }
        }
    }

    if (personDetected)
    {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Interaction: Person detected → LED ON");
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }

    esp_camera_fb_return(fb);

    delay(100);
}