/* [Remove/modify this line not to overwrite this file] */
/* Generated by RPARSE 2020-03-30 13:26 */

/* Reactions:
     X+Y > X*Y/vol > Z
     Z > Z > X+Y
*/

#include <math.h>
#include "propensities.h"
#include "report.h"

enum Species {
  X,
  Y,
  Z
};

const int NR = 2; /* number of reactions */

/* rate constants */
/* forward declaration */
double rFun1(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd);
double rFun2(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd);

/* static propensity vector */
static PropensityFun ptr[] = {rFun1,rFun2};

/* propensity definitions */
double rFun1(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd)
{
  return xstate[X]*xstate[Y]/vol;
}

double rFun2(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd)
{
  return xstate[Z];
}

/* URDME solver interface */
PropensityFun *ALLOC_propensities(size_t Mreactions)
{
  if (Mreactions > NR) PERROR("Wrong number of reactions.");
  return ptr;
}

void FREE_propensities(PropensityFun *ptr)
{ /* do nothing since a static array was used */ }
