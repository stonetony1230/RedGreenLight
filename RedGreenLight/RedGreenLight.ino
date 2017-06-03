/*
這是一個紅綠燈程式
 */
int mode = 0;//記憶此時位於的模式，0為預設模式，1為強制模式，2為測心率模式
int GrTime = 0;//綠燈設定ㄉ時間
int RdTime = 0;//紅燈設定ㄉ時間
void displayTime(int time);//顯示時間的函數
void settingMode();//呼叫進入設定綠燈紅燈時間的模式
void DefaultMode();//進入預設模式
void ForceMode();//進入強制模式

int Button1();//回傳個位數的按鈕是否按下，是則回傳1，否則回傳0
int Button2();//回傳十位數的按鈕是否...
int ButtonS();//回傳設定紐...

int Button1=LOW;//紀錄上一次檢查button1狀態的變數
int Button2=LOW;//紀錄上一次...
int Button3 = LOW;//紀錄...
int pause = 0;//暫停的切換器

void Green(int val);//綠燈亮，val 傳入LOW關閉，HIGH打開
void Red(int val);//紅燈亮...
void Orange(int val);//黃燈...

// the setup function runs once when you press reset or power the board
void setup() {


}

// the loop function runs over and over again forever
void loop() {

	}


}

void displayTime(int time)
{

}

void settingMode()
{

}

void DefaultMode()
{
	int light = 0;//0 is green, 1 is orange, 2 is red
	int time = GrTime*10;//綠燈時間的百毫秒
	if (pause == 0) {
		if (time == 0) {
			light = light + 1;
			if (light == 3)
				light = 0;
			
		}
	}

}
