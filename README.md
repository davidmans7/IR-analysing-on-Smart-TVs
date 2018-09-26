# IR analysing on Smart TVs

This project is aimed to study infrared communitations, focused on those between TV controls and TVs.  
Within the project, two Arduino libraries are used:  
######     1. *IRLremote* Arduino library developed by Nico Hood.  
> [Available here: https://github.com/NicoHood/IRLremote](https://github.com/NicoHood/IRLremote)
######     2. *IRremote* Arduino library from Ken Shirriff y Rafi Khan.  
> [Available here: https://github.com/z3t0/Arduino-IRremote](https://github.com/z3t0/Arduino-IRremote)  

There are two scripts that read, decode and display IR signals:  
######     1. *rcv_IRLremote*: this script uses IRLremote Arduino library (above-mentioned).  
######     2. *rcv_IRremote*:  this script uses IRremote Arduino library (above-mentioined).  
There is also one more third script, quite different from previous two ones:
######     3. *matrix_guess*:  
Third script named *matrix_guess* treats to simulate one attack to a Smart TV.  
Imagine a user seated in front of his LG SmartTV typing on his TV control his Netflix password.  
QWERTY alphanumeric Netflix on-screen keyboard is supposed to perform this trial:  
  
![Netflix_kb_image](https://raw.githubusercontent.com/davidmans7/IR-analysing-on-Smart-TVs/master/test_cases/netflix_keyboard.jpg)
  
Script catches IR signals from UP, DOWN, LEFT, RIGHT and OK keys on TV control and treats to guess user data using that Netflix keyboard.
