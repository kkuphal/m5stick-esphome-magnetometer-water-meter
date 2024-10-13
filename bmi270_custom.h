/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/**
 * @file getSensorData.ino
 * @brief M5Unit IMU Pro Mini Get Sensor Data Demo.
 * @version 0.2
 * @date 2024-07-02
 *
 * @Hardwares:M5Unit IMU Pro Mini
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 * M5_IMU_PRO: https://github.com/m5stack/M5Unit-IMU-Pro-Mini
 * Adafruit BMP280 Library: https://github.com/adafruit/Adafruit_BMP280_Library
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5GFX: https://github.com/m5stack/M5GFX
 *
 */

#include "esphome.h"
#include "M5_IMU_PRO.h"

#define BIM270_SENSOR_ADDR 0x68
#define BMP280_SENSOR_ADDR 0x76

class CustomBMI270 : public PollingComponent {
 public:
  // constructor
  CustomBMI270() : PollingComponent(1000) {}

  BMI270::BMI270 bmi270;
  Sensor *magnetic_x = new Sensor();
  Sensor *magnetic_y = new Sensor();
  Sensor *magnetic_z = new Sensor();
  // Adafruit_BMP280 bmp;

  void setup() override {
    // M5.begin();
    // M5.Ex_I2C.begin();

    //unsigned status = bmp.begin(BMP280_SENSOR_ADDR);
    //if (!status) {
	//ESP_LOGE("BMI270","Could not find a valid BMP280 sensor, check wiring or try a different address!");
	//ESP_LOGI("BMI270","SensorID was 0x%d",bmp.sensorID());
        //while (1) delay(10);
    //}

    bmi270.init(I2C_NUM_1, BIM270_SENSOR_ADDR);
  }

  void update() override{
    float x, y, z;

    if (bmi270.accelerationAvailable()) {
        bmi270.readAcceleration(x, y, z);
    }

    if (bmi270.gyroscopeAvailable()) {
        bmi270.readGyroscope(x, y, z);
    }

    if (bmi270.magneticFieldAvailable()) {
        int16_t mx, my, mz = 0;
        bmi270.readMagneticField(mx, my, mz);
	magnetic_x->publish_state(mx);
	magnetic_y->publish_state(my);
	magnetic_z->publish_state(mz);
    }
  }

  void loop(void) override{
  }

};

