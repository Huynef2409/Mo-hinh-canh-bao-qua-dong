const int bienTro = A2;

const int ledXanh = 2;
const int ledDo = 3;
const int buzzer = 4;
const int relay = 5;

float nguongDong = 4.0; // Ngưỡng cảnh báo (A)

unsigned long lastPrint = 0;
const unsigned long printInterval = 4000; // 4giây

void setup()
{
  pinMode(ledXanh, OUTPUT);
  pinMode(ledDo, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);

  Serial.begin(9600);

  digitalWrite(ledXanh, HIGH);
  digitalWrite(ledDo, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(relay, LOW);
}

void loop()
{
  int giaTriADC = analogRead(bienTro);

  // Điện áp đọc từ biến trở
  float voltage = giaTriADC * 5.0 / 1023.0;

  // Giả lập dòng điện 0A -> 5A
  float current = voltage;

  String status;

  if (current > nguongDong)
  {
    digitalWrite(ledDo, HIGH);
    digitalWrite(ledXanh, LOW);
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);

    status = "OVERCURRENT";
  }
  else
  {
    digitalWrite(ledDo, LOW);
    digitalWrite(ledXanh, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);

    status = "NORMAL";
  }

  // Chỉ in sau mỗi 4 giây
  if (millis() - lastPrint >= printInterval)
  {
    lastPrint = millis();

    Serial.println("================================");

    Serial.print("ADC        : ");
    Serial.println(giaTriADC);

    Serial.print("VOLTAGE    : ");
    Serial.print(voltage, 2);
    Serial.println(" V");

    Serial.print("CURRENT    : ");
    Serial.print(current, 2);
    Serial.println(" A");

    Serial.print("THRESHOLD  : ");
    Serial.print(nguongDong, 2);
    Serial.println(" A");

    Serial.print("STATUS     : ");
    Serial.println(status);

    Serial.println("================================");
    Serial.println();
  }
}
