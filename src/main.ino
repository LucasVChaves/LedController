#include <OneButton.h>
#include <FastLED.h>

#define NUM_LEDS 60
#define PIN 7
#define BUTTON_PIN 2

CRGB leds[NUM_LEDS];

uint8_t hue = 0;
uint8_t paletteIndex = 0;
uint16_t patternCounter = 0;

OneButton button = OneButton(BUTTON_PIN, true, true);

DEFINE_GRADIENT_PALETTE(fire_gp){
     0, 0, 0, 0,           //Preto 
     100, 255, 0, 0,      //Vermelho
     200, 255, 255, 0,   //Amarelo
     255, 255, 255, 255 //Branco
};

DEFINE_GRADIENT_PALETTE(water_gp){
     0, 8, 126, 225,        //Azul
     127, 250, 250, 250,   //Branco
     200, 5, 232, 186,    //Aqua
     255, 79, 221, 221   //Ciano
};


DEFINE_GRADIENT_PALETTE(blueToRed_gp) {
     0,0,0,255,            //Azul
     127,250,250,250,     //Branco
     200, 200, 200, 200, //Cinza claro
     255,255,0,0        //Vermelho
};

CRGBPalette16 firePalette = fire_gp;
CRGBPalette16 waterPalette = water_gp;
CRGBPalette16 blueToRedPalette = blueToRed_gp;

void setup() {
     FastLED.addLeds<WS2812B, PIN, RGB>(leds, NUM_LEDS);
     FastLED.setBrightness(127); //0-255
     FastLED.clear();
     Serial.begin(57600);
     button.attachClick(nextPattern);
}

void loop() {

     switch(patternCounter){
      case 0:
          //Cor Solida
          fill_solid(leds, NUM_LEDS, CRGB::Azure);
          Serial.println(patternCounter);
          break;
     case 1:
          //Arco iris entre o intervalo
          fill_rainbow(leds, NUM_LEDS, 0, 255 / NUM_LEDS);
          Serial.println(patternCounter);
          break;
     case 2:
          //Unico led se movendo de um lado ao outro
          //ledMoving();
          Serial.println(patternCounter);
          break;
     case 3:
          //Fade rapido
          //ledFadeFast();
          Serial.println(patternCounter);
          break;
     case 4:
          //Fade lento
          //ledFadeSlow();
          Serial.println(patternCounter);
          break;
     case 5:
          //Flicker aleatorio
          //ledRandFlicker();
          Serial.println(patternCounter);
          break;
     case 6:
          //Cores aleatoria em leds aleatorios
          //ledRand();
          Serial.println(patternCounter);
          break;
     case 7:
          //Fade com paleta de cores (fogo)
          //paletteLoopFire();
          Serial.println(patternCounter);
          break;
     case 8:
          //Fade com paleta de cores (agua)
          //paletteLoopWater();
          Serial.println(patternCounter);
          break;
     case 9:
          //Fade com paleta de cores (azul -> vermelho)
          //paletteLoopBlueToRed();
          Serial.println(patternCounter);
          break;
        
     }
     
     FastLED.show(); //Liga o strip
     button.tick();
}

void nextPattern(){
  patternCounter = (patternCounter + 1) % 9; //Mudar numero de patterns depois do %
}

void ledMoving(){
     for (int i = 0; i < NUM_LEDS; i++){
          leds[i] = CRGB::BlueViolet;
          delay(100);
          leds[i] = CRGB::Black;
     }
     for (int i = NUM_LEDS; i >= 0; i--){
          leds[i] = CRGB::Goldenrod;
          delay(100);
          leds[i] = CRGB::Black;
     }
}

void ledRand(){
     for (int i = 0; i < NUM_LEDS; i++){
          leds[i] = CHSV(random8(0, 255), random8(0, 255), random8(125, 255));
          delay(50);
          leds[i] = CRGB::Black;
     }
     
}

void ledFadeFast(){
     for (int i = 0; i < NUM_LEDS; i++){
          leds[i] = CHSV(hue + (i * 10), 255, 255);
     }
     
     EVERY_N_MILLISECONDS(10){
          hue++;
     }
}

void ledFadeSlow(){
     for (int i = 0; i < NUM_LEDS; i++){
          leds[i] = CHSV(hue + (i * 10), 255, 255);
     }
     
     EVERY_N_MILLISECONDS(50){
          hue++;
     }
}

void ledRandFlicker(){
     EVERY_N_MILLISECONDS(60){
          leds[0] = CHSV(random8(0, 255), random8(0, 255), random8(100, 255));

          for (int i = 0; i < NUM_LEDS; i++){
               leds[i] = leds[i - 1];
          }
          
     }
}

void paletteLoopFire(){
     fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, firePalette, 255, LINEARBLEND);

     EVERY_N_MILLISECONDS(25){
          paletteIndex++;
     }
}

void paletteLoopWater(){
     fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, waterPalette, 255, LINEARBLEND);

     EVERY_N_MILLISECONDS(25){
          paletteIndex++;
     }
}

void paletteLoopBlueToRed(){
     fill_palette(leds, NUM_LEDS, paletteIndex, 255 / NUM_LEDS, blueToRedPalette, 255, LINEARBLEND);

     EVERY_N_MILLISECONDS(25){
          paletteIndex++;
     }
}
