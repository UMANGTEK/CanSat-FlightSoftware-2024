
String addZeroSuffix(String st, int n)      //Add n 0 to end of string
{
  for(int i=0;i<n;i++)
    st = st + "0";
  
  return st;
}

String addZeroToPrefix(String st, int n)    //Add n 0 to strat of string
{
  for(int i=1;i<=n;i++)
    st = "0" + st;

  return st;
}

String printFloat(float val, int totalLength, int decimalPlaces, bool valid) {
  String stringValue;
  if(valid == true)
  {
    // Convert float to string with desired number of decimal places
    stringValue = String(val, decimalPlaces);
  
    // Find the position of the decimal point
    int decimalIndex = stringValue.indexOf('.');
  
    // If no decimal point found, add one at the end
   if (decimalIndex == -1) {
      stringValue += ".";
      decimalIndex = stringValue.length() - 1;
    }
  
    // Calculate the number of zeros to add before the decimal point
    int zerosBefore = totalLength - stringValue.length();
  
    // Add zeros before and after the decimal point as required
    for (int i = 0; i < zerosBefore; ++i) {
     stringValue = "0" + stringValue;
    }
  
    // Calculate the number of zeros to add after the decimal point
    int zerosAfter = decimalPlaces - (stringValue.length() - decimalIndex - 1);
  
    // Add zeros after the decimal point as required
    for (int i = 0; i < zerosAfter; ++i) {
      stringValue += "0";
    }
  }
  else
  {
     for (int i=0; i<totalLength; i++)
      stringValue+="*";
  }

  
  return stringValue;
}


 String printInt(unsigned long val, int len, bool valid)    //Converts integer to string of appropriate length given sensor data is valid
{
  String finalStr="";
  if (valid)
  {
    String st = String(val);
    int zeroAtPrefix = len - (st.length());
    finalStr = addZeroToPrefix(st, zeroAtPrefix);
    return finalStr;
  }

  else
  {
    for (int i=0; i<len; i++)
      finalStr+="*";
  }
  return(finalStr);
}



String printStr(String str, int len, bool valid)
{
    int a =0;
    String stri="";
    if (valid)
    {
      int slen = str.length();
      for (int i=0; i<len; ++i)
          if (i<(len-slen))
              stri+=" ";
          else
          {
             stri+=str[a++];
          }
    }
    else
    {
      for (int i=0; i<len; ++i)
        stri+="*";
    }
    return stri;
}

String printDate(int day, int month, int year, bool valid)
{
    String date="";
    if (valid)
    {
        String d = String(day);
        String m = String(month);
        String yr = String(year);

         if(day/10 == 0)
        {
          d = "0" + d;
        }

        if (month/10==0)
        {
          m = "0" + m;
        }
        if (year/10==0)
        {
          yr = "0" + yr;
        }

        date = yr + ":" + m + ":" + d;
    }
    else
    {
        date="**********" ;  
    }
    return date;
}

String printTime(int hour, int minute, int second, bool valid)
{
    String tim="";
    if (valid)
    {
        String hr = String(hour);
        String min = String(minute);
        String sec = String(second);
        if(hour/10 == 0)
        {
          hr = "0" + hr;
        }

        if (minute/10==0)
        {
          min = "0" + min;
        }
        if (second/10==0)
        {
          sec = "0" + sec;
        }

        tim = hr + ":" + min + ":" +sec;
    }
    else
    {
        greenOFF();
        tim="********" ;  
    }
    return tim;
}
