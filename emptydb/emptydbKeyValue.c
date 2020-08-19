/*
	emptydb::KeyValue
*/
#include "emptydbKeyValue.h"

bool emptydbKeyValue_createKeyValue( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray , size_t DataSize , size_t DataLength )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer || DataSize == 0 || DataLength == 0 )
		return false ;
	
	size_t Index ;
	uint8_t *NewMemory ;
	struct plibStdDataBST *NewKeyValueNode ;
	struct emptydbCommonKeyValueType *NewValue ;
	
	for( Index = 0 ; Index < KeyCount ; Index ++ )
	{
		NewMemory = plbStdMemoryPool_allocate( Root->KeyValueNodePool ) ;
		NewKeyValueNode = ( struct plibStdDataBST* )NewMemory ;
		NewKeyValueNode->Left = plibStdTypeNullPointer ;
		NewKeyValueNode->Right = plibStdTypeNullPointer ;
		NewKeyValueNode->Key = NewMemory + sizeof( struct plibStdDataBST ) ;
		*( emptydbCommonKeyType* )NewKeyValueNode->Key = KeyArray[ Index ] ;
		NewKeyValueNode->Type = 0 ;
		NewKeyValueNode->Value = NewMemory + sizeof( struct plibStdDataBST ) + sizeof( emptydbCommonKeyType ) ; ;

		NewValue = ( struct emptydbCommonKeyValueType* )NewKeyValueNode->Value ;
		NewValue->DataSize = DataSize ;
		NewValue->DataLength = DataLength ;
		//NewValue->Data = plibStdTypeNullPointer ;
		
		if( plibStdDataBST_push( &( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberKeyValueRootNode , NewKeyValueNode , emptydbCommon_compareKey ) )
			Root->KeyValueCount ++ ;
		else
			plbStdMemoryPool_deallocate( Root->KeyValueNodePool , &NewMemory ) ;
	}
	
	return true ;
}
bool emptydbKeyValue_deleteKeyValue( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer )
		return false ;
	
	size_t Index ;
	struct plibStdDataBST *KeyValueNode ;
	
	for( Index = 0 ; Index < KeyCount ; Index ++ )
	{
		KeyValueNode = plibStdDataBST_pop( &( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberKeyValueRootNode , ( uint8_t* )( KeyArray + Index ) , emptydbCommon_compareKey ) ;
		if( KeyValueNode == plibStdTypeNullPointer )
			continue ;
		plbStdMemoryPool_deallocate( Root->KeyValueNodePool , ( uint8_t** )( &KeyValueNode ) ) ;
		Root->KeyValueCount -- ;
	}
	
	return true ;
}

size_t emptydbKeyValue_lookupKeyValue( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray , struct plibStdDataBST **ResultKeyValueArray )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer )
		return 0 ;
		
	size_t Index , Count ;
	struct plibStdDataBST *KeyValueRootNode = ( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberKeyValueRootNode , *KeyValueThisNode ;
	
	for( Index = 0 , Count = 0 ; Index < KeyCount ; Index ++ )
	{
		KeyValueThisNode = plibStdDataBST_lookup( KeyValueRootNode , ( uint8_t* )( KeyArray + Index ) , emptydbCommon_compareKey ) ;
		if( KeyValueThisNode == plibStdTypeNullPointer )
			continue ;
		ResultKeyValueArray[ Count ] = KeyValueThisNode ;
		Count ++ ;
	}
	
	return Count ;
}
