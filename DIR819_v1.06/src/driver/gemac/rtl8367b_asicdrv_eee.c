/*
 * Copyright (C) 2009 Realtek Semiconductor Corp. 
 * All Rights Reserved.
 *
 * This program is the proprietary software of Realtek Semiconductor
 * Corporation and/or its licensors, and only be used, duplicated, 
 * modified or distributed under the authorized license from Realtek. 
 *
 * ANY USE OF THE SOFTWARE OTHER THAN AS AUTHORIZED UNDER 
 * THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED. 
 *
 * $Revision: 28599 $
 * $Date: 2012-05-07 09:41:37 +0800 (星期一, 07 五月 2012) $
 *
 * Purpose : RTL8370 switch high-level API for RTL8367B
 * Feature : 
 *
 */

#include "rtl8367b_asicdrv_eee.h"

/*
@func int | rtl8367b_setAsicEee100M | Set eee force mode function enable/disable.
@parm unsigned int | port | The port number.
@parm unsigned int | enabled | 1: enabled, 0: disabled.
@rvalue RT_ERR_OK | Success.
@rvalue RT_ERR_SMI | SMI access error. 
@rvalue RT_ERR_INPUT | Invalid input parameter.
@comm
    This API set the 100M EEE enable function.

*/
int rtl8367b_setAsicEee100M(unsigned int port, unsigned int enable)
{
    if(port >= RTL8367B_PORTNO)
        return RT_ERR_PORT_ID;
	
    if (enable > 1)
        return RT_ERR_INPUT;
    
    return rtl8367b_setAsicRegBit(RTL8367B_PORT_EEE_CFG_REG(port), RTL8367B_PORT_EEE_100M_OFFSET, enable);
}

/*
@func int | rtl8367b_getAsicEee100M | Get 100M eee enable/disable.
@parm unsigned int | port | The port number.
@parm unsigned int* | enabled | 1: enabled, 0: disabled.
@rvalue RT_ERR_OK | Success.
@rvalue RT_ERR_SMI | SMI access error. 
@rvalue RT_ERR_INPUT | Invalid input parameter.
@comm
    This API get the 100M EEE function.
*/
int rtl8367b_getAsicEee100M(unsigned int port, unsigned int *enable)
{
    if(port >= RTL8367B_PORTNO)
        return RT_ERR_PORT_ID;
	
    return rtl8367b_getAsicRegBit(RTL8367B_PORT_EEE_CFG_REG(port), RTL8367B_PORT_EEE_100M_OFFSET, enable);
}

/*
@func int | rtl8367b_setAsicEeeGiga | Set eee force mode function enable/disable.
@parm unsigned int | port | The port number.
@parm unsigned int | enabled | 1: enabled, 0: disabled.
@rvalue RT_ERR_OK | Success.
@rvalue RT_ERR_SMI | SMI access error. 
@rvalue RT_ERR_INPUT | Invalid input parameter.
@comm
    This API set the 100M EEE enable function.

*/
int rtl8367b_setAsicEeeGiga(unsigned int port, unsigned int enable)
{
    if(port >= RTL8367B_PORTNO)
        return RT_ERR_PORT_ID;
	
    if (enable > 1)
        return RT_ERR_INPUT;
    
    return rtl8367b_setAsicRegBit(RTL8367B_PORT_EEE_CFG_REG(port), RTL8367B_PORT_EEE_GIGA_OFFSET, enable);
}

/*
@func int | rtl8367b_getAsicEeeGiga | Get 100M eee enable/disable.
@parm unsigned int | port | The port number.
@parm unsigned int* | enabled | 1: enabled, 0: disabled.
@rvalue RT_ERR_OK | Success.
@rvalue RT_ERR_SMI | SMI access error. 
@rvalue RT_ERR_INPUT | Invalid input parameter.
@comm
    This API get the 100M EEE function.
*/
int rtl8367b_getAsicEeeGiga(unsigned int port, unsigned int *enable)
{
    if(port >= RTL8367B_PORTNO)
        return RT_ERR_PORT_ID;
	
    return rtl8367b_getAsicRegBit(RTL8367B_PORT_EEE_CFG_REG(port), RTL8367B_PORT_EEE_GIGA_OFFSET, enable);
}
