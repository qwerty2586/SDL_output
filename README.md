Tento program slouzi k rozsireni programu stimulator_control o obrazovy a zvukovy vystup

Balicky potrebne ke kompilaci na raspbian stretch

```
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev cmake
```


# Result 2016

## SDL_output

 - vytvoren program
 - pouziti SDL2 wiringPi 
 - zjisteni kolize hlavniho vlakna pro prijimani eventu, wiringPi vyzaduje root 
 rozdeleni SDL_output STDCR_monitor
 - otestovani behu pomoci arduina
 https://www.youtube.com/watch?v=-nnjyeOld5I 


# Roadmap 2017

## SDL_output
 - doplnit import nastaveni z XML, predbezne se jevi jako dobra volba https://github.com/zeux/pugixml
 - otestovat opozdeni osciloscopem
 
## STDCR_monitor
 - prejmenovat projekt na neco normalniho (stimulator, stimulator control), forknout ho na svuj github
 - pridat stranku s nastavenim SDL_output, moznost spusteni ukonceni
 - opravit layout, pridat scrollovatka
 - doplnit rozsireny protokol (pokud bude) stimulatoru
 - pridat pozadavkovy server pro android, bude umet
   - odeslat, prijmout soubor do pracovniho adresare s obrazky, hudbou
   - odeslat miniaturu obrazku
   - prijmout konfiguraci ve formatu XML pro SDL_output a spustit SDL_output
 
## celek
 - vytvorit komunikacni protokol mezi Androidem a Raspberry
 - limitace obou procesu na konktretni cpu https://linux.die.net/man/2/sched_setaffinity

# Roadmap 2018

