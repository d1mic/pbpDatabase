## KATANCI

jedino sto mozemo da zakljucamo je cela tabela
```c
EXEC SQL LOCK TABLE ime IN EXCLUSIVE MODE
```
u oba terminala pokrecemo exclusive mode
tek kad jedan skroz zavrsi moze drugi da cita
```c
EXEC SQL LOCK TABLE ime IN SHARE MODE
```
dva procesa mogu da paralelno da citaju

to je to , posle radili primere sa 3. i 4. casa
