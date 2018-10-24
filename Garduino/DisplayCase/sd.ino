void logInteraction(String sensorName){

  String dataString = "";
  dataString+=sensorName;
  dataString+=",";
  dataString += " //datetime placeholder//"; // < rtc code goes here
  
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
