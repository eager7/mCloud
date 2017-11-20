/****************************************************************************
*
* MODULE:             utils.h
*
* COMPONENT:          utils define
*
* REVISION:           $Revision:  0.1$
*
* DATED:              $Date: 2017-10-17 15:13:17
*
* AUTHOR:             PCT
*
****************************************************************************
*
* Copyright  panchangtao@gmail.com  B.V. 2017.     All  rights reserved
*
***************************************************************************/


#ifndef __BLOCK_SERVER_H
#define __BLOCK_SERVER_H

#if defined __cplusplus
extern "C" {
#endif
/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/****************************************************************************/
/***        Macro Definitions                                             ***/
/****************************************************************************/
#define MIBF 128
#define MDBF 256
#define MXBF 1024

#define PACKED __attribute__((__packed__))

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
//typedef unsigned char uint8_t;
//typedef unsigned short int uint16_t;
//typedef unsigned int uint32_t;
//typedef unsigned long long uint64_t;

typedef enum _teGprsCommand
{
    E_GPRS_COMMAND_SYNC_TIME = 201,
    E_GPRS_COMMAND_SETTING_REQUEST = 202,
    E_GPRS_COMMAND_RFID_REQUEST = 102,
    E_GPRS_COMMAND_RFID_RESPONSE = 101,
    E_GPRS_COMMAND_FINISHED_REQUEST = 205,
} teGprsCommand;

typedef union _uTimeSyncRequest
{
    uint8_t auData[11];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint32_t u32DeviceID;
    } PACKED sMessage;
} tuTimeSyncRequest;

typedef union _uTimeSyncResponse
{
    uint8_t auData[13];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint8_t u8Year;
        uint8_t u8Month;
        uint8_t u8Day;
        uint8_t u8Hour;
        uint8_t u8Minute;
        uint8_t u8Second;
    } PACKED sMessage;
} tuTimeSyncResponse;

typedef union _uReadSettingRequest
{
    uint8_t auData[11];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint32_t u32DeviceID;
    } PACKED sMessage;
} tuReadSettingRequest;

typedef union _uReadSettingResponse
{
    uint8_t auData[75];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint32_t u32DeviceID;
        uint8_t auOption[60];
        uint32_t u32Setting;
    } PACKED sMessage;
} tuReadSettingResponse;

typedef union _uErrorCodeResponse
{
    uint8_t auData[8];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint8_t u8ErrorCode;
    } PACKED sMessage;
} tuErrorCodeResponse;

typedef union _uRFIDRequest
{
    uint8_t auData[15];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint8_t auRFIDCode[8];
    } PACKED sMessage;
} tuRFIDRequest;

typedef union _uRFIDResponse
{
    uint8_t auData[20];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint32_t u32DeviceID;
        uint32_t u32UserID;
        uint8_t u8CardType;
        uint32_t u32Balance;
    } PACKED sMessage;
} tuRFIDResponse;

typedef union _uRFIDResponseError
{
    uint8_t auData[17];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint32_t u32DeviceID;
        uint32_t u32UserID;
        uint8_t u8CardType;
        uint8_t u8CareState;
    } PACKED sMessage;
} tuRFIDResponseError;

typedef union _uFinishRequest
{
    uint8_t auData[19];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint32_t u32DeviceID;
        uint32_t u32UserID;
        uint32_t u32Expense;
    } PACKED sMessage;
} tuFinishRequest;

typedef union _uFinishResponse
{
    uint8_t auData[19];
    struct
    {
        uint32_t u32Time;
        uint16_t u16Command;
        uint8_t u8Length;
        uint32_t u32DeviceID;
        uint32_t u32UserID;
        uint32_t u32Expend;
    } PACKED sMessage;
} tuFinishResponse;

/****************************************************************************/
/***        Local Function Prototypes                                     ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

/****************************************************************************/
/***        Local Variables                                               ***/
/****************************************************************************/

/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
/****************************************************************************/
/***        Locate   Functions                                            ***/
/****************************************************************************/
#if defined __cplusplus
}
#endif

#endif
