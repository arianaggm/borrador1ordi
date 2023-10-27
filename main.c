#include "config.h"
#include "LCD_PORTD.h"
#include <xc.h>
#include <pic18f4550.h>


#define PWM1_out TRISCbits.RC2
#define PWM2_out TRISCbits.RC1
#define PWM3_out TRISCbits.RC0
#define PWM3_pin LATCbits.LC0

#define UP_BUTTON PORTBbits.RB0
#define DOWN_BUTTON PORTBbits.RB3
#define LEFT_BUTTON PORTBbits.RB1
#define RIGHT_BUTTON PORTBbits.RB2
#define ON 1
#define OFF 0
#define HI 1
#define LO 0
#define LINE_UP 0
#define LINE_DOWN 1

#define IN 1
#define OUT 0
#define LINE_DOWN 1
#define LINE_UP 0

unsigned int analogRead(char canal);
void configADC(char CHANNELS);
void configPWM1 (void);
void configPWM2 (void);
void configPWM3 (void);
void setDC1 (char x);
void setDC2 (char x);
void setDC3 (char x);

void myChars(void);
void delay(int a);
void configPorts(void);
void specialChars(void);
void configInterrupts(void);
void T0_1s(void);
void practicaInfusion(void);
void animateDrop(int speed);
void contar(void);
void programarTiempo(void);
void check4Buttons(void);

char y = 0;
char contador = 0;
char bandera = OFF;
int speed = 0;
int espera = 100;
int x = 0;
char s_unit = '0';
char s_dec = '0';
char m_unit = '0';
char m_dec = '0';
char SETTING = 1;
char COUNT_END = 0;

char duty3;
char HiLo;
//double multiplier = _XTAL_FREQ/(PWM_FREQ*16.0*100.0);

#define _XTAL_FREQ 8000000      // PIC18F4550 internal oscillator frequency

#define PWM_FREQ 2500            // PWM frequency in Hz
#define DESIRED_TEMP 37         // Default desired temperature


//void main(void) {
//    OSCCON = 127; //0b01111111;        // Start the oscillator
//    TRISEbits.RE0 = 0;
//    TRISEbits.RE1 = 0;
//    TRISB = 0x0F;
//    iniLCD();
//    LCDcommand(DispOnC);
//    practicaInfusion();
//    return;
//
//    // Step 8: Initialize ports and resources
//    // (Configure I/O pins, ADC port, PWM, and LEDs)
//
//    // Step 9: Configure timers and interrupts (if needed)
//
//    // Step 10: Start the LCD or 7-segment display
//
//    unsigned char dutyCycle = 0;
//    unsigned char heatingStatus = 0; // 0 - Not heating, 1 - Heating
//
//    while (1) {
//        // Step 11: Read buttons to adjust desired temperature
//        // (Implement button reading logic)
//
//        // Step 12: Wait for the start button to be pressed
//        // (Implement button reading logic)
//
//        // Step 13: Read the ADC port (temperature sensor) and assign values
//        // (Implement ADC reading and processing logic)
//
//        // Step 14: Control heating resistance with the correct PWM signal
//        // (Implement logic to control heating resistance based on desired temperature)
//
//        // Step 15: Show the temperature on the display
//        // (Implement logic to display the temperature on LCD or 7-segment display)
//        
//
//        // Step 16: Use LEDs to indicate heating status
//        if (heatingStatus == 1) {
//            // Red LED On
//            LATDbits.LATD0 = 1;
//            LATDbits.LATD1 = 0; // Green LED Off
//        } else {
//            // Green LED On
//            LATDbits.LATD0 = 0; // Red LED Off
//            LATDbits.LATD1 = 1;
//        }
//    }
//    return;
//}
//
//// Function to initialize the ADC
//void initADC() {
//    ADCON1 = 0x0E;             // Right justify, ADC Fosc/64
//}
//
//// Function to initialize PWM
//void initPWM() {
//    TRISC2 = 0;                // RC2 (PWM pin) as output
//    PR2 = (_XTAL_FREQ / (4.0 * PWM_FREQ * 16.0)) - 1;
//    CCPR1L = 0x00;             // Initialize duty cycle
//    CCP1CON = 0x0C;            // PWM mode
//    T2CON = 0x03;              // Timer2 ON, prescaler 16
//}
//
//// Function to set PWM duty cycle
//void setPWMDutyCycle(unsigned char dutyCycle) {
//    CCPR1L = dutyCycle;
//}
//
//void myChars(){
//    LCDcommand(SetCGRAM);
//    GenChar(DROP1);
//    GenChar(DROP2);
//}
//
//void practicaInfusion(){
//    myChars();
//    MoveCursor(0,LINE_UP);
//    LCDprint(8,"INFUSION",10);
//    MoveCursor(0,LINE_DOWN);
//    LCDprint(5,"00:00",10);
//    MoveCursor(0,LINE_DOWN);
//    programarTiempo();
//    LCDprint(10,"          ", 0);
//    LCDcommand(DispOn);
//    while(1){
//        animateDrop(250);
//        contar();
//        if(COUNT_END == 1){
//            MoveCursor(8,LINE_DOWN);
//            LCDprint(3,"END",0);
//            while(1){}
//        }
//    }
//}
//
//void programarTiempo(){
//    while(SETTING == 1){
//        check4Buttons();
//        delay(200);
//    }
//}
//
//void contar(){
//    __delay_ms(400);
//    s_unit--;
//    if(s_unit < '0'){
//        s_dec--;
//        if(s_dec < '0'){
//            m_unit--;
//            if(m_unit < '0'){
//                m_dec--;
//                if(m_dec < '0'){
//                    COUNT_END = 1;
//                }
//                m_unit = '9';
//            }
//            s_dec = '5';
//        }
//        s_unit = '9';
//    }
//    if(COUNT_END != 1){
//        MoveCursor(0,1);
//        LCDchar(m_dec);
//        LCDchar(m_unit);
//        MoveCursor(3,1);
//        LCDchar(s_dec);
//        LCDchar(s_unit);
//    }
//}
//
//void animateDrop(int speed){
//    MoveCursor(15,LINE_UP);
//    LCDchar(DROP1);
//    delay(speed);
//    MoveCursor(15,LINE_UP);
//    LCDchar('  ');
//    MoveCursor(15,LINE_DOWN);
//    LCDchar(DROP2);
//    delay(speed);
//    MoveCursor(15,LINE_DOWN);
//    LCDchar('  ');
//}
//
//void check4Buttons(){
//    if(UP_BUTTON == HI){
//        switch(x){
//            case 0:
//                m_dec++;
//                if(m_dec > '5'){
//                    m_dec = '0';
//                }
//                LCDchar(m_dec);
//                MoveCursor(x,1);
//                break;
//            case 1:
//                m_unit++;
//                if(m_unit > '9'){
//                    m_unit = '0';
//                }
//                LCDchar(m_unit);
//                MoveCursor(x,1);
//                break;
//            case 3:
//                s_dec++;
//                if(s_dec > '5'){
//                    s_dec = '0';
//                }
//                LCDchar(s_dec);
//                MoveCursor(x,1);
//                break;
//            case 4:
//                s_unit++;
//                if(s_unit > '9'){
//                    s_unit = '0';
//                }
//                LCDchar(s_unit);
//                MoveCursor(x,1);
//                break;
//            default:
//                break;        
//        }
//    }
//    if(LEFT_BUTTON == 1){
//        x--;
//        if(x == 2){
//            x = 1;
//        }
//        if(x < 0){
//            x = 4;
//        }
//        if(x == 4){
//            MoveCursor(x+1,1);
//            LCDprint(10,"      ",0);
//        }
//        MoveCursor(x,1);
//    }
//    if(RIGHT_BUTTON == 1){
//        x++;
//        if(x == 2){
//            x = 3;
//        }
//        if(x == 5){
//            MoveCursor(x,1);
//            LCDprint(10," RE<- ->OK",0);
//        }
//        if(x > 5){
//            SETTING = 0;
//        }
//        MoveCursor(x,1);
//    }
//}
//
//void delay(int a){
//    for(int i = 0; i <= a; i++){
//        __delay_ms(1);
//    }
//}
//
//void configPorts(){
//    ADCON1 = 0x0F;          //pines digitales
//    TRISD = 0x00;           //PORTD salida
//    TRISE = 0b11111000;     //E0-E2 salidas
//    TRISB = 0xFF;           //PORTB entrada
//}
//
//void specialChars(){
//    LCDcommand(SetCGRAM);
//    //GenChar(drop1);   //char0
//    //GenChar(drop2);   //char1
//}
//
//void configInterrupts(){ //Configura interrupciones
//    INTCONbits.GIE = ON; //Habilita interrupciones globales
//    INTCONbits.PEIE = ON; //Habilita interrupciones perifericas <6>
//    //--UNCOMMENT AS NEEDED
//    INTCONbits.TMR0IE = ON;// Habilita la interrupción del tmr0
//    //INTCONbits.RBIE = 1; //Habilita la interrupción del puerto b
//    //INTCON2bits.RBPU = 1; //Deshabilita pullups
//    INTCONbits.INT0E = ON; //Habilita la interrupción externa0;
//    INTCON2bits.INTEDG0 = LO; //flanco descendente
//    INTCON3bits.INT1E = ON; //Habilita la interrupción externa1;
//    INTCON2bits.INTEDG1 = LO; //flanco descendente
//    //INTCON3bits.INT2E = 1; //Habilita la interrupción externa1;
//    //INTCON2bits.INTEDG2 = 0; //flanco descendente
//    //PIE1bits.TMR1IE = 1; //Habilita la interrupción del timer1
//    //PIE1bits.TMR2IE = 1; //Habilita la interrupción del timer2
//    //PIE2bits.TMR3IE = 1; //Habilita la interrupción del timer3
//    //-----------------
//    RCONbits.IPEN = 0; //Desactiva las prioridades
//}
//
//void T0_1s(){
//    T0CONbits.TMR0ON = OFF;     //T0 OFF
//    INTCONbits.T0IF = OFF;      //Baja la bandera
//    //Precarga 3036 en el timer
//    TMR0H = 0x0B;
//    TMR0L = 0xDC;               //0BCD (hex) = 3036
//    T0CON = 0b10000100;
//}
//
//
//void __interrupt ()miISR(){
//    if(INTCONbits.TMR0IF == 1){
//        contador++;     //clear int flag 
//        INTCONbits.TMR0IF = LO;
//    }if(INTCONbits.INT0F == 1){
//        contador--;   
//        INTCONbits.INT0F = 0;
//    }
//    if(INTCON3bits.INT1IF == 1){
//        contador++;     //clear int flag
//        INTCON3bits.INT1IF = 0; 
//    }
//    bandera = ON;
//}
