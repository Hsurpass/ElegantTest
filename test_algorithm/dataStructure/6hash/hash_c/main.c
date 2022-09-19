#include <stdio.h>

unsigned int RSHash(const char* str, unsigned int len)
{
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash = hash * a + (*str);
        a = a * b;
    }
    return hash;
}

unsigned int JSHash(const char* str, unsigned int len)
{
    unsigned int hash = 1315423911;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }
    return hash;
}
unsigned int PJWHash(const char* str, unsigned int len)
{
    const unsigned int BitsInUnsignedInt
            = (unsigned int)(sizeof(unsigned int) * 8);
    const unsigned int ThreeQuarters
            = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    const unsigned int OneEighth
            = (unsigned int)(BitsInUnsignedInt / 8);
    const unsigned int HighBits
            = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt -
                                             OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash = (hash << OneEighth) + (*str);
        if((test = hash & HighBits) != 0)
        {
            hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
    return hash;
}
unsigned int ELFHash(const char* str, unsigned int len)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash = (hash << 4) + (*str);
        if((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }
    return hash;
}

unsigned int BKDRHash(const char* str, unsigned int len)
{
    unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
    unsigned int hash = 0;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash = (hash * seed) + (*str);
    }
    return hash;
}
unsigned int SDBMHash(const char* str, unsigned int len)
{
    unsigned int hash = 0;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash = (*str) + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}
/* End Of SDBM Hash Function */
unsigned int DJBHash(const char* str, unsigned int len)
{
    unsigned int hash = 5381;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash = ((hash << 5) + hash) + (*str);
    }
    return hash;
}
/* End Of DJB Hash Function */
unsigned int DEKHash(const char* str, unsigned int len)
{
    unsigned int hash = len;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
    }
    return hash;
}
/* End Of DEK Hash Function */

unsigned int BPHash(const char* str, unsigned int len)
{
    unsigned int hash = 0;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash = hash << 7 ^ (*str);
    }
    return hash;
}
/* End Of BP Hash Function */
unsigned int FNVHash(const char* str, unsigned int len)
{
    const unsigned int fnv_prime = 0x811C9DC5;
    unsigned int hash = 0;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash *= fnv_prime;
        hash ^= (*str);
    }
    return hash;
}
/* End Of FNV Hash Function */
unsigned int APHash(const char* str, unsigned int len)
{
    unsigned int hash = 0xAAAAAAAA;
    unsigned int i = 0;
    for(i = 0; i < len; str++, i++)
    {
        hash ^= ((i & 1) == 0) ? ( (hash << 7) ^ (*str) * (hash >> 3)) :
                                 (~((hash << 11) + ((*str) ^ (hash >> 5))));
    }
    return hash;
}
/* End Of AP Hash Function */

int main()
{
    char* key = "abcdefghijklmnopqrstuvwxyz1234567890";
    printf("General Purpose Hash Function Algorithms Test\n");
    printf("By Arash Partow - 2002 \n" );
    printf("Key: %s\n",key );
    printf(" 1. RS-Hash Function Value: %u\n",RSHash (key,36));
    printf(" 2. JS-Hash Function Value: %u\n",JSHash (key,36));
    printf(" 3. PJW-Hash Function Value: %u\n",PJWHash (key,36));
    printf(" 4. ELF-Hash Function Value: %u\n",ELFHash (key,36));
    printf(" 5. BKDR-Hash Function Value: %u\n",BKDRHash(key,36));
    printf(" 6. SDBM-Hash Function Value: %u\n",SDBMHash(key,36));
    printf(" 7. DJB-Hash Function Value: %u\n",DJBHash (key,36));
    printf(" 8. DEK-Hash Function Value: %u\n",DEKHash (key,36));
    printf(" 9. BP-Hash Function Value: %u\n",BPHash (key,36));
    printf("10. FNV-Hash Function Value: %u\n",FNVHash (key,36));
    printf("11. AP-Hash Function Value: %u\n",APHash (key,36));

    return 0;
}
