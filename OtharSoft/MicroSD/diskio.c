/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/
#include "tm_stm32f4_rtc.h"
#include "diskio.h"		/* FatFs lower layer API */
#include "ff.h"


























































#include "sd.h"



/* Definitions of physical drive number for each media */
#define SD		   0
#define USB		   1
#define SDRAM      2
#define SPI_FLASH  3



TM_RTC_Time_t datatime;






















































/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
	if (pdrv == SD){
		return SD_disk_initialize();
	}
	
	return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
	if (pdrv == SD){
		return SD_disk_status();
	}
	
	return STA_NOINIT;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	/* Check count */
	if (!count) {
		return RES_PARERR;
	}
	
	if (pdrv == SD){
		return SD_disk_read(buff, sector, count);
	}
	
	/* Return parameter error */
	return RES_PARERR;
}




/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	UINT count			/* Number of sectors to write (1..128) */
)
{
	/* Check count */
	if (!count) {
		return RES_PARERR;
	}
	
	/* Return low level status */
	if (pdrv == SD) {
		return SD_disk_write(buff, sector, count);
	}
	
	/* Return parameter error */
	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	/* Return low level status */
	if (pdrv == SD) {
		return SD_disk_ioctl(cmd, buff);
	}
	
	/* Return parameter error */
	return RES_PARERR;
}


/*-----------------------------------------------------------------------*/
/* Get time for fatfs for files                                          */
/*-----------------------------------------------------------------------*/
__weak DWORD get_fattime(void) {

	TM_RTC_GetDateTime(&datatime, TM_RTC_Format_BIN);
	/* Returns current time packed into a DWORD variable */
	return	  ((DWORD)(datatime.year+2000) << 25)	/* Year */
			| ((DWORD)(datatime.month) << 21)				/* Month */
			| ((DWORD)(datatime.date) << 16)				/* Mday  */
			| ((DWORD)(datatime.hours) << 11)				/* Hour  */
			| ((DWORD)(datatime.month) << 5)				/* Min   */
			| ((DWORD)(datatime.minutes) >> 1);				/* Sec   */
}





















