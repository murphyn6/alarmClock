# ATMEGA328P-Common_Timers
Common Timers used in various librarys for the atmega328P

The only parameter for both timers is speed, which is set to scale between 8 mhz and 16 mhz. This can be passed using F_CPU which should be defined with the speed set for the microcontroller. 

init100usTimer2 sets up a 100us per increment counter with a variable accesable via e_100microseconds which is only defined in the header and declared in the implimentation file. This also uses timer 2 register. 

init1msTimer0 sets up a 1 ms per increment counter with a varaiable accessable via e_milliseconds which is only defined in the header and declared in the implimentation file. This also uses timer 0 register.
