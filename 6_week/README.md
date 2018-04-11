## DINAMICKI SQL

ucitavamo sa 
```c
char stmt[255];
fgets(stmt, 255, stdin);
  
```

Odma izvrsava upit koji unesemo
```sql
EXEC SQL EXECUTE IMMEDIATE :stmt
```
Ukoliko koristimo sve sem select upita mozemo prvo pripremiti upit
pa onda traziti od korisnika da unese parametre


```sql
sprintf(stmt,"INSERT INTO ISPITNI_ROK VALUES(?, ?, ?, ?, ?, ?)"
EXEC SQL PREPARE ime FROM :stmt
...
EXEC SQL EXECUTE ime USING :prom1,:prom2,:prom3,:prom4,:prom5;

```

Ako koristimo select naredbu. U kombinaciji sa kursorom. Posto kad otvaramo kursor tad se izvrsava upit, u tom trenutku moraju biti poznate sve promenljive upita.

```sql
sprintf(naredba, "%s", "select naziv from smer where oznaka = ?");
EXEC PREPARE ime FROM :stmt;
...
EXEC SQL DECLARE cursor CURSOR FOR ime;
EXEC SQL OPEN cursor USING :oznaka

posle sve regularno 
EXEC SQL FETCH cursor INTO :prom1

```
