/*
這是一個紅綠燈程式，兼計時器與心率檢測器XDD
 */
int mode = 0;//記憶此時位於的模式，0為預設模式，1為強制模式綠燈，2為強制模式紅燈，3為測心率模式，4為settingMode
int GrTime = 0;//綠燈設定ㄉ時間
int RdTime = 0;//紅燈設定ㄉ時間
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

// the setup function runs once when you press reset or power the board
void setup() {


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
}


void displayTime(int time)//153458
{
	int digit = 0;
	int tendigit = 0;
	int sevensegment[10][8] = {
		{1,1,1,1,1,1,0,0},//0
		{0,1,1,0,0,0,0,0},//1
		{1,1,0,1,1,0,1,0},//2
		{1,1,1,1,0,0,1,0},//3
		{0,1,1,0,0,1,1,0},//4
		{1,0,1,1,0,1,1,0},//5
		{1,0,1,1,1,1,1,0},//6
		{1,1,1,0,0,0,0,0},//7
		{1,1,1,1,1,1,1,0},//8
		{1,1,1,1,0,1,1,0} }; //9 

	if (digit > 9)
		digit = 0;
	if (tendigit > 9)
		tendigit = 0;
	if (digit > 9, tendigit > 9)
		digit = tendigit = 0;
	digitalWrite(, HIGH);//*****************紅燈亮()紅燈腳位



}


void settingMode()
{
	int ButtomSstatus = 0; // 宣告設定鍵狀態
	int Button1status = 0; // 宣告個位鍵狀態
	int Button2status = 0; // 宣告十位鍵狀態
	int digit = 0; //七段顯示個位數
	int tendigit = 0; //七段顯示器十位數
	ButtonSstatus = digitalRead();//判斷ButtonS 的電位 ()為接點*********************
	delay(100);

	if (ButtomSstatus == HIGH) //當設定鍵為高電位進入設定模式---綠燈>>>>紅燈
		Button1status = digitalRead(); //()為接點***********************************

	displayTime();

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
}

void DefaultMode()
{
	int light = 0;//0 is green, 1 is orange, 2 is red
	int time = GrTime * 10;//綠燈時間的百毫秒
	do {
		if (!pause) {
			if (time == 0) {
				light = light + 1;
				if (light == 3)
					light = 0;
				switch (light) {
				case 0:
					Red(LOW);
					Green(HIGH);
					time = GrTime * 10;
				case 1:
					Green(LOW);
					Orange(HIGH);
					time = 50;
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
			delay(100);
		}
	} while (!changeMode());
}

void HeartRateMode()
{
	int count = 0;//計數器
	for (int time = 0; time <= 600; time++) {
		if (ButtonS())
			ButtonsS++;
		else if (ButtonsS > 0) {
			count++;
			ButtonsS = 0;
		}
		delay(100);
	}
	displayTime(count);//顯示平均每分鐘的心跳數
	mode = 0;
}

boolean changeMode()
{
	int status = Button1() + Button2() * 10 + ButtonS() * 100;
	switch (status) {
	case 0:
		if (Buttons1 > 0) {
			Buttonsreset();
			mode = 1;
			return true;
		}
		if (Buttons2 > 0) {
			Buttonsreset();
			mode = 2;
			return true;
		}
		if (ButtonsS > 0) {
			Buttonsreset();
			pause = !pause;
			return false;
		}
		return false;
	case 100:
		ButtonsS++;
		if (ButtonsS >= 4) {
			Buttonsreset();
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
			Buttonsreset();
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

void Buttonsreset()
{
	Buttons1 = 0;
	Buttons2 = 0;
	ButtonsS = 0;
}
