/*
硂琌厚縊祘Α
 */
int green = 0; //北厚縊獹办跑计
int red = 0; //北縊獹办跑计
int orange = 0;//北独縊獹办跑计
int mode = 0;//癘拘家Α0箇砞家Α1眏家Α2代み瞯家Α
int time = 0;//计
int GrTime = 0;//厚縊砞﹚丁
int RdTime = 0;//縊砞﹚丁
void displayTime(int time);//陪ボ丁ㄧ计
void settingMode();//㊣秈砞﹚厚縊縊丁家Α

//digit seven-segment LED
int diseven[10][8]
{
	{1,1,1,1,1,1,0,0},//0
	{0,1,1,0,0,0,0,0},//1
	{1,1,0,1,1,0,1,0},//2
	{1,1,1,1,0,0,1,0},//3
	{0,1,1,0,0,1,1,0},//4
	{1,0,1,1,0,1,1,0},//5
	{1,0,1,1,1,1,1,0},//6
	{1,1,1,0,0,0,0,0},//7
	{1,1,1,1,1,1,1,0},//8
	{1,1,1,1,0,1,1,0},//9
}

//tendigit seven-segment LED
int tendiseven[10][8]
{
	{1, 1, 1, 1, 1, 1, 0, 0},//0
	{ 0,1,1,0,0,0,0,0 },//1
	{ 1,1,0,1,1,0,1,0 },//2
	{ 1,1,1,1,0,0,1,0 },//3
	{ 0,1,1,0,0,1,1,0 },//4
	{ 1,0,1,1,0,1,1,0 },//5
	{ 1,0,1,1,1,1,1,0 },//6
	{ 1,1,1,0,0,0,0,0 },//7
	{ 1,1,1,1,1,1,1,0 },//8
	{ 1,1,1,1,0,1,1,0 },//9
}

// the setup function runs once when you press reset or power the board
void setup() {


}

// the loop function runs over and over again forever
void loop() {

}

void displayTime(int time)
{

}

void settingMode()
{
}
