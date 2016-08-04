#include "HSToker.h"


bool HSToker::validateMessage(char *message) {

    int msglen = this->strlen(message);
    int colon_count=0;

    if (msglen > MAX_MSG_LEN) {
        return (valid=false);
    }

    for (int i=0; i<msglen; i++)
        if (message[i] == ':')
            colon_count++;

    if (colon_count != 8)
        return (valid=false);

    return (valid=true);
}

HSToker::HSToker() {}


HSToker::HSToker(char *message) {

    char *pmsg = &message[8];

    if (!validateMessage(message)) {
        return;
    }

    type = message[0];

    for (int i=0; i<MAX_MSG_LEN; i++)
        buffer[i] = '\0';

    int msglen = this->strlen(pmsg);
    for (int i=0; i<msglen; i++)
        buffer[i] = pmsg[i];
}


/* retorna o tamanho da string, excluindo o caractere '\0' */
int HSToker::strlen(char *buffer) {

    int count=0;
    char *p = buffer;

    while ( (*p != '\0') && (*p < MAX_MSG_LEN) ) {
        count++;
        p++;
    }

    return count;
}


bool HSToker::isValid() {
    return valid;
}


char HSToker::getType() {
    return type;
}

int HSToker::getField(char *buff, int wanted) {
    
    char *pbuff = buffer, ch;
    int bcount;

    if ( (wanted < 1) || (wanted >7) )
        return 0;

    for (int c=1; c<=MAX_FIELDS; c++) { //iterar sobre os 7 campos de dados

        for (int i=0; i<MAX_FIELD_LEN; i++) //zerar o user-buffer
            buff[i] = '\0';

        bcount = 0;

        for (int i=0; i<MAX_FIELD_LEN; i++) { //maximo de 32 casas por campo

            ch = *pbuff++;

            if ( (ch == ':') && (i==0) ) { //ja comecou com ':'
                if (c == wanted)
                    return 0;

                break;

            } else if ( (ch == ':') && (i>0) ) { //terminamos
            
                if (c == wanted)
                    return bcount;
                else
                    break;

            } else {
             
                buff[bcount++] = ch;
            }

        }
    }

    return 0;
}
