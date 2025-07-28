#include "ALACAKART.h"
#include "BNO055.h"

// ----------- PWM SABİTLERİ ------------
const int MOTOR_STOP_PWM  = 1200;
const int MOTOR_MAX_PWM   = 1400;
const int MOTOR_DONUS_PWM = 1300;

const int LED_PWM_ACIK    = 1900;
const int LED_PWM_KAPALI  = 1100;

// ----------- ZAMANLAR -----------------
const int SISTEM_GECIKME       = 5000;
const int GOREV_ARASI_BEKLEME  = 60000;
const int YUZEYDE_BEKLEME      = 4000;

// ----------- NESNELER -----------------
ALACA_KART Veri_Kontrol;
BNO055Sensor bno055;

uint32_t currentTime = 0;
uint32_t previousTime = 0;

void setup() {
  Serial1.begin(9600);
  if (!bno055.begin(0x28)) {
    Serial1.println("BNO sensörü başlatılamadı!");
  }

  Veri_Kontrol.Servo_1(MOTOR_STOP_PWM);
  tumServolariNotrle();
  ledPWMSon();

  delay(SISTEM_GECIKME);

  // Görevler
  currentTime = millis();
  previousTime = millis();
  gorev1();
  delay(GOREV_ARASI_BEKLEME);
  gorev2();
}

void loop() {}

// --------- LED KONTROLÜ ---------------
void ledPWMYak() {
  Veri_Kontrol.Servo_LED_Write(LED_PWM_ACIK);
}

void ledPWMSon() {
  Veri_Kontrol.Servo_LED_Write(LED_PWM_KAPALI);
}

// --------- SERVOLARI NÖTRLE -----------
void tumServolariNotrle() {
  Veri_Kontrol.Servo_2_Write(90);
  Veri_Kontrol.Servo_3_Write(90);
  Veri_Kontrol.Servo_4_Write(90);
  Veri_Kontrol.Servo_5_Write(90);
}

// --------- MOTOR KONTROLLERİ ----------
void motorYavasArtir(int baslangicPWM, int hedefPWM) {
  for (int pwm = baslangicPWM; pwm <= hedefPWM; pwm += 2) {
    Veri_Kontrol.Servo_1(pwm);
    delay(1);
  }
}

void motorYavasAzalt(int baslangicPWM, int hedefPWM) {
  for (int pwm = baslangicPWM; pwm >= hedefPWM; pwm -= 2) {
    Veri_Kontrol.Servo_1(pwm);
    delay(1);
  }
}

// --------- YÖNLENDİRME FONKS. ---------
void sagaDondur() {
  Veri_Kontrol.Servo_3_Write(135);
  Veri_Kontrol.Servo_5_Write(45);
}

void solaDondur() {
  Veri_Kontrol.Servo_3_Write(45);
  Veri_Kontrol.Servo_5_Write(135);
}

void yukariDondur() {
  Veri_Kontrol.Servo_2_Write(45);
  Veri_Kontrol.Servo_4_Write(135);
}

void asagiDondur() {
  Veri_Kontrol.Servo_2_Write(135);
  Veri_Kontrol.Servo_4_Write(45);
}

// ------------- GÖREV 1 ------------------
bool ilkDonus = true;
bool ikinciDonus = true;

void gorev1() {
  previousTime = millis();
  Serial1.println("Görev 1 başlıyor...");

  while (1) {
    currentTime = millis();

    if ((currentTime - previousTime) >= 63000) {
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM);
      Serial1.println("Görev 1 tamamlandı, 60 sn geçti.");
      break;
    }

    if (ikinciDonus) {
      Serial1.println("Görev 1 başladı.");
      ikinciDonus = false;
    }

    if (currentTime - previousTime < 12000) {
      tumServolariNotrle();
      if (ilkDonus) {
        motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM);
        ilkDonus = false;
      }
      if (bno055.getYaw() < 50 && bno055.getYaw() > 5) {
        solaDondur();
      } else if (bno055.getYaw() > 330 && bno055.getYaw() < 355) {
        sagaDondur();
      }
    } else if (currentTime - previousTime < 13000) {
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
    } else if (currentTime - previousTime < 18000) {
      tumServolariNotrle();
      if (bno055.getYaw() < 85) {
        sagaDondur();
      } else if (bno055.getYaw() > 95) {
        solaDondur();
      } else {
        motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
      }
    } else if (currentTime - previousTime < 19000) {
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
    } else if (currentTime - previousTime < 31000) {
      tumServolariNotrle();
      if (bno055.getYaw() < 175) {
        sagaDondur();
      } else if (bno055.getYaw() > 185) {
        solaDondur();
      } else {
        motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
      }
    } else if (currentTime - previousTime < 32000) {
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
    } else if (currentTime - previousTime < 37000) {
      tumServolariNotrle();
      if (bno055.getYaw() < 265) {
        sagaDondur();
      } else if (bno055.getYaw() > 275) {
        solaDondur();
      } else {
        motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
      }
    } else if (currentTime - previousTime < 38000) {
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
    } else if (currentTime - previousTime < 50000) {
      tumServolariNotrle();
      if (bno055.getYaw() < 50 && bno055.getYaw() > 5) {
        sagaDondur();
      } else if (bno055.getYaw() > 330 && bno055.getYaw() < 355) {
        solaDondur();
      } else {
        motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
      }
    } else if (currentTime - previousTime < 65000) {
      tumServolariNotrle();
      if (bno055.getPitch() > -35) {
        yukariDondur();
      } else if (bno055.getPitch() < -45) {
        asagiDondur();
      }
    } else if (currentTime - previousTime < 65100) {
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM);
      Serial1.println("Bitti!");
      break;
    }

    delay(50);
  }
}

// ------------- GÖREV 2 ------------------
void gorev2() {
  tumServolariNotrle();
  motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM);
  previousTime = millis();

  while (1) {
    currentTime = millis();

    if (currentTime - previousTime < 3000) {
      if (bno055.getPitch() > -35) yukariDondur();
      else if (bno055.getPitch() < -45) asagiDondur();
      else tumServolariNotrle();
    } else if (currentTime - previousTime < 6000) {
      tumServolariNotrle();
    } else if (currentTime - previousTime < 10000) {
      if (bno055.getPitch() > 0) yukariDondur();
      else if (bno055.getPitch() < -10) asagiDondur();
      else tumServolariNotrle();
    } else if (currentTime - previousTime < 14000) {
      if (bno055.getPitch() > -35) yukariDondur();
      else if (bno055.getPitch() < -45) asagiDondur();
      else tumServolariNotrle();
    } else if (currentTime - previousTime < 18000) {
      ledPWMYak();
      if (bno055.getPitch() > -35) yukariDondur();
      else if (bno055.getPitch() < -45) asagiDondur();
      else tumServolariNotrle();
    } else {
      ledPWMSon();
      tumServolariNotrle();
      motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM);
      Serial1.println("Görev 3 bitti.");
      break;
    }

    delay(50);
  }
}
