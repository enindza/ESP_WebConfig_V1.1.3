void Bouncemixutest(){

  // debounce do dole
  // Update the Bounce instance :


  // debouncer.testprint();

  if (debouncer.rise()){
    if (config.Mode > 0 ) {config.Mode = 0;}
    else {config.Mode = 1; }
  }
  if (debouncer.doubleclick()){config.Mode = 2; debouncer.reset();}
  if (debouncer.longpress()){
    if (config.Mode == 0){
      config.Mode = 3; debouncer.reset();
    }
    else {config.Mode = 0;}
  }
}
