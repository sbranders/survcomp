#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <R.h>
#include "survcomp.h"

void concordanceIndexC(int *msurv, int *ustrat, double *x2, int *cl2,
		double *st, int *se, int *weights, int *strat, int *N, int *outx,
		int *ch, int *dh, int *uh, int *rph, int *lenS, int *lenU) {
	
	int lenUstrat = *lenU;
	int lenStrat = *lenS;
	int Ns_old = 0;
	int Ns = 0;	
    for(int s=0; s < lenUstrat; s++) {
    	int ixs[lenStrat];
    	for(int i =0; i < lenStrat; i++){
    		ixs[i] = 0;
    		if(strat[i] == ustrat[s]){
    			ixs[i] = 1;
    		} else {
    			ixs[i] = 0;
    		}
    	}
    	Ns_old += Ns;
    	Ns = 0;
        for(int i=0; i < lenStrat; i++){
        	if(ixs[i] == 1){
        		Ns++;
        	}
        }
        double xs[Ns];
        int c = 0;
        for(int i=0; i < lenStrat; i++){
        	if(ixs[i] == 1){
        		xs[c] = x2[i];
        		c++;
        	}
        }
        int cls[Ns];
        c = 0;
        for(int i=0; i < lenStrat; i++){
        	if(ixs[i] == 1){
        		cls[c] = cl2[i];
        		c++;
        	}
        }
        double sts[Ns];
        c = 0;
        for(int i=0; i < lenStrat; i++){
        	if(ixs[i] == 1){
        		sts[c] = st[i];
        		c++;
        	}
        }        
        int ses[Ns];
        c = 0;
        for(int i=0; i < lenStrat; i++){
        	if(ixs[i] == 1){
        		ses[c] = se[i];
        		c++;
        	}
        }
        int weightss[Ns];
        c = 0;
        for(int i=0; i < lenStrat; i++){
        	if(ixs[i] == 1){
        		weightss[c] = weights[i];
        		c++;
        	}
        }
        int chs[Ns];
        int dhs[Ns];
        int uhs[Ns];
        int rphs[Ns];
        for (int h=0; h < Ns; h++) {       	
        	int chsj, dhsj, uhsj, rphsj = 0;
            for (int j=0; j < Ns; j++) {
                int whj = weightss[h] * weightss[j];
                if ((*msurv == 1 && (sts[h] < sts[j] && ses[h] == 1)) || (*msurv == 0 && cls[h] > cls[j])) {
                  rphsj = rphsj + whj;
                  if (xs[h] > xs[j]) {  
                    chsj = chsj + whj;
                  } else if (xs[h] < xs[j]) {
                    dhsj = dhsj + whj;
                  }
                  else {
                    if (*outx == 1) {
                      uhsj = uhsj + whj;
                    } else {
                      dhsj = dhsj + whj;
                    }
                  }
                }    
                if ((*msurv == 1 && (sts[h] > sts[j] && ses[j] == 1)) || (*msurv == 0 && cls[h] < cls[j])) { 	
                  rphsj = rphsj + whj;
                  if (xs[h] < xs[j]) {
                    chsj = chsj + whj;
                  }
                  else if (xs[h] > xs[j]) {
                    dhsj = dhsj + whj;
                  }
                  else {
                    if (*outx == 1) {
                      uhsj = uhsj + whj;
                    } else {
                      dhsj = dhsj + whj;
                    }
                  }
                }
            }
            chs[h] = chsj;
            dhs[h] = dhsj;
            uhs[h] = uhsj;
            rphs[h] = rphsj;
            chsj = 0;
            dhsj = 0;
            uhsj = 0;
            rphsj = 0;
        }
        for(int i = 0; i < Ns; i++){
        	int pos = i + Ns_old;
        	ch[pos] = chs[i];
        	dh[pos] = dhs[i];
        	uh[pos] = uhs[i];
        	rph[pos] = rphs[i];
        }
    }
}
