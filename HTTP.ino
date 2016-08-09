 
//SubmitHttpRequest()
//this function is submit a http request
//attention:the time of delay is very important, it must be set enough 
void SubmitHttpRequest()
{
  Serial1.println("AT+CSQ");
  delay(100);
  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
  Serial1.println("AT+CGATT?");
  delay(100);
  ShowSerialData();
  Serial1.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
  delay(1000);
  ShowSerialData();
  Serial1.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");//setting the APN, the second need you fill in your local apn server
  delay(4000);
  ShowSerialData();
  Serial1.println("AT+SAPBR=1,1");//setting the SAPBR, for detail you can refer to the AT command mamual
  delay(2000);
  ShowSerialData();
  Serial1.println("AT+HTTPINIT"); //init the HTTP request
  delay(2000); 
  ShowSerialData();
  //Serial1.println("AT+HTTPPARA=\"URL\",\"www.google.co.id\"");// setting the httppara, the second parameter is the website you want to access
  //www.google.com.hk
  //www.google.co.id
  // http://admin.tf.itb.ac.id/landslide/savedata(1).php?titiklokasi=ngawi&percepatanX=20&percepatanY=30&percepatanZ=75&kecepatanX=75&kecepatanY=75&kecepatanZ=75&status=waspada
  //Serial1.println("AT+HTTPPARA=\"URL\",\"http://admin.tf.itb.ac.id/landslide/savedata(1).php?titiklokasi=madiun&percepatanX=20&percepatanY=30&percepatanZ=75&kecepatanX=75&kecepatanY=75&kecepatanZ=75&status=ganteng\"");
  // "http://ta.tf.itb.ac.id/smart_building/landslide/savedata.php?titiklokasi=klitik&percepatanX=20&percepatanY=20&percepatanZ=80&kecepatanX=80&kecepatanY=75&kecepatanZ=75&status=waspada"
  Serial1.print("AT+HTTPPARA=\"URL\",\"http://ta.tf.itb.ac.id/smart_building/landslide/savedata.php?titiklokasi=");
  Serial1.print(Tempat);
  Serial1.print("&kecepatanX=");
  Serial1.print(kecepatanX);
  Serial1.print("&kecepatanY=");
  Serial1.print(kecepatanY);
  Serial1.print("&kecepatanZ=");
  Serial1.print(kecepatanZ);
  Serial1.print("&status=");
  Serial1.print(Kondisi);
  Serial1.println("\""); 
  delay(1000);
  ShowSerialData();
  Serial1.println("AT+HTTPACTION=0");//submit the request 
  delay(10000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
  //while(!Serial1.available());
  ShowSerialData();
  Serial1.println("AT+HTTPREAD");// read the data from the website you access
  delay(300);
  ShowSerialData();
  Serial1.println("");
  delay(100);
}
