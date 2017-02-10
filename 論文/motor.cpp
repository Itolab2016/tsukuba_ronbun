#include"motor.h"
//#include "joystick.h"
#include "tsukuba_time.h"

using namespace std;

static int fd_L,fd_R;


void serial_init(int fd)
{
  struct termios tio;
  memset(&tio,0,sizeof(tio));
  tio.c_cflag = CS8 | CLOCAL | CREAD;
  tio.c_cc[VTIME] = 100;
  // ボーレートの設定
  cfsetispeed(&tio,B57600);
  cfsetospeed(&tio,B57600);
  // デバイスに設定を行う
  tcsetattr(fd,TCSANOW,&tio);
}

void serial(int fd,int send){
  char str[5];
  int len=sprintf(str, "%d\r", send);
  tcflush(fd,TCOFLUSH);
  if(write(fd, str ,len )==-1){
    printf("Motor error !\n");
    exit(1);
  }
}

int motor_open(void){
	fd_L = open(SERIAL_PORT1,O_RDWR);
	fd_R = open(SERIAL_PORT2,O_RDWR);
	serial_init(fd_L);
	serial_init(fd_R);
	if(fd_L<1 or fd_R<1){
		cout<<"moter_error"<<endl;
		exit(1);
		return 0;
	}
	return 1;
}

int motor_close(void){
	close(fd_L);
	close(fd_R);
	
	return 0;
}

int motor_remote(robot_t *IH){

	IH->motor_v=get_joy_stickY()*MAX_V;
	IH->motor_o=-get_joy_stickX()*MAX_OMEGA;
	
	return 0;
}

int motor_command(robot_t *IH){
	int L,R;
	float v=IH->motor_v;
	float omega=IH->motor_o;

//  return 0;

	L=( ( v - omega ) + 1.0 )*500;
	R=( ( v + omega ) + 1.0 )*500;
	
	if ( L > 900.0 ) {
		L = 900.0;
	}
	if ( L < 100.0 ) {
		L = 100.0;
	}
	if ( R > 900.0 ) {
		R = 900.0;
	}
	if ( R < 100.0 ) {
		R = 100.0;
	}
 
	serial(fd_L,(int)L);
	serial(fd_R,(int)R);

  IH->motor_l=L;
	IH->motor_r=R;
		//cout<<L<<"___"<<R<<endl;

	return 0;

	}
