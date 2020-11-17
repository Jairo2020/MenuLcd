#include "Menu_Lcd.h"

Menu_Lcd::Menu_Lcd(byte numerosMenu, uint8_t colum, uint8_t fila, LiquidCrystal_I2C *pantalla)
{
    _opcionesMenu = numerosMenu;

    columna = colum;
    filas = fila;
    lcd = pantalla;
}
Menu_Lcd::~Menu_Lcd(void)
{
}

/* void Menu_Lcd::init(uint8_t colum, uint8_t fila, LiquidCrystal_I2C *pantalla)
{
    // :columna(colum), filas(fila), lcd(lcd){}

    
    // lcd->print("hola mundo");
} */

void Menu_Lcd::setParameters(String arrayNombresMenu[], char cursor = '>')
{
    for (size_t i = 0; i < _opcionesMenu; i++)
    {
        menus[i] = arrayNombresMenu[i];
    }
    if (cursor != '>')
    {
        cursorMenu = cursor;
    }
    else
    {
        cursorMenu = cursor;
    }
}

void Menu_Lcd::show(void)
{
    lcd->clear();
    for (size_t i = 0; i < filas - filasSalvar; i++)
    {
        lcd->setCursor(1, i + filasSalvar);
        lcd->print(menus[i]);
    }
    lcd->setCursor(0, controlCursor + filasSalvar);
    lcd->print(cursorMenu);
}

void Menu_Lcd::saludo()
{
    lcd->clear();
    lcd->setCursor(0, 0);
    lcd->print("Hola como estas");
    delay(1000);
    show();
}

byte Menu_Lcd::up(void)
{
    if (iteradorIndice == 0)
    {
        iteradorIndice = _opcionesMenu - 1;
        contadorDown = filas - iteradorIndice;
        contadorUp = 0;
        controlCursor = filas - 1;
        scrollUp();
    }
    else
    {
        iteradorIndice--;
        if (controlCursor - filasSalvar > 0)
        {
            controlCursor--;
        }
        else if (controlCursor - filasSalvar == 0 && iteradorIndice >= 0)
        {
            contadorUp++;
            scrollUp();
        }
    }
    clearCol();
    lcd->setCursor(0, controlCursor);
    lcd->print(cursorMenu);

    delay(400);
    return iteradorIndice;
}

byte Menu_Lcd::down(void)
{
    if (iteradorIndice == _opcionesMenu - 1)
    {
        iteradorIndice = 0;
        contadorDown = 0;
        controlCursor = 0;
        show();
    }
    else
    {
        iteradorIndice++;
        if (controlCursor + filasSalvar < filas - 1)
        {
            controlCursor++;
            clearCol();
            lcd->setCursor(0, controlCursor + filasSalvar);
            lcd->print(cursorMenu);
        }
        else
        {
            clearCol();
            contadorDown++;
            scrollDown();
            lcd->setCursor(0, controlCursor + filasSalvar);
            lcd->print(cursorMenu);
        }
    }
    delay(400);
    return iteradorIndice;
}

void Menu_Lcd::saveRows(byte rows)
{
    if (rows <= 2)
        if (filas == 4)
        {
            filasSalvar = rows;
            // controlCursor = filasSalvar;
        }
        else if (filas == 2 && rows > 0)
        {
            filasSalvar = 1;
            // controlCursor = filasSalvar;
        }
}
//Private:

void Menu_Lcd::clearCol(byte col = 0)
{
    for (size_t i = 0 + filasSalvar; i < filas; i++)
    {
        lcd->setCursor(col, i);
        lcd->print(" ");
    }
}

void Menu_Lcd::clearRow(byte row = 0)
{
    for (size_t i = 0; i < columna; i++)
    {
        lcd->setCursor(i, row + filasSalvar);
        lcd->print(" ");
    }
}

void Menu_Lcd::scrollDown(void)
{
    lcd->clear();
    for (size_t i = 0; i < filas - filasSalvar; i++)
    {
        lcd->setCursor(1, i + filasSalvar);
        lcd->print(menus[i + contadorDown]);
    }
}

void Menu_Lcd::scrollUp(void)
{
    lcd->clear();
    if (contadorUp == 0)
    {
        for (int i = filas - 1, j = _opcionesMenu - 1; i >= 0 + filasSalvar; i--, j--)
        {
            lcd->setCursor(1, i);
            lcd->print(menus[j]);
        }
    }
    else
    {
        for (int i = filas - 1, j = _opcionesMenu - (1 + contadorUp); i >= 0 + filasSalvar; i--, j--)
        {
            lcd->setCursor(1, i);
            lcd->print(menus[j]);
        }
    }
}

void Menu_Lcd::exit(void)
{
    nivelMenus--;
    show();
}