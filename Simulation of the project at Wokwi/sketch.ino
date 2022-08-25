#include <DHT.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include "Predict_Water_Percentage.h"
 
LiquidCrystal_I2C lcd(0x27,16,2); 

#define DHTPIN1 7 
#define DHTPIN2 5
#define DHTPIN3 6
#define DHTPIN4 4
#define Day_Night_Sensor A0

DHT dht[] = {{DHTPIN1, DHT22},{DHTPIN2, DHT22},{DHTPIN3, DHT22},{DHTPIN4, DHT22},};

float humidity[4] = {0,0,0,0},H_temp[4];
float temperature[4] = {0,0,0,0},T_temp[4];
int water_percent[4] = {0,0,0,0},W_temp[4];
int flag = 1;

const float GAMMA = 0.7;
const float RL10 = 50;

Servo servo[4]; 

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
  for (auto& sensor : dht) 
  {
    sensor.begin();
  }
  pinMode(Day_Night_Sensor, INPUT);

  servo[0].attach(10);
  servo[1].attach(9);
  servo[2].attach(11);
  servo[3].attach(8);

  lcd.setCursor(0,0);
  lcd.print("1.");
  lcd.setCursor(9,0);
  lcd.print("2.");
  lcd.setCursor(0,1);
  lcd.print("3.");
  lcd.setCursor(9,1);
  lcd.print("4.");
}

void read_temp_humid()
{
  for (int i = 0; i < 4; i++) 
  {
    T_temp[i] = dht[i].readTemperature();
    H_temp[i] = dht[i].readHumidity();
  }
} 

int  predict_water(float temp, float humid)
{
  float water_percent = 0;
  water_percent = predict_water_percentage(humid,temp);
  water_percent = water_percent * 100;
  int percent = int(water_percent);
  return percent;
}

void Change_Water_Flow(int percentage, int pos)
{
  float change = percentage * 0.01;
  int mov = 180 * change;
  servo[pos].write(mov);
  write_Percent_lcd(pos);
}

void Erase_LCD(int pos)
{
  switch (pos)
  {
    case 0: 
    {
      lcd.setCursor(3,0);
	    lcd.print("    ");
      break;
    }
    case 1: 
    {
      lcd.setCursor(12,0);
	    lcd.print("    ");
      break;
      break;
    }
    case 2: 
    {
      lcd.setCursor(3,1);
	    lcd.print("    ");
      break;
    }
    case 3: 
    {
     lcd.setCursor(12,1);
	    lcd.print("    ");
      break;
    }
}
}
void write_Percent_lcd(int pos)
{
  switch (pos)
  {
    case 0: 
    {
      Erase_LCD(pos);
      lcd.setCursor(3,0);
	    lcd.print(water_percent[0]);
      lcd.print("%");
      break;
    }
    case 1: 
    {
      Erase_LCD(pos);
      lcd.setCursor(12,0);
	    lcd.print(water_percent[1]);
      lcd.print("%");
      break;
    }
    case 2: 
    {
      Erase_LCD(pos);
      lcd.setCursor(3,1);
	    lcd.print(water_percent[2]);
      lcd.print("%");
      break;
    }
    case 3: 
    {
      Erase_LCD(pos);
      lcd.setCursor(12,1);
	    lcd.print(water_percent[3]);
      lcd.print("%");
      break;
    }
}
}

void Stop_Water_Flow()
{
  for(int i = 0; i < 4; i++)
  {
    servo[i].write(0);
    temperature[i]   = 0;
    humidity[i]      = 0;
    water_percent[i] = 0;
    write_Percent_lcd(i);
  }
}
int Day()
{
  int analogValue = analogRead(Day_Night_Sensor);
  float voltage = analogValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
  if (lux > 50)  
    return 1;
  else 
    return 0;
}
void loop()
{
  if (Day()) 
   {
      read_temp_humid();
      for(int i = 0 ; i < 4 ; i++)
      {
        if(T_temp[i] != temperature[i] || H_temp[i] != humidity[i])
        {
          temperature[i] = T_temp[i]; humidity[i] = H_temp[i];
          W_temp[i] = predict_water(temperature[i], humidity[i]);
        } 
      }
      for(int i = 0 ; i < 4 ; i++)
      {
        if(W_temp[i] != water_percent[i])
        {
          water_percent[i] = W_temp[i];          
          Change_Water_Flow(water_percent[i], i); // For changing water flow percentage
        } 
      }
      flag = 1;    
    } 
  else 
  {
    if(flag == 1)
    {
      flag = 0;
      Stop_Water_Flow();
    }
  }
}