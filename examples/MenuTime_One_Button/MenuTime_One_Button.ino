#include <Menu_Lcd.h>
#include <LiquidCrystal_I2C.h>

#define pinDown 10
#define pinUp 9

LiquidCrystal_I2C lcd(0x27);
const byte opciones = 6;
String menus[opciones] = {"Saludar", "Encender", "Mover pieza", "Config", "Otros", "Rename"};
Menu_Lcd menu(opciones, 20, 4, &lcd);
void setup()
{
    Serial.begin(9600);
    lcd.begin(20, 4);
    menu.setParameters(menus);
    menu.saveRows(1);
    lcd.setBacklightPin(3, POSITIVE);
    lcd.setBacklight(HIGH);
    pinMode(pinDown, INPUT);
    pinMode(pinUp, INPUT);
    menu.show();
}
void loop()
{
    if (digitalRead(pinDown) == 1)
    {
        // Serial.println(menu.down());
        menu.down();
    }
    else if (digitalRead(pinUp) == 1)
    {
        // Serial.println(menu.up());
        menu.up();
    }
}