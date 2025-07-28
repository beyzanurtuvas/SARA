#include "ALACAKART.h"
ALACA_KART Veri_Kontrol;

// -------- PWM Sabitleri --------
const int MOTOR_MAX_PWM    = 1000;
const int MOTOR_STOP_PWM   = 1500;
const int MOTOR_DONUS_PWM  = 1200;

// -------- Zamanlar --------
const int DONUS_SURESI     = 1500;
const int LED_SERVO        = 6;


// --------- Manevra Fonksiyonları ---------

void ileriGit(int sure) {
  tumServolariNotrle();
  delay(sure);
}

void sagaDon(int sure) {
  Veri_Kontrol.Servo_3_Write(135); // Yaw sağ servo
  Veri_Kontrol.Servo_5_Write(45);  // Yaw sol servo
  delay(sure);
  tumServolariNotrle();
}

void yukariCik(int sure) {
  Veri_Kontrol.Servo_2_Write(45);  // Pitch yukarı
  Veri_Kontrol.Servo_4_Write(135); // Pitch aşağı
  delay(sure);
  tumServolariNotrle();
}

void asagiIn(int sure) {
  Veri_Kontrol.Servo_2_Write(135); // Pitch yukarı
  Veri_Kontrol.Servo_4_Write(45);  // Pitch aşağı
  delay(sure);
  tumServolariNotrle();
}

// --------- Motor PWM Fonksiyonları ---------

void motorBasla(int pwm) {
  Veri_Kontrol.Servo_1(pwm);
}

void motorDur() {
  Veri_Kontrol.Servo_1(MOTOR_STOP_PWM);
}

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

// --------- Servo ve LED ---------

void tumServolariNotrle() {
  Veri_Kontrol.Servo_2_Write(90);
  Veri_Kontrol.Servo_3_Write(90);
  Veri_Kontrol.Servo_4_Write(90);
  Veri_Kontrol.Servo_5_Write(90);
}

void ledAc() {
  Veri_Kontrol.Servo_6(1900);
}

void ledKapali() {
  Veri_Kontrol.Servo_6(1100);
}

void setup() {

  Veri_Kontrol.Sensor_begin();
  Veri_Kontrol.Servo_1_begin();
  Veri_Kontrol.Servo_2_begin();
  Veri_Kontrol.Servo_3_begin();
  Veri_Kontrol.Servo_4_begin();
  Veri_Kontrol.Servo_5_begin();
  Veri_Kontrol.Servo_6_begin();

  tumServolariNotrle();
  motorDur();
  ledKapali();
  
  
  delay(7000); // Sistem başlama gecikmesi (7 saniye)

  // Görev Başlıyor
  motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM); // Motoru yumuşak başlat

  yukariCik(4000); //0-8 saniye yukarı
  ileriGit(7000); // 8-15 sn düz git

  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  sagaDon(DONUS_SURESI);          // Sağa dön (1.5 sn)
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  ileriGit(5000);                 // 16.5–21.5 sn düz git

  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  sagaDon(DONUS_SURESI);          // Sağa dön (1.5 sn)
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  ileriGit(5000);                 // 23-28 sn düz git

  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  sagaDon(DONUS_SURESI);          // Sağa dön (1.5 sn)
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  ileriGit(5000);                 // 29.5–34.5 sn düz git

  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  sagaDon(DONUS_SURESI);          // Sağa dön (1.5sn)
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);

  yukariCik(8000);                // 36–44 sn yukarı çıkış

  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM); // Motoru yavaş durdur
  tumServolariNotrle();

  delay(60000); // 1 dakika bekleme (görev arası)

  // ----------- Yunuslama Hareketi -----------
  motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM); // Motoru yumuşak başlat

  yukariCik(3000);   // 3 sn yukarı çık
  ileriGit(5000);    // 5 sn düz git
  asagiIn(7000);     // 7 sn aşağı in
  yukariCik(5000);   // 5 sn yukarı çık

  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM); // Motoru yavaşlat
  tumServolariNotrle();
  motorYavasAzalt(MOTOR_DONUS_PWM, MOTOR_STOP_PWM);

  // LED sadece bu noktada yanar
  ledAc();       // LED’i aç
  delay(5000);   // 5 saniye açık kalsın
  ledKapali();   // Kapat
}

void loop() {
  // loop boş çünkü her şey setup içinde bir kez çalışır
}
