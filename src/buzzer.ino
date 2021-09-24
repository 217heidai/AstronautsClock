extern void Beep(unsigned char num){
  Buzzer buzzer(1, 2);
  buzzer.begin(100);

  for(int i = 0; i < num; i++)
  {
    buzzer.sound(NOTE_E7, 80);
    buzzer.sound(0, 80);
  } 
  buzzer.end(0);
}

extern void Beep_SuperMario(void) {
  Buzzer buzzer(1, 2);
  buzzer.begin(100);

  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_G7, 80);
  buzzer.sound(0, 240);
  buzzer.sound(NOTE_G6, 80);
  buzzer.sound(0, 240);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_G6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_E6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_A6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_B6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_AS6, 80);
  buzzer.sound(NOTE_A6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_G6, 100);
  buzzer.sound(NOTE_E7, 100);
  buzzer.sound(NOTE_G7, 100);
  buzzer.sound(NOTE_A7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_F7, 80);
  buzzer.sound(NOTE_G7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(NOTE_D7, 80);
  buzzer.sound(NOTE_B6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_G6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_E6, 80);
  buzzer.sound(0, 160);
  buzzer.sound(NOTE_A6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_B6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_AS6, 80);
  buzzer.sound(NOTE_A6, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_G6, 100);
  buzzer.sound(NOTE_E7, 100);
  buzzer.sound(NOTE_G7, 100);
  buzzer.sound(NOTE_A7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_F7, 80);
  buzzer.sound(NOTE_G7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_E7, 80);
  buzzer.sound(0, 80);
  buzzer.sound(NOTE_C7, 80);
  buzzer.sound(NOTE_D7, 80);
  buzzer.sound(NOTE_B6, 80);
  buzzer.sound(0, 160);

  buzzer.end(0);
}

extern void Beep_StarWars(void){
  Buzzer buzzer(1, 2);
  buzzer.begin(10);

  buzzer.sound(NOTE_A3, 500); 
  buzzer.sound(NOTE_A3, 500);
  buzzer.sound(NOTE_A3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);

  buzzer.sound(NOTE_A3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_A3, 1000);

  buzzer.sound(NOTE_E4, 500); 
  buzzer.sound(NOTE_E4, 500);
  buzzer.sound(NOTE_E4, 500);
  buzzer.sound(NOTE_F4, 375);
  buzzer.sound(NOTE_C4, 125);

  buzzer.sound(NOTE_GS3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_A3, 1000);

  buzzer.sound(NOTE_A4, 500);
  buzzer.sound(NOTE_A3, 375);
  buzzer.sound(NOTE_A3, 125);
  buzzer.sound(NOTE_A4, 500);
  buzzer.sound(NOTE_GS4, 375);
  buzzer.sound(NOTE_G4, 125);

  buzzer.sound(NOTE_FS4, 125);
  buzzer.sound(NOTE_E4, 125);
  buzzer.sound(NOTE_F4, 250);
  buzzer.sound(0, 250);
  buzzer.sound(NOTE_AS3, 250);
  buzzer.sound(NOTE_DS4, 500);
  buzzer.sound(NOTE_D4, 375);
  buzzer.sound(NOTE_CS4, 125);

  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_B3, 125);
  buzzer.sound(NOTE_C4, 250);
  buzzer.sound(0, 250);
  buzzer.sound(NOTE_F3, 250);
  buzzer.sound(NOTE_GS3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_A3, 125);

  buzzer.sound(NOTE_C4, 500);
  buzzer.sound(NOTE_A3, 375);
  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_E4, 1000);

  buzzer.sound(NOTE_A4, 500);
  buzzer.sound(NOTE_A3, 375);
  buzzer.sound(NOTE_A3, 125);
  buzzer.sound(NOTE_A4, 500);
  buzzer.sound(NOTE_GS4, 375);
  buzzer.sound(NOTE_G4, 125);

  buzzer.sound(NOTE_FS4, 125);
  buzzer.sound(NOTE_E4, 125);
  buzzer.sound(NOTE_F4, 250);
  buzzer.sound(0, 250);
  buzzer.sound(NOTE_AS3, 250);
  buzzer.sound(NOTE_DS4, 500);
  buzzer.sound(NOTE_D4, 375);
  buzzer.sound(NOTE_CS4, 125);

  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_B3, 125);
  buzzer.sound(NOTE_C4, 250);
  buzzer.sound(0, 250);
  buzzer.sound(NOTE_F3, 250);
  buzzer.sound(NOTE_GS3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);

  buzzer.sound(NOTE_A3, 500);
  buzzer.sound(NOTE_F3, 375);
  buzzer.sound(NOTE_C4, 125);
  buzzer.sound(NOTE_A3, 1000);

  buzzer.end(0);
}

extern void Beep_JingleBells(void){
  Buzzer buzzer(1, 2);
  int time = 500;

  buzzer.begin(10);

  buzzer.sound(NOTE_G3, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_C4, time / 2);
  buzzer.sound(NOTE_G3, time * 2);
  
  buzzer.sound(NOTE_G3, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_C4, time / 2);
  buzzer.sound(NOTE_A4, time * 2);

  buzzer.sound(NOTE_A4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_G4, time);
  buzzer.sound(NOTE_G4, time);
  
  buzzer.sound(NOTE_A5, time / 2);
  buzzer.sound(NOTE_G4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_E4, time * 2);
  
  buzzer.sound(NOTE_G3, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_C4, time / 2);
  buzzer.sound(NOTE_G3, time * 2);
  
  buzzer.sound(NOTE_G3, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_C4, time / 2);
  buzzer.sound(NOTE_A4, time * 2);
  
  buzzer.sound(NOTE_A4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_G4, time / 2);
  buzzer.sound(NOTE_G4, time / 2);
  buzzer.sound(NOTE_G4, (time * 3) / 4);
  buzzer.sound(NOTE_G4, time / 4);
  
  buzzer.sound(NOTE_A5, time / 2);
  buzzer.sound(NOTE_G4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_C4, time * 2);

  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time);
  
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_G4, time / 2);
  buzzer.sound(NOTE_C4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_E4, time * 2);
  
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time / 4);
  buzzer.sound(NOTE_E4, time / 4);

  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_D4, time);
  buzzer.sound(NOTE_G4, time);

  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time);
  
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_G4, time / 2);
  buzzer.sound(NOTE_C4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_E4, time * 2);
  
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time / 2);
  buzzer.sound(NOTE_E4, time / 4);
  buzzer.sound(NOTE_E4, time / 4);
  
  buzzer.sound(NOTE_G4, time / 2);
  buzzer.sound(NOTE_G4, time / 2);
  buzzer.sound(NOTE_F4, time / 2);
  buzzer.sound(NOTE_D4, time / 2);
  buzzer.sound(NOTE_C4, time * 2);

  buzzer.end(0);
}
