static char sqla_program_id[292] = 
{
 172,0,65,69,65,81,65,73,67,65,122,74,82,71,69,105,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,8,0,83,84,85,68,69,78,
 84,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,83,72,65,82,69,77,79,68,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "ShareMode.sqc"
#include <stdio.h>
#include <stdlib.h>


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 4 "ShareMode.sqc"



int is_error(char *str){  
  if(SQLCODE < 0 ){
    printf("Error %s ,error code: %d\n",str,SQLCODE);
    
/*
EXEC SQL ROLLBACK;
*/

{
#line 10 "ShareMode.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 10 "ShareMode.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 10 "ShareMode.sqc"
  sqlastop(0L);
}

#line 10 "ShareMode.sqc"

    return 1;
  }
  return 0;
}
#define CHECKERR(str) if(is_error(str)) exit(1);


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 17 "ShareMode.sqc"


long id_smera;
char oznaka[11];
char naziv[201];


/*
EXEC SQL END DECLARE SECTION;
*/

#line 23 "ShareMode.sqc"


int main(){

  
/*
EXEC SQL CONNECT TO vstud USER student USING abcdef;
*/

{
#line 27 "ShareMode.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 27 "ShareMode.sqc"
  sqlaaloc(2,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 27 "ShareMode.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 27 "ShareMode.sqc"
      sql_setdlist[0].sqldata = (void*)"vstud";
#line 27 "ShareMode.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 27 "ShareMode.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 27 "ShareMode.sqc"
      sql_setdlist[1].sqldata = (void*)"student";
#line 27 "ShareMode.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 27 "ShareMode.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 27 "ShareMode.sqc"
      sql_setdlist[2].sqldata = (void*)"abcdef";
#line 27 "ShareMode.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 27 "ShareMode.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 27 "ShareMode.sqc"
  sqlacall((unsigned short)29,5,2,0,0L);
#line 27 "ShareMode.sqc"
  sqlastop(0L);
}

#line 27 "ShareMode.sqc"

  CHECKERR("connection");
  
  
  
/*
EXEC SQL LOCK TABLE smer IN SHARE MODE;
*/

{
#line 31 "ShareMode.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 31 "ShareMode.sqc"
  sqlacall((unsigned short)24,1,0,0,0L);
#line 31 "ShareMode.sqc"
  sqlastop(0L);
}

#line 31 "ShareMode.sqc"

  CHECKERR("Lock table");
  
  
/*
EXEC SQL DECLARE smerKursor CURSOR FOR
  select id_smera, oznaka,naziv
  from smer;
*/

#line 36 "ShareMode.sqc"

  CHECKERR("Declare cursor");
  
  
/*
EXEC SQL OPEN smerKursor;
*/

{
#line 39 "ShareMode.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 39 "ShareMode.sqc"
  sqlacall((unsigned short)26,2,0,0,0L);
#line 39 "ShareMode.sqc"
  sqlastop(0L);
}

#line 39 "ShareMode.sqc"

  CHECKERR("Open cursor");

  
  while(1){
    
    
/*
EXEC SQL FETCH smerKursor INTO :id_smera , :oznaka , :naziv;
*/

{
#line 45 "ShareMode.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 45 "ShareMode.sqc"
  sqlaaloc(3,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 45 "ShareMode.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 45 "ShareMode.sqc"
      sql_setdlist[0].sqldata = (void*)&id_smera;
#line 45 "ShareMode.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 45 "ShareMode.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 45 "ShareMode.sqc"
      sql_setdlist[1].sqldata = (void*)oznaka;
#line 45 "ShareMode.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 45 "ShareMode.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 201;
#line 45 "ShareMode.sqc"
      sql_setdlist[2].sqldata = (void*)naziv;
#line 45 "ShareMode.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 45 "ShareMode.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 45 "ShareMode.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 45 "ShareMode.sqc"
  sqlastop(0L);
}

#line 45 "ShareMode.sqc"

    
    if(SQLCODE == 100) break;
    
    printf("Id smera: %ld ,oznaka: %s,naziv: %s\n", id_smera,oznaka,naziv);
    
    printf("Pritisnite taster za citanje\n");
    getchar();
    
  }
  
  
/*
EXEC SQL CLOSE smerKursor;
*/

{
#line 56 "ShareMode.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 56 "ShareMode.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 56 "ShareMode.sqc"
  sqlastop(0L);
}

#line 56 "ShareMode.sqc"

  CHECKERR("Close cursor");

  
/*
EXEC SQL CONNECT RESET;
*/

{
#line 59 "ShareMode.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 59 "ShareMode.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 59 "ShareMode.sqc"
  sqlastop(0L);
}

#line 59 "ShareMode.sqc"

  CHECKERR("Disconect");
  return 0;
}