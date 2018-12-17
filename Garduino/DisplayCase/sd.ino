void logInteraction(String sensorName){

  String dataString = "";
  dataString+=sensorName;
  dataString+=F(",");
  dataString += F(" //datetime placeholder//"); // < rtc code goes here
  
  File dataFile = SD.open(F("datalog.txt"), FILE_WRITE);
  
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println(F("error opening datalog.txt"));
  }
}
