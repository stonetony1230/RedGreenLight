/*
這是一個紅綠燈程式，兼計時器與心率檢測器XDD
*/
int mode = 0;//記憶此時位於的模式，0為預設模式，1為強制模式綠燈，2為強制模式紅燈，3為測心率模式，4為settingMode
int GrTime = 20;//綠燈設定ㄉ時間
int RdTime = 30;//紅燈設定ㄉ時間
void displayTime(int time);//顯示時間的函數
void settingMode();//呼叫進入設定綠燈紅燈時間的模式
void DefaultMode();//進入預設模式
void ForceMode(int light);//進入強制模式，傳入0進入綠燈，傳入1進入紅燈
void HeartRateMode();//進入測心率模式
boolean changeMode();//轉換模式測試，要轉換模式傳回是，不用轉換模式傳回否，應該每0.1秒被呼叫一次於預設或強制模式

int Button1();//回傳個位數的按鈕是否按下，是則回傳1，否則回傳0
int Button2();//回傳十位數的按鈕是否...
int ButtonS();//回傳設定紐...

int Buttons1 = 0;//紀錄button1狀態的變數，個位數
int Buttons2 = 0;//紀錄十位數
int ButtonsS = 0;//紀錄設定/暫停鍵
void Buttonsreset();//重製按鈕狀態變數
boolean pause = false;//暫停的切換器

void Green(int val);//綠燈亮，val 傳入LOW關閉，HIGH打開
void Red(int val);//紅燈亮...
void Orange(int val);//黃燈...

					 //腳位設定**************************************************

					 //74HC595腳位(2~7)

					 //74HC595個位
int dataPin = 2;//個位數IC 14腳位(data)
int latchPin = 3;//個位數IC12腳位(latch暫存器時脈)
int clockPin = 4;//個位數IC 11腳位(clock序列時脈)

				 //74HC595十位
int dataPin1 = 5;//十位數IC 14腳位(data)
int latchPin1 = 6;//十位數IC12腳位(latch暫存器時脈)
int clockPin1 = 7;//十位數IC 11腳位(clock序列時脈)

				  //LED
int led_green = 8;
int led_yellow = 9;
int led_red = 10;

//Button
int Button1p = 11;//個位
int Button2p = 12;//十位
int ButtonSp = 13;//設定


				 // the setup function runs once when you press reset or power the board
void setup() {
	for (int i = 2; i <= 10; i++)
	{
		pinMode(i, OUTPUT);
	}
	for (int j = 11; j <= 13; j++)
	{
		pinMode(j, INPUT);
	}
}

// the loop function runs over and over again forever
void loop() {
	switch (mode) {
	case 0:
		DefaultMode();
		break;
	case 1:
		ForceMode(0);
		break;
	case 2:
		ForceMode(1);
		break;
	case 3:
		HeartRateMode();
		break;
	case 4:
		settingMode();
	}
	Green(LOW);
	Red(LOW);
	Orange(LOW);
	do {
		delay(100);
	} while (Button1() || Button2() || ButtonS());
	Buttonsreset();
}



//  dp,a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[11] = {
	B01111110,
	B00110000,
	B01101101,
	B01111001,
	B00110011,
	B01011011,
	B01011111,
	B01110000,
	B01111111,
	B01111011,
	B00000000
};

byte seven_seg_tendigits[11] = {
	B01111110,
	B00110000,
	B01101101,
	B01111001,
	B00110011,
	B01011011,
	B01011111,
	B01110000,
	B01111111,
	B01111011,
	B00000000
};



//個位
void sevenSegWrite(byte digit) {
	// 送資料前要先把 latchPin 拉成低電位
	digitalWrite(latchPin, LOW);

	// 送出數字的位元資料 (bit pattern)
	shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);

	// 送完資料後要把 latchPin 拉回成高電位
	digitalWrite(latchPin, HIGH);
}

//十位
void sevenSegWrite1(byte tendigit) {
	// 送資料前要先把 latchPin 拉成低電位
	digitalWrite(latchPin1, LOW);

	// 送出數字的位元資料 (bit pattern)
	shiftOut(dataPin1, clockPin1, LSBFIRST, seven_seg_tendigits[tendigit]);

	// 送完資料後要把 latchPin 拉回成高電位
	digitalWrite(latchPin1, HIGH);
}

void displayTime(int time)//
{

	sevenSegWrite(time % 10);
	sevenSegWrite1(time / 10);
}


void settingMode()
{
	int ButtonSstatus = 0; // 宣告設定鍵狀態
	int Button1status = 0; // 宣告個位鍵狀態
	int Button2status = 0; // 宣告十位鍵狀態
	int digit = 0; //七段顯示個位數
	int tendigit = 0; //七段顯示器十位數
	ButtonSstatus = digitalRead(13);//判斷ButtonS 的電位 13為接點*********************
	delay(100);

	if (ButtonSstatus == HIGH) //當設定鍵為高電位進入設定模式---綠燈>>>>紅燈
		Button1status = digitalRead(11); //11為個位接點
	Button2status = digitalRead(12); //12為十位接點
//	displayTime();

	if (Button1status == HIGH)
		digit++;
	GrTime == digit;
	if (Button2status == HIGH)
		tendigit++;
	GrTime += tendigit * 10;


	if (GrTime != 0 && Button1status == HIGH)
		digit++;
	RdTime == digit;
	if (GrTime != 0 && Button2status == HIGH)
		tendigit++;
	RdTime += tendigit * 10;

	return;
}

void DefaultMode()
{
	int light = 0;//0 is green, 1 is orange, 2 is red
	int time = GrTime * 10;//綠燈時間的百毫秒
	Orange(LOW);
	Red(LOW);
	Green(HIGH);
	do {
		if (!pause) {
			if (time == 0) {
				light = light + 1;
				if (light == 3)
				{
					light = 0;
				}
				switch (light) {
				case 0:
					Red(LOW);
					Green(HIGH);
					time = GrTime * 10;
					break;
				case 1:
					Green(LOW);
					Orange(HIGH);
					time = 50;
					break;
				case 2:
					Orange(LOW);
					Red(HIGH);
					time = RdTime * 10;
				}
			}
			displayTime(time / 10);
			time--;
		}
		delay(100);
	} while (!changeMode());
}

void ForceMode(int light)
{
	int time = 0;//百毫秒數
	if (light == 0) {
		Green(HIGH);
		Red(LOW);
		Orange(LOW);
	}
	else if (light == 1) {
		Green(LOW);
		Red(HIGH);
		Orange(LOW);
	}
	do {
		if (!pause) {
			if (time > 600)
				displayTime(time / 600);
			else
				displayTime(time / 10);
			time++;
		}
		delay(100);
	} while (!changeMode());
}

void HeartRateMode()
{
	int count = 0;//計數器
	for (int time = 50; time >= 0; time--) {
		displayTime(time / 10);
		delay(100);
	}
	for (int time = 600; time >= 0; time--) {
		if (ButtonS()) {
			ButtonsS++;
			Red(HIGH);
			if (ButtonsS >= 4) {
				mode = 0;
				return;
			}
		}
		else if (ButtonsS > 0) {
			count++;
			ButtonsS = 0;
			Red(LOW);
		}
		displayTime(time / 10);
		delay(100);
	}
	if (count >= 400) {
		mode = 0;
		return;
	}
	else if (count >= 300) {
		Green(HIGH);
		Orange(HIGH);
		Red(HIGH);
		count = count - 300;
	}
	else if (count >= 200) {
		Orange(HIGH);
		Red(HIGH);
		count = count - 200;
	}
	else if (count >= 100) {
		Red(HIGH);
		count = count - 100;
	}
	displayTime(count);//顯示平均每分鐘的心跳數
	mode = 0;
	delay(2000);
	ButtonsS = 0;
	do {
		if (ButtonS())
			ButtonsS++;
		delay(100);
	} while (ButtonsS == 0 || ButtonS());
}

boolean changeMode()
{
	int status = Button1() + Button2() * 10 + ButtonS() * 100;
	switch (status) {
	case 0:
		if (Buttons1 > 0) {
			mode = 1;
			return true;
		}
		if (Buttons2 > 0) {
			mode = 2;
			return true;
		}
		if (ButtonsS > 0) {
			pause = !pause;
			return false;
		}
		return false;
	case 100:
		ButtonsS++;
		if (ButtonsS >= 4) {
			if (mode == 0) {
				mode = 4;
				return true;
			}
			if (mode == 1 || mode == 2) {
				mode = 0;
				return true;
			}
		}
		return false;
	case 1:
		Buttons1++;
		if (Buttons1 >= 4) {
			mode = 3;
			return true;
		}
		return false;
	case 10:
		Buttons2++;
	default:
		return false;
	}
	return false;
}

int Button1()
{
	if (digitalRead(Button1p) == HIGH) {
		return 1;
	};
	return 0;
}

int Button2()
{
	if (digitalRead(Button2p) == HIGH) {
		return 1;
	};
	return 0;
}

int ButtonS()
{
	if (digitalRead(ButtonSp) == HIGH) {
		return 1;
	};
	return 0;
}

void Buttonsreset()
{
	Buttons1 = 0;
	Buttons2 = 0;
	ButtonsS = 0;
}

void Green(int val)
{
	digitalWrite(led_green, val);
}

void Red(int val)
{
	digitalWrite(led_red, val);
}

void Orange(int val)
{
	digitalWrite(led_yellow, val);
}
