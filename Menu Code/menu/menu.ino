
#include <U8glib.h>

#define outputA 46
#define outputB 47
#define confirmButton 12

int counter = 0;
int aState;
int aLastState;
int menuOption = 0;
bool inSubMenu = false; 

U8GLIB_ST7920_128X64_1X u8g(51, 52, 53, 6); 

void drawMenu();
void drawSubMenu();
void handleEncoder();
void handleConfirmButton();

void setup() {
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(confirmButton, INPUT_PULLUP);
  Serial.begin(9600);
  aLastState = digitalRead(outputA);
  u8g.setFont(u8g_font_unifont);
}

void loop() {
  handleEncoder();
  handleConfirmButton();
  if (inSubMenu) {
    drawSubMenu();
  } else {
    drawMenu();
  }
}

void drawMenu() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_5x7); 

    
    u8g.drawStr(10, 10, "V 1.8");

    
    u8g.drawLine(0, 14, 127, 14);
    u8g.drawLine(0, 0, 127, 0);
    u8g.drawLine(0, 0, 0, 64);
    u8g.drawLine(0, 63, 127, 63);
    u8g.drawLine(127, 0, 127, 63);

    
    switch (menuOption) {
      case 0:
        u8g.drawStr(5, 25, "> Option 1");
        u8g.drawStr(5, 35, "  Option 2");
        break;
      case 1:
        u8g.drawStr(5, 25, "  Option 1");
        u8g.drawStr(5, 35, "> Option 2");
        break;
      default:
        break;
    }
  } while (u8g.nextPage());
}

void drawSubMenu() {
  u8g.firstPage();
  do {
    u8g.setFont(u8g_font_5x7); 

    
    u8g.drawStr(10, 10, "Submenu");

    
    u8g.drawLine(0, 14, 127, 14);
    u8g.drawLine(0, 0, 127, 0);
    u8g.drawLine(0, 0, 0, 64);
    u8g.drawLine(0, 63, 127, 63);
    u8g.drawLine(127, 0, 127, 63);

    
    u8g.drawStr(10, 25, "This is Option 1");
    u8g.drawStr(10, 35, "Submenu Example");
    u8g.drawStr(10, 50, "Back to Main Menu");
  } while (u8g.nextPage());
}

void handleEncoder() {
  aState = digitalRead(outputA);
  if (aState != aLastState) {
    if (digitalRead(outputB) != aState) {
      counter++;
    } else {
      counter--;
    }

    if (counter > 1) {
      counter = 0;
    } else if (counter < 0) {
      counter = 1;
    }

    if (counter != menuOption) {
      menuOption = counter;
      Serial.print("Selected Option: ");
      Serial.println(menuOption);

      if (inSubMenu) {
        inSubMenu = false; 
      }
    }
  }
  aLastState = aState;
}

void handleConfirmButton() {
  if (digitalRead(confirmButton) == LOW) {
   
    switch (menuOption) {
      case 0:
        if (inSubMenu) {
          
          Serial.println("Submenu Option 1 selected!");
        } else {
         
          inSubMenu = true;
        }
        break;
      case 1:
        
        Serial.println("Option 2 confirmed!");
        break;
      default:
        break;
    }
    delay(200); 
  }
}
