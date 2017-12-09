/* bavV5 / 09/12/2017     Boîte à histoire sur base d'Arduino - StoryBox with an arduino

   La Petite boite à histoires

   Ce programme s'appuie sur le travail mené par Giles Booth http://www.suppertime.co.uk/blogmywiki/2012/10/howtopoems/
           et la dadaist poetry box réalisée par Robottini   http://robottini.altervista.org/dadaist-poetry-box

   Ainsi que sur le travail de Julien Devriendt  http://blog.animtic.fr/2016/08/boite-a-histoires-v1/
                              Alias julanimtic : http://blog.animtic.fr

   Modifié et réadapté en novembre et décembre 2017 par les membres du Technistub de Mulhouse http://technistub.org et fièrement partagé sur https://github.com/TechniStub/Boite-a-histoire
   
   Ont participés activement a cette version : Vincent Sahler, Bertrand Sahler, Guillaume Strub, Christophe de Sabbata (mail : christophe(at)technistub.org )
   
   Commenté par Christophe de Sabbata (merci de votre indulgence quand aux fautes orthographes et de grammaires pouvant subsister

   Réalisées dans le cadre d'un projet de mise en place de boites à histoires dans les 7 bibliothèque de l'agglomération de Mulhouse, elles ont reçu le nom de "Textes en boîte"

   Ce programme est placé sous licence Creative Commons NC-BY-SA : https://creativecommons.org/licenses/by-nc-sa/2.0/fr/

   Il faut le matériel suivant :
     - 1 carte Arduino Mega2560R3 officiel : https://boutique.semageek.com/fr/4-arduino-mega-2560-r3-8058333490083.html 
     - 1 shield Mémoire DAtalogger Adafruit v2 (lecteur de carte SD + horloge RTC) : https://boutique.semageek.com/fr/547-data-logging-shield-pour-arduino-adafruit.html
     - 1 résistance de 10kOhm : https://boutique.semageek.com/fr/137-10-x-r%C3%A9sistances-025w-10kohms.html?search_query=resistance&results=164
     - un peu de fil electrique : https://boutique.semageek.com/fr/26-kit-de-70-wires-pour-prototypage.html?search_query=fil&results=137
     - 1 Pile type CR1220 : https://boutique.semageek.com/fr/464-pile-bouton-cr1220.html?search_query=cr1220&results=16
     - 1 carte SD de maxi 32Go (nous avons utilisé une version 4Go) : https://boutique.semageek.com/fr/674-carte-micro-sd-4-go-avec-adaptateur-sd.html?search_query=micro+sd&results=330 
     - 1 bouton poussoir avec voyant : https://boutique.semageek.com/fr/684-bouton-poussoir-chrome-avec-anneau-led-rouge-16mm.html?search_query=bouton+poussoir+metal&results=201     Ce bouton poussoir offre l'avantage d'avoir un voyant intégré pouvant être alimenté directement en 5V.
     - 1 imprimante Thermique Adafruit : https://boutique.semageek.com/fr/691-mini-imprimante-thermique.html?search_query=thermique&results=26
     - quelques rouleaux de papier pour imprimante thermique de largeur 2,25" en rouleau de 50ft (15 metres) : https://boutique.semageek.com/fr/692-rouleau-de-papier-thermique-largeur-225-longueur-50-ft.html
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
   Cela vous permettra de surveiller d'éventuel problème lors du premier démarrage du votre boite à histoires.

   Si vous souhaitez personnaliser certains textes d'impression contenue directement dans ce programme (messages, nom de la boite à histoires, nom de la bibliothèque, de la signature) gardez à l'esprit qui vous faudra prendre en compte les carractères accentués directement :
      remplacez alors les carractères accentués :  
      é par \x82      è par \x8A      ê par \x88      ë par \x89
      à par \x85      ä par \x84      â par \x83      ù par \x97
      û par \x96      ü par \x81      ô par \x93      ö par \x94
      î par \x8C      ï par \x8B      ç par \x87


   Belles réalisations à tous.
   Pour le TechniStub, Christophe
   By TechniStub ©2017
   PS : si vous constatez des erreurs, merci de nous le signaler.
*/

#include <SPI.h>                                // inclusion de la librairie du port SPI
#include <SD.h>                                 // inclusion de la librairie de gestion du lecteur SD
#include <Wire.h>                               // inclusion de la librairie de câblage simplifié : les numéros des pins utilisé dans les librairies s'adapterons automatiquement à la carte arduino utilisée.
#include "RTClib.h"                             // inclusion de la librairie RTC pour la gestion de la date et de l'heure via i2C
#include "Adafruit_Thermal.h"                   // inclusion de la librairie de l'imprimante thermique
#include "SoftwareSerial.h"                     // inclusion de la librairie de gestion du port serie logiciel

#define TX_PIN 6                                // FIL JAUNE depuis pin 6 de l'arduino vers la pin RX sur l'imprimante
#define RX_PIN 5                                // FIL VERT  depuis pin 5 de l'arduino vers la pin TX sur l'imprimante
#define PIN_BOUTON    2                         // retour du bouton sur pin 2, en même temps qu'une borne d'une résistance de 10KOhm ( dont l'autre borne va à la masse), l'autre borne du bouton est directement relié au +5V
#define PIN_LED       3                         // Pin pour alimenter le voyant du bouton poussoir (rajouter une résistance en série si la LED n'a pas de résistance interne)

RTC_PCF8523 rtc;                                // selection de la puce RTC
SoftwareSerial mySerial(RX_PIN, TX_PIN);        // affectation des pins pour un port serie logiciel
Adafruit_Thermal printer(&mySerial);            // affectation de ce port serie logiciel à l'imprimante thermique

// déclaration des noms des jours de la semaine
char daysOfTheWeek[7][12] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"}; 

// déclaration des variables
int nLigne = 0;
int nTailleIndex;
File root;
File Index_File;

void setup() {
 pinMode(PIN_BOUTON, INPUT);                             // défini la broche du bouton comme une entrée
 pinMode(PIN_LED, OUTPUT);                               // défini la broche du voyant du bouton comme une sortie

 Serial.begin(9600);                                     // Ouverture du port série (miniteur de débogage et RTC
 while (!Serial) {                                       // attente de l'activation du port série
       ;                                                 // attente necessaire avec un port USB natif
       }
 mySerial.begin(19200);                                  // Ouverture du port série logiciel
 printer.begin();                                        // Ouverture de la communication avec l'imprimante
 Serial.print("Initialisation lecteur de carte SD...");  // affichage dans le moniteur série 
 if (!SD.begin(10)) {                                    // si pas de réponse sur la pin 10
    Serial.println("Echec de l'initialisation !");       // affichage dans le moniteur série
    return;
    }
 if (! rtc.begin()) {                                    // si pas de présence du module horloge alors
    printer.wake();                                      // réveille de l'imprimante
    printer.setDefault();                                // application des paramètres par défaut de l'imprimante
    printer.println("Je ne trouve pas mon horloge");     // impression du message
    printer.feed(1);                                     // déroule le papier sans imprimer sur 1 ligne
    printer.sleep();                                     // met en sommeil l'imprimante
    while (1);
    }

 if (! rtc.initialized())  {                             // si l'horloge RTC n'a pas été initialisée, alors
    printer.wake();                                      // réveille de l'imprimante
    printer.setDefault();                                // application des paramètres par défaut de l'imprimante
    printer.println("Horloge inactive, activation en cours");    // impression du message
    printer.feed(1);                                     // déroule le papier sans imprimer
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));      // réglage du module RTC à la date et l'heure du PC qui connecté
    printer.println("Horloge mise à jour");              // impression du message
    printer.sleep();                                     // met en sommeil l'imprimante
    }

 Serial.println("initialisation Ok !");                  // affichage dans le moniteur série

 root = SD.open("/");                                    // verification de la présence du fichier index.txt
 if (Charger_Index()) {
    Serial.println("Erreur chargement INDEX.TXT");       // affichage dans le moniteur série en cas d'erreur
    return;
    } 
 Serial.println("Chargement index OK!");                 // affichage dans le moniteur série 

 Serial.print("Resultat chargement index (lignes vues) : ");        // affichage dans le moniteur série
 Serial.println(nTailleIndex);                           // affichage dans le moniteur série du nombre de ligne du fichier Index.txt et donc logiquement du nombre d'histoires devant être présente sur la carte SD
}



void loop() {
 digitalWrite(PIN_LED,HIGH);                             // allumage de la LED du bouton
 char stFile[32];                                        //
 char stTitre[32];                                       //
 char stAuteur[32];                                      //
 char stLivre[32];                                       // 
 char stAnnee[8];                                        //  

 if (digitalRead(PIN_BOUTON) == HIGH) {                  // si on appuie sur le bouton, alors
       digitalWrite(PIN_LED,LOW);                        // extinction de la LED du bouton et passage à la condition suivante
       if (nLigne >= nTailleIndex)  nLigne = 0;          // si le dernier fichier de l'index qui a été lu au tour précédent (nLigne étant = à nTailleIndex) alors on remet nLigne à 0
       nLigne = nLigne+1;                                // incrémente de 1 la valeur de nLigne pour lire le fichier suivant de la liste de l'index et eviter les lectures du même texte a répétition
            
       Serial.print("Ligne selectionnee : ");            // affichage dans le moniteur série
       Serial.println(nLigne);                           // affichage dans le moniteur série du numéro de la ligne de l'index qui va être utilisée
       memset(stFile, 0, 32);                            // déclaration de variable sur 32 octets
       memset(stTitre, 0, 32);                           // déclaration de variable sur 32 octets
       memset(stAuteur, 0,32);                           // déclaration de variable sur 32 octets
       memset(stLivre, 0, 32);                           // déclaration de variable sur 32 octets
       memset(stAnnee, 0, 8);                            // déclaration de variable sur  8 octets
    if (Select_Line_Index(nLigne, stFile, stTitre, stAuteur, stLivre, stAnnee)) {      // s'il y a une discordance entre tout cela, alors on a une erreur de lecture dans l'index
         Serial.println("Erreur index");                 // affichage dans le moniteur série de l'erreur
         return;
         }
    
        Serial.print("==> File : ");                     // affichage dans le moniteur série
        Serial.print(stFile);                            // affichage dans le moniteur série du nom du fichier qui va être utilisé
        Serial.print("  Titre : ");                      // affichage dans le moniteur série
        Serial.print(stTitre);                           // affichage dans le moniteur série du titre de l'histoire qui sera utilisée
        Serial.print("  Auteur : ");                     // affichage dans le moniteur série
        Serial.print(stAuteur);                          // affichage dans le moniteur série du nom de l'auteur de l'histoire qui sera utilisée
        Serial.print("  Livre : ");                      // affichage dans le moniteur série
        Serial.print(stLivre);                           // affichage dans le moniteur série du nom de l'oeuvre dont est issu l'histoire qui sera utilisée
        Serial.print("  Annee : ");                      // affichage dans le moniteur série
        Serial.println(stAnnee);                         // affichage dans le moniteur série

        printer.wake();                                  //reveille de l'imprimante
        printer.setDefault();                            // Demande à l'imprimante d'utiliser les paramètres par défaut
        printer.feed(1);                                 // deroule le papier sans imprimer (saut de ligne)
        printer.justify('C');                            // justification Centrée
        printer.boldOn();                                // met le texte en gras
        printer.doubleHeightOn();                        // double hauteur

// Impression du titre
        Affiche_Titre(stTitre);                          // appel de la fonction d'affichage du Titre (avec détection et traitement des accentuations)   
        printer.doubleHeightOff();                       // fin double hauteur
        printer.boldOff();                               // fin du texte en gras
        printer.justify('L');                            // justification à gauche
        printer.feed(1);                                 // deroule le papier sans imprimer (saut de ligne)

//  Impression du texte
        printer.println();                               // autre façon de faire un saut de ligne
        Affiche_Texte(stFile);                           // appel de la fonction d'affichage du Texte (avec détection et traitement des accentuations)

// Impression du nom de l'auteur
        printer.justify('R');                            // justification à droite
        printer.boldOn();                                // met le texte en gras
        Affiche_Auteur(stAuteur);                        // appel de la fonction d'affichage du nom de l'Auteur (avec détection et traitement des accentuations)
        printer.boldOff();                               // fin du texte en gras

// Impression du nom de l'oeuvre
        Affiche_Livre(stLivre);                          // appel de la fonction d'affichage du nom de l'Oeuvre (avec détection et traitement des accentuations)

// Impression de la date de l'oeuvre
        printer.setSize('S');                            // passage en taille plus petite
        printer.println(stAnnee);                        // affichage de la date de l'histoire (pas de traitement particulier ici
        printer.setSize('M');                            // passage en taille moyenne
        printer.justify('C');;                           // justification Centrée
        printer.feed(1);                                 // deroule le papier sans imprimer (saut de ligne)
        printer.println("Textes en bo\x8Cte \n Biblioth\x8Aque de Mulhouse");     // personalisez ici votre boite à histoire
        printer.setSize('S');                            // passage en taille plus petite
        printer.println("By TechniStub.org");            // Personalisation ici également

// rajout de la date et de l'heure
        DateTime now = rtc.now();                        // va lire la date et l'heure actuel dans le module RTC
        printer.print(daysOfTheWeek[now.dayOfTheWeek()]);// affichage du nom du jour
        printer.print(" ");                              // rajout d'un espace
        printer.print(now.day(), DEC);                   // affichage du numéro du jour
        printer.print('/');                              // affichage du séparateur /
        printer.print(now.month(), DEC);                 // affichage du numéro du mois
        printer.print('/');                              // affichage du séparateur /
        printer.print(now.year(), DEC);                  // affichage de l'année
        printer.print(' ');                              // rajout d'un espace
        printer.print(now.hour(), DEC);                  // affichage des heures
        printer.print(':');                              // affichage du séparateur /
        printer.print(now.minute(), DEC);                // affichage des minutes
        printer.print(':');                              // affichage du séparateur /
        printer.println(now.second(), DEC);              // affichage des secondes
        printer.feed(3);                                 // deroule le papier sans imprimer (3 saut de ligne)
        printer.sleep();                                 // met en sommeil l'imprimante
        digitalWrite(PIN_LED,HIGH);                      // rallume la LED pour inviter à un nouvel appui sur le petit bouton ;)
        Serial.println("Led du bouton active");          // affichage dans le moniteur série
        }
}


// *************************************
// *                                   *
// *  début des différentes fonctions  *
// *                                   *
// *************************************

// ces fonctions sont la création de Bertrand Sahler, je ne suis pas en mesure de vous en expliquer la totalité, d'ou un volume de commentaire de cette section plus reduit.

// analyse de la ligne du fichier index.txt en cours de selection
int Select_Line_Index(int nLigne, char *stFile, char *stTitre, char *stAuteur, char *stLivre, char *stAnnee)
    {
    char cLu;         // Caractere lu
    int nPosIns;      // Position dans la chaine (permet une insertion plus rapide)
    int nPos;         // Numero du champ que l'on est en train de traiter

    if ((Index_File = SD.open("index.txt", FILE_READ))== 0)  {
       Serial.println("Fichier index.txt ne peut etre ouvert");         // affichage dans le moniteur série
       return 1;
       }
    while (nLigne > 0)  {
        while ((Index_File.available()) && (nLigne > 0))
              if (Index_File.read() == 0x0D)  nLigne --;
        }
   
    while (Index_File.available())  {
        cLu = Index_File.read();
        switch (cLu)  {
             case ';' :                             // On passe au champ suivant
                 nPos ++;
                 nPosIns = 0;                       // Remise a zero sur la position d'insertion (on est suppose avoir une chaine vide)
                 break;
             case 0x0D :                            // Fin de la ligne. Fin de la lecture
                 Index_File.close();    return 0;
                 break;
             case 0x0A :
                 break;
             default :
                 switch (nPos)  {
                          case 0 :
                              stFile[nPosIns ++] = cLu;
                              break;
                          case 1 :
                              stTitre[nPosIns ++] = cLu;
                              break;
                          case 2 :
                              stAuteur[nPosIns ++] = cLu;
                              break;
                          case 3 :
                              stLivre[nPosIns ++] = cLu;
                              break;
                          case 4 :
                              stAnnee[nPosIns ++] = cLu;
                              break;
                          default :
                              Serial.println ("ERREUR lecture index");         // affichage dans le moniteur série
                              break;
                        }
                       break;
             }
        }
    Index_File.close();    return 1;
    }

// Analyse du contenu correct du fichier index et récupération des différentes variables (nom du fichier à lire, nom de l'histoire, nom de l'auteur, nom de l'oeuvre, date)
int Charger_Index()    {
    int nPos;
    char cLu;
    int nPosIns;

    nTailleIndex = 0;
    if ((Index_File = SD.open("index.txt", FILE_READ))== 0)
       {
       Serial.println("Fichier index.txt ne peut etre ouvert");         // affichage dans le moniteur série
       return 1;
       }
    nPos = 0;
    while (Index_File.available())
       {
       cLu = Index_File.read();

       switch (cLu)
            {
            case ';' :
                nPos ++;  // On passe au champ suivant
                break;
            case 0x0D :
                nTailleIndex ++;
                nPos = 0;
                break;
            case 0x0A:
                break;
            default :
                break;
            }
       }
    Index_File.close();
    return 0;
}

// traitement du contenu de l'histoire et conversion des accentuations (l'imprimante ne comprenant pas tout de l'UFT8 il faut donc faire la conversion)
int Affiche_Texte(char *stFile)   {
 File Index_File;
 unsigned char cLu;
 char printerStr;
 int nLu;
 bool bflag;

 if ((Index_File = SD.open(stFile, FILE_READ))== 0) {
    Serial.print("Fichier >>");                       // affichage dans le moniteur série
    Serial.print(stFile);                             // affichage dans le moniteur série
    Serial.println("<< ne peut etre ouvert");         // affichage dans le moniteur série
    return 1;
  }
  nLu = 0;   bflag=false;
  while (Index_File.available())
  {
    cLu = Index_File.read();
    printerStr = cLu;
    if (cLu == 239)    continue;
    if (cLu == 195)
    {
      bflag=true;
      continue;
      }
    if ((cLu == 0x0D) || (cLu == 0x0A))  printer.print(printerStr);  // Gestion du retour chariot
    if ((cLu < 128) && (cLu >= 32)) printer.print(printerStr);       // Si on a un caractere normal on l'imprime
    if (bflag)
       {
        switch (cLu)
         {
          case  169 :    //é
              printer.print("\x82");
              break;
          case  168 :    //è
              printer.print("\x8A");
              break;
          case  170 :    //ê
              printer.print("\x88");
              break;
          case  171 :    //ë
              printer.print("\x89");
              break;
          case  160 :    //à
              printer.print("\x85");
              break;
          case  164 :    //ä
              printer.print("\x84");
              break;
          case  162 :    //â
              printer.print("\x83");
              break;
          case  185 :    //ù
              printer.print("\x97");
              break;
          case  187 :    //û
              printer.print("\x96");
              break;
          case  188 :    //ü
              printer.print("\x81");
              break;
          case  180 :    //ô
              printer.print("\x93");
              break;
          case  182 :    //ö
              printer.print("\x94");
              break;
          case  174 :    //î
              printer.print("\x8C");
              break;
          case  175 :    //ï
              printer.print("\x8B");
              break;
          case  167 :    //ç
              printer.print("\x87");
              break;
        }
       }
    nLu ++;
  }
  printer.println();
  Index_File.close();    return 0;
}

// traitement du titre l'histoire et conversion des accentuations (l'imprimante ne comprenant pas tout de l'UFT8 il faut donc faire la conversion)
int Affiche_Titre(char *stTitre)   {
 File Index_File;
 unsigned char cLu;
 char printerStr;
 int nLu;
 bool bflag;
 
 nLu = 0;   bflag=false;
  while (*stTitre)
  {
    cLu = (unsigned char)*stTitre ++;
    printerStr = cLu;
    if (cLu == 239)    continue;
    if (cLu == 195)
    {
      bflag=true;
      continue;
      }

    if ((cLu < 128) && (cLu >= 32)) printer.print(printerStr);  // Si on a un caractere normal on l'imprime
    if (bflag)
       {
        switch (cLu)
         {
          case  169 :    //é
              printer.print("\x82");
              break;
          case  168 :    //è
              printer.print("\x8A");
              break;
          case  170 :    //ê
              printer.print("\x88");
              break;
          case  171 :    //ë
              printer.print("\x89");
              break;
          case  160 :    //à
              printer.print("\x85");
              break;
          case  164 :    //ä
              printer.print("\x84");
              break;
          case  162 :    //â
              printer.print("\x83");
              break;
          case  185 :    //ù
              printer.print("\x97");
              break;
          case  187 :    //û
              printer.print("\x96");
              break;
          case  188 :    //ü
              printer.print("\x81");
              break;
          case  180 :    //ô
              printer.print("\x93");
              break;
          case  182 :    //ö
              printer.print("\x94");
              break;
          case  174 :    //î
              printer.print("\x8C");
              break;
          case  175 :    //ï
              printer.print("\x8B");
              break;
          case  167 :    //ç
              printer.print("\x87");
              break;
        }
       }
    nLu ++;
  }
  printer.println();
  return 0;
}

// traitement du nom de l'auteur de l'histoire et conversion des accentuations (l'imprimante ne comprenant pas tout de l'UFT8 il faut donc faire la conversion)
int Affiche_Auteur(char *stAuteur)   {
 File Index_File;
 unsigned char cLu;
 char printerStr;
 int nLu;
 bool bflag;
 
 nLu = 0;   bflag=false;
  while (*stAuteur)
  {
    cLu = (unsigned char)*stAuteur ++;
    printerStr = cLu;
    if (cLu == 239)    continue;
    if (cLu == 195)
    {
      bflag=true;
      continue;
      }

    if ((cLu < 128) && (cLu >= 32)) printer.print(printerStr);  // Si on a un caractere normal on l'imprime
    
    if (bflag)
       {
        switch (cLu)
         {
          case  169 :    //é
              printer.print("\x82");
              break;
          case  168 :    //è
              printer.print("\x8A");
              break;
          case  170 :    //ê
              printer.print("\x88");
              break;
          case  171 :    //ë
              printer.print("\x89");
              break;
          case  160 :    //à
              printer.print("\x85");
              break;
          case  164 :    //ä
              printer.print("\x84");
              break;
          case  162 :    //â
              printer.print("\x83");
              break;
          case  185 :    //ù
              printer.print("\x97");
              break;
          case  187 :    //û
              printer.print("\x96");
              break;
          case  188 :    //ü
              printer.print("\x81");
              break;
          case  180 :    //ô
              printer.print("\x93");
              break;
          case  182 :    //ö
              printer.print("\x94");
              break;
          case  174 :    //î
              printer.print("\x8C");
              break;
          case  175 :    //ï
              printer.print("\x8B");
              break;
          case  167 :    //ç
              printer.print("\x87");
              break;
        }
       }
    nLu ++;
  }
  printer.println();
  return 0;
}

// traitement du nom de l'oeuvre d'où est tiré l'histoire s'il s'agit d'un extrait et conversion des accentuations (l'imprimante ne comprenant pas tout de l'UFT8 il faut donc faire la conversion)
int Affiche_Livre(char *stLivre)   {
 File Index_File;
 unsigned char cLu;
 char printerStr;
 int nLu;
 bool bflag;
 
 nLu = 0;   bflag=false;
    while (*stLivre)
    {
    cLu = (unsigned char)*stLivre ++;
    printerStr = cLu;
    if (cLu == 239)    continue;
    if (cLu == 195)
       {
        bflag=true;
        continue;
        }

    if ((cLu < 128) && (cLu >= 32)) printer.print(printerStr);  // Si on a un caractere normal on l'imprime
    if (bflag)
       {
        switch (cLu)
         {
          case  169 :    //é
              printer.print("\x82");
              break;
          case  168 :    //è
              printer.print("\x8A");
              break;
          case  170 :    //ê
              printer.print("\x88");
              break;
          case  171 :    //ë
              printer.print("\x89");
              break;
          case  160 :    //à
              printer.print("\x85");
              break;
          case  164 :    //ä
              printer.print("\x84");
              break;
          case  162 :    //â
              printer.print("\x83");
              break;
          case  185 :    //ù
              printer.print("\x97");
              break;
          case  187 :    //û
              printer.print("\x96");
              break;
          case  188 :    //ü
              printer.print("\x81");
              break;
          case  180 :    //ô
              printer.print("\x93");
              break;
          case  182 :    //ö
              printer.print("\x94");
              break;
          case  174 :    //î
              printer.print("\x8C");
              break;
          case  175 :    //ï
              printer.print("\x8B");
              break;
          case  167 :    //ç
              printer.print("\x87");
              break;
        }
       }
    nLu ++;
  }
  printer.println();
  return 0;
}
