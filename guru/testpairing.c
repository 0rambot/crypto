#include <stdio.h>
#include <ctime>
#include "pbc.h"
#include "pbc_time.h"
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <openssl/md5.h>
#pragma comment(lib, "libeay32.lib")


double get_time(void);

void testmd5();

int main(int argc, char **argv)
{
    

//    pairing_init_inp_str(pairing, stdin);
//  FILE *pf=fopen("a.param", "r");
//  FILE *pf=fopen("d159.param", "r");
//  FILE *pf=fopen("f.param", "r");

//    pairing_init_inp_str(pairing, stdin);
//    pairing_init_inp_str(pairing, pf);


//  a_param_input(pairing);
//  d_param_input(pairing);
//  f_param_input(pairing);

//  pairing_option_set(pairing, "method", "miller-affine");
//  pairing_option_set(pairing, "method", "shipsey-stange");


  // if(argc<2){
  //  printf("usage: testpairing <a|d|f>");
  //  return -1;
  // }

  // switch(argv[1][0]){
  // case 'a':
  //  a_param_input(pairing);
  //  break;
  // case 'd':
  //  d_param_input(pairing); 
  //  break;
  // case 'f':
  //  f_param_input(pairing);
  //  break;
  // default:
  //  printf("usage: testpairing <a|d|f>");
  //  return -1;
  //}

  //t1=get_time();
    //testSHA256();
  //t2=get_time();
  //printf("SHA256 time %f\n", t2-t1);
  
  element_t g, h, p;
  element_t x1, x2;
  element_t zg, zh, z;
  pairing_t pairing;
  double t1,t2, totaltime=0, temp;
  int i, length;

  //1.直接调用
  d_param_input(pairing);
  
  //2.动态配参数
  // a_param_t w;
  // a_param_init(w);
  // a_param_gen(w, 160,512);
  // pairing_init_a_param(pairing,w);

  // f_param_t w;
  // f_param_init(w);
  // f_param_gen(w, 160,512);
  // pairing_init_f_param(pairing,w);


  element_init_G1(g, pairing);
  element_init_G1(zg, pairing);
  element_init_G2(h, pairing);
  element_init_G2(zh, pairing);
  element_init_GT(p, pairing);
  element_init_GT(x1, pairing);
  element_init_GT(x2, pairing);
  element_init_Zr(z, pairing);

  element_random(g);
  element_random(h);
  element_random(p);
  element_random(z);
  
    //pairing->phi(g, h, pairing);
 //    element_printf("g = %B\n", g);
 //    element_printf("h = %B\n", h);
  // element_printf("p = %B\n", p);
  // element_printf("z = %B\n", z);
  

  //配对运算
  for ( i=0; i<1000; i++){
    t1=get_time();
    pairing_apply(x1, g, h, pairing); 
    t2=get_time();
    temp = t2-t1;
    totaltime = totaltime + temp;
    // printf("pairing time %f\n", t2-t1);
    // element_printf("f(g, h) = %B\n", x1);
  }
  printf("average pairing time %f\n", totaltime/1000);

  //Gt点乘
  totaltime = 0;
  for ( i=0; i<1000; i++){
    t1=get_time();
    element_mul_zn(x1, p, z);
    t2=get_time();
    temp = t2-t1;
    totaltime = totaltime + temp;
  }
  printf("average Gt point multip time %f\n", totaltime/1000);

  //Gt乘法运算
  totaltime = 0;
  for(i=0; i<1000; i++){
   t1=get_time();
   element_mul(x2, p, x1);
   t2 = get_time();
   // printf("multi time %f\n", t2-t1);
   temp = t2-t1;
   totaltime = totaltime + temp;
  }
  printf("average Gt multip time %f\n", totaltime/1000);
  
  //Gt指数运算
  totaltime = 0;
  for (i=0; i<1000; i++){
   t1=get_time();
   element_pow_zn(x2, x1, z);  
   t2=get_time();
   temp = t2-t1;
   totaltime = totaltime + temp;
   //printf("tate power time %f\n", t2-t1);
   // element_printf("f(g, h)^z = %B\n", x1);
  }
  printf("average Gt exp time %f\n", totaltime/1000);
  

  //G1加法运算
  totaltime = 0;
  for (i=0; i<1000; i++){
    t1=get_time();
    element_add(zg, g, zg);
    t2=get_time();
    temp = t2-t1;
    totaltime = totaltime + temp;
  }
  printf("average G1 addition time %f\n", totaltime/1000);

  //G1点乘
  totaltime = 0;
  for ( i=0; i<1000; i++){
    t1=get_time();
    element_mul_zn(zg, g, z);
    t2=get_time();
    temp = t2-t1;
    totaltime = totaltime + temp;
  }
  printf("average G1 point multip time %f\n", totaltime/1000);

  

  //G1乘法运算
  totaltime = 0;
  for ( i=0; i<1000; i++){
   t1=get_time();
   element_mul(zg, g, zg);
   t2=get_time();
   temp = t2-t1;
   totaltime = totaltime + temp;
  }
  printf("average G1 multip time %f\n", totaltime/1000);


  //G1指数运算
  totaltime = 0;
  for ( i=0; i<1000; i++){
   t1=get_time();
   element_pow_zn(zg, g, z);
   t2=get_time();
   temp = t2-t1;
   totaltime = totaltime + temp;
  }
  printf("average G1 exp time %f\n", totaltime/1000);

  //G2点乘
  totaltime = 0;
  for ( i=0; i<1000; i++){
    t1=get_time();
    element_mul_zn(zh, h, z);
    t2=get_time();
    temp = t2-t1;
    totaltime = totaltime + temp;
  }
  printf("average G2 point multip time %f\n", totaltime/1000);

  //G2乘法运算
  totaltime = 0;
  for ( i=0; i<1000; i++){
   t1=get_time();
   element_mul_zn(zh, h, zh);
   t2=get_time();
   temp = t2-t1;
   totaltime = totaltime + temp;
  }
  printf("average G2 multip time %f\n", totaltime/1000);


  //G2指数运算
  totaltime = 0;
  for ( i=0; i<1000; i++){
   t1=get_time();
   element_pow_zn(zh, h, z);
   t2=get_time();
   temp = t2-t1;
   totaltime = totaltime + temp;
  }
  printf("average G2 exp time %f\n", totaltime/1000);

  // // map to point hash
  // totaltime = 0;
  // for( i=0; i<1000; i++){
  //  t1=get_time();
  //  element_from_hash(g, "zxcvbnmasdfghjklqwertyuiop123456", 32);
  //  t2=get_time();
  //  temp = t2-t1;
  //  totaltime = totaltime + temp;
  // }
  // printf("average mtp time %f\n", totaltime/1000);

  // //群元素模运算
  // totaltime = 0;
  // for( i=0; i<1000; i++){
  //  t1=get_time();
  //  element_from_hash(g, "zxcvbnmasdfghjklqwertyuiop123456", 32);
  //  t2=get_time();
  //  temp = t2-t1;
  //  totaltime = totaltime + temp;
  // }
  // printf("average group mod time %f\n", totaltime/1000);

  //群元素求逆元
  totaltime = 0;
  for (i=0; i<1000; i++){
    t1=get_time();
    element_invert(g, g);
    t2=get_time();
    temp = t2-t1;
    totaltime = totaltime + temp;
  }
  printf("average group invert time %f\n", totaltime/1000);

  //Zr元素求逆元
  totaltime = 0;
  for (i=0; i<1000; i++){
    t1=get_time();
    element_invert(z, z);
    t2=get_time();
    temp = t2-t1;
    totaltime = totaltime + temp;
  }
  printf("average Zr invert time %f\n", totaltime/1000);

    element_clear(g);
    element_clear(h);
    element_clear(p);
    element_clear(x1);
    element_clear(x2);
    element_clear(zg);
    element_clear(zh);
    element_clear(z);
    pairing_clear(pairing);

//  getchar();

    return 0;
}
