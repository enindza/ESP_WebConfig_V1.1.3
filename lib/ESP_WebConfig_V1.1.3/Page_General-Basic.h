//
//  HTML PAGE
//

const char PAGE_AdminGeneralSettings[] PROGMEM =  R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="admin.html"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>General Settings</strong>
<hr>
<form action="" method="post">
<table border="0"  cellspacing="0" cellpadding="3" style="width:350px">
<tr>
	<td align="right">Name of Device</td>
	<td><input type="text" id="devicename" name="devicename" value=""></td>
</tr>

<tr>
	<td align="left" colspan="2"><hr></td>
</tr>

<tr>
	<td align="left" colspan="2">Timer 1 turn on at</td>
</tr>
<tr>
	<td align="right"> Enabled:</td>
	<td><input type="checkbox" id="tonenabled" name="tonenabled"></td>
</tr>

<tr>
	<td align="right"> Time:</td>
	<td><input type="text" id="tonhour" name="tonhour" size="2" value="00">:<input type="text" id="tonminute" name="tonminute" size="2" value="00"></td>
</tr>

<tr>
	<td align="left" colspan="2">Timer 1 turn off at:</td>
<tr>
	<td align="right"> Enabled:</td>
	<td><input type="checkbox" id="toffenabled" name="toffenabled"></td>
</tr>
<tr>
	<td align="right"> Time:</td>
	<td><input type="text" id="toffhour" name="toffhour" size="2" value="00">:<input type="text" id="toffminute" name="toffminute" size="2" value="00"></td>
</tr>

</table>

<table border="0"  cellspacing="0" cellpadding="3" style="width:350px" >

<tr>
	<td align="left" colspan="2"><hr></td>
</tr>

<tr>
	<td align="left" colspan="2">Timer 2 turn on at</td>
</tr>
<tr>
	<td align="right"> Enabled:</td>
	<td><input type="checkbox" id="tonenabled2" name="tonenabled2"></td>
</tr>

<tr>
	<td align="right"> Time:</td>
	<td><input type="text" id="tonhour2" name="tonhour2" size="2" value="00">:<input type="text" id="tonminute2" name="tonminute2" size="2" value="00"></td>
</tr>

<tr>
	<td align="left" colspan="2">Timer 2 turn off at:</td>
<tr>
	<td align="right"> Enabled:</td>
	<td><input type="checkbox" id="toffenabled2" name="toffenabled2"></td>
</tr>
<tr>
	<td align="right"> Time:</td>
	<td><input type="text" id="toffhour2" name="toffhour2" size="2" value="00">:<input type="text" id="toffminute2" name="toffminute2" size="2" value="00"></td>
</tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
</table>

</form>
<script>



window.onload = function ()
{
	load("style.css","css", function()
	{
		load("microajax.js","js", function()
		{
				setValues("/admin/generalvalues");
		});
	});
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}



</script>
)=====";


// Functions for this Page
//
//


void send_devicename_value_html()
{

	String values ="";
	values += "devicename|" + (String) config.DeviceName + "|div\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__);

}

void send_general_html()
{

	if (server.args() > 0 )  // Save Settings
	{
		config.AutoTurnOn = false;
		config.AutoTurnOff = false;
		config.AutoTurnOn2 = false;
		config.AutoTurnOff2 = false;
		String temp = "";
		for ( uint8_t i = 0; i < server.args(); i++ ) {
			if (server.argName(i) == "devicename") config.DeviceName = urldecode(server.arg(i));
			if (server.argName(i) == "tonenabled") config.AutoTurnOn = true;
			if (server.argName(i) == "toffenabled") config.AutoTurnOff = true;
			if (server.argName(i) == "tonhour") config.TurnOnHour =  server.arg(i).toInt();
			if (server.argName(i) == "tonminute") config.TurnOnMinute =  server.arg(i).toInt();
			if (server.argName(i) == "toffhour") config.TurnOffHour =  server.arg(i).toInt();
			if (server.argName(i) == "toffminute") config.TurnOffMinute =  server.arg(i).toInt();
			if (server.argName(i) == "tonenabled2") config.AutoTurnOn2 = true;
			if (server.argName(i) == "toffenabled2") config.AutoTurnOff2 = true;
			if (server.argName(i) == "tonhour2") config.TurnOnHour2 =  server.arg(i).toInt();
			if (server.argName(i) == "tonminute2") config.TurnOnMinute2 =  server.arg(i).toInt();
			if (server.argName(i) == "toffhour2") config.TurnOffHour2 =  server.arg(i).toInt();
			if (server.argName(i) == "toffminute2") config.TurnOffMinute2 =  server.arg(i).toInt();
		}
		WriteConfig();
		firstStart = true;
	}
	server.send ( 200, "text/html", PAGE_AdminGeneralSettings );
	Serial.println(__FUNCTION__);
}

void send_general_configuration_values_html()
{
	String values ="";
	values += "devicename|" +  (String)  config.DeviceName +  "|input\n";
	values += "tonhour|" +  (String)  config.TurnOnHour +  "|input\n";
	values += "tonminute|" +   (String) config.TurnOnMinute +  "|input\n";
	values += "toffhour|" +  (String)  config.TurnOffHour +  "|input\n";
	values += "toffminute|" +   (String)  config.TurnOffMinute +  "|input\n";
	values += "toffenabled|" +  (String) (config.AutoTurnOff ? "checked" : "") + "|chk\n";
	values += "tonenabled|" +  (String) (config.AutoTurnOn ? "checked" : "") + "|chk\n";
	values += "tonhour2|" +  (String)  config.TurnOnHour2 +  "|input\n";
	values += "tonminute2|" +   (String) config.TurnOnMinute2 +  "|input\n";
	values += "toffhour2|" +  (String)  config.TurnOffHour2 +  "|input\n";
	values += "toffminute2|" +   (String)  config.TurnOffMinute2 +  "|input\n";
	values += "toffenabled2|" +  (String) (config.AutoTurnOff2 ? "checked" : "") + "|chk\n";
	values += "tonenabled2|" +  (String) (config.AutoTurnOn2 ? "checked" : "") + "|chk\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__);
}
