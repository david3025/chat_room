/*---------------------------------c file--------------*/
/********************************************************
 * uid.c - UID implementation
 * 
 * Author : 
 * Reviewed and approved by :
 * 
 * 
 * 14/09/2021
 * OLRD 110 Ramat Gan
 * 
 * *********************************************************/
 

#include "uid.h"

static size_t counter = 0;
const uid_t BAD_UID = {0};


/*=================================h file-------------*/
/********************************************************
 * 
 * uid.h - UID API
 * 
 * Author : OLRD 110 Narnia (johnny ? fani : shahar)    XDDDDD
 * Reviewed and approved by : Binyamin Haymann 
 * 
 * 
 * 14/09/2021
 * OLRD 110 Ramat Gan
 * 
 * 
 * *********************************************************/
#ifndef __UID_OL_110_H__
#define __UID_OL_110_H__

#include <unistd.h> /* pid_t, getpid */
#include <sys/types.h>
#include <time.h> /* time_t, time */


struct uid
{
    size_t __counter__;
    pid_t __process_id__;
    time_t __time_ind__;
};

typedef struct uid uid_t;

uid_t GetUID(void);
int IsSameUID(uid_t uid1, uid_t uid2);
extern const uid_t BAD_UID;

#endif /* __UID_OL_110_H__ */

