#include "tsukuba_tkk.h"

using namespace std;

int TOMAfd; //global
int TOMAlen;

unsigned char TOMAbuffer[TKK_BUFF_SIZE];    // データ受信バッファ

int Counter1=1;
int Counter2=1;

int rcounter1=0;
int rcounter2=0;
int mojicount=0;

long long *TOMAaddrido1,*TOMAaddrkeido1;
long long *TOMAaddrido2,*TOMAaddrkeido2;
int *TOMAaddrtakasa;

unsigned char *TOMAdummyido1,*TOMAdummykeido1;
unsigned char *TOMAdummyido2,*TOMAdummykeido2;
unsigned char *TOMAdummytakasa;

int p=0;

//double ido4=0.0,keido4=0.0,takasa3=0.0;

int TKK_serial(void);
int set_waypoint(void);

vector<double> latwaydata;
vector<double> lonwaydata;
vector<double> takasawaydata;

char file[]=GPSDATA;
char file2[]=GPSDATA2;
char file3[]=GPSDATA3;
char file4[]=GPSDATA4;


//txtに書き出し

ofstream GPSmanualidokeido(file); //manual

int open_TKK(void){

	// デバイスファイル（シリアルポート）オープン
	TOMAfd = open(TKK,O_RDWR);
	if(TOMAfd<0){
		// デバイスの open() に失敗したら
		printf("TKK motion sensor error!\n");
		exit(1);
	}
	TKK_serial();
	return 0;

}

int TKK_serial(void){

	struct termios tio;
	memset(&tio,0,sizeof(tio));
	tio.c_cflag = CS8 | CLOCAL | CREAD;
	tio.c_cc[VTIME] = 100;
	// ボーレートの設定
	cfsetispeed(&tio,TKK_BAUD_RATE);
	cfsetospeed(&tio,TKK_BAUD_RATE);
	// デバイスに設定を行う
	tcsetattr(TOMAfd,TCSANOW,&tio);
	
	return 0;

} 

int save_wp(robot_t *tkk){

	int i,k=1;
	int kouho=0,INS=0;
	int takasa1;
	float scale;

	char str[1024];

	long long ido1,keido1;
	double ido3,keido3,takasa2;
	double ido4,keido4,takasa3;
  vectar point1,point2,point;

	float pi=3.1415926535897;

	TOMAaddrido2=&ido1;
	TOMAaddrkeido2=&keido1;
	TOMAaddrtakasa=&takasa1;

	TOMAdummyido2= (unsigned char *)TOMAaddrido2;
	TOMAdummykeido2= (unsigned char *)TOMAaddrkeido2;
	TOMAdummytakasa= (unsigned char *)TOMAaddrtakasa;

	for(i=0;i<=TOMAlen;i++){ //受信データ初期化
		TOMAbuffer[i]=0;
	}

	// ここで受信待ち
	TOMAlen=read(TOMAfd,TOMAbuffer,TKK_BUFF_SIZE);

	if(TOMAlen==0){
		// read()が0を返したら、end of file
		// 通常は正常終了するのだが今回は無限ループ
		//     continue;
	}
	if(TOMAlen<0){
		printf("TKK 受信不可\n");
		// read()が負を返したら何らかのI/Oエラー
		exit(2);
	}
	// read()が正を返したら受信データ数

	// 受信したデータを 16進数形式で表示    
	for(i=0; i<TOMAlen; i++){
		unsigned char data=TOMAbuffer[i];
	//	printf("%02X ",TOMAbuffer[i]);

		//受信データは意味の塊ごとに先頭に16進数で　16 16 06 02　と言うデータがつくことになっているので
		//以下でそのデータを受信するごとに改行して表示するようになっている．
		switch(rcounter2){
			case 0:
				if (data==0x16)rcounter2++;
				else rcounter2=0;
				break;
			case 1:
				if (data==0x16)rcounter2++;
				else rcounter2=0;
				break;
			case 2:
				if (data==0x06)rcounter2++;
				else rcounter2=0;
				break;
			case 3:
				if (data==0x02){

			//		printf("\n");

					if(TOMAbuffer[i+7]==0x40){
						kouho=i+1;
					}
					else if(TOMAbuffer[i+7]==0x20){
						INS=i+1;
					//	printf("%d\n ",i);
					}
				
				}
				rcounter2=0;
				break;
		}
	} 

	if(TOMAbuffer[kouho+6]==0x40 /*&& TOMAbuffer[INS+7+38]==0x04 && TOMAbuffer[kouho+83]==0x16 && TOMAbuffer[INS+59]==0x16*/){ 
		//航法データ受け取っているか、GPSが有効であるか、INSデータと航法データが全部入っているか

		for(i=0;i<=3;i++){

			*TOMAdummytakasa=TOMAbuffer[kouho+i+7+57];
			
			*TOMAdummytakasa++;		

		}

		for(i=0;i<=7;i++){  		//緯度,経度を抽出

			*TOMAdummyido2=TOMAbuffer[kouho+i+7+41];
			*TOMAdummykeido2=TOMAbuffer[kouho+i+7+49];

			*TOMAdummyido2++;
			*TOMAdummykeido2++;


		}

		ido3= (double)ido1;		  //long→double
		keido3= (double)keido1;

		takasa2= (double)takasa1;
		takasa2=takasa2/(10*10*10*10);

		ido3=ido3*(180/pi);		  //ラジアン→度
		keido3=keido3*(180/pi);	

		ido3=ido3/(10*10*10*10*10*10*10*10*10);
		ido3=ido3/10;

		keido3=keido3/(10*10*10*10*10*10*10*10*10);
		keido3=keido3/10;

		point1 = blh2ecef(ido3, keido3, takasa2);
		point2 = blh2ecef(ido4, keido4, takasa3);
		point = ecef2enu(point1, point2);

		ido4=ido3;
		keido4=keido3;
		takasa3=takasa2;

		scale=sqrt(SQR(point.a[0])+SQR(point.a[1]));

		cout<<"scale="<<scale<<endl;

		tkk->lat=ido3;
		tkk->lon=keido3;	
		
		tkk->scale=scale;

	//	tkk->lat_goal=ido4;
	//	tkk->lon_goal=keido4;	

		printf("緯度2=%lf 経度2=%lf 高度=%lf \n",ido3,keido3,takasa2);

		//緯度経度データをtxt化
		sprintf(str,"%d\t%lf\t%lf\t%d",Counter2++,ido3,keido3,k);
		GPSmanualidokeido<<str<<endl;
						
		return 1;
	}

	else return 0;


}

