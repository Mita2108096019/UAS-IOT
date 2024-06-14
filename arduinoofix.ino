// Menyertakan pustaka untuk mengendalikan LCD dan sensor ultrasonik..
#include <LiquidCrystal.h>
#include <NewPing.h>

// Mendefinisikan pin yang terhubung dengan trigger dan echo dari sensor ultrasonik.
#define TRIGGER_PIN 13
#define ECHO_PIN 12

//Membuat objek ultrasonic1 & lcd
NewPing ultrasonicl (TRIGGER_PIN, ECHO_PIN);
LiquidCrystal lcd(11,10,9,8,7,6);

//Mendefinisikan pin yang terhubung dengan LED indikator
#define ledaman 2
#define led1 3
#define led2 4
#define led3 5

//pendefisian variabel
int z = 0;
int y = 500;
long distance;

//setup dijalankan sekali ketika Arduino dinyalakan atau di-reset. 
//Fungsi ini digunakan untuk menginisialisasi perangkat keras dan menyiapkan kondisi awal untuk program
void setup() {
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Mita Pramesti");
  lcd.setCursor(0,1);
  lcd.print("2108096019");
  delay(200);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pengukuran");
  lcd.setCursor(0,1);
  lcd.print("Ketinggian Air");
  Serial.begin (9600);
  pinMode (ledaman, OUTPUT);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  delay (700);
  lcd.clear(); 
}

//loop dijalankan berulang kali selama Arduino hidup. 
//ketinggian air akan terus diukur dan hasilnya ditampilkan di LCD serta diindikasi oleh LED yang sesuai.
//Fungsi ini mengandung logika utama dari program yang akan dijalankan secara terus-menerus.
void loop() {
  delay(100);
  double distance = ultrasonicl.ping_cm();
  Serial.print("Hasil Sensor :");
  Serial.print(distance);
  Serial.print("cm");
  Serial.print(" ");
  z = y - distance; //Menghitung ketinggian air (z) dengan mengurangi jarak yang diukur dari nilai referensi y
  lcd.setCursor(0,0); lcd.print ("Ketinggian Air");
  lcd.setCursor(0,1); lcd.print ("Tinggi :");lcd.print(z);
  lcd.setCursor(14,1); lcd.print ("Cm");
  
  //ledaman menyala jika ketinggian air antara 0-200 cm
  if ((z <= 200) && (z > 0)) {
    digitalWrite(ledaman, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay (300);
  }
  //ledwaspada menyala jika ketinggian air antara 201-350 cm
  if ((z <= 350) && (z > 200)) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(ledaman, LOW);
    delay (300);
  }
  //ledsiaga menyala jika ketinggian air antara 351-450 cm
  if ((z <= 450) && (z > 350)) {
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(ledaman, LOW);
    delay (300);
  }
  //dan ledbahaya menyala jika ketinggian air lebih dari 450 cm
  if (z > 450) {
    digitalWrite(led3, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(ledaman, LOW);
    delay (300);
  }
}
 