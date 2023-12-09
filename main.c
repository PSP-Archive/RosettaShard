#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspgu.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <jpeglib.h>
#include "pspaudio.h"
#include "pspaudiolib.h"
#include "graphics.h"
//#include "mp3player.h"
#include <variables.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <SDL.h>
//#include <SDL_TTF.h>
//#include <SDL_image.h>
#include <time.h>
//#include <psppower.h>
//#include <ft2build.h>
//#include "fontloader.h"
#include "flib.h"
#include "audio.h"
#include "tex.h"

#define printf pspDebugScreenPrintf
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define RGB(r,v,b)              ((r) | ((v)<<8) | ((b)<<16) | (0xff<<24))
#define Classic   0
#define LeftHanded     54
#define RightHanded  108
#define SelectMethod   162

struct stat f__stat;

void myrksAudioLoad(char selectedAudio[100]){
rksAudioLoad("./Sounds/empty.mp3");
rksAudioSetPlaybackRate(10000);
rksAudioPlay();
rksAudioLoad(selectedAudio);
}
void chooseSounds(){
SceCtrlData pad, lastpad;
		sceCtrlReadBufferPositive(&lastpad, 1);
	SelectedLine = 1;
	soundmenustatus = 0;
	SelectMenuPNG = loadImage("./Images/SelectMenu.png");
	while (soundmenustatus == 0) {
		blitAlphaImageToScreen(0, 0 , 240, 136, SelectMenuPNG, 120, 68);
		if (1) {   // display select menu
			if (SelectedLine == 1) { 
				if (correctSelect == 1) {sprintf (correctSoundTxt, "Harp");sprintf (correctSound, "./Sounds/harp.mp3");}
				if (correctSelect == 2) {sprintf (correctSoundTxt, "Great");sprintf (correctSound, "./Sounds/great.mp3");}
				if (incorrectSelect == 1) {sprintf (incorrectSoundTxt, "Dong");sprintf (incorrectSound, "./Sounds/dong.mp3");}
				if (incorrectSelect == 2) {sprintf (incorrectSoundTxt, "Boo");sprintf (incorrectSound, "./Sounds/boo.mp3");}
				printTextScreen(138,110,"Correct       <          >",RGB(200,200,200));
				printTextScreen(138,120,"Incorrect     <          >",RGB(200,200,200));
				printTextScreen(282,110,correctSoundTxt,RGB(255,255,38));
				printTextScreen(282,120,incorrectSoundTxt,RGB(200,200,200));
				printTextScreen(157,175,"Press CROSS to Return",RGB(200,200,200));
			}
			if (SelectedLine == 2) { 
				if (correctSelect == 1) {sprintf (correctSoundTxt, "Harp");sprintf (correctSound, "./Sounds/harp.mp3");}
				if (correctSelect == 2) {sprintf (correctSoundTxt, "Great");sprintf (correctSound, "./Sounds/great.mp3");}
				if (incorrectSelect == 1) {sprintf (incorrectSoundTxt, "Dong");sprintf (incorrectSound, "./Sounds/dong.mp3");}
				if (incorrectSelect == 2) {sprintf (incorrectSoundTxt, "Boo");sprintf (incorrectSound, "./Sounds/boo.mp3");}
				printTextScreen(138,110,"Correct       <          >",RGB(200,200,200));
				printTextScreen(138,120,"Incorrect     <          >",RGB(200,200,200));
				printTextScreen(282,110,correctSoundTxt,RGB(200,200,200));
				printTextScreen(282,120,incorrectSoundTxt,RGB(255,255,38));
				printTextScreen(157,175,"Press CROSS to Return",RGB(200,200,200));
			}
			if (SelectedLine == 3) { 
				if (correctSelect == 1) {sprintf (correctSoundTxt, "Harp");sprintf (correctSound, "./Sounds/harp.mp3");}
				if (correctSelect == 2) {sprintf (correctSoundTxt, "Great");sprintf (correctSound, "./Sounds/great.mp3");}
				if (incorrectSelect == 1) {sprintf (incorrectSoundTxt, "Dong");sprintf (incorrectSound, "./Sounds/dong.mp3");}
				if (incorrectSelect == 2) {sprintf (incorrectSoundTxt, "Boo");sprintf (incorrectSound, "./Sounds/boo.mp3");}
				printTextScreen(138,110,"Correct       <          >",RGB(200,200,200));
				printTextScreen(138,120,"Incorrect     <          >",RGB(200,200,200));
				printTextScreen(282,110,correctSoundTxt,RGB(200,200,200));
				printTextScreen(282,120,incorrectSoundTxt,RGB(200,200,200));
				printTextScreen(157,175,"Press CROSS to Return",RGB(200,200,200));
			}
			flipScreen();
		}
		if (1) {   // take input
			sceCtrlReadBufferPositive(&pad, 1);
			if(pad.Buttons != lastpad.Buttons){
				lastpad = pad;
				if(pad.Buttons & PSP_CTRL_RIGHT){
					if (SelectedLine == 1) {
						if (correctSelect < 2) {
							correctSelect++;
							//oslPlaySound(clicksound, 1);
						}
					}
					else if (SelectedLine == 2) {
						if (incorrectSelect < 2) {
							incorrectSelect++;
							//oslPlaySound(clicksound, 1);
						}
					}
				}
				if(pad.Buttons & PSP_CTRL_LEFT){
					if (SelectedLine == 1) {
						if (correctSelect > 1) {
							correctSelect--;
							//oslPlaySound(clicksound, 1);
						}
					}
					else if (SelectedLine == 2) {
						if (incorrectSelect > 1) {
							incorrectSelect--;
							//oslPlaySound(clicksound, 1);
						}
					}
				}
				if(pad.Buttons & PSP_CTRL_UP){
					if (SelectedLine > 1) {
						SelectedLine--;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_DOWN){
					if (SelectedLine < 3) {
						SelectedLine++;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_CROSS){
					//oslPlaySound(clicksound, 1);
						SelectedLine = 1;
						soundmenustatus = 1;
				}
			}
		}
	}
}
void detectLang(){
pFile = fopen ("./Languages/CDID.TRS" , "rb");
if (pFile==NULL) sceKernelExitGame();
	else {
		c = 0;
		readTextPlace = 0;
		while(c != ',') {
			c = fgetc(pFile);
			if(c != ',') {
				langName1[readTextPlace]=c;
			}
			readTextPlace++;
		}
		readTextPlace = 0;
		/*x=0;
		x2=0;
		while(x < 8) {
			c = fgetc(pFile);
			while(c != ',') {
				c = fgetc(pFile);
			}
			x++;
		}
		while(x2 < 9) {
			c = fgetc(pFile);	
			x2++;
		}*/
		fclose(pFile);
	}
}
void detectFirstrun(){
pFile = fopen ("./Languages/CONFIG.TRS" , "rb");
c = 0;
		readTextPlace = 0;
		while(c != ',') {
			c = fgetc(pFile);
			if(c != ',') {
				roseUnitTxt[readTextPlace]=c;
				readTextPlace++;
			}
		}
		readTextPlace = 0;
		c = fgetc(pFile);
		while(c != ',') {
			if(c != ' ') {
				roseLessonTxt[readTextPlace]=c;
				readTextPlace++;
			}
		c = fgetc(pFile);
		}
		readTextPlace = 0;
		c = fgetc(pFile);
		while(c != ',') {
			if(c != ' ') {
				tutorialcheckTxt[readTextPlace]=c;
				readTextPlace++;
			}
		c = fgetc(pFile);
		}
		readTextPlace = 0;
		fclose(pFile);
	roseUnit = atoi(roseUnitTxt);
	roseLesson = atoi(roseLessonTxt);
	tutorialcheck = atoi(tutorialcheckTxt);
}
void setLanguageRun(){
if (strcmp (langName1, "Arabic I") == 0) {
	sprintf (langSoundDir, "ARA");
	sprintf (langSoundMp3, "AR");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	ArabicI = 1;
	}
if (strcmp (langName1, "Arabic II") == 0) {
	sprintf (langSoundDir, "ARA");
	sprintf (langSoundMp3, "AR");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	ArabicII = 1;
	}
if (strcmp (langName1, "Chinese I") == 0) {
	sprintf (langSoundDir, "CHI");
	sprintf (langSoundMp3, "CH");
	sprintf (langImageDir, "PCA");
	sprintf (langImagePNG, "PA");
	ChineseI = 1;
	}
if (strcmp (langName1, "Chinese II") == 0) {
	sprintf (langSoundDir, "CHI");
	sprintf (langSoundMp3, "CH");
	sprintf (langImageDir, "PCA");
	sprintf (langImagePNG, "PA");
	ChineseII = 1;
	}
if (strcmp (langName1, "Dansk I") == 0) {
	sprintf (langSoundDir, "DAN");
	sprintf (langSoundMp3, "DA");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	DanskI = 1;
	}
if (strcmp (langName1, "Nederlands I") == 0) {
	sprintf (langSoundDir, "NED");
	sprintf (langSoundMp3, "NE");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	NederlandsI = 1;
	}
if (strcmp (langName1, "Nederlands II") == 0) {
	sprintf (langSoundDir, "NED");
	sprintf (langSoundMp3, "ND");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	NederlandsII = 1;
	}
if (strcmp (langName1, "English UK I") == 0) {
	sprintf (langSoundDir, "EBR");
	sprintf (langSoundMp3, "EB");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	EnglishUKI = 1;
	}
if (strcmp (langName1, "English UK II") == 0) {
	sprintf (langSoundDir, "EBR");
	sprintf (langSoundMp3, "EB");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	EnglishUKII = 1;
	}
if (strcmp (langName1, "English US I") == 0) {
	sprintf (langSoundDir, "ENG");
	sprintf (langSoundMp3, "EN");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	EnglishUSI = 1;
	}
if (strcmp (langName1, "English US II") == 0) {
	sprintf (langSoundDir, "ENG");
	sprintf (langSoundMp3, "EN");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	EnglishUSII = 1;
	}
if (strcmp (langName1, "French I") == 0) {
	sprintf (langSoundDir, "FRA");
	sprintf (langSoundMp3, "FR");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	FrancaisI = 1;
	}
if (strcmp (langName1, "French II") == 0) {
	sprintf (langSoundDir, "FRA");
	sprintf (langSoundMp3, "FR");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	FrancaisII = 1;
	}
if (strcmp (langName1, "Deutsch I") == 0) {
	sprintf (langSoundDir, "DEU");
	sprintf (langSoundMp3, "DE");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	DeutschI = 1;
	}
if (strcmp (langName1, "Deutsch II") == 0) {
	sprintf (langSoundDir, "DEU");
	sprintf (langSoundMp3, "DE");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	DeutschII = 1;
	}
if (strcmp (langName1, "Greek I") == 0) {
	sprintf (langSoundDir, "GRK");
	sprintf (langSoundMp3, "GR");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	GreekI = 1;
	}
if (strcmp (langName1, "Greek II") == 0) {
	sprintf (langSoundDir, "GRK");
	sprintf (langSoundMp3, "GR");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	GreekII = 1;
	}
if (strcmp (langName1, "Hebrew I") == 0) {
	sprintf (langSoundDir, "HEB");
	sprintf (langSoundMp3, "HE");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	HebrewI = 1;
	}
if (strcmp (langName1, "Hindi I") == 0) {
	sprintf (langSoundDir, "HIN");
	sprintf (langSoundMp3, "HI");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	HindiI = 1;
	}
if (strcmp (langName1, "Indonesian I") == 0) {
	sprintf (langSoundDir, "IND");
	sprintf (langSoundMp3, "IN");
	sprintf (langImageDir, "PCA");
	sprintf (langImagePNG, "PA");
	IndonesianI = 1;
	}
if (strcmp (langName1, "Italiano I") == 0) {
	sprintf (langSoundDir, "ITA");
	sprintf (langSoundMp3, "IT");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	ItalianoI = 1;
	}
if (strcmp (langName1, "Italiano II") == 0) {
	sprintf (langSoundDir, "ITA");
	sprintf (langSoundMp3, "IT");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	ItalianoII = 1;
	}
if (strcmp (langName1, "Japanese I") == 0) {
	sprintf (langSoundDir, "JPN");
	sprintf (langSoundMp3, "JP");
	sprintf (langImageDir, "PCA");
	sprintf (langImagePNG, "PA");
	JapaneseI = 1;
	}
if (strcmp (langName1, "Japanese II") == 0) {
	sprintf (langSoundDir, "JPN");
	sprintf (langSoundMp3, "JP");
	sprintf (langImageDir, "PCA");
	sprintf (langImagePNG, "PA");
	JapaneseII = 1;
	}
if (strcmp (langName1, "Korean I") == 0) {
	sprintf (langSoundDir, "KOR");
	sprintf (langSoundMp3, "KO");
	sprintf (langImageDir, "PCA");
	sprintf (langImagePNG, "PA");
	KoreanI = 1;
	}
if (strcmp (langName1, "Latin I") == 0) {
	sprintf (langSoundDir, "LAT");
	sprintf (langSoundMp3, "LA");
	sprintf (langImageDir, "PCN");
	sprintf (langImagePNG, "PN");
	LatinI = 1;
	}
if (strcmp (langName1, "Portugus I") == 0) {
	sprintf (langSoundDir, "POR");
	sprintf (langSoundMp3, "PO");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	PortugeusI = 1;
	}
if (strcmp (langName1, "Portugus II") == 0) {
	sprintf (langSoundDir, "POR");
	sprintf (langSoundMp3, "PO");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	PortugeusII = 1;
	}
if (strcmp (langName1, "Russian I") == 0) {
	sprintf (langSoundDir, "RUS");
	sprintf (langSoundMp3, "RU");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	RussianI = 1;
	}
if (strcmp (langName1, "Russian II") == 0) {
	sprintf (langSoundDir, "RUS");
	sprintf (langSoundMp3, "RU");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	RussianII = 1;
	}
if (strcmp (langName1, "Espa–ol I") == 0) {
	sprintf (langSoundDir, "ESP");
	sprintf (langSoundMp3, "ES");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	EspagnolI = 1;
	}
if (strcmp (langName1, "Espa–ol II") == 0) {
	sprintf (langSoundDir, "ESP");
	sprintf (langSoundMp3, "ES");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	EspagnolII = 1;
	}
if (strcmp (langName1, "Spanish (Spain) I") == 0) {
	sprintf (langSoundDir, "ESC");
	sprintf (langSoundMp3, "ES");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	SpanishSpainI = 1;
	}
if (strcmp (langName1, "Spanish (Spain) II") == 0) {
	sprintf (langSoundDir, "ESC");
	sprintf (langSoundMp3, "ES");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	SpanishSpainII = 1;
	}
if (strcmp (langName1, "Kiswahili I") == 0) {
	sprintf (langSoundDir, "KIS");
	sprintf (langSoundMp3, "KI");
	sprintf (langImageDir, "PCF");
	sprintf (langImagePNG, "PF");
	KiswahiliI = 1;
	}
if (strcmp (langName1, "Svenska I") == 0) {
	sprintf (langSoundDir, "SVE");
	sprintf (langSoundMp3, "SV");
	sprintf (langImageDir, "PC2");
	sprintf (langImagePNG, "PC");
	SvenskaI = 1;
	}
if (strcmp (langName1, "Thai I") == 0) {
	sprintf (langSoundDir, "THA");
	sprintf (langSoundMp3, "TH");
	sprintf (langImageDir, "PCA");
	sprintf (langImagePNG, "PA");
	ThaiI = 1;
	}
if (strcmp (langName1, "Turkish I") == 0) {
	sprintf (langSoundDir, "TUR");
	sprintf (langSoundMp3, "TU");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	TurkishI = 1;
	}
if (strcmp (langName1, "Vietnamese I") == 0) {
	sprintf (langSoundDir, "VIE");
	sprintf (langSoundMp3, "VI");
	sprintf (langImageDir, "PCA");
	sprintf (langImagePNG, "PA");
	VietnameseI = 1;
	}
if (strcmp (langName1, "Cymraeg I") == 0) {
	sprintf (langSoundDir, "CYM");
	sprintf (langSoundMp3, "CY");
	sprintf (langImageDir, "PCT");
	sprintf (langImagePNG, "PC");
	CymraegI = 1;
	}
if (strcmp (langName1, "Demonstration Cardset") == 0) {
	sprintf (langSoundDir, "DEMOS");
	sprintf (langSoundMp3, "DEMOS");
	sprintf (langImageDir, "DEMO");
	sprintf (langImagePNG, "DEMO");
	DemoSet = 1;
	lessonlength = 8;
	}
}
void setlessonDescTxt(int rUnit, int rLesson) {
	if (rUnit == 1) {
		if (rLesson == 1) { sprintf (lessonDescTxt, "Intro Nouns and Prepositions"); }
		if (rLesson == 2) { sprintf (lessonDescTxt, "Verbs: Present Progressive"); }
		if (rLesson == 3) { sprintf (lessonDescTxt, "Descriptive Adjectives"); }
		if (rLesson == 4) { sprintf (lessonDescTxt, "Cardinal Numbers"); }
		if (rLesson == 5) { sprintf (lessonDescTxt, "Singular and Plural"); }
		if (rLesson == 6) { sprintf (lessonDescTxt, "Numbers and Clock Time"); }
		if (rLesson == 7) { sprintf (lessonDescTxt, "Q&A; Personal Pronouns"); }
		if (rLesson == 8) { sprintf (lessonDescTxt, "Food, Eating and Drinking"); }
		if (rLesson == 9) { sprintf (lessonDescTxt, "Clothing and Dress"); }
		if (rLesson == 10) { sprintf (lessonDescTxt, "Who, What, Where, Which"); }
		if (rLesson == 11) { sprintf (lessonDescTxt, "Unit One Review"); }
	}
	if (rUnit == 2) {
		if (rLesson == 1) { sprintf (lessonDescTxt, "More Verbs: Present Progressive"); }
		if (rLesson == 2) { sprintf (lessonDescTxt, "People and Animals"); }
		if (rLesson == 3) { sprintf (lessonDescTxt, "Big and Small"); }
		if (rLesson == 4) { sprintf (lessonDescTxt, "Shapes and Colors"); }
		if (rLesson == 5) { sprintf (lessonDescTxt, "Left and Right"); }
		if (rLesson == 6) { sprintf (lessonDescTxt, "Negative Verbs Forms"); }
		if (rLesson == 7) { sprintf (lessonDescTxt, "Compound Subjects"); }
		if (rLesson == 8) { sprintf (lessonDescTxt, "More Prepositions"); }
		if (rLesson == 9) { sprintf (lessonDescTxt, "Head, Face, Hands and Feet"); }
		if (rLesson == 10) { sprintf (lessonDescTxt, "Present Progressive,Perfect,Future"); }
		if (rLesson == 11) { sprintf (lessonDescTxt, "Unit Two Review"); }
	}
	if (rUnit == 3) {
		if (rLesson == 1) { sprintf (lessonDescTxt, "Descriptions of People"); }
		if (rLesson == 2) { sprintf (lessonDescTxt, "Quantities: Quantity Relationships"); }
		if (rLesson == 3) { sprintf (lessonDescTxt, "More Clothing"); }
		if (rLesson == 4) { sprintf (lessonDescTxt, "Inside, Outside; Prepositions"); }
		if (rLesson == 5) { sprintf (lessonDescTxt, "More Colors and Numbers"); }
		if (rLesson == 6) { sprintf (lessonDescTxt, "Animals; Real, Not Real"); }
		if (rLesson == 7) { sprintf (lessonDescTxt, "Being Human; Adjectives"); }
		if (rLesson == 8) { sprintf (lessonDescTxt, "Professions and Conditions"); }
		if (rLesson == 9) { sprintf (lessonDescTxt, "Body Parts and Pictures"); }
		if (rLesson == 10) { sprintf (lessonDescTxt, "Clock Time, Time of Day"); }
		if (rLesson == 11) { sprintf (lessonDescTxt, "Unit Three Review"); }
	}
}
void readInText(){
char roseTextFile[80];
sprintf (roseTextFile, "./Languages/%s%02d_%02d/%s%02d%02d.TXT", langSoundDir, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson);
pFile = fopen (roseTextFile , "rb");
if (pFile==NULL) sceKernelExitGame();
	else {
		sprintf (readText, "                                                                                                                                                                                              ");
		int count = 0;
		c = 0;
		readTextPlace = 0;
		while (count < (sarr[soundcall])) {
			while(c != '@') {
				c = fgetc(pFile);
			}
			c = fgetc(pFile);
			count++;
		}
		while(c != '@') {
			if (c != '@') {
				readText[readTextPlace]=c;
			}
			c = fgetc(pFile);
			readTextPlace++;
		}
		fclose(pFile);
	}
}
void menuup(){
	SelectedLine--;
	if (SelectedLine >= 1)
		//oslPlaySound(clicksound, 1);
	if (SelectedLine < 1)
		SelectedLine = 1;
}
void menudown(int x){
	SelectedLine++;
	if (SelectedLine <= x)
		//oslPlaySound(clicksound, 1);
	if (SelectedLine > x)
		SelectedLine = x;
}
void MenuReset(){
	SelectedLine = 1;
	RosettaFlash = 1;
	}



void shuffleElements(int carr1[], int size){
	int temporary, randomNum, last;
	srand((unsigned)time(NULL));
	for (last = size; last > 1; last--)
	{
		randomNum = rand( ) % last;
		temporary = carr1[randomNum];
		carr1[randomNum] = carr1[last - 1];
		carr1[last - 1] = temporary;
	}
}


void flashrender(char cardtxtfirst[20], int cardxlocation, int cardylocation){
	char buffer[200];
	Image* pnext;
	sprintf (imgType, "JPG");
	sprintf (buffer, "./Languages/%s%02d_%02d/%s%02d%02dP/%s%s.%s", langImageDir, roseUnit, roseLesson, langImagePNG, roseUnit, roseLesson, langImagePNG, cardtxtfirst, imgType);
	FileExist = (stat(buffer,&f__stat) != 0);	//if file exists returns 0, if does not exist returns 1
	if (FileExist == 0) {
		pnext = loadJpegImage(buffer);
		blitAlphaImageToScreenScaled(0, 0 , pnext->imageWidth, pnext->imageHeight, pnext, cardxlocation, cardylocation, cardxlocation+163, cardylocation+122);
	}
	else {	sprintf (imgType, "png");
		sprintf (buffer, "./Languages/%s%02d_%02d/%s%02d%02dP/%s%s.%s", langImageDir, roseUnit, roseLesson, langImagePNG, roseUnit, roseLesson, langImagePNG, cardtxtfirst, imgType);
		pnext = loadImage(buffer);
		//blitAlphaImageToScreen(0, 0 , 163, 122, pnext, cardxlocation, cardylocation);
		blitAlphaImageToScreenScaled(0, 0 , pnext->imageWidth, pnext->imageHeight, pnext, cardxlocation, cardylocation, cardxlocation+163, cardylocation+122);
	}
	freeImage(pnext);
	}
void checkscore(){
	sprintf (correctscoreprint, "%d", correctscore);
	sprintf (incorrectscoreprint, "%d", incorrectscore);
	sprintf (unitlesson, "Unit%02d Lesson%02d", roseUnit, roseLesson);
	if (correctscore < 10) {CorrectScorePrintX = 387;}
	else if (correctscore > 9) {CorrectScorePrintX = 383;}
	if (incorrectscore < 10) {inCorrectScorePrintX = 436;}
	else if (incorrectscore > 9) {inCorrectScorePrintX = 432;}
	if (firstcard <= 36) {unitlessonpaceX = 410;}
	else if (firstcard > 36) {unitlessonpaceX = 406;}
	if (firstcard <= 4) { sprintf (unitlessonpace, "1"); }
	else if (firstcard <= 8) { sprintf (unitlessonpace, "2"); }
	else if (firstcard <= 12) { sprintf (unitlessonpace, "3"); }
	else if (firstcard <= 16) { sprintf (unitlessonpace, "4"); }
	else if (firstcard <= 20) { sprintf (unitlessonpace, "5"); }
	else if (firstcard <= 24) { sprintf (unitlessonpace, "6"); }
	else if (firstcard <= 28) { sprintf (unitlessonpace, "7"); }
	else if (firstcard <= 32) { sprintf (unitlessonpace, "8"); }
	else if (firstcard <= 36) { sprintf (unitlessonpace, "9"); }
	else if (firstcard <= 40) { sprintf (unitlessonpace, "10"); }
}

void correctanswer(int cardnum){
	Image* ptemp;
	ptemp = loadImage("./Images/temp.png");
	blitAlphaImageToScreen(0, 0 , 480, 272, ptemp, 0, 0);
	freeImage(ptemp);
	if (scorechecked == 0){correctscore +=1;}
	checkscore();
	int cardxlocation=13;
	int cardylocation=12;
		sprintf (cardimage1, "%02d%02d%02d", roseUnit, roseLesson, carr[0]);
		flashrender(cardimage1, cardxlocation, cardylocation);
		cardxlocation += 167;
		sprintf (cardimage2, "%02d%02d%02d", roseUnit, roseLesson, carr[1]);
		flashrender(cardimage2, cardxlocation, cardylocation);
		cardxlocation -= 167;
		cardylocation += 126;
		sprintf (cardimage3, "%02d%02d%02d", roseUnit, roseLesson, carr[2]);
		flashrender(cardimage3, cardxlocation, cardylocation);
		cardxlocation += 167;
		sprintf (cardimage4, "%02d%02d%02d", roseUnit, roseLesson, carr[3]);
		flashrender(cardimage4, cardxlocation, cardylocation);
cardxlocation=13;
cardylocation=12;
	Image* correctansweri;
	correctansweri = loadImage("./Images/correct.png");
		if (cardnum == 1){
		}
		else if (cardnum == 2){
			cardxlocation += 167;
		}
		else if (cardnum == 3){
			cardylocation += 126;
		}
		else if (cardnum == 4){
			cardxlocation += 167;
			cardylocation += 126;
		}
	blitAlphaImageToScreen(0, 0 , 39, 39, correctansweri, (cardxlocation + 62), (cardylocation + 41)); //need to add routine to find location of center of whatever card this is. compare to carr[]
	freeImage(correctansweri);
		printTextScreen(CorrectScorePrintX,191,correctscoreprint,RGB(200,200,200));
		printTextScreen(inCorrectScorePrintX,191,incorrectscoreprint,RGB(200,200,200));
		printTextScreen(358,218,unitlesson,RGB(200,200,200));
		printTextScreen(unitlessonpaceX,242,unitlessonpace,RGB(255,255,38));
		printTextScreen(360,12,readText,RGB(0,0,0));
	flipScreen();
	cardxlocation=13;
	cardylocation=12;
}
void incorrectanswer(int cardnum){
	Image* ptemp;
	ptemp = loadImage("./Images/temp.png");
	blitAlphaImageToScreen(0, 0 , 480, 272, ptemp, 0, 0);
	freeImage(ptemp);
	if (scorechecked == 0){incorrectscore +=1;}
	checkscore();
	int cardxlocation=13;
	int cardylocation=12;

		sprintf (cardimage1, "%02d%02d%02d", roseUnit, roseLesson, carr[0]);
		flashrender(cardimage1, cardxlocation, cardylocation);
		cardxlocation += 167;

		sprintf (cardimage2, "%02d%02d%02d", roseUnit, roseLesson, carr[1]);
		flashrender(cardimage2, cardxlocation, cardylocation);

		cardxlocation -= 167;
		cardylocation += 126;
		sprintf (cardimage3, "%02d%02d%02d", roseUnit, roseLesson, carr[2]);
		flashrender(cardimage3, cardxlocation, cardylocation);

		cardxlocation += 167;
		sprintf (cardimage4, "%02d%02d%02d", roseUnit, roseLesson, carr[3]);
		flashrender(cardimage4, cardxlocation, cardylocation);
cardxlocation=13;
cardylocation=12;		
	Image* incorrectansweri;
	incorrectansweri = loadImage("./Images/incorrect.png");
		if (cardnum == 1){
		}
		else if (cardnum == 2){
			cardxlocation += 167;
		}
		else if (cardnum == 3){
			cardylocation += 126;
		}
		else if (cardnum == 4){
			cardxlocation += 167;
			cardylocation += 126;
		}
	blitAlphaImageToScreen(0, 0 , 39, 39, incorrectansweri, (cardxlocation + 62), (cardylocation + 41)); //need to add routine to find location of center of whatever card this is. compare to carr[]
	freeImage(incorrectansweri);

		printTextScreen(CorrectScorePrintX,191,correctscoreprint,RGB(200,200,200));
		printTextScreen(inCorrectScorePrintX,191,incorrectscoreprint,RGB(200,200,200));
		printTextScreen(358,218,unitlesson,RGB(200,200,200));
		printTextScreen(unitlessonpaceX,242,unitlessonpace,RGB(255,255,38));
		printTextScreen(360,12,readText,RGB(0,0,0));
	flipScreen();
	cardxlocation=11;
	cardylocation=10;
}


void showthecards (cardfirst, cardlast){
cardxlocation=13;
cardylocation=12;
	Image* ptemp;
	ptemp = loadImage("./Images/temp.png");
	blitAlphaImageToScreen(0, 0 , 480, 272, ptemp, 0, 0);
	freeImage(ptemp);
	int tmp2cardfirst = cardfirst;
	int tmp2cardlast = cardlast;
	while (tmp2cardfirst <= tmp2cardlast){
		tmp2cardfirst++;
		if (tmp2cardfirst == 1){
			sprintf (cardimage1, "%02d%02d%02d", roseUnit, roseLesson, carr[0]);
			flashrender(cardimage1, cardxlocation, cardylocation);
		}
		if (tmp2cardfirst == 2){
			cardxlocation += 167;
			sprintf (cardimage2, "%02d%02d%02d", roseUnit, roseLesson, carr[1]);
			flashrender(cardimage2, cardxlocation, cardylocation);
		}
		if (tmp2cardfirst == 3){
			cardxlocation -= 167;
			cardylocation += 126;
			sprintf (cardimage3, "%02d%02d%02d", roseUnit, roseLesson, carr[2]);
			flashrender(cardimage3, cardxlocation, cardylocation);
		}
		if (tmp2cardfirst == 4){
		cardxlocation += 167;
		sprintf (cardimage4, "%02d%02d%02d", roseUnit, roseLesson, carr[3]);
		flashrender(cardimage4, cardxlocation, cardylocation);
		}
	}
		checkscore();
		readInText();
		
		printTextScreen(CorrectScorePrintX,191,correctscoreprint,RGB(200,200,200));
		printTextScreen(inCorrectScorePrintX,191,incorrectscoreprint,RGB(200,200,200));
		printTextScreen(358,218,unitlesson,RGB(200,200,200));
		if (scoreCardStatus != 0) printTextScreen(unitlessonpaceX,242,unitlessonpace,RGB(255,255,38));
		if (scoreCardStatus != 0) printTextScreen(360,12,readText,RGB(255,255,38));
		//blitAlphaImageToScreen (TextX, TextY, 12, 13, fontWestern, 254, 92);
		
		
		//SDL_Color clrFg = {0,0,255,0};  // Blue ("Fg" is foreground)
		//SDL_Surface *sText = TTF_RenderText_Solid( fntCourier, "Courier 12", clrFg );
		//SDL_Rect rcDest = {0,0,0,0};
		//SDL_BlitSurface( sText,NULL, screen,&rcDest );
		//SDL_FreeSurface( sText );	
		//draw_term();

		//Font_PrintScreen(othFont, 230, 200, "2nd Font", GU_RGBA(255, 255, 255, 255), getVramDrawBuffer());
		
		
		/*set_font_color(0xff00ffff);	// yellow
	set_font_size(10);		// 12 point
	set_font_angle(0.0);		// no angle
	text_to_screen(readText, 357, 30);
	
	set_font_color(0xff00ffff);	// yellow
	set_font_size(9);		// 12 point
	set_font_angle(0.0);		// no angle
	text_to_screen(readText, 357, 42);
	
		set_font_color(0xff00ffff);	// yellow
	set_font_size(8);		// 12 point
	set_font_angle(0.0);		// no angle
	text_to_screen(readText, 357, 54);
	
		set_font_color(0xff00ffff);	// yellow
	set_font_size(7);		// 12 point
	set_font_angle(0.0);		// no angle
	text_to_screen(readText, 357, 66);*/
	
		sceDisplayWaitVblankStart();
		flipScreen();
}
void tutorial(){
SceCtrlData pad, lastpad;
		sceCtrlReadBufferPositive(&lastpad, 1);
	SelectedLine = 1;
	TutorialStatus = 0;
	SelectMenuPNG = loadImage("./Images/SelectMenu.png");
	while (TutorialStatus == 0) {
		blitAlphaImageToScreen(0, 0 , 240, 136, SelectMenuPNG, 120, 68);
		if (1) {   // display select menu
			if (SelectedLine == 1) { 
				printTextScreen(138,95,"As this is the first time",RGB(200,200,200));
				printTextScreen(138,105,"RosettaShard has been run",RGB(200,200,200));
				printTextScreen(138,115,"you now have the option to",RGB(200,200,200));
				printTextScreen(138,125,"go through a tutorial to",RGB(200,200,200));
				printTextScreen(138,135,"demonstrate the use of the",RGB(200,200,200));
				printTextScreen(138,145,"application. The tutorial",RGB(200,200,200));
				printTextScreen(138,155,"can be run later from the",RGB(200,200,200));
				printTextScreen(138,165,"Options menu.Do you want",RGB(200,200,200));
				printTextScreen(138,175,"to run the tutorial now?",RGB(200,200,200));
				printTextScreen(138,185,"        NO",RGB(255,255,38));
				printTextScreen(138,185,"               NO",RGB(200,200,200));
			}
			if (SelectedLine == 2) { 
				printTextScreen(138,95,"As this is the first time",RGB(200,200,200));
				printTextScreen(138,105,"RosettaShard has been run",RGB(200,200,200));
				printTextScreen(138,115,"you now have the option to",RGB(200,200,200));
				printTextScreen(138,125,"go through a tutorial to",RGB(200,200,200));
				printTextScreen(138,135,"demonstrate the use of the",RGB(200,200,200));
				printTextScreen(138,145,"application. The tutorial",RGB(200,200,200));
				printTextScreen(138,155,"can be run later from the",RGB(200,200,200));
				printTextScreen(138,165,"Options menu.Do you want",RGB(200,200,200));
				printTextScreen(138,175,"to run the tutorial now?",RGB(200,200,200));
				printTextScreen(138,185,"        NO",RGB(200,200,200));
				printTextScreen(138,185,"               NO",RGB(255,255,38));
			}
			sceDisplayWaitVblankStart();
			flipScreen();
		}
		if (TutorialStatus == 0) {   // take input
			sceCtrlReadBufferPositive(&pad, 1);
			if(pad.Buttons != lastpad.Buttons){
				lastpad = pad;
				if(pad.Buttons & PSP_CTRL_LEFT){
					if (SelectedLine > 1) {
						SelectedLine--;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_RIGHT){
					if (SelectedLine < 2) {
						SelectedLine++;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_CROSS){
					if (SelectedLine == 1) {
						//oslPlaySound(clicksound, 1);
						SelectedLine = 4;
						TutorialStatus = 1;
					}
					if (SelectedLine == 2) {
						//oslPlaySound(clicksound, 1);
						SelectedLine = 4;
						TutorialStatus = 1;
					}
				}
			}
		}
	}
}
void fontRender(){    
	TextY = 5;//sprite_position; 13
    TextX = 3;//(sprite_march * 25);  12
	//sprite_march++;
    //if (sprite_position == SelectMethod) {
//		if (sprite_march == 5) sprite_march = 0;
		//counta=0;
	//}
	
//blitAlphaImageToScreen (TextX, TextY, 18, 24, fontWestern, 254, 92);
/*if (1) {
if (strcmp (readText[Char], "!") == 0) { TextReadPlace = 1; }
if (strcmp (readText[Char], "\"") == 0) { TextReadPlace = 2; }
if (strcmp (readText[Char], "#") == 0) { TextReadPlace = 3; }
if (strcmp (readText[Char], "$") == 0) { TextReadPlace = 4; }
if (strcmp (readText[Char], "%") == 0) { TextReadPlace = 5; }
if (strcmp (readText[Char], "&") == 0) { TextReadPlace = 6; }
if (strcmp (readText[Char], "'") == 0) { TextReadPlace = 7; }
if (strcmp (readText[Char], "(") == 0) { TextReadPlace = 8; }
if (strcmp (readText[Char], ")") == 0) { TextReadPlace = 9; }
if (strcmp (readText[Char], "*") == 0) { TextReadPlace = 10; }
if (strcmp (readText[Char], "+") == 0) { TextReadPlace = 11; }
if (strcmp (readText[Char], ",") == 0) { TextReadPlace = 12; }
if (strcmp (readText[Char], "-") == 0) { TextReadPlace = 13; }
if (strcmp (readText[Char], ".") == 0) { TextReadPlace = 14; }
if (strcmp (readText[Char], "/") == 0) { TextReadPlace = 15; }
if (strcmp (readText[Char], "0") == 0) { TextReadPlace = 16; }
if (strcmp (readText[Char], "1") == 0) { TextReadPlace = 17; }
if (strcmp (readText[Char], "2") == 0) { TextReadPlace = 18; }
if (strcmp (readText[Char], "3") == 0) { TextReadPlace = 19; }
if (strcmp (readText[Char], "4") == 0) { TextReadPlace = 20; }
if (strcmp (readText[Char], "5") == 0) { TextReadPlace = 21; }
if (strcmp (readText[Char], "6") == 0) { TextReadPlace = 22; }
if (strcmp (readText[Char], "7") == 0) { TextReadPlace = 23; }
if (strcmp (readText[Char], "8") == 0) { TextReadPlace = 24; }
if (strcmp (readText[Char], "9") == 0) { TextReadPlace = 25; }
if (strcmp (readText[Char], ":") == 0) { TextReadPlace = 26; }
if (strcmp (readText[Char], ";") == 0) { TextReadPlace = 27; }
if (strcmp (readText[Char], "<") == 0) { TextReadPlace = 28; }
if (strcmp (readText[Char], "=") == 0) { TextReadPlace = 29; }
if (strcmp (readText[Char], ">") == 0) { TextReadPlace = 30; }
if (strcmp (readText[Char], "?") == 0) { TextReadPlace = 31; }
if (strcmp (readText[Char], "@") == 0) { TextReadPlace = 32; }
if (strcmp (readText[Char], "A") == 0) { TextReadPlace = 33; }
if (strcmp (readText[Char], "B") == 0) { TextReadPlace = 34; }
if (strcmp (readText[Char], "C") == 0) { TextReadPlace = 35; }
if (strcmp (readText[Char], "D") == 0) { TextReadPlace = 36; }
if (strcmp (readText[Char], "E") == 0) { TextReadPlace = 37; }
if (strcmp (readText[Char], "F") == 0) { TextReadPlace = 38; }
if (strcmp (readText[Char], "G") == 0) { TextReadPlace = 39; }
if (strcmp (readText[Char], "H") == 0) { TextReadPlace = 40; }
if (strcmp (readText[Char], "I") == 0) { TextReadPlace = 41; }
if (strcmp (readText[Char], "J") == 0) { TextReadPlace = 42; }
if (strcmp (readText[Char], "K") == 0) { TextReadPlace = 43; }
if (strcmp (readText[Char], "L") == 0) { TextReadPlace = 44; }
if (strcmp (readText[Char], "M") == 0) { TextReadPlace = 45; }
if (strcmp (readText[Char], "N") == 0) { TextReadPlace = 46; }
if (strcmp (readText[Char], "O") == 0) { TextReadPlace = 47; }
if (strcmp (readText[Char], "P") == 0) { TextReadPlace = 48; }
if (strcmp (readText[Char], "Q") == 0) { TextReadPlace = 49; }
if (strcmp (readText[Char], "R") == 0) { TextReadPlace = 50; }
if (strcmp (readText[Char], "S") == 0) { TextReadPlace = 51; }
if (strcmp (readText[Char], "T") == 0) { TextReadPlace = 52; }
if (strcmp (readText[Char], "U") == 0) { TextReadPlace = 53; }
if (strcmp (readText[Char], "V") == 0) { TextReadPlace = 54; }
if (strcmp (readText[Char], "W") == 0) { TextReadPlace = 55; }
if (strcmp (readText[Char], "X") == 0) { TextReadPlace = 56; }
if (strcmp (readText[Char], "Y") == 0) { TextReadPlace = 57; }
if (strcmp (readText[Char], "Z") == 0) { TextReadPlace = 58; }
if (strcmp (readText[Char], "[") == 0) { TextReadPlace = 59; }
if (strcmp (readText[Char], "yen") == 0) { TextReadPlace = 60; }
if (strcmp (readText[Char], "]") == 0) { TextReadPlace = 61; }
if (strcmp (readText[Char], "^") == 0) { TextReadPlace = 62; }
if (strcmp (readText[Char], "_") == 0) { TextReadPlace = 63; }
if (strcmp (readText[Char], "`") == 0) { TextReadPlace = 64; }
if (strcmp (readText[Char], "a") == 0) { TextReadPlace = 65; }
if (strcmp (readText[Char], "b") == 0) { TextReadPlace = 66; }
if (strcmp (readText[Char], "c") == 0) { TextReadPlace = 67; }
if (strcmp (readText[Char], "d") == 0) { TextReadPlace = 68; }
if (strcmp (readText[Char], "e") == 0) { TextReadPlace = 69; }
if (strcmp (readText[Char], "f") == 0) { TextReadPlace = 70; }
if (strcmp (readText[Char], "g") == 0) { TextReadPlace = 71; }
if (strcmp (readText[Char], "h") == 0) { TextReadPlace = 72; }
if (strcmp (readText[Char], "i") == 0) { TextReadPlace = 73; }
if (strcmp (readText[Char], "j") == 0) { TextReadPlace = 74; }
if (strcmp (readText[Char], "k") == 0) { TextReadPlace = 75; }
if (strcmp (readText[Char], "l") == 0) { TextReadPlace = 76; }
if (strcmp (readText[Char], "m") == 0) { TextReadPlace = 77; }
if (strcmp (readText[Char], "n") == 0) { TextReadPlace = 78; }
if (strcmp (readText[Char], "o") == 0) { TextReadPlace = 79; }
if (strcmp (readText[Char], "p") == 0) { TextReadPlace = 80; }
if (strcmp (readText[Char], "q") == 0) { TextReadPlace = 81; }
if (strcmp (readText[Char], "r") == 0) { TextReadPlace = 82; }
if (strcmp (readText[Char], "s") == 0) { TextReadPlace = 83; }
if (strcmp (readText[Char], "t") == 0) { TextReadPlace = 84; }
if (strcmp (readText[Char], "u") == 0) { TextReadPlace = 85; }
if (strcmp (readText[Char], "v") == 0) { TextReadPlace = 86; }
if (strcmp (readText[Char], "w") == 0) { TextReadPlace = 87; }
if (strcmp (readText[Char], "x") == 0) { TextReadPlace = 88; }
if (strcmp (readText[Char], "y") == 0) { TextReadPlace = 89; }
if (strcmp (readText[Char], "z") == 0) { TextReadPlace = 90; }
if (strcmp (readText[Char], "{") == 0) { TextReadPlace = 91; }
if (strcmp (readText[Char], "|") == 0) { TextReadPlace = 92; }
if (strcmp (readText[Char], "}") == 0) { TextReadPlace = 93; }
if (strcmp (readText[Char], "~") == 0) { TextReadPlace = 94; }
if (strcmp (readText[Char], "€") == 0) { TextReadPlace = 95; }
if (strcmp (readText[Char], ",") == 0) { TextReadPlace = 96; }
if (strcmp (readText[Char], "ƒ") == 0) { TextReadPlace = 97; }
if (strcmp (readText[Char], "„") == 0) { TextReadPlace = 98; }
if (strcmp (readText[Char], "…") == 0) { TextReadPlace = 99; }
if (strcmp (readText[Char], "†") == 0) { TextReadPlace = 100; }
if (strcmp (readText[Char], "‡") == 0) { TextReadPlace = 101; }
if (strcmp (readText[Char], "ˆ") == 0) { TextReadPlace = 102; }
if (strcmp (readText[Char], "‰") == 0) { TextReadPlace = 103; }
if (strcmp (readText[Char], "Š") == 0) { TextReadPlace = 104; }
if (strcmp (readText[Char], "‹") == 0) { TextReadPlace = 105; }
if (strcmp (readText[Char], "Œ") == 0) { TextReadPlace = 106; }
if (strcmp (readText[Char], "Ž") == 0) { TextReadPlace = 107; }
if (strcmp (readText[Char], "‘") == 0) { TextReadPlace = 108; }
if (strcmp (readText[Char], "’") == 0) { TextReadPlace = 109; }
if (strcmp (readText[Char], "“") == 0) { TextReadPlace = 110; }
if (strcmp (readText[Char], "”") == 0) { TextReadPlace = 111; }
if (strcmp (readText[Char], "•") == 0) { TextReadPlace = 112; }
if (strcmp (readText[Char], "–") == 0) { TextReadPlace = 113; }
if (strcmp (readText[Char], "—") == 0) { TextReadPlace = 114; }
if (strcmp (readText[Char], "˜") == 0) { TextReadPlace = 115; }
if (strcmp (readText[Char], "™") == 0) { TextReadPlace = 116; }
if (strcmp (readText[Char], "š") == 0) { TextReadPlace = 117; }
if (strcmp (readText[Char], "›") == 0) { TextReadPlace = 118; }
if (strcmp (readText[Char], "œ") == 0) { TextReadPlace = 119; }
if (strcmp (readText[Char], "ž") == 0) { TextReadPlace = 120; }
if (strcmp (readText[Char], "Ÿ") == 0) { TextReadPlace = 121; }
if (strcmp (readText[Char], " ") == 0) { TextReadPlace = 122; }
if (strcmp (readText[Char], "¡") == 0) { TextReadPlace = 123; }
if (strcmp (readText[Char], "¢") == 0) { TextReadPlace = 124; }
if (strcmp (readText[Char], "£") == 0) { TextReadPlace = 125; }
if (strcmp (readText[Char], "¤") == 0) { TextReadPlace = 126; }
if (strcmp (readText[Char], "¥") == 0) { TextReadPlace = 127; }
if (strcmp (readText[Char], "¦") == 0) { TextReadPlace = 128; }
if (strcmp (readText[Char], "§") == 0) { TextReadPlace = 129; }
if (strcmp (readText[Char], "¨") == 0) { TextReadPlace = 130; }
if (strcmp (readText[Char], "©") == 0) { TextReadPlace = 131; }
if (strcmp (readText[Char], "ª") == 0) { TextReadPlace = 132; }
if (strcmp (readText[Char], "«") == 0) { TextReadPlace = 133; }
if (strcmp (readText[Char], "¬") == 0) { TextReadPlace = 134; }
if (strcmp (readText[Char], "®") == 0) { TextReadPlace = 135; }
if (strcmp (readText[Char], "¯") == 0) { TextReadPlace = 136; }
if (strcmp (readText[Char], "°") == 0) { TextReadPlace = 137; }
if (strcmp (readText[Char], "±") == 0) { TextReadPlace = 138; }
if (strcmp (readText[Char], "²") == 0) { TextReadPlace = 139; }
if (strcmp (readText[Char], "³") == 0) { TextReadPlace = 140; }
if (strcmp (readText[Char], "´") == 0) { TextReadPlace = 141; }
if (strcmp (readText[Char], "µ") == 0) { TextReadPlace = 142; }
if (strcmp (readText[Char], "¶") == 0) { TextReadPlace = 143; }
if (strcmp (readText[Char], "·") == 0) { TextReadPlace = 144; }
if (strcmp (readText[Char], "¸") == 0) { TextReadPlace = 145; }
if (strcmp (readText[Char], "¹") == 0) { TextReadPlace = 146; }
if (strcmp (readText[Char], "º") == 0) { TextReadPlace = 147; }
if (strcmp (readText[Char], "»") == 0) { TextReadPlace = 148; }
if (strcmp (readText[Char], "¼") == 0) { TextReadPlace = 149; }
if (strcmp (readText[Char], "½") == 0) { TextReadPlace = 150; }
if (strcmp (readText[Char], "¾") == 0) { TextReadPlace = 151; }
if (strcmp (readText[Char], "¿") == 0) { TextReadPlace = 152; }
if (strcmp (readText[Char], "À") == 0) { TextReadPlace = 153; }
if (strcmp (readText[Char], "Á") == 0) { TextReadPlace = 154; }
if (strcmp (readText[Char], "Â") == 0) { TextReadPlace = 155; }
if (strcmp (readText[Char], "Ã") == 0) { TextReadPlace = 156; }
if (strcmp (readText[Char], "Ä") == 0) { TextReadPlace = 157; }
if (strcmp (readText[Char], "Å") == 0) { TextReadPlace = 158; }
if (strcmp (readText[Char], "Æ") == 0) { TextReadPlace = 159; }
if (strcmp (readText[Char], "Ç") == 0) { TextReadPlace = 160; }
if (strcmp (readText[Char], "È") == 0) { TextReadPlace = 161; }
if (strcmp (readText[Char], "É") == 0) { TextReadPlace = 162; }
if (strcmp (readText[Char], "Ê") == 0) { TextReadPlace = 163; }
if (strcmp (readText[Char], "Ë") == 0) { TextReadPlace = 164; }
if (strcmp (readText[Char], "Ì") == 0) { TextReadPlace = 165; }
if (strcmp (readText[Char], "Í") == 0) { TextReadPlace = 166; }
if (strcmp (readText[Char], "Î") == 0) { TextReadPlace = 167; }
if (strcmp (readText[Char], "Ï") == 0) { TextReadPlace = 168; }
if (strcmp (readText[Char], "Ð") == 0) { TextReadPlace = 169; }
if (strcmp (readText[Char], "Ñ") == 0) { TextReadPlace = 170; }
if (strcmp (readText[Char], "Ò") == 0) { TextReadPlace = 171; }
if (strcmp (readText[Char], "Ó") == 0) { TextReadPlace = 172; }
if (strcmp (readText[Char], "Ô") == 0) { TextReadPlace = 173; }
if (strcmp (readText[Char], "Õ") == 0) { TextReadPlace = 174; }
if (strcmp (readText[Char], "Ö") == 0) { TextReadPlace = 175; }
if (strcmp (readText[Char], "×") == 0) { TextReadPlace = 176; }
if (strcmp (readText[Char], "Ø") == 0) { TextReadPlace = 177; }
if (strcmp (readText[Char], "Ù") == 0) { TextReadPlace = 178; }
if (strcmp (readText[Char], "Ú") == 0) { TextReadPlace = 179; }
if (strcmp (readText[Char], "Û") == 0) { TextReadPlace = 180; }
if (strcmp (readText[Char], "Ü") == 0) { TextReadPlace = 181; }
if (strcmp (readText[Char], "Ý") == 0) { TextReadPlace = 182; }
if (strcmp (readText[Char], "Þ") == 0) { TextReadPlace = 183; }
if (strcmp (readText[Char], "ß") == 0) { TextReadPlace = 184; }
if (strcmp (readText[Char], "à") == 0) { TextReadPlace = 185; }
if (strcmp (readText[Char], "á") == 0) { TextReadPlace = 186; }
if (strcmp (readText[Char], "â") == 0) { TextReadPlace = 187; }
if (strcmp (readText[Char], "ã") == 0) { TextReadPlace = 188; }
if (strcmp (readText[Char], "ä") == 0) { TextReadPlace = 189; }
if (strcmp (readText[Char], "å") == 0) { TextReadPlace = 190; }
if (strcmp (readText[Char], "æ") == 0) { TextReadPlace = 191; }
if (strcmp (readText[Char], "ç") == 0) { TextReadPlace = 192; }
if (strcmp (readText[Char], "è") == 0) { TextReadPlace = 193; }
if (strcmp (readText[Char], "é") == 0) { TextReadPlace = 194; }
if (strcmp (readText[Char], "ê") == 0) { TextReadPlace = 195; }
if (strcmp (readText[Char], "ë") == 0) { TextReadPlace = 196; }
if (strcmp (readText[Char], "ì") == 0) { TextReadPlace = 197; }
if (strcmp (readText[Char], "í") == 0) { TextReadPlace = 198; }
if (strcmp (readText[Char], "î") == 0) { TextReadPlace = 199; }
if (strcmp (readText[Char], "ï") == 0) { TextReadPlace = 200; }
if (strcmp (readText[Char], "ð") == 0) { TextReadPlace = 201; }
if (strcmp (readText[Char], "ñ") == 0) { TextReadPlace = 202; }
if (strcmp (readText[Char], "ò") == 0) { TextReadPlace = 203; }
if (strcmp (readText[Char], "ó") == 0) { TextReadPlace = 204; }
if (strcmp (readText[Char], "ô") == 0) { TextReadPlace = 205; }
if (strcmp (readText[Char], "õ") == 0) { TextReadPlace = 206; }
if (strcmp (readText[Char], "ö") == 0) { TextReadPlace = 207; }
if (strcmp (readText[Char], "÷") == 0) { TextReadPlace = 208; }
if (strcmp (readText[Char], "ø") == 0) { TextReadPlace = 209; }
if (strcmp (readText[Char], "ù") == 0) { TextReadPlace = 210; }
if (strcmp (readText[Char], "ú") == 0) { TextReadPlace = 211; }
if (strcmp (readText[Char], "û") == 0) { TextReadPlace = 212; }
if (strcmp (readText[Char], "ü") == 0) { TextReadPlace = 213; }
if (strcmp (readText[Char], "ý") == 0) { TextReadPlace = 214; }
if (strcmp (readText[Char], "þ") == 0) { TextReadPlace = 215; }
if (strcmp (readText[Char], "ÿ") == 0) { TextReadPlace = 216; }
}
*/}
void SpriteAnimate(){    
	if (counta == 40) {
		frameY = sprite_position;
        frameX = (sprite_march * 99);
		sprite_march++;
        if (sprite_position == SelectMethod) {
			if (sprite_march == 5) sprite_march = 0;
			counta=0;
		}
		else if (sprite_position != SelectMethod) {
			if (sprite_march == 5) sprite_march = 1;
			counta=0;
		}
	}
	counta++;
}
void setcontrols(){
	if (sprite_position == LeftHanded){
		cardselect1 = PSP_CTRL_UP;
		cardselect2 = PSP_CTRL_LEFT;
		cardselect3 = PSP_CTRL_RIGHT;
		cardselect4 = PSP_CTRL_DOWN;
		cardreplay = PSP_CTRL_SQUARE;
		cardslowreplay = PSP_CTRL_CIRCLE;
	}
	if (sprite_position == RightHanded){
		cardselect1 = PSP_CTRL_SQUARE;
		cardselect2 = PSP_CTRL_CROSS;
		cardselect3 = PSP_CTRL_TRIANGLE;
		cardselect4 = PSP_CTRL_CIRCLE;
		cardreplay = PSP_CTRL_RIGHT;
		cardslowreplay = PSP_CTRL_LEFT;
	}
	if (sprite_position == Classic){
		cardselect1 = PSP_CTRL_UP;
		cardselect2 = PSP_CTRL_DOWN;
		cardselect3 = PSP_CTRL_TRIANGLE;
		cardselect4 = PSP_CTRL_CROSS;
		cardreplay = PSP_CTRL_SQUARE;
		cardslowreplay = PSP_CTRL_CIRCLE;
	}
	if (sprite_position == SelectMethod){
		cardselect1 = PSP_CTRL_UP;
		cardselect2 = PSP_CTRL_DOWN;
		cardselect3 = PSP_CTRL_TRIANGLE;
		cardselect4 = PSP_CTRL_CROSS;
		cardreplay = PSP_CTRL_SQUARE;
		cardslowreplay = PSP_CTRL_CIRCLE;
	}
}
void controlScheme(){
SceCtrlData pad, lastpad;
		sceCtrlReadBufferPositive(&lastpad, 1);
	SelectedLine = 1;
	controlSchemeStatus = 0;
	SelectMenuPNG = loadImage("./Images/SelectMenu.png");

	sprite_position = Classic;
	counta=40;
	
	
	
	while (controlSchemeStatus == 0) {
		blitAlphaImageToScreen(0, 0 , 240, 136, SelectMenuPNG, 120, 68);
		if (1) {   // display select menu
			if (SelectedLine == 1) {
				sprite_position = LeftHanded;
				SpriteAnimate();
				blitAlphaImageToScreen (frameX, frameY, 99, 54, sprite, 254, 92); 
				printTextScreen(138,130,"Left Handed",RGB(255,255,38));
				printTextScreen(138,140,"Right Handed",RGB(200,200,200));
				printTextScreen(138,150,"Classic Controls",RGB(200,200,200));
				printTextScreen(138,160,"Select Method 'NYI'",RGB(200,200,200));
				printTextScreen(157,175,"Press CROSS to Accept",RGB(200,200,200));
			}
			if (SelectedLine == 2) { 
				sprite_position = RightHanded;
				SpriteAnimate();
				blitAlphaImageToScreen (frameX, frameY, 99, 54, sprite, 254, 92); 
				printTextScreen(138,130,"Left Handed",RGB(200,200,200));
				printTextScreen(138,140,"Right Handed",RGB(255,255,38));
				printTextScreen(138,150,"Classic Controls",RGB(200,200,200));
				printTextScreen(138,160,"Select Method 'NYI'",RGB(200,200,200));
				printTextScreen(157,175,"Press CROSS to Accept",RGB(200,200,200));
			}
			if (SelectedLine == 3) { 
				sprite_position = Classic;
				SpriteAnimate();
				blitAlphaImageToScreen (frameX, frameY, 99, 54, sprite, 254, 92);  
				printTextScreen(138,130,"Left Handed",RGB(200,200,200));
				printTextScreen(138,140,"Right Handed",RGB(200,200,200));
				printTextScreen(138,150,"Classic Controls",RGB(255,255,38));
				printTextScreen(138,160,"Select Method 'NYI'",RGB(200,200,200));
				printTextScreen(157,175,"Press CROSS to Accept",RGB(200,200,200));
			}
			if (SelectedLine == 4) { 
				sprite_position = SelectMethod;
				SpriteAnimate();
				blitAlphaImageToScreen (frameX, frameY, 99, 54, sprite, 254, 92); 
				printTextScreen(138,130,"Left Handed",RGB(200,200,200));
				printTextScreen(138,140,"Right Handed",RGB(200,200,200));
				printTextScreen(138,150,"Classic Controls",RGB(200,200,200));
				printTextScreen(138,160,"Select Method 'NYI'",RGB(255,255,38));
				printTextScreen(157,175,"Press CROSS to Accept",RGB(200,200,200));
			}
			flipScreen();
		}
		if (controlSchemeStatus==0) {   // take input
			sceCtrlReadBufferPositive(&pad, 1);
			if(pad.Buttons != lastpad.Buttons){
				lastpad = pad;
				if(pad.Buttons & PSP_CTRL_UP){
					if (SelectedLine > 1) {
						SelectedLine--;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_DOWN){
					if (SelectedLine < 4) {
						SelectedLine++;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_CROSS){
					if (SelectedLine == 1) {
						//oslPlaySound(clicksound, 1);
						SelectedLine = 2;
						controlSchemeStatus = 1;
					}
					if (SelectedLine == 2) {
						//oslPlaySound(clicksound, 1);
						SelectedLine = 2;
						controlSchemeStatus = 1;
					}
					if (SelectedLine == 3) {
						//oslPlaySound(clicksound, 1);
						SelectedLine = 2;
						controlSchemeStatus = 1;
					}
					if (SelectedLine == 4) {
						//oslPlaySound(clicksound, 1);
						SelectedLine = 2;
						controlSchemeStatus = 1;
					}
				}
			}
		}
	}
	
	sprite_march = 0;
	frameX = 99;
	frameY = 0;
}
void rewindSet(){
if (firstcard > 36) { firstcard = 33; cardlast -= 4;xix -= 4;}
if (firstcard > 32) { firstcard = 29; cardlast -= 4;xix -= 4;}
if (firstcard > 28) { firstcard = 25; cardlast -= 4;xix -= 4;}
if (firstcard > 24) { firstcard = 21; cardlast -= 4;xix -= 4;}
if (firstcard > 20) { firstcard = 17; cardlast -= 4;xix -= 4;}
if (firstcard > 16) { firstcard = 13; cardlast -= 4;xix -= 4;}
if (firstcard > 12) { firstcard = 9; cardlast -= 4;xix -= 4;}
if (firstcard > 8) { firstcard = 5; cardlast -= 4;xix -= 4;}
if (firstcard > 4) { firstcard = 1; cardlast -= 4;xix -= 4;}
}
void showScoreCard(){
	SelectedLine = 1;
	scoreCardStatus = 0;
		SceCtrlData pad, lastpad;
		sceCtrlReadBufferPositive(&lastpad, 1);
	selectmenustatus = 0;
	SelectMenuPNG = loadImage("./Images/SelectMenu.png");
	
	while (scoreCardStatus == 0) {
		blitAlphaImageToScreen(0, 0 , 240, 136, SelectMenuPNG, 120, 68);
		if (1) {   // display select menu
			if (SelectedLine == 1) { 
				sprintf (roseUnitTxt, "%02d", roseUnit);
				sprintf (roseLessonTxt, "%02d", roseLesson);
				printTextScreen(138,110,"Correct Answers",RGB(200,200,200));
				printTextScreen(138,120,"Incorrect Answers",RGB(200,200,200));
				printTextScreen(282,110,correctscoreprint,RGB(200,200,200));
				printTextScreen(282,120,incorrectscoreprint,RGB(200,200,200));
				printTextScreen(138,130,"Advance to the Next Lesson",RGB(255,255,38));
				printTextScreen(138,140,"Retry Current Lesson",RGB(200,200,200));
				printTextScreen(138,150,"Choose Unit   <          >",RGB(200,200,200));
				printTextScreen(138,160,"Choose Lesson <          >",RGB(200,200,200));
				printTextScreen(156,175,"  Exit RosettaShard  ",RGB(200,200,200));
				printTextScreen(290,150,roseUnitTxt,RGB(200,200,200));
				printTextScreen(290,160,roseLessonTxt,RGB(200,200,200));
			}
			if (SelectedLine == 2) { 
				sprintf (roseUnitTxt, "%02d", roseUnit);
				sprintf (roseLessonTxt, "%02d", roseLesson);
				printTextScreen(138,110,"Correct Answers",RGB(200,200,200));
				printTextScreen(138,120,"Incorrect Answers",RGB(200,200,200));
				printTextScreen(282,110,correctscoreprint,RGB(200,200,200));
				printTextScreen(282,120,incorrectscoreprint,RGB(200,200,200));
				printTextScreen(138,130,"Advance to the Next Lesson",RGB(200,200,200));
				printTextScreen(138,140,"Retry Current Lesson",RGB(255,255,38));
				printTextScreen(138,150,"Choose Unit   <          >",RGB(200,200,200));
				printTextScreen(138,160,"Choose Lesson <          >",RGB(200,200,200));
				printTextScreen(156,175,"  Exit RosettaShard  ",RGB(200,200,200));
				printTextScreen(290,150,roseUnitTxt,RGB(200,200,200));
				printTextScreen(290,160,roseLessonTxt,RGB(200,200,200));
			}
			if (SelectedLine == 3) { 
				sprintf (roseUnitTxt, "%02d", roseUnit);
				sprintf (roseLessonTxt, "%02d", roseLesson);
				printTextScreen(138,110,"Correct Answers",RGB(200,200,200));
				printTextScreen(138,120,"Incorrect Answers",RGB(200,200,200));
				printTextScreen(282,110,correctscoreprint,RGB(200,200,200));
				printTextScreen(282,120,incorrectscoreprint,RGB(200,200,200));
				printTextScreen(138,130,"Advance to the Next Lesson",RGB(200,200,200));
				printTextScreen(138,140,"Retry Current Lesson",RGB(200,200,200));
				printTextScreen(138,150,"Choose Unit   <          >",RGB(200,200,200));
				printTextScreen(138,160,"Choose Lesson <          >",RGB(200,200,200));
				printTextScreen(156,175,"  Exit RosettaShard  ",RGB(200,200,200));
				printTextScreen(290,150,roseUnitTxt,RGB(255,255,38));
				printTextScreen(290,160,roseLessonTxt,RGB(200,200,200));
			}
			if (SelectedLine == 4) { 
				sprintf (roseUnitTxt, "%02d", roseUnit);
				sprintf (roseLessonTxt, "%02d", roseLesson);
				printTextScreen(138,110,"Correct Answers",RGB(200,200,200));
				printTextScreen(138,120,"Incorrect Answers",RGB(200,200,200));
				printTextScreen(282,110,correctscoreprint,RGB(200,200,200));
				printTextScreen(282,120,incorrectscoreprint,RGB(200,200,200));
				printTextScreen(138,130,"Advance to the Next Lesson",RGB(200,200,200));
				printTextScreen(138,140,"Retry Current Lesson",RGB(200,200,200));
				printTextScreen(138,150,"Choose Unit   <          >",RGB(200,200,200));
				printTextScreen(138,160,"Choose Lesson <          >",RGB(200,200,200));
				printTextScreen(156,175,"  Exit RosettaShard  ",RGB(200,200,200));
				printTextScreen(290,150,roseUnitTxt,RGB(200,200,200));
				printTextScreen(290,160,roseLessonTxt,RGB(255,255,38));
			}
			if (SelectedLine == 5) { 
				sprintf (roseUnitTxt, "%02d", roseUnit);
				sprintf (roseLessonTxt, "%02d", roseLesson);
				printTextScreen(138,110,"Correct Answers",RGB(200,200,200));
				printTextScreen(138,120,"Incorrect Answers",RGB(200,200,200));
				printTextScreen(282,110,correctscoreprint,RGB(200,200,200));
				printTextScreen(282,120,incorrectscoreprint,RGB(200,200,200));
				printTextScreen(138,130,"Advance to the Next Lesson",RGB(200,200,200));
				printTextScreen(138,140,"Retry Current Lesson",RGB(200,200,200));
				printTextScreen(138,150,"Choose Unit   <          >",RGB(200,200,200));
				printTextScreen(138,160,"Choose Lesson <          >",RGB(200,200,200));
				printTextScreen(156,175,"  Exit RosettaShard  ",RGB(255,255,38));
				printTextScreen(290,150,roseUnitTxt,RGB(200,200,200));
				printTextScreen(290,160,roseLessonTxt,RGB(200,200,200));
			}
		flipScreen();
		}
		if (scoreCardStatus==0) {   // take input
			sceCtrlReadBufferPositive(&pad, 1);
			if(pad.Buttons != lastpad.Buttons){
				lastpad = pad;
				if(pad.Buttons & PSP_CTRL_UP){
					if (SelectedLine > 1) {
						SelectedLine--;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_DOWN){
					if (SelectedLine < 5) {
						SelectedLine++;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_RIGHT){
					if (SelectedLine == 3) {
						if ((unitCount + 1) < availableUnits) {
							unitCount++;
							lessonCount = 0;
							roseUnit = availableUnitsByUnit[unitCount];
							roseLesson = (detectedUnits[unitCount][lessonCount]);
							//oslPlaySound(clicksound, 1);
						}
					}
					else if (SelectedLine == 4) {
						if ((lessonCount + 1) < availableLessonsByUnit[unitCount]) {
							lessonCount++;
							roseLesson = (detectedUnits[unitCount][lessonCount]);
							//oslPlaySound(clicksound, 1);
						}
					}
				}
				if(pad.Buttons & PSP_CTRL_LEFT){
					if (SelectedLine == 3) {
						if ((unitCount + 1) > 1) {
							unitCount--;
							lessonCount = 0;
							roseUnit = availableUnitsByUnit[unitCount];
							roseLesson = (detectedUnits[unitCount][lessonCount]);
							//oslPlaySound(clicksound, 1);
						}
					}
					else if (SelectedLine == 4) {
						if ((lessonCount + 1) > 1) {
							lessonCount--;
							roseLesson = (detectedUnits[unitCount][lessonCount]);
							//oslPlaySound(clicksound, 1);
						}
					}
				}
				if(pad.Buttons & PSP_CTRL_CROSS){
					if (SelectedLine == 1) {
						//oslPlaySound(clicksound, 1);
						if ((lessonCount + 1) < availableLessonsByUnit[unitCount]) { lessonCount++; roseLesson = (detectedUnits[unitCount][lessonCount]); }
						else if ((unitCount + 1) < availableUnits) { unitCount++; lessonCount = 0; roseUnit = availableUnitsByUnit[unitCount]; roseLesson = (detectedUnits[unitCount][lessonCount]); }
						SelectedLine = 1;
						scoreCardStatus = 1;
						rewindSet();
						loadtheflash(0,3);
						//keepgoing = 0;
					}
					if (SelectedLine == 2) {
						//oslPlaySound(clicksound, 1);
						SelectedLine = 1;
						scoreCardStatus = 1;
						rewindSet();
						loadtheflash(0,3);
						//keepgoing = 0;
					}
					if (SelectedLine == 3) {
						//oslPlaySound(clicksound, 1);
						SelectedLine = 1;
						scoreCardStatus = 1;
						rewindSet();
						loadtheflash(0,3);
						//keepgoing = 0;
					}
					if (SelectedLine == 4) {
						//oslPlaySound(clicksound, 1);
						SelectedLine = 1;
						scoreCardStatus = 1;
						rewindSet();
						loadtheflash(0,3);
						//keepgoing = 0;
					}
					if (SelectedLine == 5) {
						//oslPlaySound(clicksound, 1);
						//oslQuit();
						//sceKernelSleepThread();
						sceKernelExitGame();
					}
				}
			}
		}
	}
}
void selectOptionsMenu() {
		SceCtrlData pad, lastpad;
		sceCtrlReadBufferPositive(&lastpad, 1);
	selectmenustatus = 0;
	SelectMenuPNG = loadImage("./Images/SelectMenu.png");
	
	while (selectmenustatus == 0) {
		blitAlphaImageToScreen(0, 0 , 240, 136, SelectMenuPNG, 120, 68);
		if (1) {   // display select menu
			if (SelectedLine == 1) { 
				printTextScreen(138,110,"Choose Sounds",RGB(255,255,38));
				printTextScreen(138,120,"Control Schemes",RGB(200,200,200));
				printTextScreen(138,130,"Change Unit or Lesson",RGB(200,200,200));
				printTextScreen(138,140,"Run the Tutorial",RGB(200,200,200));
				printTextScreen(138,150,"Exit RosettaShard",RGB(200,200,200));
				printTextScreen(154,175,"Press CIRCLE to Return",RGB(200,200,200));
			}
			if (SelectedLine == 2) { 
				printTextScreen(138,110,"Choose Sounds",RGB(200,200,200));
				printTextScreen(138,120,"Control Schemes",RGB(255,255,38));
				printTextScreen(138,130,"Change Unit or Lesson",RGB(200,200,200));
				printTextScreen(138,140,"Run the Tutorial",RGB(200,200,200));
				printTextScreen(138,150,"Exit RosettaShard",RGB(200,200,200));
				printTextScreen(154,175,"Press CIRCLE to Return",RGB(200,200,200));
			}
			if (SelectedLine == 3) { 
				printTextScreen(138,110,"Choose Sounds",RGB(200,200,200));
				printTextScreen(138,120,"Control Schemes",RGB(200,200,200));
				printTextScreen(138,130,"Change Unit or Lesson",RGB(255,255,38));
				printTextScreen(138,140,"Run the Tutorial",RGB(200,200,200));
				printTextScreen(138,150,"Exit RosettaShard",RGB(200,200,200));
				printTextScreen(154,175,"Press CIRCLE to Return",RGB(200,200,200));
			}
			if (SelectedLine == 4) { 
				printTextScreen(138,110,"Choose Sounds",RGB(200,200,200));
				printTextScreen(138,120,"Control Schemes",RGB(200,200,200));
				printTextScreen(138,130,"Change Unit or Lesson",RGB(200,200,200));
				printTextScreen(138,140,"Run the Tutorial",RGB(255,255,38));
				printTextScreen(138,150,"Exit RosettaShard",RGB(200,200,200));
				printTextScreen(154,175,"Press CIRCLE to Return",RGB(200,200,200));
			}
			if (SelectedLine == 5) { 
				printTextScreen(138,110,"Choose Sounds",RGB(200,200,200));
				printTextScreen(138,120,"Control Schemes",RGB(200,200,200));
				printTextScreen(138,130,"Change Unit or Lesson",RGB(200,200,200));
				printTextScreen(138,140,"Run the Tutorial",RGB(200,200,200));
				printTextScreen(138,150,"Exit RosettaShard",RGB(255,255,38));
				printTextScreen(154,175,"Press CIRCLE to Return",RGB(200,200,200));
			}
			flipScreen();
		}
		if (1) {   // take input
		
			sceCtrlReadBufferPositive(&pad, 1);
			if(pad.Buttons != lastpad.Buttons){
				lastpad = pad;
				if(pad.Buttons & PSP_CTRL_UP){
					if (SelectedLine > 1) {
						SelectedLine--;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_DOWN){
					if (SelectedLine < 5) {
						SelectedLine++;
						//oslPlaySound(clicksound, 1);
					}
				}
				if(pad.Buttons & PSP_CTRL_CROSS){
					if (SelectedLine == 1) {
						//oslPlaySound(clicksound, 1);
						chooseSounds();
					}
					else if (SelectedLine == 2) {
						//oslPlaySound(clicksound, 1);
						controlScheme();
						setcontrols();
					}
					else if (SelectedLine == 3) {
						//oslPlaySound(clicksound, 1);
						showScoreCard();
						selectmenustatus = 1;
					}
					else if (SelectedLine == 4) {
						//oslPlaySound(clicksound, 1);
						tutorial();
					}
					else if (SelectedLine == 5) {
						SelectedLine = 1;
						firstcard=1;
						MenuReset();
						//sceKernelSleepThread();
						sceKernelExitGame();
						//oslPlaySound(clicksound, 1);
						//oslQuit();
					}
				}
				if(pad.Buttons & PSP_CTRL_CIRCLE){
					//oslPlaySound(clicksound, 1);
					selectmenustatus = 1;
				}
			}
		}
	}
}
void detectUnits(){
	while (unitCount < 20) { // Detect the units and lessons
		if (1) {
			while (lessonCount < 41) {
				sprintf (FolderName, "./Languages/%s%02d_%02d", langImageDir, unitCount, lessonCount);
				FileExist = (stat(FolderName,&f__stat) != 0);	//if file exists returns 0, if does not exist returns 1
				if (FileExist == 0) {
					(detectedUnits[placedunit][placedlesson]) = lessonCount;
					placedlesson++;
					availableLessonsByUnit[placedunit] = placedlesson;
					UnitExists = 1;
				}
				lessonCount++;
			}
			if (UnitExists == 1) {
				availableUnitsByUnit[placedunit] = unitCount;
				placedunit++;
				availableUnits++;
			}
			UnitExists = 0;
		}
		unitCount++;
		placedlesson = 0;
		lessonCount = 1;
	}
roseUnit = availableUnitsByUnit[0];
roseLesson = (detectedUnits[0][0]);
}
void loadingScreen() {
rksAudioInit();
SelectMenuPNG = loadImage("./Images/SelectMenu.png");
// Splash Screen
blitAlphaImageToScreen(0, 0 , 480, 272, splash, 0, 0);
flipScreen();
myrksAudioLoad("./Sounds/intro.mp3");
rksAudioSetPlaybackRate(10000);
rksAudioPlay();
sleep(5);
while (loadingstatus == 0){
	blitAlphaImageToScreen(0, 0 , 480, 272, logo, 0, 0);
	flipScreen();
	detectLang();
	detectFirstrun();
	setLanguageRun();
	detectUnits();
	unitCount = 0;
	lessonCount = 0;
	//ttfinit();
	texInit((void *) 0x44088000, 0);
	AllLoaded = 1;
	loadingstatus = 1;
	//sleep(3);
	}
}
void loadtheflash(cardfirst, cardlast){
if (AllLoaded == 0) { loadingScreen(); }
while (keepgoing == 1) {
correctscore=0;
incorrectscore=0;
sprintf (correctscoreprint, "0");
sprintf (incorrectscoreprint, "0");
if (correctSelect == 1) {sprintf (correctSound, "./Sounds/harp.mp3");}
if (correctSelect == 2) {sprintf (correctSound, "./Sounds/great.mp3");}
if (incorrectSelect == 1) {sprintf (incorrectSound, "./Sounds/dong.mp3");}
if (incorrectSelect == 2) {sprintf (incorrectSound, "./Sounds/boo.mp3");}

	xix= 1;
	while (firstcard <= lessonlength){
		carr[0] = xix;
		carr[1] = xix+1;
		carr[2] = xix+2;
		carr[3] = xix+3;
		sarr[0] = xix;
		sarr[1] = xix+1;
		sarr[2] = xix+2;
		sarr[3] = xix+3;
		
		shuffleElements(carr, 4);
		shuffleElements(sarr, 4);
		
		soundcall = 0;
		showthecards(cardfirst, cardlast);
		if (tutorialcheck == 1) { showthecards(cardfirst, cardlast); tutorial();}
		while ( firstcard <= (cardlast + 1) ){
			scorechecked = 0;
			showthecards(cardfirst, cardlast);
			sprintf (audType, "mp3");
			sprintf (flashsound, "./Languages/%s%02d_%02d/%s%02d%02dS/%s%02d%02d%02d.%s", langSoundDir, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, sarr[soundcall], audType);
				FileExist = (stat(flashsound,&f__stat) != 0);	//if file exists returns 0, if does not exist returns 1
				if (FileExist == 0) {
					myrksAudioLoad(flashsound);
					rksAudioSetPlaybackRate(10000);
					rksAudioPlay();
					audioType = 2;
				}
				else {
					sprintf (audType, "SWA");
					sprintf (flashsound, "./Languages/%s%02d_%02d/%s%02d%02dS/%s%02d%02d%02d.%s", langSoundDir, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, sarr[soundcall], audType);
					//rksAudioInit();
					myrksAudioLoad(flashsound);
					//rksPlayViewSetFrameCount(rksAudioDuration());
					rksAudioSetPlaybackRate(5000);
					rksAudioPlay();
					audioType = 1;
				}
			done = 0;
			while (done == 0) {
				SceCtrlData pad, lastpad;
				sceCtrlReadBufferPositive(&lastpad, 1);
				sceCtrlReadBufferPositive(&pad, 1);
				lastpad = pad;
					if(pad.Buttons & PSP_CTRL_SELECT){
						showthecards(cardfirst, cardlast);
						SelectedLine = 1;
						selectOptionsMenu();
						freeImage(SelectMenuPNG);
						showthecards(cardfirst, cardlast);
						
						sprintf (audType, "mp3");
						sprintf (flashsound, "./Languages/%s%02d_%02d/%s%02d%02dS/%s%02d%02d%02d.%s", langSoundDir, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, sarr[soundcall], audType);
						FileExist = (stat(flashsound,&f__stat) != 0);	//if file exists returns 0, if does not exist returns 1
						if (FileExist == 0) {audioType = 2;}
						else {
							sprintf (audType, "SWA");
							sprintf (flashsound, "./Languages/%s%02d_%02d/%s%02d%02dS/%s%02d%02d%02d.%s", langSoundDir, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, sarr[soundcall], audType);
							audioType = 1;
						}
						if (audioType == 1) {
							myrksAudioLoad(flashsound);
							rksAudioSetPlaybackRate(5000);
							rksAudioPlay();
						}
						if (audioType == 2) {
							myrksAudioLoad(flashsound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
						}
					}
					else if(pad.Buttons & PSP_CTRL_START){
						showthecards(cardfirst, cardlast);
						SelectedLine = 1;
						selectOptionsMenu();
						freeImage(SelectMenuPNG);
						showthecards(cardfirst, cardlast);
						
						sprintf (audType, "mp3");
						sprintf (flashsound, "./Languages/%s%02d_%02d/%s%02d%02dS/%s%02d%02d%02d.%s", langSoundDir, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, sarr[soundcall], audType);
						FileExist = (stat(flashsound,&f__stat) != 0);	//if file exists returns 0, if does not exist returns 1
						if (FileExist == 0) {audioType = 2;}
						else {
							sprintf (audType, "SWA");
							sprintf (flashsound, "./Languages/%s%02d_%02d/%s%02d%02dS/%s%02d%02d%02d.%s", langSoundDir, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, langSoundMp3, roseUnit, roseLesson, sarr[soundcall], audType);
							audioType = 1;
						}
						if (audioType == 1) {
							myrksAudioLoad(flashsound);
							rksAudioSetPlaybackRate(5000);
							rksAudioPlay();
						}
						if (audioType == 2) {
							myrksAudioLoad(flashsound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
						}					
					}
				else if(pad.Buttons & PSP_CTRL_LTRIGGER){
					if (firstcard >= 4) { done = 3; break;}
				}
				else if(pad.Buttons & PSP_CTRL_RTRIGGER){
					if (firstcard < (lessonlength - 4)) { done = 4; break;}
				}
				else if(pad.Buttons & cardreplay){
						if (audioType == 1) {
							myrksAudioLoad(flashsound);
							rksAudioSetPlaybackRate(5000);
							rksAudioPlay();
							sleep(1);
						}
						if (audioType == 2) {
							myrksAudioLoad(flashsound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							sleep(1);
						}	
				}
				else if(pad.Buttons & cardslowreplay){
					if (audioType == 1) {
							myrksAudioLoad(flashsound);
							rksAudioSetPlaybackRate(4000);
							rksAudioPlay();
							sleep(1);
						}
						if (audioType == 2) {
							myrksAudioLoad(flashsound);
							rksAudioSetPlaybackRate(8000);
							rksAudioPlay();
							sleep(1);
						}	
				}
				else if (firstcard == (cardlast - 2)){
					if(pad.Buttons & cardselect1){
						// MP3_Init(1);
						if (sarr[soundcall] == carr[0]){
							correctanswer(1);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(1);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect2){
						if (sarr[soundcall] == carr[2]){
							correctanswer(3);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(3);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect3){
						if (sarr[soundcall] == carr[1]){
							correctanswer(2);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(2);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect4){
						if (sarr[soundcall] == carr[3]){
							correctanswer(4);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(4);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
				}
				else if (firstcard == (cardlast - 1)){
					if(pad.Buttons & cardselect1){
						if (sarr[soundcall] == carr[0]){
							correctanswer(1);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(1);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect2){
						if (sarr[soundcall] == carr[2]){
							correctanswer(3);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(3);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect3){
						if (sarr[soundcall] == carr[1]){
							correctanswer(2);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(2);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect4){
						if (sarr[soundcall] == carr[3]){
							correctanswer(4);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(4);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
				}
				else if (firstcard == cardlast){
					if(pad.Buttons & cardselect1){
						if (sarr[soundcall] == carr[0]){
							correctanswer(1);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(1);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect2){
						if (sarr[soundcall] == carr[2]){
							correctanswer(3);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(3);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect3){
						if (sarr[soundcall] == carr[1]){
							correctanswer(2);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(2);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect4){
						if (sarr[soundcall] == carr[3]){
							correctanswer(4);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(4);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
				}
				else if (firstcard == (cardlast + 1)){
					if(pad.Buttons & cardselect1){
						if (sarr[soundcall] == carr[0]){
							correctanswer(1);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(1);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect2){
						if (sarr[soundcall] == carr[2]){
							correctanswer(3);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							shuffleElements(carr, 4);
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(3);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect3){
						if (sarr[soundcall] == carr[1]){
							correctanswer(2);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(2);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
					else if (pad.Buttons & cardselect4){
						if (sarr[soundcall] == carr[3]){
							correctanswer(4);
							myrksAudioLoad(correctSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							
							done = 1 ;
						} else {
							incorrectanswer(4);scorechecked=1;
							
							myrksAudioLoad(incorrectSound);
							rksAudioSetPlaybackRate(10000);
							rksAudioPlay();
							showthecards(cardfirst, cardlast);
							if (audioType == 1) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(5000);
								rksAudioPlay();
							}
							if (audioType == 2) {
								myrksAudioLoad(flashsound);
								rksAudioSetPlaybackRate(10000);
								rksAudioPlay();
							}
						}
					}
				}
			}
			if (done == 2) {break;}
			if (done == 3) {break;}
			if (done == 4) {break;}
			firstcard++;
			soundcall++;
		}
		if (done == 1) {cardlast+=4;	xix=(xix + 4); }
		if (done == 2) {break;}
		if (done == 3) {
			if (firstcard > 36) { firstcard = 33; cardlast -= 4;xix=(xix - 4);}
			else if (firstcard > 32) { firstcard = 29; cardlast -= 4;xix=(xix - 4);}
			else if (firstcard > 28) { firstcard = 25; cardlast -= 4;xix=(xix - 4);}
			else if (firstcard > 24) { firstcard = 21; cardlast -= 4;xix=(xix - 4);}
			else if (firstcard > 20) { firstcard = 17; cardlast -= 4;xix=(xix - 4);}
			else if (firstcard > 16) { firstcard = 13; cardlast -= 4;xix=(xix - 4);}
			else if (firstcard > 12) { firstcard = 9; cardlast -= 4;xix=(xix - 4);}
			else if (firstcard > 8) { firstcard = 5; cardlast -= 4;xix=(xix - 4);}
			else if (firstcard > 4) { firstcard = 1; cardlast -= 4;xix=(xix - 4);}
		}
		if (done == 4) {
			if (firstcard < 4) { firstcard = 5; cardlast += 4;xix=(xix + 4);}
			else if (firstcard < 8) { firstcard = 9; cardlast += 4;xix=(xix + 4);}
			else if (firstcard < 12) { firstcard = 13; cardlast += 4;xix=(xix + 4);}
			else if (firstcard < 16) { firstcard = 17; cardlast += 4;xix=(xix + 4);}
			else if (firstcard < 20) { firstcard = 21; cardlast += 4;xix=(xix + 4);}
			else if (firstcard < 24) { firstcard = 25; cardlast += 4;xix=(xix + 4);}
			else if (firstcard < 28) { firstcard = 29; cardlast += 4;xix=(xix + 4);}
			else if (firstcard < 32) { firstcard = 33; cardlast += 4;xix=(xix + 4);}
			else if (firstcard < 36) { firstcard = 37; cardlast += 4;xix=(xix + 4);}
		}
		done = 0;
	}
	SelectedLine = 1;
	firstcard=1;
	sprintf (readText," ");
	scoreCardStatus = 0;
	showthecards(cardfirst, cardlast);
	showScoreCard();
	freeImage(SelectMenuPNG);
}
}
int main(){
//TTF_Init();
//TTF_Font *fntCourier = TTF_OpenFont( "./cour.ttf", 12 );
//SDL_Surface *screen;
//scePowerSetClockFrequency(333, 333, 166);
initGraphics();
//pspAudioInit();
//loadthefont();

    /* Initialize SDL */
    /*if (SDL_Init (SDL_INIT_VIDEO|SDL_INIT_JOYSTICK) < 0)
    {
#ifdef _WIN32
        sprintf (msg, "Couldn't initialize SDL: %s\n", SDL_GetError ());
        MessageBox (0, msg, "Error", MB_ICONHAND); 
        free (msg);
#endif
        exit (1);
    }
    atexit (SDL_Quit);

	TTF_Init();

     Set 640x480 16-bits video mode 
    screen = SDL_SetVideoMode (480, 272, 32, SDL_SWSURFACE);
    if (screen == NULL)
    {
#ifdef _WIN32
        sprintf (msg, "Couldn't set 480x272x16 video mode: %s\n",
          SDL_GetError ());
        MessageBox (0, msg, "Error", MB_ICONHAND); 
        free (msg);
#endif
        exit (2);
    }
    SDL_WM_SetCaption ("PSPFlashcard SDL by HardHat", NULL);

	SDL_Joystick *joy=0;
	if(SDL_NumJoysticks()>0)
	   joy=SDL_JoystickOpen(0);

    

    done = 0;
	//SDL_Rect rect;
//	SDL_Delay(3000);	
	//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 255, 255));
	headline=TTF_OpenFont("./cour.ttf",24);
	subhead=TTF_OpenFont("./cour.ttf",18);
	//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 255));
	body=TTF_OpenFont("./cour.ttf",12);
	//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 0, 255));
	prompt=TTF_OpenFont("./cour.ttf",8);
    //SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0x7f, 0x7f));





//bgskin=SDL_LoadBMP("bg.bmp");
//SDL_BlitSurface(bgskin,0,screen,0);
*/


	load_font("./cour.TTF");	// load "times new roman" font
	

splash = loadImage("./Images/splash.png");
logo = loadImage("./Images/logo.png");

sprite = loadImage ("./Images/control.png");

// Application Start
	while(1){
		loadtheflash(0,3);
		keepgoing = 1;
	}
	
// End The Madness
//Font_Unload(othFont); //UNLOAD othFont
sceKernelSleepThread();
sceKernelExitGame();
return 0;
}//hardhat for general assistance with coding issues, insertwittyname for image resizing.
