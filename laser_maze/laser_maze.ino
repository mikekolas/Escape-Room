#include <LiquidCrystal.h>

#define EASY 6
#define MEDIUM 4
#define HARD 2

LiquidCrystal lcd(12,13,4,5,6,7);
//digital sensors
const int rl = 2;
const int yl = 11;
const int gl = 0;

const int buzzer = 3;

const int rb = 10;
const int yb = 9;
const int gb = 8;

//Analog sensors
const int ph1 = A0;
const int ph2 = A1;
const int ph3 = A2;


void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);

  pinMode(rb, INPUT);
  pinMode(yb, INPUT);
  pinMode(gb, INPUT);

  pinMode(rl, OUTPUT);
  pinMode(yl, OUTPUT);
  pinMode(gl, OUTPUT);
  digitalWrite(rl, LOW);
  digitalWrite(yl, LOW);
  digitalWrite(gl, LOW);

  pinMode(buzzer, OUTPUT);

  delay(500);

  pinMode(ph1, INPUT);
  pinMode(ph2, INPUT);
  pinMode(ph3, INPUT);

  lcd.setCursor(0,0);
  lcd.print("Loading");

  digitalWrite(gl, HIGH);
  delay(1000);
  digitalWrite(yl, HIGH);
  delay(1000);
  digitalWrite(rl, HIGH);
  delay(1000);


  lcd.clear();
}

void loop() {
  //print choose difficulty
  int lives = 0;
  bool result = false;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("EN: Choose level");
  lcd.setCursor(0,1);
  lcd.print("GR: Epipedo");

  Serial.print(analogRead(ph1));
  Serial.print(" ");
  Serial.print(analogRead(ph2));
  Serial.print(" ");
  Serial.println(analogRead(ph3));
  delay(100);
  if(digitalRead(gb) == HIGH) //easy
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EN: Beginner");
    lcd.setCursor(0,1);
    lcd.print("GR: Arxarios");
    lives = EASY;
    result = game(lives);
  }
  if(digitalRead(yb) == HIGH) //medium
  {
    Serial.println(digitalRead(yb));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EN: Tricky");
    lcd.setCursor(0,1);
    lcd.print("GR: Metrio");
    lives = MEDIUM;
    result = game(lives);
  }
  if(digitalRead(rb) == HIGH) //hard
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EN: Hardcore");
    lcd.setCursor(0,1);
    lcd.print("GR: Diskolo");
    lives = HARD;
    result = game(lives);
  }

  if(result == true)
  {
    //buzzer
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EN: You lose");
    lcd.setCursor(0,1);
    lcd.print("GR: Exases");
    tone(3, 900, 2000);
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EN: New game");
    lcd.setCursor(0,1);
    lcd.print("GR: Neo paixnidi");
    delay(2000);
  }
}

bool game(int l)
{
  while(l > 0)
  {
    Serial.println("In game");
    int phr1 = analogRead(ph1);
    int phr2 = analogRead(ph2);
    int phr3 = analogRead(ph3);
    if(phr1 < 700 || phr2 < 700 || phr3 < 700)
    {
      l = l - 1;
      delay(1500);
    }
  }
  return true;
}
