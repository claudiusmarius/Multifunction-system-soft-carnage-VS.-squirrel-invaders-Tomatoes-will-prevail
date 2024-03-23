  //SqirrelInvaders
  //https://youtu.be/Xx6eqsZWyMc
  //https://www.youtube.com/c/ClaudeDufourmont
  //Seeeduino XIAO + AD9833 + PAM8403 + HC-SR501
  
  #include <SPI.h>
  #include <MD_AD9833.h>
  #include <Adafruit_NeoPixel.h>
  #define DATA  9 
  #define CLK   8  
  #define FSYNC1 10  
  #define DINEOPIXEL      7
  #define N_LEDS 8
  Adafruit_NeoPixel strip(N_LEDS, DINEOPIXEL, NEO_GRB + NEO_KHZ800);
  
  #define BrochePIR 6
  #define D2 2
  #define D3 3
  #define D4 4
  #define LED1 5
  #define D1 1
  
  MD_AD9833 AD(DATA, CLK, FSYNC1);

  bool ETATPIR ;
  bool ETATD2 ;
  bool ETATD3 ;
  bool ETATD4 ;
  int ANAD1;
  bool ETATANAD1;
  
  void setup() 
  { 
  pinMode(CLK, OUTPUT);    
  pinMode(DATA, OUTPUT);
  pinMode(FSYNC1, OUTPUT);
  
  pinMode(DINEOPIXEL, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  
  pinMode(BrochePIR, INPUT);
  pinMode(D1, INPUT);
  
  AD.begin();
  } 

  void loop() 
  { 
  ANAD1 = analogRead (D1);
  //if (ANAD1 < 100)                  //Pénombre
  if (ANAD1 > 200)                  //hors pénombre
  
  {
  ETATANAD1 = HIGH;
  }
  else
  {
  ETATANAD1 = LOW;   
  }
  ETATPIR = digitalRead(BrochePIR);
  ETATD2 =  !digitalRead(D2);
  ETATD3 =  !digitalRead(D3);
  ETATD4 =  !digitalRead(D4);

  if (ETATPIR && ETATD4 == HIGH)
  {
  digitalWrite (LED1, HIGH);
  Chenillard ();
  }
    
  //if (ETATPIR  == HIGH)
  //if (ETATPIR  == HIGH && ETATD3== HIGH)// PIR détection + D3 strappé à zéro (AUTORISATION PIR)
  //if (ETATPIR  == HIGH && ETATD3 == HIGH && ETATANAD1 == HIGH) //PIR détection + D3 strappé à zéro (AUTORISATION PIR)+ Pas de pénombre
  if (ETATPIR  == HIGH && ETATD3 == HIGH && ETATANAD1 == HIGH) //PIR détection + D3 strappé à zéro (AUTORISATION PIR)+ Pas de pénombre

  // ----------------------- NOTA : POUR L'INSTANT D2 N'EST PAS UTILISE -----------------------------------------------------------------
  
  {
  digitalWrite (LED1, HIGH);
 
  bonusRoundSound();
  gameOverSound();                             
  bonusRoundSound();
  missileApproachSound03();
  }
  else
  {
  AD.setMode(MD_AD9833::MODE_OFF); 
  digitalWrite (LED1, LOW);
  }
  }
  
  void missileApproachSound03() 
  {
  AD.setMode(MD_AD9833::MODE_TRIANGLE);
  const float baseFreq = 400.0;
  const float maxFreqChange = 800.0;
  const unsigned long duration = 5000;
  const unsigned long approachDuration = duration / 2;

  unsigned long startTime = millis();
  while (millis() - startTime < duration) 
  {
  unsigned long elapsedTime = millis() - startTime;
  float freqChange = maxFreqChange * ((float)elapsedTime / approachDuration);
  float freq = baseFreq + freqChange;
  AD.setFrequency(MD_AD9833::CHAN_0, freq);
  delay(10);
  }
  AD.setMode(MD_AD9833::MODE_OFF);
  ETATPIR == LOW;
  }

  void gameOverSound() {
  AD.setMode(MD_AD9833::MODE_TRIANGLE);
  const float startFreq = 2000.0;
  const float endFreq = 300.0;
  const unsigned long rampDuration = 1000;

  for (float freq = startFreq; freq >= endFreq; freq -= 20.0) 
  {
  AD.setFrequency(MD_AD9833::CHAN_0, freq);
  delay(rampDuration / ((startFreq - endFreq) / 20.0));
  }
  AD.setMode(MD_AD9833::MODE_OFF);
  }

  void bonusRoundSound() 
  {
  AD.setMode(MD_AD9833::MODE_SQUARE1);
  const float centerFreq = 1000.0;
  const float modulationFreq = 20.0;
  const float modulationDepth = 500.0;
  const unsigned long duration = 400;

  for (unsigned long startTime = millis(); millis() - startTime < duration; ) 
  {
  float freq = centerFreq + modulationDepth * sin(2 * PI * modulationFreq * (millis() - startTime) / 1000.0);
  AD.setFrequency(MD_AD9833::CHAN_0, freq);
  }
  AD.setMode(MD_AD9833::MODE_OFF);
  }

  void Chenillard ()
  {
  int nombre = 15;
  
  for (int j =0; j <nombre; j++)
  {
  ChenillardRouge ();
  }
  
  for (int j =0; j <nombre; j++)
  {
  ChenillardVert ();
  }

  for (int j =0; j <nombre; j++)
  {
  ChenillardBleu ();
  }
  delay(1);
  
  for (int j =0; j <nombre; j++)
  {
  ChenillardRouge ();
  }
  
  for (int j =0; j <nombre; j++)
  {
  ChenillardVert ();
  }

  for (int j =0; j <nombre; j++)
  {
  ChenillardBleu ();
  }
  
  }
  
  void ChenillardRouge ()
  {
  
  for (int i = 0; i <= N_LEDS -1; i++) 
  {
  strip.setPixelColor(i, 255, 0, 0);
  strip.show ();
  }
  strip.clear ();
  strip.show();
  digitalWrite (LED1, LOW);
  }

  void ChenillardVert ()
  {
  
  for (int i = 0; i <= N_LEDS -1; i++) 
  {
  strip.setPixelColor(i, 0, 255, 0);
  strip.show ();
  }
  strip.clear ();
  strip.show();
  digitalWrite (LED1, LOW);
  }

  void ChenillardBleu ()
  {
  
  for (int i = 0; i <= N_LEDS -1; i++) 
  {
  strip.setPixelColor(i, 0, 0, 255);
  strip.show ();
  }
  strip.clear ();
  strip.show();
  digitalWrite (LED1, LOW);
  }

  
