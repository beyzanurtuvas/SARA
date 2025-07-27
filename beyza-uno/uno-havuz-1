#include <Servo.h>

// ----------- SERVO NESNELERİ -----------
Servo servo1; // ESC (itici motor)
Servo servo2; // Pitch yukarı
Servo servo3; // Yaw sağ
Servo servo4; // Pitch aşağı
Servo servo5; // Yaw sol
Servo servoLED; // PWM LED çıkışı

// ----------- PWM SABİTLERİ ------------
const int MOTOR_STOP_PWM  = 1490;
const int MOTOR_MAX_PWM   = 1100;
const int MOTOR_DONUS_PWM = 1250;

const int LED_PWM_ACIK    = 1900;
const int LED_PWM_KAPALI  = 1100;

// ----------- PINLER -------------------
const int ledPin = 11; // PWM LED pin

// ----------- ZAMANLAR -----------------
const int SISTEM_GECIKME = 5000;
const int GOREV_ARASI_BEKLEME = 60000; // 1 dk
const int YUZEYDE_BEKLEME = 4000;

void setup() {
  // Servo pinleri bağlanıyor
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo5.attach(10);
  servoLED.attach(ledPin);

  // Başlangıç durumu
  servo1.writeMicroseconds(MOTOR_STOP_PWM);
  tumServolariNotrle();
  ledPWMSon();
  delay(SISTEM_GECIKME);

  // GÖREV 1
  gorev1();
  delay(GOREV_ARASI_BEKLEME);

  // GÖREV 2
  gorev2();
}

void loop() {
  // Görevler sadece 1 defa setup’ta çalışır
}

// ---------- LED FONKSİYONLARI ----------
void ledPWMYak() {
  servoLED.writeMicroseconds(LED_PWM_ACIK);
}

void ledPWMSon() {
  servoLED.writeMicroseconds(LED_PWM_KAPALI);
}

// --------- SERVOLARI NÖTRLE -----------
void tumServolariNotrle() {
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
}

// --------- MOTOR KONTROLLERİ ----------
void motorYavasArtir(int baslangicPWM, int hedefPWM) {
  for (int pwm = baslangicPWM; pwm >= hedefPWM; pwm -= 2) {
    servo1.writeMicroseconds(pwm);
    delay(10);
  }
}

void motorYavasAzalt(int baslangicPWM, int hedefPWM) {
  for (int pwm = baslangicPWM; pwm <= hedefPWM; pwm += 2) {
    servo1.writeMicroseconds(pwm);
    delay(10);
  }
}

// ------------- GÖREV 1 ------------------
void gorev1() {
  tumServolariNotrle();
  motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM);
  delay(15000); // düz git 15sn

  // 1. sağa dön
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  servo3.write(135);
  servo5.write(45);
  delay(1500);
  tumServolariNotrle();
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  delay(5000); // sağa gittikten sonra düz 5sn

  // 2. tekrar sağa dön
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  servo3.write(135);
  servo5.write(45);
  delay(1500);
  tumServolariNotrle();
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  delay(5000); // tekrar düz 5sn

  // Hafif ileri ve yüzeye çık
  delay(15000); // düz git
  servo2.write(45); // yukarı pitch
  servo4.write(135);
  delay(2000); // yüzeye çık
  tumServolariNotrle();
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM);
}

// ------------- GÖREV 2 ------------------
void gorev2() {
  tumServolariNotrle();
  motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM);
  delay(7000); // düz git 7sn

  // 1. sola dön
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  servo3.write(45);
  servo5.write(135);
  delay(1500);
  tumServolariNotrle();
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  delay(5000); // sola gittikten sonra düz 5sn

  // 2. tekrar sağa dön
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  servo3.write(135);
  servo5.write(45);
  delay(1500);
  tumServolariNotrle();
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  delay(5000); // tekrar düz 5sn

  // Aşağı dal
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  servo2.write(135); // aşağı pitch
  servo4.write(45);
  delay(2000);

  // Yukarı çık (yunuslama)
  servo2.write(45);
  servo4.write(135);
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  delay(3000);

  // Yüzeyde kal 4 sn – hafif motor sinyaliyle
  servo1.writeMicroseconds(1350);
  ledPWMYak();
  delay(YUZEYDE_BEKLEME);
  ledPWMSon();

  // Durdur
  motorYavasAzalt(1350, MOTOR_STOP_PWM);
  tumServolariNotrle();
}
