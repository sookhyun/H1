


const int nbins_max = 20;

const int nbinsx = 6;//x
const int nbinsQ2 = 12;//Q2
const int nbinstau = 14;//tau, added one overflow bin >1

float Q2bins[nbinsQ2+1] = {1.65,1.85,2.05,2.25,2.45,2.65,2.85,3.05,3.25,3.55,4.00,4.4437,4.8881};
float xbins[nbinsx+1] = {-2.80,-2.40,-2.00,-1.60,-1.20,-0.8386,0.00};
float taubins[nbinstau+1] ={0.0,0.05,0.10,0.15,0.22,0.3,0.4,0.5,0.6,0.7,0.8,0.9,0.98,1.0,1.05};

void setbins()
{
for(int iq=0; iq<(nbinsQ2+1); ++iq){ Q2bins[iq] = pow(10,Q2bins[iq]);}
for(int iz=0; iz<(nbinsx+1); ++iz) {xbins[iz] = pow(10,xbins[iz]);}
}

// Bins used for unfolding
float *varbins[3];
