
/*
    Controler Class
*/

#include <ifstream>

#include <MPU6050_tockn.h> 
#include <Servo.h>
#include <json/value.h>

class Controller {
    public: 
        MPU6050 mpu6050;

        Servo servo1;
        Servo servo2;
        Servo servo3;
        Servo servo4;

        void Controller(MPU6050 mpu6050, string fromFile='pins.json') {
            this->mpu6050 = mpu6050;

            Json::Value pins = getPins(fromFile);

            initializeServos(pins);
            initializeOutput(pins);

            Serial.begin(9600);
            Wire.begin();
            mpu6050.begin();
            mpu6050.calcGyroOffsets(true);
        }

        Json::Value getPins(string fromFile='pins.json') {
            // read a JSON file
            std::ifstream pins_file(fromFile, std::ifstream::binary);
            pins_file >> pins;

            return pins;
        }

        void initializeServos(Json::Value pins) {
            int servo1pin = pins["servoPins"]["servo1"];
            int servo2pin = pins["servoPins"]["servo2"];
            int servo3pin = pins["servoPins"]["servo3"];
            int servo4pin = pins["servoPins"]["servo4"];

            servo1.attach(servo1pin);
            servo2.attach(servo2pin);
            servo3.attach(servo3pin);
            servo4.attach(servo4pin);
        }

        void initializeOutput(Json::Value pins) {
            int greenLED = pins["outputPins"]["greenLED"];
            int redLED = pins["outputPins"]["redLED"];
            int buzzer = pins["outputPins"]["buzzer"];

            pinMode(greenLED, OUTPUT);  
            pinMode(redLED, OUTPUT);
            pinMode(buzzer, OUTPUT);
        }

        void setOutputPin(int pin, )

    private: 

}