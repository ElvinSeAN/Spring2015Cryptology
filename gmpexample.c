#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <assert.h>

// Modular Exponentiation function 
// a=base, k=exponent, m=modulus
void modularexpon(mpz_t l, mpz_t a, mpz_t k, mpz_t m)
{
  printf("Start modular expon\n");
  // c remainder
  mpz_t c;
  mpz_init(c);
  mpz_set_ui(c,1);
  //printf("result %d !\n", mpz_cmp(k,c));
  // loop 
  mpz_t x;
  mpz_init(x);
  mpz_set_ui(x,1);
  //printf("result %d !\n", mpz_cmp(k,x));
  while  ( mpz_cmp(k,x)>=0)
  {
    //printf("while loop start\n");
    mpz_mul(c,c,a);
    mpz_mod(c,c,m);
    //mpz_out_str(stdout,10,c);
    //printf("\n");
    mpz_add_ui(x,x,1);

  }
  mpz_set(l,c);
  // clean up c and x 
  mpz_clear(c);
  mpz_clear(x);
}
// generate prime and the primitive root 
void primenoandroot(mpz_t p, mpz_t g, int nob, int t)
 {
     // random generate thing 
    int             lo;            /* Loop variable */
    mpz_t           randNum;      /* Hold our random numbers */
    mpz_t           rndBnd;       /* Bound for mpz_urandomm */
    gmp_randstate_t gmpRandState; /* Random generator state object */


    /* Initialize randNum before we use it. */
    mpz_init(randNum);
    mpz_init(rndBnd);
    mpz_out_str(stdout,10,randNum);
    printf ("\n");

    /* Initialize Bounds */
    mpz_ui_pow_ui(rndBnd, 2, nob);
    /*
    printf(" base 2 power 200 : ");
    mpz_out_str(stdout,10,rndBnd);
    printf ("\n");
    */

    /* Initialize the random state with default algorithm... */
    gmp_randinit_default(gmpRandState);
      /* Seed the state with an unsigned long int before we begin.. */
    /* One can set the seed from an mpz_t too with gmp_randseed() */
    // for testing purpose, now only use seed 234
    gmp_randseed_ui(gmpRandState, 234);

    /*
      printf("10 random numbers in U[0, 200");

      printf("]:\n");
    */
    for(lo=0; lo<10; lo++) {
      /* mpz_get_ui() can convert randNum to unsigned long int... */
      mpz_urandomb(randNum, gmpRandState, 201);
      if (mpz_cmp(randNum,rndBnd)>0)
      {
        mpz_nextprime(randNum,randNum);
        mpz_out_str(stdout, 10, randNum);
      printf("\n");
      printf("testing prime : %d \n" ,mpz_probab_prime_p(randNum,50));
      }
     }
    mpz_set(p, randNum);
    // find the primitive root so g^p-1 = 1 mod p then g is a primitive root 
    mpz_urandomm(g, gmpRandState, p); 
    // for temp variable 
    mpz_t tempc; // temp remainder
    mpz_init(tempc);
    mpz_t tempe; // temp exponent 
    mpz_init(tempe);
    mpz_sub_ui(tempe,p,1);
    // g^p-1 mod p = tempc
    mpz_powm_sec(tempc,g,tempe,p);
    printf("result of tempc:");
    mpz_out_str(stdout, 10, tempc);
        printf("\n");

    // if g^p-1 != 1 mod p , find another g 
    while ( mpz_cmp_d(tempc, 1) !=0)
    {
        printf("testing for g and c ");
        mpz_out_str(stdout, 10, g);
        printf("\n");
        mpz_out_str(stdout, 10, tempc);
        printf("\n");
        mpz_urandomm(g, gmpRandState, p);
    }
    printf("Result for g : \n");
    mpz_out_str(stdout, 10, g);
    printf("\n");
    printf(" compare g and p :%d\n ", mpz_cmp(p,g));

    mpz_clear(randNum);
    mpz_clear(rndBnd);
    mpz_clear(tempc);
    mpz_clear(tempe);
}
// public and private key generation , 
//should auto output the public key and private key 
// to the K1 and K2 file 

void publicandprivatekey(mpz_t p,mpz_t g)
  {
    printf("generating keys\n");
     // random generate thing 
    int             lo;            /* Loop variable */
    mpz_t           randNum;      /* Hold our random numbers */
    gmp_randstate_t gmpRandState; /* Random generator state object */

    /* Initialize randNum before we use it. */
    mpz_init(randNum);
    
    /* Initialize the random state with default algorithm... */
    gmp_randinit_default(gmpRandState);
      /* Seed the state with an unsigned long int before we begin.. */
    /* One can set the seed from an mpz_t too with gmp_randseed() */
    // for testing purpose, now only use seed 234
    gmp_randseed_ui(gmpRandState, 234);
    // generate random no under p
    mpz_urandomm(randNum, gmpRandState, p); 

    mpz_t tempc; // temp remainder
    mpz_init(tempc);
   
    mpz_powm_sec(tempc,g,randNum,p);
    printf("Result for h: \n");
    mpz_out_str(stdout, 10, tempc);
    printf("Result for x: \n");
    mpz_out_str(stdout, 10, randNum);
    printf("\n");

    // write to file K1 
    FILE *fp = fopen("K1.txt", "w");
    if (fp == NULL)
    {
      printf("error opening file\n");
      exit(1);
    }
    mpz_out_str(fp,10,p);
    fprintf(fp,"\n");
    mpz_out_str(fp,10,g);
    fprintf(fp,"\n");
    mpz_out_str(fp, 10, tempc);
    fclose(fp);
    // write to file K2
    FILE *fp2 = fopen("K2.txt", "w");
    if (fp2 == NULL)
    {
      printf("error opening file\n");
      exit(1);
    }
    mpz_out_str(fp2,10,p);
    fprintf(fp2,"\n");
    mpz_out_str(fp2,10,g);
    fprintf(fp2,"\n");
    mpz_out_str(fp2, 10, randNum);
    fclose(fp2);
    
    

  }

void encoding(mpz_t *z, char *inputStr, int zi)
{
    // for testing purpose k = 25
    /* 
    for (int yi=0; yi<tempxi; yi++)
    {
      printf("%c%d\n", inputStr[yi],inputStr[yi]);
    }
    */
    mpz_t tempz; // temp variable to store z 
    mpz_init (tempz); 
    mpz_t tempbase;
    mpz_init(tempbase);
    mpz_ui_pow_ui(tempbase, 2,8); // base 2^8
    mpz_t tempcounter; // 2^8 ith term 
    mpz_init(tempcounter);
    

    // two loop to loop through the whole message and turn into z 
    for (int zy=0; zy<zi; zy++)
    {
      mpz_init(tempz);
          for (int ai=0; ai<=24; ai++)
          {
            // 2^8 ith term value 
            mpz_pow_ui(tempcounter, tempbase, ai);

            // tempz = 2^8 ith term * mi term
            // also read the character into integer value
            mpz_mul_ui(tempz,tempcounter, (int)inputStr[ai+(zy*25)]);
            /*
            printf("Result for tempz: \n");
            mpz_out_str(stdout, 10, tempz);
            printf("\n");
            */
            mpz_add(z[zy],z[zy],tempz); // z = z + tempz 
            
            printf("Result for z: \n");
            mpz_out_str(stdout, 10, z[zy]);
            printf("\n");
            
          }
          /*
            printf("Result for z%d: \n", zy);
            mpz_out_str(stdout, 10, z[zy]);
            printf("\n");
            */
    }

    // decode now 
    printf("decode now Result for z: \n");
    mpz_out_str(stdout, 10, z[0]);
    printf("\n");
        mpz_t temppower;
        mpz_init(temppower);
        mpz_t tempvalue;
        mpz_init(tempvalue);
       // printf("finish initiate variable\n");
        mpz_t zero;
        mpz_init(zero);

        mpz_ui_pow_ui(temppower, 256, 24);
        
        
        mpz_mod(tempvalue,z[0],temppower);
        printf("result of tempvalue:\n");
        mpz_out_str(stdout, 10, tempvalue);




}

void encryption(mpz_t h, mpz_t p, mpz_t g, mpz_t *z, int zi)
{
// random generate y 
  mpz_t y;// y hold the random variable 
  mpz_init(y); // initiate variable 

  gmp_randstate_t gmpRandState; /* Random generator state object */

  /* Initialize the random state with default algorithm... */
    gmp_randinit_default(gmpRandState);
      /* Seed the state with an unsigned long int before we begin.. */
    /* One can set the seed from an mpz_t too with gmp_randseed() */
    // for testing purpose, now only use seed 234
    gmp_randseed_ui(gmpRandState, 234);
    // generate a random no. into y 
    mpz_urandomm(y, gmpRandState, p); 
    // start to compute ci and di 

    mpz_t ci;
    mpz_init(ci);
    mpz_t di;
    mpz_init(di);
    mpz_t tempbase;
    mpz_init(tempbase);

    // open a file to output ci, di pair  
    FILE *fp = fopen("cipher.txt", "w");
    if (fp == NULL)
    {
      printf("error opening file\n");
      exit(1);
    }
    
    
    // start loop 
    for (int i=0; i<=zi; i++)
    {
      // each loop begining , will random generate new y 
      mpz_urandomm(y, gmpRandState, p);

    mpz_powm_sec(ci, g,y, p);

    mpz_powm_sec(tempbase, h,y, p);
    mpz_mul(tempbase,z[i],tempbase);
    mpz_mod(di, tempbase, p);
    mpz_out_str(fp,10,ci);
    fprintf(fp,",");
    mpz_out_str(fp,10,di);
    fprintf(fp, "\n");
    /*
            printf("Result %dth for ci,di: \n", i);
            mpz_out_str(stdout, 10, ci);
            printf("\n");
            mpz_out_str(stdout, 10, di);
            printf("\n");
            */

    }

    fclose(fp);
    mpz_clear(di);
    mpz_clear(ci);
}


void decryption(mpz_t x, mpz_t p, mpz_t g, mpz_t *enz, int zi)
{
  // read in the cipher txt 
   FILE *fp = fopen("cipher.txt", "r");
    if (fp == NULL)
    {
      printf("error opening file\n");
      exit(1);
    }

    mpz_t ci;
    mpz_init(ci);
    mpz_t di;
    mpz_init(di);
    mpz_t s;
    mpz_init(s);
    // loop for loop through the whole file 
    /*
    for (int i=0; i<=zi; i++)
    {
    mpz_inp_str(ci,fp,10);
    printf("result of ci:");
    mpz_out_str(stdout, 10, ci);
        printf("\n");
    mpz_inp_str(di,fp,10);
    printf("result of di:");
    mpz_out_str(stdout, 10, di);
        printf("\n");
    mpz_inp_str(di,fp,10);
    printf("result of di:");
    mpz_out_str(stdout, 10, di);
        printf("\n");
    }
    */
    mpz_inp_str(ci,fp,10);
    mpz_inp_str(di,fp,10); // this is a dumpy input 
    mpz_inp_str(di,fp,10);
    // step 1 s = ci^x mod p 
    mpz_powm_sec(s, ci,x, p);

    // step 2 
    // zi = di s mod p 
    mpz_t tempexp; // for p-2 power
    mpz_init(tempexp);
    mpz_sub_ui(tempexp,s,2);
    // s=  s^p-2 mod p 
    mpz_powm_sec(s,s,tempexp,p);
    
    // di * s 
    mpz_mul(enz[0],di,s);
    // di * s mod p = zi 

    mpz_mod(enz[0], enz[0], p);

        //printf("result of zi:");
    //mpz_out_str(stdout, 10, enz[0]);
        //printf("\n");

    //reconstruct message
    // we know 0<=mi<2^8 so we keep subtract 2^8i from z to get m24
        mpz_t temppower;
        mpz_init(temppower);
        mpz_t tempvalue;
        mpz_init(tempvalue);
       // printf("finish initiate variable\n");
        mpz_t zero;
        mpz_init(zero);

        mpz_ui_pow_ui(temppower, 256, 24);
        
        
        mpz_mod(tempvalue,enz[0],temppower);
        //printf("result of tempvalue:");
        //mpz_out_str(stdout, 10, tempvalue);
        printf("\n");




    fclose(fp);

}



int main(){

  /* parameters for global setup */
  int nob=200; //no of bit 
  int t=100;

  char inputStr[1024];
  /*
     mpz_t is the type defined for GMP integers.
     It is a pointer to the internals of the GMP integer data structure
   */

  printf ("Enter your number: ");
  scanf("%1023s" , inputStr); /* NOTE: never every write a call scanf ("%s", inputStr);
                                  You are leaving a security hole in your code. */
  mpz_t u;
  mpz_init(u);
  /*
  printf (" u= \n");
  mpz_out_str(stdout,10,u);
  printf ("\n");
  */
  // for a, k, m initate 
  mpz_t a; 
  mpz_t k; 
  mpz_t m;
  mpz_init(a);
  mpz_init(k);
  mpz_init(m);
  mpz_set_ui(a,4);
  mpz_set_ui(k,13);
  mpz_set_ui(m,497);
  modularexpon(u,a,k,m);

  printf (" exponent mod p :");
  mpz_out_str(stdout,10,u);
  printf ("\n");
  
  /* Return 2 if n is definitely prime, 
  return 1 if n is probably prime (without being certain), 
  or return 0 if n is definitely non-prime.
  */
  mpz_t testpm;
  mpz_init(testpm);
  mpz_set_ui(testpm, 23);
  printf("testing prime : %d \n" ,mpz_probab_prime_p(testpm,50));

  mpz_t p; 
  mpz_t g;
  mpz_init(p);
  mpz_init(g);
  mpz_set_ui(p,1);
  mpz_set_ui(g,1);
  printf("prime and root start\n");
  primenoandroot(p,g,nob,t); 
  // public and private key generation 

  publicandprivatekey(p,g);

  // read in K1 
  mpz_t h; // storing h value from k1 .txt
  mpz_init(h);
    FILE *fp = fopen("K1.txt", "r");
      if (fp == NULL)
      {
        printf("error opening file\n");
        exit(1);
      }
      mpz_inp_str(p,fp,10);
      
      mpz_inp_str(g,fp,10);
      
      mpz_inp_str(h,fp,10);
      /*
      printf (" P, G, H: \n");
      mpz_out_str(stdout,10,p);
      printf ("\n");
      mpz_out_str(stdout,10,g);
      printf ("\n");
      mpz_out_str(stdout,10,h);
      printf ("\n");
      */
      fclose(fp);
  // read in K2
   mpz_t x; // storing h value from k1 .txt
  mpz_init(x);
  FILE *fp2 = fopen("K2.txt", "r");
    if (fp2 == NULL)
      {
        printf("error opening file\n");
        exit(1);
      }
      mpz_inp_str(p,fp2,10);
      
      mpz_inp_str(g,fp2,10);
      
      mpz_inp_str(x,fp2,10);
      /*
      printf (" P, G, X: \n");
      mpz_out_str(stdout,10,p);
      printf ("\n");
      mpz_out_str(stdout,10,g);
      printf ("\n");
      mpz_out_str(stdout,10,x);
      printf ("\n");
      */    
    fclose(fp2);
  // encode
  // read in message
    FILE *msg = fopen("message.txt","r");
      if (msg == NULL)
      {
        printf("error opening file\n");
        exit(1);
      }
    // read all the character into a string of character
    fscanf(msg, "%[^\n]",inputStr);
    // get the no. of word what was inside the char array
    int xi=0;
    while (inputStr[xi]!=0)
    {
      xi++;
    }
    printf(" no. of char in the msg:%d\n", xi);
    printf("print msg: \n");
   /* 
   for (int yi=0; yi<xi; yi++)
    {
      printf("%c%d\n", inputStr[yi],inputStr[yi]);
    }
    */
// getting the zi now 
    // we are setting k = 25 for testing purpose 
    // so (no of char / 24) + 1 equal to no. of z we need 
    int zi = xi/24 +1;
    printf ("no. of z we need : %d\n", zi);
    mpz_t z[zi];
    for (int temp=0;temp<zi; temp++)
      {
        mpz_init(z[temp]);
            /*
            printf("Result for z: \n");
           mpz_out_str(stdout, 10, z[temp]);
            printf("\n");
            */
    } 

    // we are setting k = 25 so k -1 = 24
    // for the zi encoding 

    encoding(z, inputStr, zi);

    // Encryption 
    encryption(h, p, g, z, zi);

    // Decryption 
    mpz_t enz[zi]; // encrypted zi
    for (int temp=0;temp<zi; temp++)
      {
        mpz_init(enz[temp]);
            /*
            printf("Result for z: \n");
           mpz_out_str(stdout, 10, z[temp]);
            printf("\n");
            */
    } 
    decryption(x,p,g,enz,zi);



  /* 6. Clean up the mpz_t handles or else we will leak memory */
  //mpz_clear(n);
  mpz_clear(u);
  mpz_clear(testpm);
  mpz_clear(p);
  mpz_clear(g);
  mpz_clear(h);
  mpz_clear(x);
}