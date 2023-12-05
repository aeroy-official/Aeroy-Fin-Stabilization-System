
/*
    Controler Class
*/

#include <ifstream>

#include <MPU6050_tockn.h> 
#include <Servo.h>
#include <json/value.h>

class Controller {
    public: 
        Servo servo1;
        Servo servo2;
        Servo servo3;
        Servo servo4;

        Json::Value pins;

        void static initializeController(MPU6050 mpu6050, string fromFile) {
            // read a JSON file
            std::ifstream pins_file(fromFile, std::ifstream::binary);
            pins_file >> pins;

            initializeServos();
            initializeOutput();

            Serial.begin(9600);
            Wire.begin();
            mpu6050.begin();
            mpu6050.calcGyroOffsets(true);
        }

        void static initializeServos() {
            int servo1pin = pins["servoPins"]["servo1"];
            int servo2pin = pins["servoPins"]["servo2"];
            int servo3pin = pins["servoPins"]["servo3"];
            int servo4pin = pins["servoPins"]["servo4"];

            servo1.attach(servo1pin);
            servo2.attach(servo2pin);
            servo3.attach(servo3pin);
            servo4.attach(servo4pin);
        }

        void static initializeOutput() {
            int greenLED = pins["outputPins"]["greenLED"];
            int redLED = pins["outputPins"]["redLED"];
            int buzzer = pins["outputPins"]["buzzer"];

            pinMode(greenLED, OUTPUT);  
            pinMode(redLED, OUTPUT);
            pinMode(buzzer, OUTPUT);
        }

    private: 

}