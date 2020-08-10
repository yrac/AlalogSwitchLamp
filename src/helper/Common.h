
//Function to convert time to milisecond
//in order to get excact larger time as day time
int ToMilis(int hh, int mm){
  int res = (hh * 60 * 60) + (mm * 60);
  return res;
}