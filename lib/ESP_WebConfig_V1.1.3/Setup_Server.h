void SetupServer(){
  //server.on ( "/", processExample  );
  server.on ( "/", []() { Serial.println("admin.html");	server.send ( 200, "text/html", PAGE_AdminMainPage ); } );
  server.on ( "/admin/filldynamicdata", filldynamicdata );

  server.on ( "/favicon.ico",   []() { Serial.println("favicon.ico"); server.send ( 200, "text/html", "" );   }  );

  server.on ( "/admin.html", []() { Serial.println("admin.html"); server.send ( 200, "text/html", PAGE_AdminMainPage );   }  );
  server.on ( "/config.html", send_network_configuration_html );
  server.on ( "/info.html", []() { Serial.println("info.html"); server.send ( 200, "text/html", PAGE_Information );   }  );
  server.on ( "/ntp.html", send_NTP_configuration_html  );
  server.on ( "/appl.html", send_application_configuration_html );
  server.on ( "/general.html", send_general_html  );
  server.on ( "/example.html", []() { server.send ( 200, "text/html", PAGE_example );  } );
  server.on ( "/style.css", []() { Serial.println("style.css"); server.send ( 200, "text/plain", PAGE_Style_css );  } );
  server.on ( "/microajax.js", []() { Serial.println("microajax.js"); server.send ( 200, "text/plain", PAGE_microajax_js );  } );
  server.on ( "/admin/values", send_network_configuration_values_html );
  server.on ( "/admin/connectionstate", send_connection_state_values_html );
  server.on ( "/admin/infovalues", send_information_values_html );
  server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
  server.on ( "/admin/applvalues", send_application_configuration_values_html );
  server.on ( "/admin/generalvalues", send_general_configuration_values_html);
  server.on ( "/admin/devicename",     send_devicename_value_html);
  server.on ( "/admin/singleheating", set_singleheating  );
  server.on ( "/admin/midsingleheating", set_midsingleheating  );
  server.on ( "/admin/manualturnoff", set_manualturnoff  );
  server.onNotFound ( []() { Serial.println("Page Not Found"); server.send ( 400, "text/html", "Page not Found" );   }  );
  server.begin();
  Serial.println( "HTTP server started" );
  tkSecond.attach(1,Second_Tick);
  //tkSecond.attach(0.5,Half_Second_Tick);
  tkSecond.attach(0.02,Debounce_Tick);

  UDPNTPClient.begin(2390);  // Port for NTP receive
}
