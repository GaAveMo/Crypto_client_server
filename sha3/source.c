#include "sha3_model.h"

void  f_read(unsigned char* buf, char* filename) {
    long   length;
    FILE*  fd = fopen (filename, "r");

    if (!fd) {
        return;
    }

    fseek(fd, 0, SEEK_END);
    length = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    if (buf) {
        fread(buf, 1, length, fd);
    }
    fclose (fd);

}


int len(char *filename) {
    FILE * fd = fopen (filename, "r");
    int length = 0;

    if (!fd) {
        return length;
    }

    fseek(fd, 0, SEEK_END);
    length = ftell(fd);
    fclose(fd);
    return length;
}


void print_transaction(transaction_t trans) {
    unsigned int digest_length;

    unsigned char* algo_type;

    if( trans.algo== SHA3_224 ) {
        algo_type = (unsigned char*)"SHA3_224";
        digest_length = SHA224_DIGEST_LENGTH;

    } else if ( trans.algo == SHA3_256 ){
        algo_type = (unsigned char*)"SHA3_256";
        digest_length = SHA256_DIGEST_LENGTH;

    } else if( trans.algo == SHA3_384 ) {
        algo_type = (unsigned char*)"SHA3_384";
        digest_length = SHA384_DIGEST_LENGTH;     

    } else if( trans.algo == SHA3_512 ) {
        algo_type = (unsigned char*)"SHA3_512";
        digest_length = SHA512_DIGEST_LENGTH;

    }

    fprintf(stdout, "message:\n");
    BIO_dump_fp(stdout, (char*)trans.message, trans.message_bytes);

    fprintf(stdout, "\nalgorithm type: %s\n", algo_type);

    fprintf(stdout, "digest:\n"); 
    BIO_dump_fp(stdout, (char*)trans.result_digest, digest_length);   

}


int main() {
    char filename[] = "message.bin"; 
    int length = len(filename);
    transaction_t trans; 
    unsigned  char text[length];
    f_read(text, filename);
   
    trans.algo = SHA3_512;
    trans.message_bytes = length;
    trans.message = text;
    trans.result_digest = malloc(get_digest_length(trans.algo));
    trans.finalize = true;

    int error_code = sha3_dgst_calc(&trans);
    if ( error_code == 0 ) {
        print_transaction(trans);
    }

    free(trans.result_digest);
    return 0;
}


