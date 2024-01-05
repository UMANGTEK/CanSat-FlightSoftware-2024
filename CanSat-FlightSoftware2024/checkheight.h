#define MOVINGAVG 5
#define ERR_DIFF 1
#define FRACTION 0.6
float arr[MOVINGAVG]={0,0,0,0,0}; // add more zeros here if u are increasing MOVINGAVG
/*
void updateAlt(float alt  )
{
  for(int i=0;i<MOVINGAVG-1;i++){
    arr[i] = arr[i+1];
  }
  arr[MOVINGAVG-1] = alt;
}
float getFiltered(){
  int mean=0;
  for(int i=0; i<MOVINGAVG; i++){
    mean+= arr[i];
  }
  mean = mean/MOVINGAVG;
  return ( mean );
}
*/
#define ALPHA 0.9
float y = 0;
void updateAlt(float alt  )
{
  y = y * ( 1 - ALPHA ) + ALPHA * alt ;
  
  for(int i=0;i<MOVINGAVG-1;i++){
    arr[i] = arr[i+1];
  }
  arr[MOVINGAVG-1] = alt;
}
float getFiltered(){
  return(y);
}

bool checkAlt(float lessthanAlti) {
  float mean = getFiltered();
  if( mean > lessthanAlti  ){
    return false;
  }
  else{
    return true;
  }
}
bool movingUp(){
  int j = 0;
  for(int i=1;i<MOVINGAVG ;i++){
    if ( arr[i] > arr[i-1] ){
      j++;
    }
  }
  if ( j > FRACTION * MOVINGAVG ){
    return true;
  }
  else {
    return false;
  }
}

bool movingDown(){
  int j = 0;
  for(int i=1;i<MOVINGAVG ;i++){
    if ( arr[i] < arr[i-1] ){
      j++;
    }
  }
  if ( j > FRACTION*MOVINGAVG ){
    return true;
  }
  else {
    return false;
  }
}

bool notMoving (){
  int j = 0;
  float filtered_alt = getFiltered();
  for(int i=0;i<MOVINGAVG ;i++){
    if ( arr[i] < filtered_alt + ERR_DIFF && arr[i] > filtered_alt - ERR_DIFF ){
      j++;
    }
  }
  if ( j == MOVINGAVG-1 ){
    return true;
  }
  else {
    return false;
  }
}
