/* [Remove/modify this line not to overwrite this file] */
/* Generated by RPARSE 2020-05-19 17:02 */

/* Reactions:
     @ > k1*vol > U
     U > k2*U > @
     @ > k3*vol > V
     U+U+V > (k4/(vol*vol))*(U*(U-1)*V) > U+U+U
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
const double k1 = 1.000000000000000055511e-01;
const double k2 = 1.000000000000000000000e+00;
const double k3 = 9.000000000000000222045e-01;
const double k4 = 1.000000000000000000000e+00;

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
  return k1*vol;
}

double rFun2(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd)
{
  return k2*xstate[U];
}

double rFun3(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd)
{
  return k3*vol;
}

double rFun4(const URDMEstate_t *xstate,double time,double vol,
             const double *ldata,const double *gdata,int sd)
{
  return (k4/(vol*vol))*(xstate[U]*(xstate[U]-1)*xstate[V]);
}

/* URDME solver interface */
PropensityFun *ALLOC_propensities(size_t Mreactions)
{
  if (Mreactions > NR) PERROR("Wrong number of reactions.");
  return ptr;
}

void FREE_propensities(PropensityFun *ptr)
{ /* do nothing since a static array was used */ }

