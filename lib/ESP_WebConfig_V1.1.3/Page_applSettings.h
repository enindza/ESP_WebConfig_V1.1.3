//
//  HTML PAGE
//
const char PAGE_ApplicationConfiguration[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Application Configuration</strong>
<hr><strong>
Sensor reading:<br><br>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" style="width:350px" >
<tr><td align="right">ID</td><td align="left"> Sensor serial </td><td align="left"> Sensor location </td><td align="left"> Temperature </td></tr>
<tr><td align="right">0:</td><td id="I2Cadd0"> Dinamic data </td><td><input type="text" id="temp1" name="temp1" value=""></td><td id="s1read">Here comes the Dynamic Data in </td></tr>
<tr><td align="right">1:</td><td id="I2Cadd1"> Dinamic data </td><td><input type="text" id="temp2" name="temp2" value=""></td><td id="s2read">Here comes the Dynamic Data in </td></tr>
<tr><td align="right">2:</td><td id="I2Cadd2"> Dinamic data </td><td><input type="text" id="temp3" name="temp3" value=""></td><td id="s3read">Here comes the Dynamic Data in </td></tr>
<tr><td align="right">3:</td><td id="I2Cadd3"> Dinamic data </td><td><input type="text" id="temp4" name="temp4" value=""></td><td id="s4read">Here comes the Dynamic Data in </td></tr>
<tr><td align="right">4:</td><td id="I2Cadd4"> Dinamic data </td><td><input type="text" id="temp5" name="temp5" value=""></td><td id="s5read">Here comes the Dynamic Data in </td></tr>

<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
</table>
<hr>
<strong>List connected sensors:</strong><br>
<table border="0"  cellspacing="3" style="width:350px" >
<tr><td align="left"> Sensor serial </td><td align="right"> Sensor temperature </td><td align="right"> Set ID number </td></tr>
<tr><td id="I2C0"> Not available </td><td align="right" id="I2Ctemp0">--.-- </td><td><input type="text" id="LinkID0" name="LinkID0" value="99"></td></tr>
<tr><td id="I2C1"> Not available </td><td align="right" id="I2Ctemp1">--.-- </td><td><input type="text" id="LinkID1" name="LinkID1" value="99"></td></tr>
<tr><td id="I2C2"> Not available </td><td align="right" id="I2Ctemp2">--.-- </td><td><input type="text" id="LinkID2" name="LinkID2" value="99"></td></tr>
<tr><td id="I2C3"> Not available </td><td align="right" id="I2Ctemp3">--.-- </td><td><input type="text" id="LinkID3" name="LinkID3" value="99"></td></tr>
<tr><td id="I2C4"> Not available </td><td align="right" id="I2Ctemp4">--.-- </td><td><input type="text" id="LinkID4" name="LinkID4" value="99"></td></tr>
</table>
<table border="0"  cellspacing="3" style="width:350px" >
<tr><td align="center"><a href="javascript:GetState()" style="width:150px" class="btn btn--m btn--blue">Refresh</a></td></tr>
</table>
</form>

<script>

function GetState()
{
  setValues("/admin/applvalues");
}


window.onload = function ()
{
  load("style.css","css", function()
  {
    load("microajax.js","js", function()
    {
          setValues("/admin/applvalues");

    });
  });
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}

</script>


)=====";


//
//  SEND HTML PAGE OR IF A FORM SUMBITTED VALUES, PROCESS THESE VALUES
//

void send_application_configuration_html()
{
  if (server.args() > 0 )  // Save Settings
  {
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      if (server.argName(i) == "temp1") config.SensName0 = urldecode(server.arg(i)); //urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "temp2") config.SensName1 = urldecode(server.arg(i)); //urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "temp3") config.SensName2 = urldecode(server.arg(i)); //urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "temp4") config.SensName3 = urldecode(server.arg(i)); //urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "temp5") config.SensName4 = urldecode(server.arg(i)); //urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "LinkID0") config.LinkID[0] = urldecode(server.arg(i)).toInt(); //urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "LinkID1") config.LinkID[1] = urldecode(server.arg(i)).toInt(); //urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "LinkID2") config.LinkID[2] = urldecode(server.arg(i)).toInt(); //urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "LinkID3") config.LinkID[3] = urldecode(server.arg(i)).toInt(); //urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "LinkID4") config.LinkID[4] = urldecode(server.arg(i)).toInt();
    }
      Serial.println("send app temp2: " + config.temp2);
      for (uint8_t i = 0; i < 5; i++){
        if (config.LinkID[i] >= 0 and config.LinkID[i] < 5){
          if (numberOfDevices > i){
          sensors.getAddress(tempDeviceAddress, i);
          CopySensorAddress(config.SensorID, config.LinkID[i] , tempDeviceAddress);
          }
          else {for (uint8_t j = 0; j < 8; j++){config.SensorID[config.LinkID[i]][j] = 255;}
          }
        }
      }
    //if (config.wayToStation>20) config.wayToStation=20;
    //if (config.wayToStation<0) config.wayToStation=0;

    //if (config.warningBegin>10) config.warningBegin=10;
    //if (config.warningBegin<0) config.warningBegin=0;

    WriteConfig();
  }
   server.send ( 200, "text/html", PAGE_ApplicationConfiguration );
  Serial.println(__FUNCTION__);
}



//
//   FILL THE PAGE WITH VALUES
//

void send_application_configuration_values_html()
{

  String values ="";

  values += "temp1|" + (String) config.SensName0 + "|input\n";
  values += "temp2|" +  (String) config.SensName1 + "|input\n";
  values += "temp3|" +  (String) config.SensName2 + "|input\n";
  values += "temp4|" +  (String) config.SensName3 + "|input\n";
  values += "temp5|" +  (String) config.SensName4 + "|input\n";

  values += "I2Cadd0|" + (String) bin_to_strhex(config.SensorID[0], 8) + "|div\n";
  values += "I2Cadd1|" + (String) bin_to_strhex(config.SensorID[1], 8) + "|div\n";
  values += "I2Cadd2|" + (String) bin_to_strhex(config.SensorID[2], 8) + "|div\n";
  values += "I2Cadd3|" + (String) bin_to_strhex(config.SensorID[3], 8) + "|div\n";
  values += "I2Cadd4|" + (String) bin_to_strhex(config.SensorID[4], 8) + "|div\n";
  values += "s1read|" + (String) sensors.getTempC(config.SensorID[0]) + "|div\n";
  values += "s2read|" + (String) sensors.getTempC(config.SensorID[1]) + "|div\n";
  values += "s3read|" + (String) sensors.getTempC(config.SensorID[2]) + "|div\n";
  values += "s4read|" + (String) sensors.getTempC(config.SensorID[3]) + "|div\n";
  values += "s5read|" + (String) sensors.getTempC(config.SensorID[4]) + "|div\n";
  if (numberOfDevices > 0) {
  sensors.getAddress(tempDeviceAddress, 0);
  values += "I2C0|" + (String) bin_to_strhex(tempDeviceAddress, 8) + "|div\n";
  values += "I2Ctemp0|" + (String) sensors.getTempC(tempDeviceAddress) + "|div\n";
  values += "LinkID0|" +  (String) GetSensorID(config.SensorID, tempDeviceAddress) + "|input\n";}
  if (numberOfDevices > 1) {
  sensors.getAddress(tempDeviceAddress, 1);
  values += "I2C1|" + (String) bin_to_strhex(tempDeviceAddress, 8) + "|div\n";
  values += "I2Ctemp1|" + (String) sensors.getTempC(tempDeviceAddress) + "|div\n";
  values += "LinkID1|" +  (String) GetSensorID(config.SensorID, tempDeviceAddress) + "|input\n";}
  if (numberOfDevices > 2) {
  sensors.getAddress(tempDeviceAddress, 2);
  values += "I2C2|" + (String) bin_to_strhex(tempDeviceAddress, 8) + "|div\n";
  values += "I2Ctemp2|" + (String) sensors.getTempC(tempDeviceAddress) + "|div\n";
  values += "LinkID2|" +  (String) GetSensorID(config.SensorID, tempDeviceAddress) + "|input\n";}
  if (numberOfDevices > 3) {
  sensors.getAddress(tempDeviceAddress, 3);
  values += "I2C3|" + (String) bin_to_strhex(tempDeviceAddress, 8) + "|div\n";
  values += "I2Ctemp3|" + (String) sensors.getTempC(tempDeviceAddress) + "|div\n";
  values += "LinkID3|" +  (String) GetSensorID(config.SensorID, tempDeviceAddress) + "|input\n";}
  if (numberOfDevices > 4) {
  sensors.getAddress(tempDeviceAddress, 4);
  values += "I2C4|" + (String) bin_to_strhex(tempDeviceAddress, 8) + "|div\n";
  values += "I2Ctemp4|" + (String) sensors.getTempC(tempDeviceAddress) + "|div\n";
  values += "LinkID4|" +  (String) GetSensorID(config.SensorID, tempDeviceAddress) + "|input\n";}
  server.send ( 200, "text/plain", values);
  Serial.print("1 ");
  Serial.println(__FUNCTION__);
  AdminTimeOutCounter=0;

}
