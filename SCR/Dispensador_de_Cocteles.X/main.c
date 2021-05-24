/*
/////////////////// DATOS DEL PROGRAMA ////////////////////
//  TTITULO: Dispensador_de_Cocteles
//  MICRO: PIC16F15244-CNANO
//  ESTUDIANTES: 
 *  Juan Felipe Betancourth Ledezma - 2420191018
 *  Juan Sebastian Jimenez Peña - 2420192018
 * 
//  PROFESOR: Harold F MURCIA
//  FECHA: 23 de abril de 2021
 * 
 *  * 
///////////// CONFIGURACIÓN DEL MCU ////////////////// */

//<<<<  Librerias >>>>
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "flex_lcd.h"                   //Libreria Para la LCD  4x20

#pragma config FEXTOSC = OFF    // External Oscillator Mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_1MHZ    // Power-up Default Value for COSC bits->HFINTOSC (1 MHz)
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; I/O function on RA4
#pragma config VDDAR = HI    // VDD Range Analog Calibration Selection bit->Internal analog systems are calibrated for operation between VDD = 2.3V - 5.5V

// CONFIG2
#pragma config MCLRE = EXTMCLR    // Master Clear Enable bit->If LVP = 0, MCLR pin is MCLR; If LVP = 1, RA3 pin function is MCLR
#pragma config PWRTS = PWRT_OFF    // Power-up Timer Selection bits->PWRT is disabled
#pragma config WDTE = OFF    // WDT Operating Mode bits->WDT disabled; SEN is ignored
#pragma config BOREN = ON    // Brown-out Reset Enable bits->Brown-out Reset Enabled, SBOREN bit is ignored
#pragma config BORV = LO    // Brown-out Reset Voltage Selection bit->Brown-out Reset Voltage (VBOR) set to 1.9V
#pragma config PPS1WAY = ON    // PPSLOCKED One-Way Set Enable bit->The PPSLOCKED bit can be cleared and set only once in software
#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a reset

// CONFIG4
#pragma config BBSIZE = BB512    // Boot Block Size Selection bits->512 words boot block size
#pragma config BBEN = OFF    // Boot Block Enable bit->Boot Block is disabled
#pragma config SAFEN = OFF    // SAF Enable bit->SAF is disabled
#pragma config WRTAPP = OFF    // Application Block Write Protection bit->Application Block is not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block is not write-protected
#pragma config WRTC = OFF    // Configuration Registers Write Protection bit->Configuration Registers are not write-protected
#pragma config WRTSAF = OFF    // Storage Area Flash (SAF) Write Protection bit->SAF is not write-protected
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/Vpp pin function is MCLR. MCLRE Configuration bit is ignored.

// CONFIG5
#pragma config CP = OFF    // User Program Flash Memory Code Protection bit->User Program Flash Memory code protection is disabled



////////////////////////// DEFINICIONES  //////////////////////////////////////
#define _XTAL_FREQ 1000000          //Definiendo Frecuencia del Oscilador a 1Mhz
#define ACQ_US_DELAY 10

//  <<<<  Bombas de Agua (Motores) >>>>

#define on_motor1()             LATAbits.LATA4 = 1;  //motor 1  ---> Vodka
#define off_motor1()            LATAbits.LATA4 = 0;  //motor 1

#define on_motor2()             LATAbits.LATA5 = 1;  //motor 2  ---> Ginger
#define off_motor2()            LATAbits.LATA5 = 0;  //motor 2

#define on_motor3()             LATAbits.LATA1 = 1;  //motor 3  ---> Ron
#define off_motor3()            LATAbits.LATA1 = 0;  //motor 3

#define on_motor4()             LATBbits.LATB5 = 1;  //motor 4  ---> Naranja
#define off_motor4()            LATBbits.LATB5 = 0;  //motor 4

//Tiras led

#define off_tira1()            LATAbits.LATA2 = 0;   //Tira Led 1  ---> Rojo y Violeta
#define on_tira1()             LATAbits.LATA2 = 1;   //Tira Led 1

#define off_tira2()            LATBbits.LATB7 = 0;   //Tira 2  ---> Verde
#define on_tira2()             LATBbits.LATB7 = 1;   //Tira 2



///////////////////////////////////////////////////////////////////////////////

//////////////////////// VARIABLES GLOBALES  ///////////////////////////////////

char s[20];         // Variable char encargada de almacenar las pálabras.

///////////////////////////////////////////////////////////////////////////////


/////////////// DECLARACI?N DE FUNCIONES Y PROCEDIMIENTOS //////////////////////

//Inicialización de pines
void PIN_MANAGER_Initialize(void) {
  // LATx registers
  LATA = 0x00;
  LATB = 0x00;
  LATC = 0x00;

  // TRISx registers     ---> Estableciendo entradas (1) y salidas (0)
  TRISA = 0b00000000;
  TRISB = 0b00000000;
  TRISC = 0b00001111;         // 4 entradas  Botones de seleccion 

  // ANSELx registers
  ANSELC = 0;
  //ANSELB = 0;
  ANSELA = 0;

  // WPUx registers/

  // ODx registers
  ODCONA = 0x04;
  //ODCONB = 0x00;
  ODCONC = 0x00;

  // SLRCONx registers
  SLRCONA = 0x37;
  //SLRCONB = 0xFF;
  SLRCONC = 0xFF;

  // INLVLx registers
  INLVLA = 0x3F;
  //INLVLB = 0xFF;
  INLVLC = 0xFF;

}
//Inicialización de Oscilador
void OSCILLATOR_Initialize(void)
{
    OSCEN = 0x00;                                                               // MFOEN disabled; LFOEN disabled; ADOEN disabled; HFOEN disabled;
    OSCFRQ = 0x00;                                                              // HFFRQ0 1_MHz
    OSCTUNE = 0x00;
}


/* <<<< COMANDOS PARA ESCRIBIR EN LA LCD >>>>
 * sprintf(s, "PALABRA");   --> Guarda la palabra en la cadena de char < s >  
 * Lcd_Out2(1, 0, s);       --> Escribe en la LCD lo que esta en <s> (Filas, columnas, <s>)
 * Lcd_Cmd(LCD_CLEAR);      --> Borra lo que hay en la LCD
 */


// Funcion saludo           --> Texto inicial en la LCD 
void saludo (void){
     
    Lcd_Cmd(LCD_CLEAR);                     //Limpiando LCD
    sprintf(s, "====================");     //Realizando marco decorativo       
    Lcd_Out2(1, 0, s);                      //Escribiendo en la linea 1 espacio 0 la palabra
    sprintf(s, "DISPENSADOR DE");           //Guardando la palabra en la cadena de char < s >         
    Lcd_Out2(2, 3, s);                      //Escribiendo en la linea 2 espacio 3 la palabra
    sprintf(s, "COCTELES");                 //Guardando la palabra en la cadena de char < s >     
    Lcd_Out2(3, 6, s);                      //Escribiendo en la linea 3 espacio 6 la palabra
    sprintf(s, "====================");     //Realizando marco decorativo         
    Lcd_Out2(4, 0, s);                      //Escribiendo en la linea 4 espacio 0 la palabra
    __delay_ms(5000);                       //Tiempo que permanece el Texto en la LCD 5s
    
          Lcd_Cmd(LCD_CLEAR);                //Limpiando LCD
          sprintf(s, "====================");     //Realizando marco decorativo       
          Lcd_Out2(1, 0, s);                      //Escribiendo en la linea 1 espacio 0 la palabra
          sprintf(s, "MENU");           //Agregando nuevo texto
          Lcd_Out2(2, 8, s);
          sprintf(s, "COCTELES");
          Lcd_Out2(3, 6, s);
          sprintf(s, "====================");  
          Lcd_Out2(4, 0, s);   
           __delay_ms(3000);            //Tiempo que permanece el Texto en la LCD 3s
}

//Funcion Despedida         --> Texto final en la LCD
void despedida (void){
     
    Lcd_Cmd(LCD_CLEAR);                 //Limpiando LCD
    sprintf(s, "====================");  
    Lcd_Out2(1, 0, s);   
    sprintf(s, "GRACIAS");              //Escribiendo nuevo texto        
    Lcd_Out2(2, 7, s);                  
    sprintf(s, "QUE LO DISFRUTES");
    Lcd_Out2(3, 2, s);
    sprintf(s, "====================");  
    Lcd_Out2(4, 0, s);   
    __delay_ms(2000);                   //Tiempo que permanece el Texto en la LCD 2s

}

//Funcion menú              --> Mostrar las diferentes mezclas
void menu(void) {

     Lcd_Cmd(LCD_CLEAR);
          sprintf(s, "<1> Vodka y Ginger");
          Lcd_Out2(1, 0, s);
          sprintf(s, "<2> Vodka y Naranja");
          Lcd_Out2(2, 0, s);
          sprintf(s, "<3> Ron y Ginger");
          Lcd_Out2(3, 0, s);
          sprintf(s, "<4> Ron y Naranja");
          Lcd_Out2(4, 0, s);
          __delay_ms(5000);
        
}

//Función tiras leds        --> Secuencias Tiras Leds

        //  <<<< Secuencia de 7 segundos >>>>
void secuencias_leds(void){        
    
       for(int i =1; i<3; i++ ){
        
        // 1 secuencia
            on_tira1();             
          __delay_ms(150);
            off_tira1();             
          __delay_ms(150);
            on_tira1();             
          __delay_ms(150);
          
             on_tira2();
          __delay_ms(150);
             off_tira2();
          __delay_ms(150);
              on_tira2();
          __delay_ms(150);
         
          
          // 2 secuencia
         
          
             on_tira2();
          __delay_ms(150);
             off_tira2();
          __delay_ms(150);
              on_tira2();
          __delay_ms(150);
          
          
             on_tira1();
          __delay_ms(150); 
             off_tira1();
          __delay_ms(150);
             on_tira1();
          __delay_ms(150); 
           
          //3 secuencia
             off_tira1();             
             off_tira2();
          __delay_ms(150);       

              on_tira1();
          __delay_ms(150); 
             off_tira1();
          __delay_ms(150);
 
             on_tira2();
          __delay_ms(150); 
             off_tira2();
          __delay_ms(150);
         
           //4 secuencia
             off_tira1();             
             off_tira2();
          __delay_ms(200);    
          
             on_tira1();             
             on_tira2();
          __delay_ms(200); 
          
          
             off_tira1();             
             off_tira2();
          __delay_ms(200); 
          
             on_tira1();             
             on_tira2();
          __delay_ms(200); 
          
             off_tira1();             
             off_tira2();
          __delay_ms(200); 
          
         } 
    }

        //  <<<< Secuencia de 12 segundos >>>>
void secuencias_leds2(void){       
    
       for(int i =1; i<5; i++ ){
           
          // 2 secuencia
             on_tira2();
          __delay_ms(150);
             off_tira2();
          __delay_ms(150);
              on_tira2();
          __delay_ms(150);
          
          
             on_tira1();
          __delay_ms(150); 
             off_tira1();
          __delay_ms(150);
             on_tira1();
          __delay_ms(150); 
           
          //3 secuencia
             off_tira1();             
             off_tira2();
          __delay_ms(150);       

              on_tira1();
          __delay_ms(150); 
             off_tira1();
          __delay_ms(150);
 
    
            on_tira2();             
          __delay_ms(200);
            on_tira1();             
          __delay_ms(200);
          off_tira1();
          __delay_ms(200);
          off_tira2();
          __delay_ms(200);
           on_tira2();             
          __delay_ms(200);
            on_tira1();             
          __delay_ms(200);
          off_tira1();
          __delay_ms(200);
          off_tira2();
          __delay_ms(200);
         } 
    }

        //  <<<< Secuencia de 15 segundos >>>>
void secuencias_leds3(void){       
    
       for(int i =1; i<5; i++ ){
        
        // 1 secuencia
            on_tira1();             
          __delay_ms(150);
            on_tira2();             
          __delay_ms(150);
          off_tira2();
          __delay_ms(150);
          off_tira1();
          __delay_ms(150);
           on_tira1();             
          __delay_ms(150);
            on_tira2();             
          __delay_ms(150);
          off_tira2();
          __delay_ms(150);
          off_tira1();
          __delay_ms(150);
          
          // 2 secuencia
             on_tira2();
          __delay_ms(150);
             off_tira2();
          __delay_ms(150);
              on_tira2();
          __delay_ms(150);
          
          
             on_tira1();
          __delay_ms(150); 
             off_tira1();
          __delay_ms(150);
             on_tira1();
          __delay_ms(150); 
           
          //3 secuencia
             off_tira1();             
             off_tira2();
          __delay_ms(150);       

              on_tira1();
          __delay_ms(150); 
             off_tira1();
          __delay_ms(150);
 
             on_tira2();
          __delay_ms(150); 
             off_tira2();
          __delay_ms(150);
         
           //4 secuencia
             off_tira1();             
             off_tira2();
          __delay_ms(200);    
          
             on_tira1();             
             on_tira2();
          __delay_ms(200); 
          
          
             off_tira1();             
             off_tira2();
          __delay_ms(200); 
          
             on_tira1();             
             on_tira2();
          __delay_ms(200); 
          
             off_tira1();             
             off_tira2();
          __delay_ms(200); 
         
          
         } 
    }

        //  <<<< Secuencia de 20 segundos >>>>
void secuencias_leds4(void){      
    
       for(int i =1; i<6; i++ ){
        
           on_tira1();
           on_tira2();
           __delay_ms(400); 
           
           off_tira1();
           off_tira2();
           __delay_ms(400);
           
              on_tira2();             
             on_tira1();
          __delay_ms(400); 
          
             off_tira2();             
             off_tira1();
          __delay_ms(400); 
          
          on_tira1();             
          __delay_ms(150);
            on_tira2();             
          __delay_ms(150);
          off_tira2();
          __delay_ms(150);
          off_tira1();
          __delay_ms(150);
           on_tira1();             
          __delay_ms(150);
            on_tira2();             
          __delay_ms(150);
          off_tira2();
          __delay_ms(150);
          off_tira1();
          __delay_ms(150);
          on_tira1();             
          __delay_ms(150);
            on_tira2();             
          __delay_ms(150);
          off_tira2();
          __delay_ms(150);
          off_tira1();
          __delay_ms(150);
           on_tira1();             
          __delay_ms(150);
            on_tira2();             
          __delay_ms(150);
          off_tira2();
          __delay_ms(150);
          off_tira1();
          __delay_ms(150);
          
       }     
    }


//Funciones de lo cocteles

    // <1> COCTEL 1 : Vodka y Ginger
void coctel_1(void)
{
   
           on_motor1();                 // Sale Vodka
           secuencias_leds3();          // Espera 12 seg
           off_motor1();                // No sale Vodka
           __delay_ms(1000);            // Espera 1 seg
           on_motor2();                 // Sale Ginger
           secuencias_leds4();          // Espera 20 seg
           off_motor2();                // No sale Ginger
           __delay_ms(1000);            // Espera 1 seg
           
}

    // <2> COCTEL 2 : Vodka y Naranja
void coctel_2(void)
{
    
           on_motor1();                 // Sale Vodka
           secuencias_leds();           // Espera 7 seg
           off_motor1();                // No sale Vodka
           __delay_ms(1000);            // Espera 1 seg
           on_motor4();                 // Sale Naranja
           secuencias_leds3();          // Espera 15 seg
           off_motor4();                // No sale Naranja
           __delay_ms(1000);            // Espera 1 seg

}

    // <3> COCTEL 3 : Ron y Ginger
void coctel_3(void)
{
           on_motor3();                 // Sale Ron
           secuencias_leds4();          // Espera 20 seg
           off_motor3();                // No sale Vodka
           __delay_ms(1000);            // Espera 1 seg
           on_motor2();                 // Sale Ginger
           secuencias_leds3();          // Espera 15 seg
           off_motor2();                // No sale Ginger
           __delay_ms(1000);            // Espera 1 seg
    
}

    // <4> COCTEL 4 : Ron y Naranja
void coctel_4(void)
{ 
    
           on_motor3();                 // Sale Ron
           secuencias_leds4();          // Espera 20 seg
           off_motor3();                // No sale Vodka
           __delay_ms(1000);            // Espera 1 seg
           on_motor4();                 // Sale Naranja
           secuencias_leds3();          // Espera 15 seg
           off_motor4();                // No sale Naranja
           __delay_ms(1000);            // Espera 1 seg
                    
}

///////////////////////////////////////////////////////////////////////////////

/////////////  INICIO DEL PROGRAMA PRINCIPAL //////////////////////////

void main(void)
{
   
    PIN_MANAGER_Initialize();       //Inicializando pines
    OSCILLATOR_Initialize();        //Inicializando Oscilador de 1MHz
    
    Lcd_Init();                     //Inicializando el LCD
    Lcd_Cmd(LCD_CLEAR);             //Limpiando LCD
    Lcd_Cmd(LCD_CURSOR_OFF);        //Apagando el cursor de la LCD
    
    saludo();                       // Se muetra el saludo
    menu();                         // Se muetra el menú de cocteles
    
    // Se crea un bucle infinito para que se muestre el menú y se pueda se selccionar una bebida
   while(1){ 
        if (PORTCbits.RC0 == 0) {           // Sí se presiona Boton 1
            coctel_1();                     // Se prepara coctel 1
            despedida();                    // Se muestra la despedida en la LCD
            menu();                         // Se muestra de nuevo el menú, para esperar nueva orden 
        }
        else if(PORTCbits.RC1 == 0) {       // Sí se presiona Boton 2
      
            coctel_2();                     // Se prepara coctel 2
            despedida();                    // Se muestra la despedida en la LCD
            menu();                         // Se muestra de nuevo el menú, para esperar nueva orden 
        }
        else if(PORTCbits.RC2 == 0) {       // Sí se presiona Boton 3
      
            coctel_3();                     // Se prepara coctel 3
            despedida();                    // Se muestra la despedida en la LCD
            menu();                         // Se muestra de nuevo el menú, para esperar nueva orden 
        }
        else if(PORTCbits.RC3 == 0) {       // Sí se presiona Boton 3
          
            coctel_4();                     // Se prepara coctel 3
            despedida();                    // Se muestra la despedida en la LCD
            menu();                         // Se muestra de nuevo el menú, para esperar nueva orden 
        }
       
   }
}


