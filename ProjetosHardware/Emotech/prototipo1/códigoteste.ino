#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LARGURA_TELA 128 
#define ALTURA_TELA 64   
#define OLED_RESET -1 

Adafruit_SSD1306 display(LARGURA_TELA, ALTURA_TELA, &Wire, OLED_RESET);

// Pinos dos botões (todos do lado direito)
const int btnFeliz = 19;
const int btnTriste = 18;
const int btnNeutro = 5;

// Variáveis do Debounce
unsigned long tempoUltimoFeliz = 0;
unsigned long tempoUltimoTriste = 0;
unsigned long tempoUltimoNeutro = 0;
const unsigned long atrasoDebounce = 50; 

int ultimoEstadoFeliz = HIGH;
int ultimoEstadoTriste = HIGH;
int ultimoEstadoNeutro = HIGH;

int telaAtual = 0; 

void setup() {
  pinMode(btnFeliz, INPUT_PULLUP);
  pinMode(btnTriste, INPUT_PULLUP);
  pinMode(btnNeutro, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); 
  }

  display.setTextColor(SSD1306_WHITE); 
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 28);
  display.print("Pronto para texto");
  display.display();
}

void loop() {
  int leituraFeliz = digitalRead(btnFeliz);
  int leituraTriste = digitalRead(btnTriste);
  int leituraNeutro = digitalRead(btnNeutro);

  // --- Debounce Feliz ---
  if (leituraFeliz != ultimoEstadoFeliz) tempoUltimoFeliz = millis();
  if ((millis() - tempoUltimoFeliz) > atrasoDebounce) {
    if (leituraFeliz == LOW && telaAtual != 1) {
      imprimirTextoCentralizado("FELIZ");
      telaAtual = 1;
    }
  }

  // --- Debounce Triste ---
  if (leituraTriste != ultimoEstadoTriste) tempoUltimoTriste = millis();
  if ((millis() - tempoUltimoTriste) > atrasoDebounce) {
    if (leituraTriste == LOW && telaAtual != 2) {
      imprimirTextoCentralizado("TRISTE");
      telaAtual = 2;
    }
  }

  // --- Debounce Neutro ---
  if (leituraNeutro != ultimoEstadoNeutro) tempoUltimoNeutro = millis();
  if ((millis() - tempoUltimoNeutro) > atrasoDebounce) {
    if (leituraNeutro == LOW && telaAtual != 3) {
      imprimirTextoCentralizado("NEUTRO");
      telaAtual = 3;
    }
  }

  ultimoEstadoFeliz = leituraFeliz;
  ultimoEstadoTriste = leituraTriste;
  ultimoEstadoNeutro = leituraNeutro;
}

void imprimirTextoCentralizado(String texto) {
  display.clearDisplay(); 
  display.setTextSize(3); 
  
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(texto, 0, 0, &x1, &y1, &w, &h);
  
  display.setCursor((LARGURA_TELA - w) / 2, (ALTURA_TELA - h) / 2);
  display.print(texto);
  display.display(); 
}
