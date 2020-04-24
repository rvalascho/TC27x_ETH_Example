/*
 *  vadc.h
 *
 *  Created on: May 12, 2017
 *      Author: Lance Gurka
 */

#ifndef VADC_H_
#define VADC_H_

/*Select VADC trigger source*/
#define CCU6_TRIGGER 0
#define CCU6_TRIGGER_SYNCFIX 0
#define GTM_TRIGGER 1
#define ERU_TRIGGER 0

void vadc_init_queue(void);
void vadc_init_scan(void);
void vadc_init_bgndscan(void);
void vadc_init_queue_sync(void);

void ADC_TC068_W4_Sync(void);

#endif /* VADC_H_ */
