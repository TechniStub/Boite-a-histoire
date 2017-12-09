# Boite-a-histoire
Boîte à histoire sur base d'Arduino - StoryBox with an arduino

bavV5 / 09/12/2017
 
La Petite boite à histoires

 Ce programme s'appuie sur le travail mené par Giles Booth http://www.suppertime.co.uk/blogmywiki/2012/10/howtopoems/
         et la dadaist poetry box réalisée par Robottini   http://robottini.altervista.org/dadaist-poetry-box

 Ainsi que sur le travail de Julien Devriendt  http://blog.animtic.fr/2016/08/boite-a-histoires-v1/
                            Alias julanimtic : http://blog.animtic.fr

 Modifié et réadapté en novembre et décembre 2017 par les membres du Technistub de Mulhouse http://technistub.org
      Vincent Sahler, Bertrand Sahler, Guillaume Strub, Christophe de Sabbata (mail : christophe(at)technistub.org )
 Commenté par Christophe de Sabbata (merci de votre indulgence quand aux fautes orthographes et de grammaires pouvant subsister

 Réalisées dans le cadre d'un projet de mise en place de boites à histoires dans les 7 bibliothèque de l'agglomération de Mulhouse, elles ont reçu de nom de "Textes en boîte"

Ce programme est placé sous licence Creative Commons NC-BY-SA : https://creativecommons.org/licenses/by-nc-sa/2.0/fr/

Il faut le matériel suivant :
  - 1 carte Arduino Mega2560R3 officiel : https://boutique.semageek.com/fr/4-arduino-mega-2560-r3-8058333490083.html 
  - 1 shield Mémoire DAtalogger Adafruit v2 (lecteur de carte SD + horloge RTC) : https://boutique.semageek.com/fr/547-data-logging-shield-pour-arduino-adafruit.html
  - 1 résistance de 10kOhm : https://boutique.semageek.com/fr/137-10-x-r%C3%A9sistances-025w-10kohms.html?search_query=resistance&results=164
  un peu de fil electrique : https://boutique.semageek.com/fr/26-kit-de-70-wires-pour-prototypage.html?search_query=fil&results=137
  - 1 Pile type CR1220 : https://boutique.semageek.com/fr/464-pile-bouton-cr1220.html?search_query=cr1220&results=16
  - 1 carte SD de maxi 32Go (nous avons utilisé une version 4Go) : https://boutique.semageek.com/fr/674-carte-micro-sd-4-go-avec-adaptateur-sd.html?search_query=micro+sd&results=330 
  - 1 bouton poussoir avec voyant : https://boutique.semageek.com/fr/684-bouton-poussoir-chrome-avec-anneau-led-rouge-16mm.html?search_query=bouton+poussoir+metal&results=201     Ce bouton poussoir offre l'avantage d'avoir un voyant intégré pouvant être alimenté directement en 5V.
  - 1 imprimante Thermique Adafruit : https://boutique.semageek.com/fr/691-mini-imprimante-thermique.html?search_query=thermique&results=26
  quelques rouleaux de papier pour imprimante thermique de largeur 2,25" en rouleau de 50ft (15 metres) : https://boutique.semageek.com/fr/692-rouleau-de-papier-thermique-largeur-225-longueur-50-ft.html
  - 1 bloc secteur 5V 2,5A (ceux pour raspberry Pi conviennent parfaitement, il faudra juste couper la fiche) : https://boutique.semageek.com/fr/723-alimentation-raspberry-pi3-5v-25a-micro-usb.html
  - 1 boitier pour tout y mettre : le fichier de découpe laser est joint dans ce Github. Nous avons réalisée la découpe sur une Epilog Helix60

Ce programme utilise les bibliothèque suivante :
  - Adafruit Thermal Printer Library : https://github.com/adafruit/Adafruit-Thermal-Printer-Library ecrite par Limor Fried/Ladyada pour Adafruit Industries, avec la contribution de la comunauté open source. Basé sur la librairie Thermique originale de bildr.org sous licence MIT, all text above must be included in any redistribution.
  - SD : inclus dans l'IDE arduino (dans certains cas il peut être nécessaire de modifier certains paramètre en fonction des cartes arduino utiliser, se référer à la documentation du datalogger Adafruit)
  - RTClib : disponible sur le Github : https://github.com/adafruit/RTClib
  - SPI : inclus dans l'IDE arduino
  - Wire : inclus dans l'IDE arduino
  - Software Serial : inclus dans l'IDE arduino

La carte SD (obligatoirement formaté en FAT32) doit impérativement contenir un fichier nommé index.txt enregistré au format UTF8 (avec notepad++ par exemple).
Le fichier index contiendra une ligne par histoire sur le modèle suivant :
           chat.txt;Mon Chat;auteur inconnu;Oeuvre sans nom;2007      (fichier.txt;Titre;Auteur;Oeuvre;Date)
La date ne doit comporter que l'année
La première ligne du fichier index.txt doit être laissée vide.
   
Chaque histoire doit être placée sur la carte SD au format .txt en encodage UTF8 (avec notepad++) en respectant un nom de fichier de 8 carractères maxi (sans accents dans le nom du fichier)

Les histoires peuvent comporter les accents suivants : é, è, ê, ë, à, ä, â, ù, û, ü, ô, ö, î, ï, ç   
D'autres types d'accents peuvent être rajoutés en modifiant le programme.
Les E dans l'O sous la formes littéraire doivent être remplacé manuellement par un o suivi du e.
Les lettres accentuées en Majuscules ne sont pas remplacées, il conviendra soit d'utilisé le carractère accentué en minuscule, soit la lettre non accentuée en majuscule.
Les virgules, apostrophes, points, point d'exclamation et d'intérrogations sont interprété nativement en UTF8.
Les ! et ? ne doivent pas être précédés d'un espace.
Les symboles monaitaire, les & ~# [ ] { } $ £ µ * %  sont à remplacer par leur forme littéraire.
Les guillements « et » doivent être remplacés par la forme "   , de même que ’ (apostrohpe en forme de virgule) sera remplacé par '

Veuillez à prévoir une pagination de 32 carractères maximum par ligne (espaces et carractère de césure compris) pour une meilleur lisibilité.

Avant le transfert vers la carte arduino (avec le module shield installé et cablé + pile insérée et carte SD en place), juste après le versement du programme dans l'arduino, ouvrez le moniteur série de l'IDE arduino, reglez le sur 9600baud avec la case "Défilement" automatique coché ainsi que le mode "Les deux, NL et CR" selectionné.
Celà vous permettra de surveiller d'éventuel problème lors du premier démarrage du votre boite à histoires.

Si vous souhaitez personnaliser certains textes d'impression contenue directement dans ce programme (messages, nom de la boite à histoires, nom de la bibliothèque, de la signature) gardez à l'esprit qui vous faudra prendre en compte les carractères accentués directement :
      remplacez alors les carractères accentués :  
      é par \x82
      è par \x8A
      ê par \x88
      ë par \x89
      à par \x85
      ä par \x84
      â par \x83
      ù par \x97
      û par \x96
      ü par \x81
      ô par \x93
      ö par \x94
      î par \x8C
      ï par \x8B
      ç par \x87


Belles réalisations à tous.
Pour le TechniStub, Christophe

PS : si vous constatez des erreurs, merci de nous le signaler.
