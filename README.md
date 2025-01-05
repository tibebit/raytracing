# Raytracing in C
## Descrizione generale

Lo scopo di questo progetto è la realizzazione di un programma in grado di effettuare il
rendering tramite tecniche di raytracing di un insieme di sfere in cui l'utente possa
specificare posizione, raggio e colore.

## Esecuzione di raytracer.exe

### Sintassi
```bash
./raytracer nome_file_scena.txt nome_file_immagine.ppm larghezza_immagine altezza_immagine
```
### Parametri

| Parametro               | Descrizione                                                         | Tipo |
|-------------------------|---------------------------------------------------------------------|------|
| nome_file_scena.txt     | Il nome del file da cui leggere le informazioni sulla scena         | testo |
| nome_file_immagine.ppm  | Il nome del file su cui scrivere i dati del rendering dell'immagine | testo |
| larghezza_immagine      | La larghezza dell'immagine.                                         | intero |
| altezza_immagine        | L'altezza dell'immagine.                                            | intero |


## Esempio
### Esecuzione
```bash
./raytracer test.txt immagine.ppm 1920 1080
```
### Risultato atteso
Il risultato dell'esecuzione del programma deve produrre un file ppm nella cartella stessa cartella in cui si trova lo script

