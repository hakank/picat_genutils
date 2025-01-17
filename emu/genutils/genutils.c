/********************************************************************
 *   File   : genutils.c
 *   Author : Dilshad Mustafa Copyright (C) 2021
 *   Purpose: General utilities in C

 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 ********************************************************************/

#include "picat.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

p(){
	return PICAT_FALSE;
}

char* replace_char(char* str, char find, char replace){
    char *current_pos = strchr(str,find);
    while (current_pos) {
        *current_pos = replace;
        current_pos = strchr(current_pos,find);
    }
    return str;
}

int strfiltercopy(char* source, char* target){
    int oddindex = 1;
    int index = 0 ;
    int len = strlen(source);
    
    while (oddindex < len) {
		
		if ((oddindex + 2 < len) &&
			'\'' == *(source+oddindex) &&
			',' == *(source+oddindex + 1) &&
			'\'' == *(source+oddindex + 2)) {
			oddindex+=4;
			target[index] = ',';
			index++;
			continue;
		}
		else if ((oddindex + 2 < len) &&
			'\'' == *(source+oddindex) &&
			' ' == *(source+oddindex + 1) &&
			'\'' == *(source+oddindex + 2)) {
			oddindex+=4;
			target[index] = ' ';
			index++;
			continue;
		}
		else if ((oddindex + 2 < len) &&
			'\'' == *(source+oddindex) &&
			'\"' == *(source+oddindex + 1) &&
			'\'' == *(source+oddindex + 2)) {
			oddindex+=4;
			target[index] = '\"';
			index++;
			continue;
		}
		else if ((oddindex + 2 < len) &&
			'\'' == *(source+oddindex) &&
			isalnum(*(source+oddindex + 1)) &&
			'\'' == *(source+oddindex + 2)) {
			target[index] = *(source+oddindex + 1);
			oddindex+=4;
			index++;
			continue;
		}
		else if ((oddindex + 2 < len) &&
			'\'' == *(source+oddindex) &&
			'.' == *(source+oddindex + 1) &&
			'\'' == *(source+oddindex + 2)) {
			oddindex+=4;
			target[index] = '.';
			index++;
			continue;
		}
		
		else if ((oddindex + 3 < len) &&
			'\'' == *(source+oddindex) &&
			'\\' == *(source+oddindex + 1) &&
			'\'' == *(source+oddindex + 2) &&
			'\'' == *(source+oddindex + 3)) {
			oddindex+=5;
			target[index] = '\'';
			index++;
			continue;
		}
		/*
		else if ((oddindex + 2 < len) &&
			'\'' == *(source+oddindex) &&
			'\'' == *(source+oddindex + 1) &&
			'\'' == *(source+oddindex + 2)) {
			oddindex+=4;
			target[index] = '\'';
			index++;
			continue;
		}
*/

				
		target[index] = *(source+oddindex);
		oddindex+=2;
		index++;	
	}
	target[index] = '\0';
	
    return index-1;
}

int exec(char* psResult, char* command) {
   char buffer[128];
   int index = 0;
   

   // Open pipe to file
   FILE* pipe = popen(command, "r");
   if (!pipe) {
      return "popen failed!";
   }

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         strcpy(psResult+index, buffer);
         index+=128;
   }

   pclose(pipe);
   return 0;
}





shell(){
TERM a1, a2, a, b, c, f1, l1, f12;
TERM s1;
char *name_ptr;
char strResult[1000000];
char strFinal[1000];
char strTemp[1000];

a1 = picat_get_call_arg(1, 2);
a2 = picat_get_call_arg(2, 2);

picat_write_term(a2);
//name_ptr = a2; // picat_get_atom_name(a2);
name_ptr = bp_term_2_string(a2);
printf("characters : ");
for (int i = 0; i < strlen(name_ptr); i++) {
	printf("%c ", name_ptr[i]);
}	

printf("name_ptr : %s", name_ptr);
sprintf(strTemp, "%s", name_ptr);
printf("strTemp : %s",strTemp);
strfiltercopy(name_ptr, strFinal);
printf("strFinal : %s",strFinal);

/*
int status = system(strFinal);
int exitcode = status;
f12 = picat_build_float(exitcode);
s1 = picat_build_atom("exitcode");
// return picat_unify(a1, f12);
return picat_unify(a1, s1);
*/
exec(strResult, strFinal);
s1 = picat_build_atom(strResult);
return picat_unify(a1, s1);

//return PICAT_TRUE;


}


