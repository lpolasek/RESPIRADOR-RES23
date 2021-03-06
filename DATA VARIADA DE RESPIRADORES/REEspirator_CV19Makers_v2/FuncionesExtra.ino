void inicializarPantalla() {
  //Byte para crear el icono flecha
  byte Flecha[] = {
    B00000,
    B00100,
    B01100,
    B11111,
    B11111,
    B01100,
    B00100,
    B00000
  };

  byte Cruz[] = {
    B00000,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110,
    B01110,
    B00000
  };
  
  // Inicializar el LCD
//  lcd.init();
  //Creamos el icono flecha
  lcd.createChar(0, Flecha);
  lcd.createChar(1, Cruz);
  //Encender la luz de fondo.
  lcd.backlight();
}

void escribirPantalla(int rpm, float vol, int posMenu, int caracter) {
  // Escribimos el Mensaje en el LCD.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Freq:    rpm");
  lcd.setCursor(6, 0);
  lcd.print(rpm);
  lcd.setCursor(0, 1);
  lcd.print("Vol:      L/r");
  lcd.setCursor(5, 1);
  lcd.print(vol);
  lcd.setCursor(15, posMenu);
  lcd.write(caracter);

}

void actualizarMenu() {
  tecla = encoder1.leerEncoder();
  switch (tecla) {
    case 2: //Giramos horario (Bajamos en el menu)
      if (posMenu == 0 && !editandoMenu) {
        posMenu++;
        escribirPantalla(rpm, vol, posMenu, 0);
      } else if (posMenu == 0 && editandoMenu) {
        rpm++;
        escribirPantalla(rpm, vol, posMenu, 1);
      } else if (posMenu == 1 && editandoMenu) {
        vol = vol + 0.1;
        escribirPantalla(rpm, vol, posMenu, 1);
      }
      break;

    case 8: //Giramos antihorario (Subimos en el menu)
      if (posMenu == 1 && !editandoMenu) {
        posMenu--;
        escribirPantalla(rpm, vol, posMenu, 0);
      } else if (posMenu == 1 && editandoMenu) {
        if (vol >= 0.1) {
          vol = vol - 0.1;
          escribirPantalla(rpm, vol, posMenu, 1);
        }
      } else if (posMenu == 0 && editandoMenu) {
        if (rpm >= 1) {
          rpm --;
          escribirPantalla(rpm, vol, posMenu, 1);
        }
      }
      break;

    case 5: //Pulsamos (Modificamos valor)
      editandoMenu = !editandoMenu;
      if (editandoMenu == true) {
        escribirPantalla(rpm, vol, posMenu, 1);
      } else {
        escribirPantalla(rpm, vol, posMenu, 0);
      }
      break;

    default:
      break;
  }
}

void enableMotor ()
{
  digitalWrite(ENpin, HIGH);
}

void disableMotor ()
{
  digitalWrite(ENpin, LOW);
}
