#include <htc.h>
#include "system.h"
#include "adc.h"

/*******************************************************************************
* PUBLIC FUNCTION: adc_initialize
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Initialize the ADC module.
*
*******************************************************************************/
void adc_initialize(void)
{
	// A/D Conversion Clock = FOSC/64.
	ADCS2 = 1;
	ADCS1 = 1;
	ADCS0 = 0;
	
	// Set AN0 only as analog input, others AN as digital pin
	PCFG3 = 1;
	PCFG2 = 1;
	PCFG1 = 1;
	PCFG0 = 0;
	
	// Configure the result to be right justified, will take as 10-bit ADC
	ADFM = 1;
	
	// Turn Off ADC module by default
	ADON = 0;
}

	
/*******************************************************************************
* PUBLIC FUNCTION: adc_on
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Activate ADC module
*
*******************************************************************************/
void adc_on(void)
{
	// Turn On ADC module
	ADON = 1;
}

/*******************************************************************************
* PUBLIC FUNCTION: adc_off
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ void
*
* DESCRIPTIONS:
* Deactivate ADC module
*
*******************************************************************************/
void adc_off(void)
{
	// Turn Off ADC module, to save power
	ADON = 0;
}

/*******************************************************************************
* PUBLIC FUNCTION: ui_adc_read
*
* PARAMETERS:
* ~ void
*
* RETURN:
* ~ The ADC result in 16-bit
*
* DESCRIPTIONS:
* Convert and read the result of the ADC from ANO.
*
*******************************************************************************/
unsigned int ui_adc_read(void)
{
	unsigned int ohm = 0;
	// Select the ADC channel, AN0
	CHS2 = 0;
	CHS1 = 0;
	CHS0 = 0;
	
	// Delay 1mS to fully charge the holding capacitor in the ADC module.
	__delay_ms(1);
	
	// Start the conversion and wait for it to complete.
	GO = 1;
	while (GO == 1);
	// Return 10-bit ADC result.
	ohm = (unsigned int)ADRESH << 8;
	ohm = ohm + ADRESL;
	return ohm;
}	
