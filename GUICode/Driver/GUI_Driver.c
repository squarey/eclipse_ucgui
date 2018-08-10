

#include "GUI.h"



void GUI_DriverInit(GUI_Driver_t *pDriver)
{
	LCD_DriverInit(&pDriver->tLCDDriver);
	pDriver->tTouchDriver = NULL;
}
void GUI_DriverRegister(GUI_Driver_t *pDriver)
{
	LCD_DriverRegister(&pDriver->tLCDDriver);
	GUI_TouchDriverRegister(&pDriver->tTouchDriver);
}
