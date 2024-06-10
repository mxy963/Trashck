#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// WiFi bilgileri
const char* ssid = "Neom";
const char* password = "12345678";

// Web sunucusu oluştur
ESP8266WebServer server(80);

#define TRIG_PIN D2   // NodeMCU 4 pinine
#define ECHO_PIN D0   // NodeMCU 16 pinine
#define GREEN_LED D3  // NodeMCU 0 pinine
#define RED_LED D4    // NodeMCU 2 pinine

int referenceDistance = 0;    // Başlangıçta 0 olarak ayarlanır
const int MAX_PERCENT = 100;  // Maksimum yüzde

void setup() {
  Serial.begin(115200);        // Seri iletişim başlatılır
  pinMode(TRIG_PIN, OUTPUT);   // TRIG_PIN çıkış olarak ayarlanır
  pinMode(ECHO_PIN, INPUT);    // ECHO_PIN giriş olarak ayarlanır
  pinMode(RED_LED, OUTPUT);    // Kırmızı LED çıkış olarak ayarlanır
  pinMode(GREEN_LED, OUTPUT);  // Yeşil LED çıkış olarak ayarlanır

  // WiFi bağlantısı başlatılır
  WiFi.begin(ssid, password);
  Serial.print("WiFi'ye bağlanılıyor..");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Bağlandı!");

  // mDNS başlatılır
  if (MDNS.begin("iot")) {  // Cihaz adını "iot" olarak ayarlayın
    Serial.println("mDNS başlatıldı. http://iot.local olarak erişebilirsiniz.");
  } else {
    Serial.println("mDNS başlatılamadı.");
  }

  // Web sunucusu başlatılır
  server.on("/", handleRoot);  // Ana sayfa isteği geldiğinde handleRoot fonksiyonu çalıştırılır
  server.begin();
  Serial.println("Web Sunucusu Başlatıldı!");

  // Başlangıçta referans mesafeyi ölç
  referenceDistance = measureDistance();
}

void loop() {
  // Web sunucusu isteklerini işle
  server.handleClient();
  MDNS.update();  // mDNS güncellemelerini yönet

  // Mesafe ölçülür
  int distance = measureDistance();

  // Mesafenin yüzde cinsinden oranını hesapla
  int percent = 0;
  if (distance <= 20) {
    percent = -(map(distance, referenceDistance, 0, MAX_PERCENT, 0) - MAX_PERCENT);
    percent = constrain(percent, 0, MAX_PERCENT);
  }

  // Kırmızı LED'i açık, yeşil LED'i kapalı yap
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);

  // Eğer yüzde ışığındaki mesafe belirli bir eşiği geçerse, LED'leri tersine çevir
  if (percent >= 70) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }

  // Seri porta yazdır
  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.print(" cm, Yüzde: ");
  Serial.print(percent);
  Serial.println("%");

  delay(1000);  // 1 saniye beklenir
}

// Mesafe ölçen fonksiyon
int measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// Ana sayfa isteği işlendiğinde çağrılan fonksiyon
void handleRoot() {
  int distance = measureDistance();
  int percent = 0;
  if (distance < 20) {
    percent = -(map(distance, referenceDistance, 0, MAX_PERCENT, 0) - MAX_PERCENT);
    percent = constrain(percent, 0, MAX_PERCENT);
  }

  // İkon rengi belirlenir
  String iconColor = "green";  // Varsayılan olarak yeşil

  if (percent >= 70) {
    iconColor = "red";  // Doluluk oranı %70'in üstündeyse kırmızı
  } else if (percent >= 40) {
    iconColor = "yellow";  // Doluluk oranı %40 ile %70 arasındaysa sarı
  }

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta http-equiv='refresh' content='2'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>IoT</title>";
  html += "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.0.0-beta3/css/all.min.css'>";  // Font Awesome eklenmesi
  html += "<style>body {font-family: Ubuntu, sans-serif; background-color: gray; text-align: center; display: flex; flex-direction: column; justify-content: center; align-items: center; height: 100vh; margin: 0;}";
  html += "h1 {color: #333333; margin-top: 10px; margin-bottom: 10px;} p {font-size: 25px; color: white; margin: 10px 0;} .icon {font-size: 100px; color: " + iconColor + "; margin-top: 10px; margin-bottom: 10px;}";

  // Telefon için ek düzenleme
  html += "@media (max-width: 768px) {";
  html += "h1 {font-size: 24px;} p {font-size: 18px;}}";
  html += "</style></head><body>";
  html += "<h1>Çöp Kutusu İzleme Sistemi</h1>";                    // Başlık eklendi
  html += "<p class='icon'><i class='fas fa-trash-alt'></i></p>";  // Çöp kutusu ikonu eklendi

  html += "<p><strong>Doluluk Oranı:</strong> " + String(percent) + "%</p>";
  html += "<br><p><strong>Muhammed Yusufoğlu</strong><br>215260610</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}
