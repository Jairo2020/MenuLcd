/**************************************************************************/
/*! 
    @file     Menu_Lcd.h
    @author   Jairo Rohatan Zapta
	
*/

#ifndef Menu_Lcd_H
#define Menu_Lcd_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include <WString.h>
#endif

#include <LiquidCrystal_I2C.h>

class Menu_Lcd
{
public:
    /**Variables */

    /*!
    @method
    @abstract constructor
    @param numerosMenu [in] cantidad de opciones de menús. máximo de 10.
    @param colum [in] Cantidad de columnas para la pantalla.
    @param fila [in] cantidad de filas para la pantalla.
    @param pantalla [in] Objeto creado para la pantalla lcd.
    */
    Menu_Lcd(byte numerosMenu, uint8_t colum, uint8_t fila, LiquidCrystal_I2C *pantalla);
    ~Menu_Lcd(void);
    /*!
    @method
    @param arrayNombresMenus [in] Escribe los nombres de los menús.
    @param cursor [in] Cursor personalizado, por defecto es '>'.
    */
    void setParameters(String arrayNombresMenus[], char cursor = '>');
    void show(void);
    /*!
    @return Posición del cursor
     */
    byte up(void);
    /*!
    @return Posición del cursor
     */
    byte down(void);
    /*!
    @method
    @param  rows[in] Cantidad de filas a salvar Nota: maximo 2 mínimo 1
     */
    void saveRows(byte rows);
    // void init();
    void saludo();
    // Data members
    

private:
    byte _opcionesMenu; // Almacena la cantidad de opciones en el menú.
    byte iteradorIndice = 0; // Contador que tine como objetivo guardar el indice del puntero de selección del menú.
    byte contadorUp = 0;
    byte contadorDown = 0;
    byte nivelMenus = 0; // Controla los niveles del menús.
    byte controlCursor = 0;
    byte filasSalvar = 0;
    uint8_t columna;
    uint8_t filas;
    char cursorMenu;
    String menus[10];
    String salir = "Exit";
    LiquidCrystal_I2C *lcd;

    void clearCol(byte col = 0);
    void clearRow(byte row = 0);
    void scrollDown(void);
    void scrollUp(void);
    void exit(void);
};

#endif
