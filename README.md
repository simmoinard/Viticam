# Viticam
La Viticam est une caméra permettant d'envoyer une image tous les jours d'une parcelle de vigne.

## Parametrer le raspberry

installer les librairies nécessaires : 
`sudo apt-get install wiringpi`

Lancer le script au démarrage du raspberry :
`sudo nano /etc/rc.local`
y insérer en bas de ligne ceci :
`sudo bash /home/pi/Viticam.sh &`
