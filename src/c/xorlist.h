#pragma once


struct itmx;

typedef struct {
  struct itmx* at; 
  struct itmx* pre;
} itrx;

enum{
  N_B = 32,
  MAX_ITRX = (N_B - sizeof(int))/sizeof(itrx),
};


typedef struct itmx {
   size_t link;
  union{
    char c[N_B];
    struct {
      int numit;
      int level;
      itrx it[MAX_ITRX];
    };
  };
} itmx;


  
typedef struct {
  int ord;
  size_t link;
  itmx ims[128];
} alx;

