#include "ALACAKART.h"

// ----------- PWM SABITLERI -----------
const int MOTOR_STOP_PWM   = 1500;
const int MOTOR_MAX_PWM    = 1000;
const int MOTOR_DONUS_PWM  = 1300;
const int LED_PWM_ACIK     = 1900;
const int LED_PWM_KAPALI   = 1100;

// ----------- ZAMANLAR ---------------
const int SISTEM_GECIKME         = 10000;
const int GOREV_ARASI_BEKLEME    = 60000;
const int YUZEYDE_BEKLEME        = 4000;

ALACA_KART Veri_Kontrol;

uint32_t currentTime = millis();
uint32_t previousTime = millis();

bool ilkDonus = 1;
bool ikinciDonus = 1;
bool yukariKontrolFlag = 1;

void setup() {
  Serial.begin(9600);
  if (!Veri_Kontrol.Sensor_begin()) {
    Serial.println("BNO sensörü başlatılamadı!");
  }

  Veri_Kontrol.Servo_1_begin(); // Motor
  Veri_Kontrol.Servo_2_begin(); // Pitch yukarı
  Veri_Kontrol.Servo_3_begin(); // Yaw sağ
  Veri_Kontrol.Servo_4_begin(); // Pitch aşağı
  Veri_Kontrol.Servo_5_begin(); // Yaw sol
  Veri_Kontrol.Servo_6_begin(); // LED (PWM)

  Veri_Kontrol.Servo_1_Write(MOTOR_STOP_PWM);
  tumServolariNotrle();
  ledPWMSon();
  delay(SISTEM_GECIKME);

  currentTime = millis();
  previousTime = millis();
  gorev1();
  delay(GOREV_ARASI_BEKLEME);
  gorev2();
}

void loop() {}

void ledPWMYak() {
  Veri_Kontrol.Servo_6_Write(LED_PWM_ACIK);
}

void ledPWMSon() {
  Veri_Kontrol.Servo_6_Write(LED_PWM_KAPALI);
}

void tumServolariNotrle() {
  Veri_Kontrol.Servo_2_Write(90);
  Veri_Kontrol.Servo_3_Write(90);
  Veri_Kontrol.Servo_4_Write(90);
  Veri_Kontrol.Servo_5_Write(90);
}

void motorYavasArtir(int baslangicPWM, int hedefPWM) {
  for (int pwm = baslangicPWM; pwm >= hedefPWM; pwm -= 2) {
    Veri_Kontrol.Servo_1_Write(pwm);
    delay(1);
  }
}

void motorYavasAzalt(int baslangicPWM, int hedefPWM) {
  for (int pwm = baslangicPWM; pwm <= hedefPWM; pwm += 2) {
    Veri_Kontrol.Servo_1_Write(pwm);
    delay(1);
  }
}

void sagaDondur()   { Veri_Kontrol.Servo_3_Write(135); Veri_Kontrol.Servo_5_Write(45); }
void solaDondur()   { Veri_Kontrol.Servo_3_Write(45);  Veri_Kontrol.Servo_5_Write(135); }
void yukariDondur() { Veri_Kontrol.Servo_2_Write(45);  Veri_Kontrol.Servo_4_Write(135); }
void asagiDondur()  { Veri_Kontrol.Servo_2_Write(135); Veri_Kontrol.Servo_4_Write(45); }

void gorev1() {
  previousTime = millis();
  Serial.println("Görev 1 başlıyor...");

  while (1) {
    currentTime = millis();

    if ((currentTime - previousTime) >= 63000) {
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM);
      Serial.println("Görev 1 tamamlandı, 60 sn geçti.");
      break;
    }

    if (ikinciDonus) {
      Serial.println("Görev 1 başladı.");
      ikinciDonus = 0;
    }

    if (currentTime - previousTime < 12000) {
      tumServolariNotrle();
      if (ilkDonus) {
        motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM);
        ilkDonus = 0;
      }
      if (Veri_Kontrol.getYaw() < 50 && Veri_Kontrol.getYaw() > 5) solaDondur();
      else if (Veri_Kontrol.getYaw() > 330 && Veri_Kontrol.getYaw() < 355) sagaDondur();
      delay(50);
    }

    if (currentTime - previousTime > 12000 && currentTime - previousTime < 13000)
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);

    if (currentTime - previousTime > 13000 && currentTime - previousTime < 18000) {
      tumServolariNotrle();
      if (Veri_Kontrol.getYaw() < 85) sagaDondur();
      else if (Veri_Kontrol.getYaw() > 95) solaDondur();
      else motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
      delay(50);
    }

    if (currentTime - previousTime > 18000 && currentTime - previousTime < 19000)
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);

    if (currentTime - previousTime > 19000 && currentTime - previousTime < 31000) {
      tumServolariNotrle();
      if (Veri_Kontrol.getYaw() < 175) sagaDondur();
      else if (Veri_Kontrol.getYaw() > 185) solaDondur();
      else motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
      delay(50);
    }

    if (currentTime - previousTime > 31000 && currentTime - previousTime < 32000)
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);

    if (currentTime - previousTime > 32000 && currentTime - previousTime < 37000) {
      tumServolariNotrle();
      if (Veri_Kontrol.getYaw() < 265) sagaDondur();
      else if (Veri_Kontrol.getYaw() > 275) solaDondur();
      else motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
      delay(50);
    }

    if (currentTime - previousTime > 37000 && currentTime - previousTime < 38000)
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);

    if (currentTime - previousTime > 38000 && currentTime - previousTime < 50000) {
      tumServolariNotrle();
      if (Veri_Kontrol.getYaw() < 50 && Veri_Kontrol.getYaw() > 5) sagaDondur();
      else if (Veri_Kontrol.getYaw() > 330 && Veri_Kontrol.getYaw() < 355) solaDondur();
      else motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
      delay(50);
    }

    if (currentTime - previousTime > 38000 && currentTime - previousTime < 65000) {
      tumServolariNotrle();
      if (Veri_Kontrol.getPitch() > -35) yukariDondur();
      else if (Veri_Kontrol.getPitch() < -45) asagiDondur();
      delay(50);
    }

    if (currentTime - previousTime > 36000 && currentTime - previousTime < 36100) {
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM);
      Serial.println("Bitti!");
      delay(100);
      break;
    }
  }
}

void gorev2() {
  tumServolariNotrle();
  motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM);
  previousTime = millis();

  while (1) {
    currentTime = millis();

    if (currentTime - previousTime < 3000) {
      if (Veri_Kontrol.getPitch() > -35) yukariDondur();
      else if (Veri_Kontrol.getPitch() < -45) asagiDondur();
      else tumServolariNotrle();
    }
    else if (currentTime - previousTime > 3000 && currentTime - previousTime < 6000) {
      tumServolariNotrle();
    }
    else if (currentTime - previousTime > 6000 && currentTime - previousTime < 10000) {
      if (Veri_Kontrol.getPitch() > 0) yukariDondur();
      else if (Veri_Kontrol.getPitch() < -10) asagiDondur();
      else tumServolariNotrle();
    }
    else if (currentTime - previousTime > 10000 && currentTime - previousTime < 14000) {
      if (Veri_Kontrol.getPitch() > -35) yukariDondur();
      else if (Veri_Kontrol.getPitch() < -45) asagiDondur();
      else tumServolariNotrle();
    }
    else if (currentTime - previousTime > 14000 && currentTime - previousTime < 18000) {
      ledPWMYak();
      if (Veri_Kontrol.getPitch() > -35) yukariDondur();
      else if (Veri_Kontrol.getPitch() < -45) asagiDondur();
      else tumServolariNotrle();
    }
    else if (currentTime - previousTime > 18000) {
      ledPWMSon();
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM);
      Serial.println("Görev 3 bitti.");
      delay(100);
      break;
    }
    delay(50);
  }
}
