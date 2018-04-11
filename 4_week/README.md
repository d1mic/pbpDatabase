### COMPOUND SQL 
vise komandi se izvrsava `istovremeno` i `bez pisanja EXEC SQL` svaki cas. <br/>
* `ATOMIC` - ceo skup naredbi se izvrsava kao jedna komanda tj ako jedna naredba pukne - ni jedna se ne izvrsi
* `NOT ATOMIC` - pojedinacne greske se ignorisu

obrati paznju na sintaksu , da je sve jedna naredba, bez vise EXEC-a i `;`
```sql
EXEC SQL BEGIN COMPOUND ATOMIC STATIC
	... 
	INSERT
	DELETE
	UPDATE
	...
END COMPOUND;
```
ima brda nekih opcija - mi smo radili: <br/>
`STOP AFTER FIRST :br STATEMENTS` tj 

```c
EXEC SQL BEGIN COMPOUND ATOMIC STATIC STOP AFTER FIRST :br STATEMENTS
	...
END COMPOUND;

```
 
 
### SAVEPOINT

kao labela na koju se mozemo vratiti ako se nesto pokvari 
u sustini stavimo 
```sql
EXEC SQL SAVEPOINT ime_savepointa ON ROLLBACK RETAIN CURSORS;
```
i ako pozovemo
```sql
EXEC SQL ROLLBACK TO SAVEPOINT ime_savepointa
```
sve posle EXEC SAVEPOINT se ponistava.
 poenta je da ih mozemo imati vise, zato su bolji od jednostavnog `COMMIT`-a

