
#include <zephyr/init.h>
#include <hal/nrf_power.h>

static int Cruise_Dongle_Init( const struct device *dev )
{
	ARG_UNUSED(dev);

	/* if the nrf52840dongle_nrf52840 board is powered from USB
	 * (high voltage mode), GPIO output voltage is set to 1.8 volts by
	 * default and that is not enough to turn the green and blue LEDs on.
	 * Increase GPIO voltage to 3.0 volts.
	 */
	if ( ( nrf_power_mainregstatus_get( NRF_POWER ) == NRF_POWER_MAINREGSTATUS_HIGH ) && ( ( NRF_UICR->REGOUT0 & UICR_REGOUT0_VOUT_Msk ) != ( UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos ) ) )
	{
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;

		while ( NRF_NVMC->READY == NVMC_READY_READY_Busy )
		{
			;
		}

		NRF_UICR->REGOUT0 = ( NRF_UICR->REGOUT0 & ~ ( ( uint32_t )UICR_REGOUT0_VOUT_Msk ) ) | ( UICR_REGOUT0_VOUT_3V3 << UICR_REGOUT0_VOUT_Pos );
		NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
		
		while ( NRF_NVMC->READY == NVMC_READY_READY_Busy )
		{
			;
		}

		/* a reset is required for changes to take effect */
		NVIC_SystemReset();
	}

	return 0;
}

SYS_INIT( Cruise_Dongle_Init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY );