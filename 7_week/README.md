# Konekcija s dve baze
## Glavni deo: dbmcon.sqc
### Prvi tip konekcije

1. setup strukture
2. rad sa prvom bazom
	* konekcija na prvu bazu `CONNECT TO`
	* akcija u prvoj bazi ( pozivamo fje iz `dbcon1.h` sa `rc = fja()`)  
    * `COMMIT`
	* raskid konekcije sa prvom bazom

3. rad sa drugom bazom
	* konekcija na drugu bazu `CONNECT TO`
	* akcija u drugoj bazi ( pozivamo fje iz `dbcon2.h` sa `rc = fja()`)  
    * `COMMIT`
	* raskid konekcije sa prvom bazom

Tako svaki put kad nesto radimo sa bazom naizmenicno. Nezgodno jer svaki put radimo brda stvari 


### Drugi tip konekcije

1. setup strukture
2. konekcija na prvu bazu: `CONNECT TO`
3. konekcija na drugu bazu: `CONNECT TO`
4. rad sa prvom bazom
	* `EXEC SQL SET CONNECTION :db1Alias1` - aktivna konekcija
    *  akcija u prvoj bazi ( pozivamo fje iz `dbcon1.h` sa `rc = fja()`) 
    * `COMMIT` moze a i ne mora, tj moze da sacuva i promene na obe baze
    
5. rad sa drugom bazom
	* `EXEC SQL SET CONNECTION :db1Alias2` - aktivna konekcija
    *  akcija u drugoj bazi ( pozivamo fje iz `dbcon2.h` sa `rc = fja()`) 
    * `COMMIT` moze a i ne mora, tj moze da sacuva i promene na obe baze
    
6. `EXEC SQL DISCONNECT ALL` - sve konekcije pogasimo



### Treci tip konekcije ( najbolji i taj koristimo ) 

1. setup strukture 
2. konekcija na prvu bazu: `CONNECT TO`
3.  akcija u prvoj bazi ( pozivamo fje iz `dbcon1.h` sa `rc = fja()`) 
4. konekcija na drugu bazu: `CONNECT TO`
5.  akcija u drugoj bazi ( pozivamo fje iz `dbcon2.h` sa `rc = fja()`) 

svaki sledeci put kad hocemo da promenimo bazu nad kojoj radimo akciju samo uradimo 
```sql
EXEC SQL SET CONNECTION :db1Alias1/2
```

kada sve zavrsimo:  
```sql
EXEC SQL COMMIT
EXEC SQL DISCONNECT ALL
```

### Napomene

* u opt/../samples imas uradjeno samo `cp dbmcon* path` ili `kate dbmcon`
* u mainu moramo postaviti ime baza, username, pass i ostalo jer ne koristimo fju koja je data u opt/ibm... 
* dodamo `EXEC SQL INCLUDE SQLCA` u glavni fajl
* `is_error` - pisali u glavnom delu
* `CHECKERR` - iskopirati u svaki deo
* izbrisati `utilemb.h` i sve sto ima veze s tim - tipa provere gresaka i to


## Drugi deo : dbmcon1.sqc/h 
Ukljucujemo u glavni deo i ovde definisemo fje koje vracaju `int` i nemaju argumenata koje pozivamo sa
```c
rc = FirstDbNekaAkcija() 
```
u glavnom programu
U sklopu fje se pozivaju kursori , drop , create , sve sto se moze raditi s bazom.


