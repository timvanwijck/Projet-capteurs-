# Projet-capteurs-
Réalisation d'une plateforme multi-capteurs sans fil à 2.4 GHz - Mesure et réduction de la consommation en énergie


Université Paris-Est Marne-la-Vallée  
Capteurs et acquisition de données 
Filière Electronique-Informatique : Systèmes Commun
icants 
(EISC3) 
Projet :  
Réalisation d'une plateforme multi-capteurs sans fi
l à 2.4 GHz 
Mesure et réduction de la consommation en énergie  
Hakim TAKHEDMIT 
Hakim.takhedmit@u-pem.fr
Bureau 4B035 - Bâtiment Copernic 
2 
Introduction
Nous souhaitons dans ce projet réaliser une platefo
rme multi-capteurs sans fil en bande ISM à 
2.4 GHz. Cette plateforme intégrera des capteurs de
 température, de pression et d'humidité et 
utilisera des cartes arduino. Aussi, on s'intéresse
ra à la consommation en énergie de la partie 
émission du dispositif ainsi qu'à quelque solutions
 visant à la réduire. 
Liste du matériel
−
2 cartes Arduino Uno 
−
2 émetteurs/récepteurs nRF24L01 à 2.4 GHz  
−
1 capteur de température TMP36  
−
1 capteur de pression (qui fait aussi température) 
BMP180 
−
1 capteur d'humidité (qui fait aussi température) D
HT22 
−
plaques d'essais et fils de connexion  
−
résistances et condensateurs   
Cahier des charges  
Les  grandeurs  physiques  :  température,  humidité  et 
pression  seront  mesurées  à  intervalles 
réguliers  et  transmises  à  distance  et  sans  fil  vers
  une  station  de  collecte.  Les  données  de 
mesure seront stockées et aussi affichées sur un éc
ran LCD.  
La consommation de la partie émission sera mesurée 
et des solutions visant à la réduire seront 
explorées  et  testées.  On  s'intéressera  particulière
ment  au  module  radio  nRF24L01  et  aux 
différents  capteurs  :  BMP180,  DHT22  et  TMP36.  On  ch
erchera  notamment  à  répondre  aux 
questions suivantes :   
−
combien de puissance est consommé en état de veille
?  
−
combien de puissance est consommée pendant le révei
l et la transmission de données?  
−
combien de temps dure le cycle de veille?  
−
combien de temps dure le cycle réveil/transmission 
de données? 
Travail demandé  
−
Il vous est demandé de concevoir et de réaliser la 
plateforme multi-capteurs sans fil. 
−
Vous   devez   définir   différents   scénarios   de   fonction
nement   et   de   mesurer   la 
consommation (puissance moyenne ou énergie) de la p
artie émission. 
−
Vous  devez  proposer  des  solutions  de  réduction  de  l
a  consommation  et  d'évaluer 
l'apport en énergie de chacune d'elles. 
−
Vous  devez  remettre  un  rapport  final  expliquant  la 
réalisation  du  montage,  la 
démarche  pour  les  différentes  mesures  et  pour  l'éva
luation  des  différentes  solutions 
visant à réduire la  consommation en énergie.  Il est
 évident que le code arduino et les 
circuits  électroniques  peuvent  utiliser  des  élément
s  que  vous  aurez  repris  par  ailleurs 
mais vous devez citer vos sources. Vous devez avoir
 compris ce que vous avez repris 
ailleurs pour pouvoir le modifier, l'adapter et l'e
xpliquer.        
3 
Comment aborder ce projet?   
−
Il est indispensable, dans un premier temps, de lir
e et de comprendre la documentation 
techniques  du  module  radio  nRF24L01  et  des  différen
ts  capteurs  TMP36,  DHT22  et 
BMP180. 
−
Faire le schéma électronique de l'émetteur sur papi
er puis le câbler. 
−
Faire le schéma électronique du récepteur sur papie
r puis le câbler
−
Mesurer   la   consommation   (puissance   moyenne   ou   énerg
ie)   des   capteurs   de 
température, d'humidité et de pression.  
−
Mesurer la consommation du module radio nRF24L01 da
ns différentes configurations 
et comparer la aux données fabriquant lorsque cela 
est possible.  
o
différents mode de fonctionnement : veille (s), tra
nsmission ...  
o
différents débits d'information : 250 kbps, 1 Mbps,
 2 Mbps  
o
différentes fréquences de 2.4 à 2.5 GHz 
o
différentes puissance d'émission : -18, -12, -6 et 
0 dBm  
o
différentes valeurs de rapport cyclique (duty cycle
)   
−
Proposer des solutions de réduction de la consommat
ion et les évaluer. Voici quelques 
pistes : 
o
choix de la fréquence
o
choix de la puissance en émission
o
mise en veille de périphériques non utilisés
o
   ... 
Le rapport doit comporter au minimum :  
−
Un plan, une introduction. 
−
Un organigramme du code arduino et le programme com
plet. 
−
Des schémas électroniques avec tous les éléments du
 ou des montages. 
−
Des courbes d'évolution des grandeurs physiques (te
mpérature, pression et humidité) 
en fonction du temps. 
−
Des résultats de mesures de la consommation (couran
t, puissance et énergie). 
−
Des résultats d'évaluation des solutions proposées 
pour réduire la consommation. 
−
Une conclusion.  
Vous  travaillerez  en  groupe  de  4  à  5.  La  notation  t
iendra  compte  de  votre  comportement 
pendant les séances, de vos initiatives par rapport
 au schéma proposé et de la pertinence de la 
ou  des  solutions  proposées.  En  fonction  de  l'avance
ment  dans  le  projet,  le  modèle  proposé 
afin  d'investiguer  la  pertinence  des  techniques  de 
réduction  de  la  consommation  en  énergie 
pourra être étendu à la carte arduino.   
