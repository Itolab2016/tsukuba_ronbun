#include "tsukuba_urg.h"

#define SAVEPOINT "urg_data.txt"
#define MEASURMENTANGLE 270.0

using namespace std;
using namespace qrk;

Urg_driver urg;
//ofstream urg_point(SAVEPOINT);


void print_data(const Urg_driver& urg, const vector<long>& data, long time_stamp)
{
#if 1
  // Shows only the front step
  int front_index = urg.step2index(0);
  cout << data[front_index] << " [mm], ("
    << time_stamp << " [msec])" << endl;

#else
  // Prints the X-Y coordinates for all the measurement points
  long min_distance = urg.min_distance();
  long max_distance = urg.max_distance();
  size_t data_n = data.size();
  for (size_t i = 0; i < data_n; ++i) {
    long l = data[i];
    if ((l <= min_distance) || (l >= max_distance)) {
      continue;
    }

    double radian = urg.index2rad(i);
    long x = static_cast<long>(l * cos(radian));
    long y = static_cast<long>(l * sin(radian));
    cout << "(" << x << ", " << y << ")" << endl;
  }
  cout << endl;
#endif
}



int open_URG(void)
{

  long baudrate=115200;    
  Urg_driver::connection_type_t c_type=Urg_driver::Serial;
  char device[]=LIDER;
  int cnt=0;
  while(!urg.open(device, baudrate, c_type)){
    printf("#%02d URG open error !\n",cnt);
    fflush(stdout);
    cnt++;
    sleep(1);
  }
  cout << "URG open !"<<endl; 
  urg.set_scanning_parameter(urg.deg2step(-MEASURMENTANGLE/2), urg.deg2step(+MEASURMENTANGLE/2), 0);
}



int get_urg_data(robot_t* robo)
{
  vector<long> data;
	//char str[255];
  long time_stamp = 0;

	//計測司令
  urg.start_measurement(Urg_driver::Distance, 1, 0);
	
	//計測データ取得
  if (!urg.get_distance(data, &time_stamp)) {
    cout << "Urg_driver::get_distance(): error" << endl;
    return 1;
  }
	for (int i=0; i<data.size(); i++){
		robo->urg_pt[i]=data[i];
	}

  return 0;
}
