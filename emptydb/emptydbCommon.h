/*
	emptydb::Common
*/
#pragma once
#include "../plib/plibStdDataBST.h"
#include "../plib/plibStdMemoryPool.h"

typedef uint32_t emptydbCommonKeyType ;
typedef uint32_t emptydbCommonCountType ;

struct emptydbCommonObjectValueType
{
	struct plibStdDataBST *MemberObjectGenesisNode , *MemberPropertGenesisNode ;
} ;

struct emptydbCommonPropertyValueType
{
	emptydbCommonCountType DataSize , DataLength ;
	uint8_t DataType ;
	uint8_t *Data ;
} ;

enum plibStdDataBSTStatus emptydbCommon_compareKey( uint8_t *Key1 , uint8_t *Key2 ) ;