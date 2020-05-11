/* [Remove/modify this line not to overwrite this file] */
/* Generated by RPARSE 2020-05-11 10:42 */

/* Reactions:
     @ > k1*a*vol > U
     U > k2*b*U > V
     U+U+V > (k3/(vol*vol))*(U*(U-1)*V) > U+U+U
     U > k4*U > @
*/

#include <math.h>
#include "propensities.h"
#include "report.h"

enum Species {
  U,
  V
};

const int NR = 4; /* number of reactions */

/* rate constants */
const double k1 = 1.000000000000000000000e+00;
const double k2 = 1.000000000000000000000e+00;
const double k3 = 1.000000000000000000000e+00;
const double k4 = 1.000000000000000000000e+00;
const double a = 4.500000000000000000000e+00;
const double b = 7.500000000000000000000e+00;

/* forward declaration */
double rFun1(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd);
double rFun2(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd);
double rFun3(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd);
double rFun4(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd);

/* static propensity vector */
static PropensityFun ptr[] = {rFun1,rFun2,rFun3,rFun4};

/* propensity definitions */
double rFun1(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd)
{
  return k1*a*vol;
}

double rFun2(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd)
{
  return k2*b*xstate[U];
}

double rFun3(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd)
{
  return (k3/(vol*vol))*(xstate[U]*(xstate[U]-1)*xstate[V]);
}

double rFun4(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd)
{
  return k4*xstate[U];
}

/* URDME solver interface */
PropensityFun *ALLOC_propensities(size_t Mreactions)
{
  if (Mreactions > NR) PERROR("Wrong number of reactions.");
  return ptr;
}

void FREE_propensities(PropensityFun *ptr)
{ /* do nothing since a static array was used */ }

