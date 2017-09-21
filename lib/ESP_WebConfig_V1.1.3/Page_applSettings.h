//
//  HTML PAGE
//
const char PAGE_ApplicationConfiguration[] PROGMEM = R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>Application Configuration</strong>
<hr>
Ocitavanja senzora:<br>
<form action="" method="get">
<table border="0"  cellspacing="0" cellpadding="3" style="width:350px" >
<tr><td align="right">Senzor 1:</td><td><input type="text" id="temp1" name="temp1" value=""></td><td id="mydynamicdata">Here comes the Dynamic Data in </td></tr>
<tr><td align="right">Senzor 2:</td><td><input type="text" id="temp2" name="temp2" value=""></td></tr>
<tr><td align="right">Senzor 3:</td><td><input type="text" id="temp3" name="temp3" value=""></td></tr>
<tr><td align="right">Senzor 4:</td><td><input type="text" id="temp4" name="temp4" value=""></td></tr>
<tr><td align="right">Senzor 5:</td><td><input type="text" id="temp5" name="temp5" value=""></td></tr>

<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
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
      if (server.argName(i) == "temp1") config.temp1 = urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "temp2") config.temp2 = urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "temp3") config.temp3 = urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "temp4") config.temp4 = urldecode(server.arg(i)).toInt();
      if (server.argName(i) == "temp5") config.temp5 = urldecode(server.arg(i)).toInt();
      }
      Serial.println("send app temp2: " + config.temp2);
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

  values += "temp1|" + (String) config.temp1 + "|input\n";
  values += "temp2|" +  (String) config.temp2 + "|input\n";
  values += "temp3|" +  (String) config.temp3 + "|input\n";
  values += "temp4|" +  (String) config.temp4 + "|input\n";
  values += "temp5|" +  (String) config.temp5 + "|input\n";
  values += "mydynamicdata|" + (String) millis() + "|div\n";

  server.send ( 200, "text/plain", values);
  Serial.print("1 ");
  Serial.println(__FUNCTION__);
  AdminTimeOutCounter=0;

}
