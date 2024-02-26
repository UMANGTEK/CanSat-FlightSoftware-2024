 #define MOVINGAVG 5
#define ALT_DIFF 2  //Minimum difference between two altitude values to consider CanSat moving
#define FRACTION 0.6    //If MOVINGAVG is 10 and FRACTION is set to 0.7, the function will return true if at least 70% (7 out of 10) of the altitude values are inc or dec.
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
    if ( (arr[i] > arr[i-1]) && ((arr[i] - arr[i-1]) > ALT_DIFF)){
      j++;
    }
  }
  if ( j >= FRACTION * MOVINGAVG ){
    return true;
  }
  else {
    return false;
  }
}

bool movingDown(){
  int j = 0;
  for(int i=1;i<MOVINGAVG ;i++){
    if ( arr[i] < arr[i-1] && ((arr[i-1] - arr[i]) > ALT_DIFF)){
      j++;
    }
  }
  if ( j >= FRACTION*MOVINGAVG ){
    return true;
  }
  else {
    return false;
  }
}

bool notMoving(float ERR_DIFF){
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
