#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

//* tong so hang
const byte Row = 4;
//* tong so cot
const byte Col = 4;

char keyLY[Row][Col] =
{
  //* giao dien ban phim
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowP[Row] = {6, 7, 8, 9};      //* chan cam theo hang
byte colP[Col] = {10, 11, 12, 13};  //* chan cam theo cot

//* khai bao man hinh lcd voi
//* lcd(rs, e, D4, D5, D6, D7)
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

//* khai bao ban phim voi
/*
  Keypad
  (
    * thiet lap lai gia tri tra ve,
    * chan theo hang,
    * chan theo cot,
    * tong so hang,
    * tong s cot
  )
*/
Keypad kp = Keypad
(
  makeKeymap(keyLY),
  rowP, colP, Row, Col
);

//* bien dung de tinh toan
short int i = 6;
const short int pass_len = 4;
char pass[pass_len];
const char valid[pass_len] =
  {'0', '5', '0', '7'}; //* <- doi mat khau tai day

void clear_pass(char *pass)
{
  for(int j = 0; j < pass_len; j++)
  {
    pass[j] = ' ';
  }
}

void setup()
{ 
  lcd.begin(16, 2);
}

void loop()
{
  HERE: char key = kp.getKey();
  lcd.setCursor(0,0);
  lcd.print("Dang nhan: ");

  //* chon nut C de xoa toan bo mat khau da nhap
  if(key == 'C')
  {
    clear_pass(pass);
    i = 6;
    lcd.clear();
    goto HERE;
  }
  //* chon nut D de xac nhan dang nhap
  else if(key == 'D')
  {
    if(pass[3] && pass[3] != ' ')
    {
      if
      (
        pass[0] == valid[0] &&
        pass[1] == valid[1] &&
        pass[2] == valid[2] &&
        pass[3] == valid[3]
      )
        {
          lcd.clear();
          delay(500);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(" Mat khau dung");
          lcd.setCursor(0,1);
          lcd.print("Chap nhan mo cua");
          delay(2000);
          clear_pass(pass);
          lcd.clear();
          goto HERE;
        }
      else
      {
        lcd.clear();
        lcd.setCursor(2,0);
        lcd.print("Sai mat khau");
        lcd.setCursor(2,1);
        lcd.print("Hay nhap lai");
        delay(1500);
        clear_pass(pass);
        lcd.clear();
        goto HERE;
      }
      
    }
  }
  else if
  (
    key &&
    key != '*' &&
    key != 'A' &&
    key != 'B' &&
    key != '#'
  )
    {
      lcd.setCursor(i, 1);
      lcd.print(key);
      pass[i-6] = key;
      i++;
      i = (i > 9) ? 6 : i;
    }
}

/*
  * Nguyen ly nut C:
  * -> reset bien pass
  * -> xoa toan bo ky tu tren lcd
  * -> nhay toi nhan dan 'HERE'

  * Nguyen ly nut D:
  * -> kiem tra bien pass co rong hay ko
  * -> neu rong thi ko lam gi ca
  * -> neu ko rong thi di kiem tra voi bien valid
  * -> neu 2 bien giong nhau xuat ra lcd va mo cua
  * -> neu 2 bien ko giong nhau xuat ra lcd va xoa mat khau da nhap
*/