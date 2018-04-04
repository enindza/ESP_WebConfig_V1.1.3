# BlinkPattern

Arduino library still in testing.


The main aim of this code is to visualise difference between two values by different LED ON and OFF ratio. <br />
Intended use is for battery status indication, progress, hot or cold indication, etc. <br />
Pattern can be also set manualy to indicate error, saving info, etc.

Library function `Update()` will generate output based on current pattern. <br />
It is recommended that full cycle is finished in 1 second period. <br />
pattern 000000001 will look like short LED light pulse <br />
pattern 000000011 will look like slightly longer LED light pulse <br />
... <br />
pattern 011111111 will look like LED is ON with very short brake <br />
pattern 010101010 will look like LED is fast blinking <br />
etc <br />

Library function `BlinkPatternCreate(MaxValue, CurrentValue)` generates 7 different codes for patterns based on difference between two values.<br /> 
011111111 <br />
001111111 <br />
000111111 <br />
000011111 <br />
000001111 <br />
000000111 <br />
000000011 <br />
000000001 <br />

Pattern can be set manualy with function `BlinkPatternSet` <br />




