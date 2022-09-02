#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define SS_PIN 10
#define RST_PIN 9
Servo s; 
#include <ArduinoJson.h>
const int TAMANHO = 42;  //define o tamanho do buffer para o json
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
char st[20];
void setup()
{
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522                                //Inicia o leitor
  s.attach(7);                                    //Anexa o servo-motor ao pino 4
  s.write(0);                                     //Inicia o motor na posição 0
}
void loop()
{
  String id = "";
    StaticJsonDocument<TAMANHO> json; //Aloca buffer para objeto json
 // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
/*
  id = le_cartao(); 
*/                                               //Chama a função para ler a uid   
/*
  String le_cartao() {  
  String _id = "";                                //Cria a variável "_id"
  for (byte i = 0; i < 4; i++) {                  //Loop for para percorrer os caracteres lidos, seguindo o formato proposto
    _id += (mfrc522.uid.uidByte[i] < 0x10 ? "0" : "") + String(mfrc522.uid.uidByte[i], HEX) + (i!=3 ? ":" : "");
  }
 }
*/
  //Mostra UID na seria
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    // Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    // Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
 conteudo.toUpperCase();
  if (conteudo.substring(1) == "89 AA 07 98")
  {
    Serial.println("Acesso permitido");           //Imprime a mensagem
    s.write(90);                                  //Gira o motor a 90°
    delay(5000);                                  //Delay de 1 segundo
    s.write(0);                                   //Retorna para a posição de 0°
    //formato de escrita do json
  json["tagID"]= conteudo;
 serializeJson(json, Serial);
  Serial.println();
 //delay
  delay(500);
  }
}
