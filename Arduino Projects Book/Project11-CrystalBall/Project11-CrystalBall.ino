
// Initialize the liquid crystal library with the numbers of the interface pins.
// The parameter order is (rs, enable, d4, d5, d6, d7).
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// We will read the status of the tilt switch on pin 6.
const int SWITCH_PIN = 6;
int switchState = 0;
int prevSwitchState = 0;

void setup() {

  // Set the switch pin as an input.
  pinMode(SWITCH_PIN, INPUT);

  // Specify the number of columns and rows on the LCD.
  lcd.begin(16, 2);

  // Print a message to the LCD. The setCursor() parameters are (col, row).
  lcd.print("Ask the");
  lcd.setCursor(2, 1);
  lcd.print("Crystal Ball!");
  
}

void loop() {
  
  // Check the status of the switch.
  switchState = digitalRead(SWITCH_PIN);

  // If the tilt-switch was just tripped...
  if ((prevSwitchState == HIGH) && (switchState == LOW)) {

    // Clean up the screen before printing a new reply.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("The ball says:");
    lcd.setCursor(2, 1);

    // Choose a random saying to print.
    switch (random(8)) {
      
      case 0:
        lcd.print("Yes!");
        break;

      case 1:
        lcd.print("Most likely.");
        break;

      case 2:
        lcd.print("Certainly!");
        break;

      case 3:
        lcd.print("Outlook good.");
        break;

      case 4:
        lcd.print("Unsure.");
        break;

      case 5:
        lcd.print("Ask again...");
        break;

      case 6:
        lcd.print("Doubtful.");
        break;

      case 7:
        lcd.print("No.");
        break;
        
    } // switch

  } // if
  
  // Set the switch case state for the next iteration.
  prevSwitchState = switchState;  
}
