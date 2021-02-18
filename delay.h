/* 
 * File:   delay.h
 * Author: M.Magdy
 *
 * Created on March 4, 2020, 1:12 AM
 */

#ifndef DELAY_H
#define	DELAY_H

#ifdef	__cplusplus
extern "C" {
#endif
    #include "sys.h"

#define MSdelay_enable 1
#if(MSdelay_enable == 1)
    void MSdelay(unsigned int val);
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_H */

