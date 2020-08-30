    /*
Programa para medir el nivel de agua en dos tanques usando el sensor SR-HR04 y reportarlo en un LCD
Program for measuring water level in a tank, using SR-HR04 and display it in a LCD

por/by  David Wong <dwonga@gmail.com> 

    */
    #include <LiquidCrystal.h> // includes the LiquidCrystal Library
    #include <math.h>  //para el redondeo
    
    LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
    // Connect panel using the standard lines.

    // Sensor 1, trigger pin 13 y echo pin 12.
    const int trigPin1 = 13;
    const int echoPin1 = 12;

    // Sensor 2, trigger pin 11 y echo pin 10.
    const int trigPin2 = 11;
    const int echoPin2 = 10;

    // dimensiones Tanque 1 (el que esta en la parte inferior) en metros.
    const float lengthBottomTankM = 3.2;
    const float widthBottomTankM = 2;
    const float deepBottomTankM = 1.7;
    const float volTotalBottomTankM3 = 8.96; // Restado 0.3 de distancia al sensor tanque inferior

    // dimensiones Tanque 2 (el que esta en la parte inferior) en mestros
    const float lengthUpTankM = 2.74;
    const float widthUpTankM = 2;
    const float deepUpTankM = 1.9;
    const float volTotalUpTankM3 = 9.32; // Restado 0.2 de distancia al sensor tanque superior
   
     long duration1;
    float deepBottomTankCm;


    long duration2;
    float deepUpTankCm;

    float volumeBottomTank;
    float volumeUpTank; 

    float porcBottomTank;
    float porcUpTank;

    void setup() {
      lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
      pinMode(trigPin1, OUTPUT);
      pinMode(echoPin1, INPUT);
      pinMode(trigPin2, OUTPUT);
      pinMode(echoPin2, INPUT);
      Serial.begin (9600);     
    }
  
    void loop() {
      // Trigger Lower tank
      digitalWrite(trigPin1, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin1, LOW);
      duration1 = pulseIn(echoPin1, HIGH);
      deepBottomTankCm= duration1*0.034/2;

       // Trigger upper tank
      digitalWrite(trigPin2, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin2, LOW);
      duration2 = pulseIn(echoPin2, HIGH);
      deepUpTankCm= duration2*0.034/2;

      if (deepBottomTankCm > 0 && deepUpTankCm > 0) {
        // Make calculations based on volume1 and volume2
          volumeBottomTank = lengthBottomTankM * widthBottomTankM * (deepBottomTankM - (float)deepBottomTankCm/100);
       
          porcBottomTank = (float)volumeBottomTank/(float)volTotalBottomTankM3 * 100;   
   
          volumeBottomTank = round(volumeBottomTank*10);
          volumeBottomTank = volumeBottomTank/10;
 
          volumeUpTank = lengthUpTankM * widthUpTankM * (deepUpTankM - (float)deepUpTankCm/100);
          volumeUpTank = round(volumeUpTank*10);
          volumeUpTank = volumeUpTank/10;
          porcUpTank = (float)volumeUpTank / volTotalUpTankM3 * 100;

          Serial.println("cmBottom," + String(deepBottomTankCm) + "; cmUp," + String(deepUpTankCm));
 


        // Show information on LCD
        lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
        lcd.println("S: " + String(volumeUpTank) + "m3, "+ String(round(porcUpTank)) + "%       "); // Prints string "Distance" on the LCD
       //lcd.println("DistaCm: " + String(deepUpTankCm) + "      ");
       
        delay(10);

        lcd.setCursor(0,1);
        lcd.println("I: " + String(volumeBottomTank) + "m3, "+ String(round(porcBottomTank)) + "%       ");
      // lcd.println("DistCm: " + String(deepBottomTankCm) + "          ");
  
      }
      delay(500);
    }
