#pragma once

#include <winsock2.h>
#include <windows.h>
#include <../OpenSSL-Win64/include/openssl/evp.h>
#include <../OpenSSL-Win64/include/openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <../OpenSSL-Win64/include/openssl/bio.h>
//#include <error.h>
#include <errno.h>

typedef enum hash_algo_e {
    SHA3_224,
    SHA3_256,
    SHA3_384,
    SHA3_512
} hash_algo_t;


typedef struct transaction {
   hash_algo_t    algo;
   unsigned char* message;
   unsigned  int  message_bytes; 
   unsigned char* digest;
   bool           init_with_digest;
   bool           finalize;
   unsigned char* result_digest;
} transaction_t;


int sha3_dgst_calc(transaction_t*);
int get_digest_length(hash_algo_t algo);

