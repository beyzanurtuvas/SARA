void gorev1() {
  tumServolariNotrle();
  motorYavasArtir(MOTOR_STOP_PWM, MOTOR_MAX_PWM);
  delay(12000); // düz git 12sn

  // motor yavaşla
  tumServolariNotrle();
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  delay(1000);

  // sağa dön (50°→85°)
  tumServolariNotrle();
  servo3.write(135);
  servo5.write(45);
  delay(3000);  // dönüş süresi
  tumServolariNotrle();
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  delay(5000);  // düz git

  // motor yavaşla
  tumServolariNotrle();
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  delay(1000);

  // sola dön (95°→175°)
  tumServolariNotrle();
  servo3.write(45);
  servo5.write(135);
  delay(3000);  // dönüş süresi
  tumServolariNotrle();
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  delay(5000);  // düz git

  // motor yavaşla
  tumServolariNotrle();
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  delay(1000);

  // sağa dön (185°→265°)
  tumServolariNotrle();
  servo3.write(135);
  servo5.write(45);
  delay(3000);  // dönüş süresi
  tumServolariNotrle();
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  delay(5000);  // düz git

  // motor yavaşla
  tumServolariNotrle();
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_DONUS_PWM);
  delay(1000);

  // sola dön (275°→50°)
  tumServolariNotrle();
  servo3.write(45);
  servo5.write(135);
  delay(3000);  // dönüş süresi
  tumServolariNotrle();
  motorYavasArtir(MOTOR_DONUS_PWM, MOTOR_MAX_PWM);
  delay(5000);  // düz git

  // pitch kontrolü (yukarı-aşağı yunuslama benzeri)
  tumServolariNotrle();
  delay(1000);

  // Yukarı dön
  servo2.write(45);
  servo4.write(135);
  delay(1500);

  // Aşağı dön
  servo2.write(135);
  servo4.write(45);
  delay(1500);

  // Yukarı dön
  servo2.write(45);
  servo4.write(135);
  delay(1500);

  // Bitir
  tumServolariNotrle();
  motorYavasAzalt(MOTOR_MAX_PWM, MOTOR_STOP_PWM);
  delay(1000);
  Serial.println("Görev 1 bitti");
}
