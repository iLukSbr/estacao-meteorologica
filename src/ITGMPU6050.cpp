/* ITGMPU6050 gyroscope, accelerometer and thermometer */

#include "ITGMPU6050.h"

ITGMPU6050::ITGMPU6050():
    mpu6050(new MPU6050(Wire))
{
    start();
}

ITGMPU6050::~ITGMPU6050(){
    delete mpu6050;
}

float ITGMPU6050::getAngleX() const{
    return info[0];
}

float ITGMPU6050::getAngleY() const{
    return info[1];
}

float ITGMPU6050::getAngleZ() const{
    return info[2];
}

// float ITGMPU6050::getTemperatureCelsius() const{
//     return info[3];
// }

// float ITGMPU6050::getTemperatureKelvin() const{
//     return info[3] + 273.15;
// }

void ITGMPU6050::print() const{
    Serial.println(F("ITGMPU6050:"));
    Serial.print("angle X = ");
    Serial.print(getAngleX());
    Serial.println(F("°"));
    Serial.print("angle Y = ");
    Serial.print(getAngleY());
    Serial.println(F("°"));
    Serial.print("angle Z = ");
    Serial.print(getAngleZ());
    Serial.println(F("°"));
    // Serial.print("temperature = ");
    // Serial.print(getTemperatureCelsius());
    // Serial.print(F(" °C = "));
    // Serial.print(getTemperatureKelvin());
    // Serial.println(F(" K"));
}

void ITGMPU6050::read(){
    gyro_signals();
    info[0] = info[0] - cali[0];
    info[1] = info[1] - cali[1];
    info[2] = info[2] - cali[2];
    // info[3] = mpu6050->getTemp();
}

void ITGMPU6050::start(){
    Wire.begin();
    
    Wire.setClock(400000); //especificação do sensor
    Wire.begin();
    delay(250);
    //Coloca o gyroscopio no modo energia
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission();
    Serial.println("\nCALIBRANDO");
    
    float RateCaliRoll,RateCaliPitch,RateCaliYaw;
    int RateCaliNumber;
    int maximo = 2000;
    for(RateCaliNumber=0;RateCaliNumber<maximo;RateCaliNumber++)
    {
        gyro_signals();
        RateCaliRoll+=info[0];
        RateCaliPitch+=info[1];
        RateCaliYaw+=info[2];
        delay(1);
    }
    RateCaliRoll/=maximo;
    RateCaliPitch/=maximo;
    RateCaliYaw/=maximo;
    Serial.println("Calibrado");
    cali[0] = RateCaliRoll;
    cali[1] = RateCaliPitch;
    cali[1] = RateCaliYaw;
    started = true;
}

void gyro_signals()
{
      //Filtro passa baixa
  // Verificar se realmente é necessario, o exemplo abaixo é um código de um drone
  Wire.beginTransmission(0x68);// Começa comunicação I2C com gyroscopio
  Wire.write(0x1A);            // 0X1A = Endereço do registrador
  Wire.write(0x05);            // frequecia de corte de 10 HZ
  Wire.endTransmission();

  //Setar o fator de sensitividade da escala
  Wire.beginTransmission(0x68);// Começa comunicação I2C com gyroscopio
  Wire.write(0x1B);            // 1B = registrador para alterar a escala
  Wire.write(0x8);             // 65.5 LSB/°/S
  Wire.endTransmission();

  //Acesso das medições do gyroscopio
  Wire.beginTransmission(0x68);// Começa comunicação I2C com gyroscopio           
  Wire.write(0x43);            //Primeiro registrador
  Wire.endTransmission();

  Wire.requestFrom(0x68,6);  

  int16_t GyroX=Wire.read()<<8 | Wire.read();  //Read the gyro measures around the X axis
  int16_t GyroY=Wire.read()<<8 | Wire.read();
  int16_t GyroZ=Wire.read()<<8 | Wire.read();

  info[0]=(double)GyroX/65.5;
  info[1]=(double)GyroY/65.5;
  info[2]=(double)GyroZ/65.5;
}
    
