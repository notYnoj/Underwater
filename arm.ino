#include <USBHost.h>
#include <Servo.h>

USBHost usb;
USBHIDParser hid(&usb);
HIDJoystick joy(&usb);

Servo s1, s2, s3;

int s1reset = 90, s2reset = 90, s3reset = 90;
bool big = true;

int open_big = 180;
int open_small = 130;
int close_big = 0;
int close_small = 35;

void setup() {
    Serial.begin(115200);
    usb.begin();

    s1.attach(9);
    s2.attach(10);
    s3.attach(11);
    
    Serial.println("Waiting for Controller...");
}

void loop() {
    usb.task();

    if (joy.available()) {
        Serial.println("Controller Connected!");
        int rightX = joy.getRXAxis();
        int rightY = joy.getRYAxis();
        
        int threshold = 20;
        if (abs(rightY) < threshold) rightY = 0;
        if (abs(rightX) < threshold) rightX = 0;
        
        int arm1Speed = map(rightY, -255, 255, 0, 180);
        s1.write(arm1Speed);

        int arm2Speed = map(rightX, -255, 255, 0, 180);
        s2.write(arm2Speed);

        if (joy.getButton(7)) {
            s3.write(big ? open_big : open_small);
        }
        if (joy.getButton(8)) {
            s3.write(big ? close_big : close_small);
        }
        if (joy.getButton(17)) {
            big = !big;
            delay(200);
        }
    } else {
        Serial.println("Not Connected...");
    }
}
