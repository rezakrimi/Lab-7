#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int op_sub(struct tokenStack *stack);
static int op_mul(struct tokenStack *stack);
static int op_div(struct tokenStack *stack);
static int op_gt(struct tokenStack *stack);
static int op_lt(struct tokenStack *stack);
static int op_ge(struct tokenStack *stack);
static int op_le(struct tokenStack *stack);
static int op_eq(struct tokenStack *stack);
static int op_mod(struct tokenStack *stack);
static int op_swap(struct tokenStack *stack);
static int op_s(struct tokenStack *stack);


static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_sub},
  {"*", op_mul},
  {"/", op_div},
  {"GT", op_gt},
  {"LT", op_lt},
  {"GE", op_ge},
  {"LE", op_le},
  {"EQ", op_eq},
  {"MOD", op_mod},
  {"SWAP", op_swap},
  {"S", op_s},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
  struct lexToken *t = popTokenStack(s);
  int result = atoi(t->symbol);
  freeToken(t);

  return result;
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
  struct lexToken *token;
  token = allocToken();
  sprintf(token->symbol, "%d", v);
  token ->kind = LEX_TOKEN_NUMBER;
  pushTokenStack(s, token);
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  pushTokenStack(stack, t);
  
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_sub(struct tokenStack *stack){
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2-v1);
  return(0);
}

static int op_mul(struct tokenStack *stack){
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2*v1);
  return(0);
}

static int op_div(struct tokenStack *stack){
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v2/v1);
  return(0);
}

static int op_gt(struct tokenStack *stack){
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2>v1){
    pushInt(stack, 1);
  }
  else{
    pushInt(stack, 0);
  }
  return(0);
}

static int op_lt(struct tokenStack *stack){
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2<v1){
    pushInt(stack, 1);
  }
  else{
    pushInt(stack, 0);
  }
  return(0);
}

static int op_ge(struct tokenStack *stack){
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2>=v1){
    pushInt(stack, 1);
  }
  else{
    pushInt(stack, 0);
  }
  return(0);
}

static int op_le(struct tokenStack *stack){
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2<=v1){
    pushInt(stack, 1);
  }
  else{
    pushInt(stack, 0);
  }
  return(0);
}

static int op_eq(struct tokenStack *stack){
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v2==v1){
    pushInt(stack, 1);
  }
  else{
    pushInt(stack, 0);
  }
  return(0);
}

static int op_mod(struct tokenStack *stack){
  int v1;
  v1 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v1);
  return(0);
}

static int op_swap(struct tokenStack *stack){
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1);
  pushInt(stack, v2);
  return(0);
}

static int op_s(struct tokenStack *stack){
  /*struct lexToken *list[TOKEN_STACK_SIZE];
  int i = 0;
  int j;
  while (stack->top > 0){
    list[i] = popTokenStack(stack);
    i++;
  }
  j = i-1;
  while (j>=0){
    printToken(stdout, list[j]);
    pushTokenStack(stack, list[j]);
    j--;
  }*/

  struct lexToken *t;
  if(stack->top > 0){
    t = popTokenStack(stack);
    op_s(stack);
  }
  else{
    return(0);
  }
  printToken(stdout, t);
  pushTokenStack(stack, t);
  return(0);
}
