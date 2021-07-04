# ASCII - per pixel converter from BMP to ASCII ART

My very first project which is doing __something__. Created for learning C++ from my first book when I started to be interested in programming (something around 16-17 yo).

Treat it as a nostalgic piece of code which keeps remembering that everybody started someday and first lines of code are not so perfect :)

For sure, do not treat it as paragon xD rather as an interesting example for the first project.

### Example usage

```
$ ./ascii mario_43px.bmp

ascii: ASCII Generator v. 0.2.3 Welcome!

ascii: File 'mario_43px.bmp' opened successful.
ascii: BMP Format is Correct.
ascii: Starting load BMP to memmory using 'load24'.
ascii: BMP Load Successful!
ascii: Starting Convert using PLAIN TEXT Convert Type.

                                           
                                           
                                           
                  EEEEEEEEEE               
                  EEEEEEEEEE               
               EEE::::::..::EE             
               EEE::::::..::EE             
             EE:::jjjjj,..  EE             
             EE:::jjjjj,..  EE             
          EEEjj:jjjj############           
          EEEjj:jjjj############           
         Ejjjjjj##################         
         Ejjjjjj##################         
         E   #####,,###,##,,               
       EE iii  #,,  ### ##  iiii           
       EE iii  #,,  ### ##  iiii           
       EE iii  #,,  ### ##  iiii           
       EE,iii  ###              ii         
       EE,iii  ###              ii         
       EE#,,,  #    ###,,,,,,,,,ii         
       EE#,,,  #    ###,,,,,,,,,ii         
         ####,,,  ##############           
          ###ii,,,,,,,,#######             
          ###ii,,,,,,,,#######             
          iiijjiiiiiiiiiEE                 
          iiijjiiiiiiiiiEE                 
          iiijjiiiiiiiiiEE                 
          iiijjj::iiiii...EE               
         #iii     ii    ..  EE####         
         #iii     ii    ..  EE####         
       ##iiii   iiii    ..  ##..####       
       ##iiii   iiii    ..  ##..####       
       ##iiii   iiiiiiii..EE##ii####       
       ##iiii   iiiiiiii..EE##ii####       
       ##iiii   iiiiiiii..EE##ii####       
       ##iEEEiiiiiiiiiiiEE##ii####         
       ##i...## EEEEEEEE  ##ii####         
       ##i...## EEEEEEEE  ##ii####         
         ####               ####           
         ####               ####           
                                           
                                           
                                           

ascii: File 'mario_43px.bmp' converted successful.
ascii: ASCII Generator Done! Thank You!
```

Below I'm leaving an original `HISTORY.txt` file content with all **important** changes :) (sorry but in PL)

**Version 0.2.1 -> 0.2.3**

* Zrezygnowanie z pliku CSS, deklaracja wielkosci tekstu zostala przeniesiona do pliku HTML
* Standardowy strumien wyjscia danych od tej wersji to `stdout`
* Program odczytuje 32 bitowe bitmapy
* Zostaly ulepszone algorytmy zapisu do pliku, zawsze jest dodawane rozszerzenie `*.html` jesli nie wystepuje w podanej nazwie przy korzystaniu z parametru `-o`
* Znowu usuwamy efekt lustra ... (nowe algorytmy przetwarzania bitmpy spowodowaly ten sam uchyb przy konwersji danych co poprzednie)
* Zobacz `ascii -v` lub `ascii --version` :-)

**Version 0.2.0 -> 0.2.1**

* Dołączenie pliku naglowkowego z makrami błędów
* Kontrolne wyświetlanie nagłówków bitmapy oraz danych obrazu
* Stworzenie 3 odrębnych funkcji dla każdej metody konwersji

**Version 0.1.5 -> 0.2.0**

* Utworzenie skali szarosci (metoda konwersji YUV)
* Wprowadzono 3 metody konwersji - `HTML`, `ASCII` i `ASCIICOLOR`
* Kolor tla podawany jako argument w wierszu polecen
* Reorganizacja algorytmu przetwarzania bitmapy do postaci klasy

**Version 0.1.4  -> 0.1.5**

* Usunięcie Efektu Lustra.

**Version 0.1.3  -> 0.1.4**

* Poprawienie algorytmu uzupełnienia do czterech.
* Poprawki do funkcji ParseCommandline...
* Wielkość wypełnienia zapisywana w pixelach.

**Version 0.1.0 -> 0.1.3**

* Dodanie funkcji `ParseCommandline()` wczytującej parametry z linii komend.

**Version 0.1.0**
* Pierwszy poprawnie działający program współpracujący z 24 bitowymi bitmapami
