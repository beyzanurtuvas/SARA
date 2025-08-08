#include "ALACAKART.h"
#include <math.h>

ALACA_KART Veri_Kontrol;

// Sensör ve PID verileri
float Pitch_Aci, Yaw_Aci;
float Gyro_y, Gyro_z;

float Ref_Pitch = 0;
float Ref_Yaw   = 0;

float pid_hata_pitch = 0, pid_out_pitch = 0;
float pid_hata_yaw   = 0, pid_out_yaw   = 0;

float Kp_pitch = 0.25, Ki_pitch = 0.01, Kd_pitch = 0.01;
float Kp_yaw   = 0.25, Ki_yaw   = 0.01, Kd_yaw   = 0.01;
float imax = 10;

// Mesafe hesaplama
float x = 0, vx = 0, ax;
float onceki_x = 0;
unsigned long onceki_zaman;

// Servo çıkış kayıtları (gereksiz hareketi engellemek için)
int last_pitch_out = 90;
int last_yaw_out   = 90;

void setup() {
  Serial.begin(57600);
  Veri_Kontrol.Sensor_begin();

  // Servolar
  Veri_Kontrol.Servo_1_begin();
  Veri_Kontrol.Servo_2_begin();
  Veri_Kontrol.Servo_3_begin();
  Veri_Kontrol.Servo_4_begin();
  Veri_Kontrol.Servo_5_begin();

  // PID sistemleri
  Veri_Kontrol.setup_PID_1(); // Yaw
  Veri_Kontrol.setup_PID_2(); // Pitch

  // İlk konum referans alınır
  Ref_Pitch = Veri_Kontrol.Euler_Y();
  Ref_Yaw   = Veri_Kontrol.Euler_Z();

  motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM);
  onceki_zaman = millis();
}

void loop() {
  unsigned long simdi = millis();
  float dt = (simdi - onceki_zaman) / 1000.0;
  onceki_zaman = simdi;

  // Sensör verilerini oku
  Pitch_Aci = Veri_Kontrol.Euler_Y();
  Yaw_Aci   = Veri_Kontrol.Euler_Z();
  Gyro_y = Veri_Kontrol.GYRO_Y();
  Gyro_z = Veri_Kontrol.GYRO_Z();

  // --- PITCH kontrolü (±5° tolerans)
  float pitch_diff = Pitch_Aci - Ref_Pitch;
  if (abs(pitch_diff) > 5) {
    pid_hata_pitch = (Ref_Pitch - Pitch_Aci) * 5 - Gyro_y;
    pid_out_pitch = Veri_Kontrol.PID_2(pid_hata_pitch, Kp_pitch, Ki_pitch, Kd_pitch, imax);

    int new_pitch_out = 90 + pid_out_pitch;
    if (abs(new_pitch_out - last_pitch_out) > 2) {
      Veri_Kontrol.Servo_2_Write(new_pitch_out);
      Veri_Kontrol.Servo_4_Write(180 - new_pitch_out);
      last_pitch_out = new_pitch_out;
    }
  }

  // --- YAW kontrolü (±5° tolerans)
  float yaw_diff_rad = (Yaw_Aci - Ref_Yaw) * DEG_TO_RAD;
  float yaw_diff = atan2(sin(yaw_diff_rad), cos(yaw_diff_rad)) * RAD_TO_DEG;

  if (abs(yaw_diff) > 5) {
    pid_hata_yaw = (0 - yaw_diff) * 5 - Gyro_z;
    pid_out_yaw = Veri_Kontrol.PID_1(pid_hata_yaw, Kp_yaw, Ki_yaw, Kd_yaw, imax);

    int new_yaw_out = 90 + pid_out_yaw;
    if (abs(new_yaw_out - last_yaw_out) > 2) {
      Veri_Kontrol.Servo_3_Write(new_yaw_out);
      Veri_Kontrol.Servo_5_Write(180 - new_yaw_out);
      last_yaw_out = new_yaw_out;
    }
  }

  // --- Mesafe hesaplama (LIN_ACC_X ile)
  ax = Veri_Kontrol.LIN_ACC_X();
  vx += ax * dt;
  x += vx * dt;

  // Geriye kayma varsa PWM artır
  if (x < onceki_x - 0.05) {
    Veri_Kontrol.Servo_1(1050);
  } else {
    Veri_Kontrol.Servo_1(MOTOR_MAX_PWM);
  }
  onceki_x = x;

  // DEBUG - test için açık bırak, yarışmada yorum satırına al
  Serial.print("Pitch: "); Serial.print(Pitch_Aci);
  Serial.print(" | Yaw: "); Serial.print(Yaw_Aci);
  Serial.print(" | x: "); Serial.println(x);

  // Görev tamamlandıysa sistemi durdur
  if (x >= 50.0) {
    motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM);
    tumServolariNotrle();
    while (1);
  }

  delay(10); // 100Hz loop
}

// PWM motor başlat/durdur
const int MOTOR_MAX_PWM = 1000;
const int MOTOR_STOP_PWM = 1490;

void motorYavasArtir(int baslangicPWM, int hedefPWM) {
  for (int pwm = baslangicPWM; pwm >= hedefPWM; pwm -= 2) {
    Veri_Kontrol.Servo_1(pwm);
    delay(10);
  }
}

void motorYavasAzalt(int baslangicPWM, int hedefPWM) {
  for (int pwm = baslangicPWM; pwm <= hedefPWM; pwm += 2) {
    Veri_Kontrol.Servo_1(pwm);
    delay(10);
  }
}

// Servoları nötrle
void tumServolariNotrle() {
  Veri_Kontrol.Servo_2_Write(90);
  Veri_Kontrol.Servo_3_Write(90);
  Veri_Kontrol.Servo_4_Write(90);
  Veri_Kontrol.Servo_5_Write(90);
}
