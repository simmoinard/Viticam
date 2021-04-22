# Viticam_AgroTIC
Le projet Viticam d'AgroTIC permet de développer une caméra connectée Low-cost qui envoie des photos à intervalle régulière. la caméra est protégée par un boitier et l'objectif est à l'abri de la poussière & des interventions agricoles grâce à un clapet commandé par la Viticam.
Le système comprend principalement une partie "Acquisition & envoi de l'imagea, et une partie "Allumage et Mise en veille du système" : 

- Partie "Acquisition et envoi de l'image"
  - Une Raspberry Pi zero
  - Un servo-moteur commandant l'ouverture / fermeture d'un clapet
  - Une PiCam V2.1 reliée au Raspberry par le connecteur caméra
  - Un dongle 4G fonctionnel (et une carte SIM avec forfait 50Mo/mois minimum)
- Partie "Allumage et Mise en veille du système"
  - Un arduino Pro mini 5V 
  - Un transistor pour couper le courant alimentant la Raspberry
- Partie "Batteries"
  - 4 Piles LiPo reliées 2 à 2 pour délivrer 7.4Volts
  - 1 batterie externe de 5600mAh 
- Un boitier de protection pour ranger les 3 parties

## Paramtrer le raspberry

installer les librairies nécessaires : 
`sudo apt-get install wiringpi`

Lancer le script au démarrage du raspberry :
`sudo nano /etc/rc.local`
y insérer en bas de ligne ceci :
`sudo bash /home/pi/Viticam.sh &`


## Partie Arduino
go here http://www.ftdichip.com/Drivers/VCP.htm all the way to the right under "comments" on the table it says "Available as setup executable" then download that and it will do the setup for you
