# pbpDatabase

# Pokretanje


Pokretanje programa:
* sacuvas kao .sqc
* db2start
* ./prevodjenje ime_bez_ekstenzije vstud student abcdef

ako zelis da pogledas bazu
```sql
db2 connect to vstud
db2 describe table ime_tabele
db2 list tables
db2 "select indeks from ispit"
```

### Osnovno

* odma posle includova
```sql
EXEC SQL INCLUDE SQLCA;
```

* zatim host promenljive
```sql
EXEC SQL BEGIN DECLARE SECTION;
...
EXEC SQL END DECLARE SECTION;
```
* u mainu pises upite i sve izmedju konekcija
```sql
EXEC SQL CONNECT TO vstud user student using abcdef;
....
EXEC SQL CONNECT RESET;
```

### GRESKA

* `SQLCODE = 0` - sve je okej 
* `SQLCODE > 0` - neki warning
* `SQLCODE = 100` - prazan upit
* `SQLCODE < 0` - neka veca greska

postoje `SQLSTATE` i `sqlwarn`



# 1. nedelja

### 1. zadatak  
host promenljive se koriste sa `INTO :host_promeljive`
treba zapamtiti da se ne zaborave.
Na ovaj nacin pisemo select upit:
```sql
EXEC SQL SELECT .... INTO :host_promeljive FROM ... WHERE ...;
```
### 2. zadatak
* ukoliko koristimo upit u upitu to radimo sa () npr <br> `where indeks = (select max(indeks) from dosije)`

* kada ucitavamo host promenljive proverimo kojih su dimenzija pa +1
* mozemo na uradimo `trim(ime)` u select naredbi

* kada imamo neku promenljivu koja moze biti **null** stavimo jos jednu host promenljivu - identifikator i u nju upisujemo
`INTO :ime:id_ime `
to stavlja u sam identifikator `SQLCODE` pa na osnovu njega reagujemo na null vrednost

### 3. zadatak
nista novo samo je indeks ucitan sa ulaza
ukoliko ga koristimo u upitu mora imati :, stavili smo i nju kao host

### 4. zadatak
kada zelimo da ucitamo sve vrste neke tabele mozemo automatski kreirati 
```
db2dclgn -D vstud -T predmet -L c
```
ja msm da je ovo **D-database** , **T-table**, **L-language** <br>
i kreira se `predmet.h` <br>
uradimo u mestu za host promenljive 
```sql
EXEC SQL INCLUDE predmet;
``` 
i posle sve pisemo i citamo iz njega, sa `:predmet`, odnosno `predmet.indeks` ali za stringove `predmet.naziv.data` jer su strukture 

### 5. zadatak
samo je ubacena ta cela struktura iz fajla u host sekciju

### 6. zadatak
neka obrada gresaka koju necemo koristiti
```sqc
EXEC SQL WHENEVER NOT FOUND GO TO :nije_pronadjen
EXEC SQL WHENEVER SQLERROR GO TO :obrada_greske
EXEC SQL WHENEVER SQLWARNING CONTINUE
```
pa labela:
```c
nije_pronadjen:
...
```
### 7. zadatak
pisemo kod za obradu gresaka - fja 
```c
int is_error(char *str) {
    if(SQLCODE < 0){
    	printf("Error: str, code: SQLCODE");
        return 1;
	}
    return 0;
}
```
pa onda makro kojim pozivamo onda posle svake operacije nad bazom
```c
#define CHECKERR(str) if(is_error(str)) exit(1);
```
ne zaboravi da makro nema tip argumenta i da treba ukljuciti stdlib

sto se tice obrade: 
* 100 - ukoliko je upit prazan
* <0 - *error*
* \>0 - *warning* 
* =0  - *sve kul*

### 8. zadatak
umesto `SQLCODE` mozes i `sqlca->sqlcode` samo to mora da se ubaci u 
```sql
is_error(char *str, struct sqlca *sqlca){ 
	sqlca->sqlcode
}
CHECKERR(str){ is_error(str,&sqlca) }
```

### 9. zadatak
neka obrada gresaka, koju ne koristimo tipa `sqlcaptr` tako nesto

### 10. zadatak
ako zeza ono da se cita char - samo jedan getchar() izmedju 
```sql
EXEC SQL INSERT INTO predmet
         VALUES (:nesto, :nesto)

EXEC SQL UPDATE tabela
         SET bodovi = bodovi*2
         WHERE id_predmeta = :id_predmeta

EXEC SQL DELETE FROM predmet 
         WHERE id_predmeta = :id_predmeta
```
# 2. nedelja


### 1. zadatak

#### Kursori
Kad nam upit vraca vise od jednog reda koristimo kursore.
1. Deklaracija
```c
 EXEC SQL DECLARE ime_kursora CURSOR FOR select ...
```
2. Otvaranje (odmah zatvori da ne zaboravis)
```sql
EXEC SQL OPEN ime_kursora;
```
3. Fetch [update] <br/>
unutar bloka imamo petlju koja se prekida kada vise nema redova tj <br/> `SQLCODE = 100` i radi se FETCH
```c
while(1){
		EXEC SQL FETCH ime_kursora INTO :host_promenljive
    	if(SQLCODE == 100) break;
}
```

4. zatvaranje
```sql
EXEC SQL CLOSE ime_kursora;
```

### 2. zadatak
Kursore mozemo koristiti i za update mada nad nekim smanjenim skupom upita zato bas nesto to i ne koristimo <br/>
* u DECLARE delu se posle upita stavi `FOR UPDATE OF`
```sql
FOR UPDATE OF bodovi
```
fetch radimo regularno a unutar while petlje kad pozovemo update
mozemo da kazemo tacno koji red editujemo tj bas onaj dokle je kursor stigao.
```sql
EXEC SQL UPDATE tabela
UPDATE tabela
SET bodovi = bodovi + 10
WHERE CURRENT OF ime_kursora;
```

### 3. zadatak
* da bi predmet bio polozen - `ocena>5 and status_prijave = 'o'`
* `join table on` - super objasnjenje na w3 school za left/right join
* `coalesce(1,2)` - ako je 1. vrednost null , uzme drugu npr `coalesce(datum_usmenog,datum_pismenog)`
* `avg(ocena+0.0)` - da bi vratio float mora ovako 0.0 , vraca prosek

### 4. zadatak
koristili `count(*)` u kombinaciji sa `group by` - poenta da se grupisu sve vrednosti po necemu npr ovde sve 
zene sa istim imenom i da se ispise ime i broj takvih
order by broj asc/desc - sortiranje, posle svega

dalje sve za vezbu , na slicnu foru.


# 3. nedelja

### 1. zadatak
* kursor u kursoru, mozemo prvo deklarisati kursore a onda otvarati jedan unutar drugog 
* `exists(...)` - dal neka kolona postoji , najcesce se koristi npr <br/>
```
where not exists(select * from ispit where indeks = :indeks and ocena>5)
``` 
* order by - za sortiranje, posle svega

### 2. zadatak
*  pomocne tabele se konstruisu sa
```sql
with pomocna as (upit)
```
*  kada zelimo npr max od necega mozemo koristiti `in` operator
```sql
vrednost in (select max(...) from ... where...)
```
* cesto koristimo agregatnu sum za bodove, obrati paznju da su bodovi u ispitu 0-99 a u predmetu 6,10...

### 3. zadatak

kada radis update sa kursorom jako je nezahvalno jer se mozes zeznuti ako je previse komplikovan,zato se ovde koristi:
```sql
not exists(select * ...)
```
npr da je nesto najraniji ili najkasniji ispit - ne postoji ni
jedan sa tim indeksom koji je raniji odnosno kasniji.

Ako koristimo kursor za update
```sql
for update of bodovi
-- a posle se koristi kao u obicnom updateu u where klauzuli
update ispit
set bodovi = bodovi+10
where CURRENT OF kursor
```
### 4. zadatak

nista novo , ne zaboravi one short id-jeve za null


# 4. nedelja

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


### Visekorisnicki rezim
...





### 1. zadatak
* napisali upis u tabelu i updatte u jednom 
`EXEC SQL BEGIN COMPOUND ATOMIC STATIC .... END COMPOUND` - delu.
Poenta je da se insert i update sad pisu bez ikakvih dodataka tipa EXEC SQL.
* korisceno `current_date` u upitu. 
* Ako dodajemo/oduzimamo ne zaboravi da stavis days,months..
```
SET kraj_prijavljivanja = kraj_prijavljivanja - 10 days
```
* U `CHECKERR` - dodali 
```sql
EXEC SQL ROLLBACK
```
da ponisti sve kad dodje do greske
 
### 2. zadatak
stavimo unutar compounda `COMMIT;`- to znaci da ce se to sve sacuvati u bazi do toga <br/>
u ovom primeru je poenta da se nista nece izvrsiti u compoundu ako ima gresku jer je ATOMIC , cak i sa COMMIT tj `ATOMIC > COMMIT` <br/>
dobra praksa da ga pisemo na kraju:
```sql
EXEC SQL BEGIN COMPOUND ATOMIC STATIC 
	...
	COMMIT;
END COMPOUND;
```
 
### 3. zadatak
Ako umesto `ATOMIC` stavimo `NOT ATOMIC` naredbe su nezavisne i iako ima greske u drugom upitu , upit ce se izvrsiti
 
### 4. zadatak
pisemo sada niz naredbi od kojih se izvrsava samo onoliko koliko korisnik unese
```
EXEC SQL BEGIN COMPOUND ATOMIC STATIC STOP AFTER FIRST :br_rokova STATEMENTS
	...
END COMPOUND;
```
										
### 5. zadatak
1. Ucitavamo 2 roka, i onda stavljamo savepoint
2. Ucitavamo jos dosta rokova i onda ispisemo sve.
3. Pitamo korisnika dal oce ipak samo 2 roka.
4. Ako kaze da , svi naknadno dodati rokovi se preko savepointa brisu 
5. Ispisuju se opet svi da vidimo koliko ih ima
```sql
EXEC SQL SAVEPOINT ime ON ROLLBACK RETAIN CURSORS;
EXEC SQL ROLLBACK TO SAVEPOINT ime
```
 
### 6. zadatak
samo demonstracija `EXEC SQL COMMIT;`

1. prvo ucitamo par rokova i stavimo savepoint 
2. onda odlucimo dal cemo samo 1 ili sve 
3. na sve to svakako dodamo jos rokova i comitujemo 
4. Te naredbe izmedju kraja savepoint bloka i commita se uvek izvrse

znaci ako rollback uradimo nece ni commit pomoci (ovo nisam bas lepo definisao)

