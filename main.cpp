#include <cstdio>
#include <cstring>

#include <stdint.h>

#include <math.h>
#include <time.h>

//! forward declaration from scrypt.c
void scrypt_1048576_1_1_256(const char* input, char* output);

long long current_timestamp()
{
        struct timespec te;
        clock_gettime(CLOCK_REALTIME, &te);
        return (long long) 1000LL*te.tv_sec + round(te.tv_nsec/1e6);
}

int main()
{
       unsigned char block[80];
       memset(block, 0, sizeof(block));

       unsigned char output[32];
       memset(output, 0, sizeof(output));

       int hashes = 0;
       uint32_t nonce = 0;
       uint64_t start = current_timestamp();
       uint32_t *nonceptr = (uint32_t*)&block[76];

       while (true)
       {
              *nonceptr = ++nonce;

              hashes++;
              if (current_timestamp() - start > 5000) {
                  printf("hashing at %.2f h/s\n", (float) hashes / 5);
                  hashes = 0;
                  start = current_timestamp();
              }

              scrypt_1048576_1_1_256((const char*)block, (char*)output);

              for (int i=0; i<32; i++) {
                  printf("%02hhx", output[i]);
              }
              printf("\n");
       }

       return 0;
}
