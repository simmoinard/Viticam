# Viticam
Le projet Viticam permet de développer une caméra connectée qui envoie des photos à intervalle régulière.
Le système comprend principalement un bloc "Acquisition & envoi de l'imagea, et un bloc "Allumage et Mise en veille du système" : 

- Un bloc "Acquisition et envoi de l'image"
  - Une Raspberry Pi zero
  - Une PiCam V2.1 reliée au Raspberry par le connecteur caméra
  - Un dongle 4G fonctionnel (et une carte SIM avec forfait 50Mo/mois minimum)
- Un bloc "Allumage et Mise en veille du système"
  - Un arduino Pro mini 5V 
  - Un transistor pour couper le courant alimentant la Raspberry
  - Un servo-moteur commandant l'ouverture / fermeture d'un clapet
- Un bloc "Batteries"
  - 4 Piles LiPo reliées 2 à 2 pour délivrer 7.4Volts
  - 1 batterie externe de 5600mAh 
- Un boitier de protection pour ranger le tout

## Paramtrer le raspberry

installer les librairies nécessaires : 
`sudo apt-get install wiringpi`

Lancer le script au démarrage du raspberry :
`sudo nano /etc/rc.local`
y insérer en bas de ligne ceci :
`sudo bash /home/pi/Viticam.sh &`
