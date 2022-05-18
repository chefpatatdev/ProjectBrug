# ProjectBrug

Code van de programma's die zijn gemaakt om de brug te monitoren en besturen.
![Schematic](https://user-images.githubusercontent.com/59780719/168992573-c9e88081-6b85-41b0-b615-63509bee3d7f.jpg)


Het resultaat is dat we een brug hebben die we kunnen besturen vanop afstand via smartphone of pc.

# Arduino (Ricky)
Het arduino programma verbind de arduino met cayenne en stuurt de H-brug aan.
Ricky heeft de schakeling gemaakt en het arduino programma, Thibault heeft geholpen met opzoekwerk naar cayenne implementatie.

* Gebruikte library: https://github.com/myDevicesIoT/Cayenne-MQTT-Arduino
https://github.com/chefpatatdev/ProjectBrug/blob/main/BrugSturing.ino

* In het programma wordt er gebruik gemaakt van een state machine om de status van de brug bij te houden.  
state = 0 :stop  
state = 1 :bottomLimit switch  
state = 2 :topLimit switch  
state = 3 :bridge going up  
state = 4 :bridge going down

* De switchen zijn NO en verbonden via input_pullup dus er is geen extra weerstand nodig. De H-brug is gemaakt in volgende configuratie met IRF5210 en IRF3205.
![image](https://user-images.githubusercontent.com/59780719/168990188-9cd6bc53-60d3-431d-8670-a35bd4453de7.png)

!GEEN SERIAL PRINT TOEVOEGEN IN DE CODE!

# Rasberry pi (Jarne, Dries, Thibault)
De rasberry pi leest het rekstrookje in via de qwiic scale die het signaal versterkt van het rekstrookje. Ook zal het de waarden kunnen versturen via MQTT naar cayenne.

* Inlezen van qwiic scale en plotten naar matlpotlib *(Jarne en Thibault)
https://github.com/chefpatatdev/ProjectBrug/blob/main/inlezen-rekstrookje.py

* Wheatstone brug aan de qwiic scale *(Dries)
![image](https://user-images.githubusercontent.com/59780719/168990479-891f8897-4401-41ad-a796-87cc666bbe08.png)


