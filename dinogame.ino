#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 2;
int dinoY = 48;
bool jumping = false;
int jumpHeight = 0;
int cactusX = SCREEN_WIDTH;

void setup() {
  pinMode(buttonPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  if (digitalRead(buttonPin) == HIGH && !jumping) {
    jumping = true;
  }

  // Handle jump
  if (jumping) {
    if (jumpHeight < 20) {
      dinoY -= 2;
      jumpHeight += 2;
    } else {
      jumping = false;
    }
  } else if (dinoY < 48) {
    dinoY += 2;
    if (dinoY > 48) {
      dinoY = 48;
      jumpHeight = 0;
    }
  }

  // Move cactus
  cactusX -= 2;
  if (cactusX < 0) cactusX = SCREEN_WIDTH;

  // Check collision
  if (cactusX < 20 && dinoY > 40) {
    gameOver();
    return;
  }

  drawScene();
  delay(50);
}

void drawScene() {
  display.clearDisplay();
  // Ground
  display.drawLine(0, 63, SCREEN_WIDTH, 63, WHITE);
  // Dino
  display.fillRect(10, dinoY, 10, 15, WHITE);
  // Cactus
  display.fillRect(cactusX, 48, 5, 15, WHITE);
  display.display();
}

void gameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20, 30);
  display.println("Game Over");
  display.display();
  delay(2000);
  cactusX = SCREEN_WIDTH;
  dinoY = 48;
  jumpHeight = 0;
}
