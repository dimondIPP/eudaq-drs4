#ifndef ATLASFE4IINTERPRETER_H
#define ATLASFE4IINTERPRETER_H

/*
 * macros & defines for for FE-I4 raw data and trigger data processing
 */

/*
 * unformatted records
 */
class ATLASFEI4Interpreter
{

typedef std::bitset<32> bitfield;
typedef unsigned int uint;
//-----------------
// Data Header (DH)
//-----------------
bitfield dataHeader (0x00E90000);
//#define DATA_HEADER				0x00E90000
bitfield dataHeaderMask (0xFFFF0000);
//#define DATA_HEADER_MASK			0xFFFF0000
bitfield dataHeaderFlagMask (0x00008000);
//#define DATA_HEADER_FLAG_MASK			0x00008000
bitfield dataHeaderLVL1IDMask (0x00007F00);
//#define DATA_HEADER_LV1ID_MASK		0x00007F00
bitfield dataHeaderBCIDMask (0x000000FF);
//#define DATA_HEADER_BCID_MASK			0x000000FF

bool isDataHeader(uint X) {return dataHeaderMask & bitfield(X) == dataHeader;}
//#define DATA_HEADER_MACRO(X)			((DATA_HEADER_MASK & X) == DATA_HEADER ? true : false)
bool isDataHeaderFlag(unit X) {return dataHeaderFlagMask & bitfield(X) >> 15}
#define DATA_HEADER_FLAG_MACRO(X)		((DATA_HEADER_FLAG_MASK & X) >> 15)
#define DATA_HEADER_FLAG_SET_MACRO(X)	((DATA_HEADER_FLAG_MASK & X) == DATA_HEADER_FLAG_MASK ? true : false)
#define DATA_HEADER_LV1ID_MACRO(X)		((DATA_HEADER_LV1ID_MASK & X) >> 8)
#define DATA_HEADER_BCID_MACRO(X)		(DATA_HEADER_BCID_MASK & X)

// Data Record (DR)
#define DATA_RECORD_COLUMN_MASK			0x00FE0000
#define DATA_RECORD_ROW_MASK			0x0001FF00
#define DATA_RECORD_TOT1_MASK			0x000000F0
#define DATA_RECORD_TOT2_MASK			0x0000000F

#define RAW_DATA_MIN_COLUMN				0x00000001 // 1
#define RAW_DATA_MAX_COLUMN				0x00000050 // 80
#define RAW_DATA_MIN_ROW				0x00000001 // 1
#define RAW_DATA_MAX_ROW				0x00000150 // 336
#define DATA_RECORD_MIN_COLUMN			(RAW_DATA_MIN_COLUMN << 17)
#define DATA_RECORD_MAX_COLUMN			(RAW_DATA_MAX_COLUMN << 17)
#define DATA_RECORD_MIN_ROW				(RAW_DATA_MIN_ROW << 8)
#define DATA_RECORD_MAX_ROW				(RAW_DATA_MAX_ROW << 8)

#define DATA_RECORD_MACRO(X)			(((DATA_RECORD_COLUMN_MASK & X) <= DATA_RECORD_MAX_COLUMN) && ((DATA_RECORD_COLUMN_MASK & X) >= DATA_RECORD_MIN_COLUMN) && ((DATA_RECORD_ROW_MASK & X) <= DATA_RECORD_MAX_ROW) && ((DATA_RECORD_ROW_MASK & X) >= DATA_RECORD_MIN_ROW) ? true : false)
#define DATA_RECORD_COLUMN1_MACRO(X)	((DATA_RECORD_COLUMN_MASK & X) >> 17)
#define DATA_RECORD_ROW1_MACRO(X)		((DATA_RECORD_ROW_MASK & X) >> 8)
#define DATA_RECORD_TOT1_MACRO(X)		((DATA_RECORD_TOT1_MASK & X) >> 4)
#define DATA_RECORD_COLUMN2_MACRO(X)	((DATA_RECORD_COLUMN_MASK & X) >> 17)
#define DATA_RECORD_ROW2_MACRO(X)		(((DATA_RECORD_ROW_MASK & X) >> 8) + 1)
#define DATA_RECORD_TOT2_MACRO(X)		(DATA_RECORD_TOT2_MASK & X)

// Address Record (AR)
#define ADDRESS_RECORD					0x00EA0000
#define ADDRESS_RECORD_MASK				0xFFFF0000
#define ADDRESS_RECORD_TYPE_MASK		0x00008000
#define ADDRESS_RECORD_ADDRESS_MASK		0x00007FFF

#define ADDRESS_RECORD_MACRO(X)			((ADDRESS_RECORD_MASK & X) == ADDRESS_RECORD ? true : false)
#define ADDRESS_RECORD_TYPE_MACRO(X)	((ADDRESS_RECORD_TYPE_MASK & X) >> 15)
#define ADDRESS_RECORD_TYPE_SET_MACRO(X)((ADDRESS_RECORD_TYPE_MASK & X) == ADDRESS_RECORD_TYPE_MASK ? true : false)
#define ADDRESS_RECORD_ADDRESS_MACRO(X)	(ADDRESS_RECORD_ADDRESS_MASK & X)

// Value Record (VR)
#define VALUE_RECORD					0x00EC0000
#define VALUE_RECORD_MASK				0xFFFF0000
#define VALUE_RECORD_VALUE_MASK			0x0000FFFF

#define VALUE_RECORD_MACRO(X)			((VALUE_RECORD_MASK & X) == VALUE_RECORD ? true : false)
#define VALUE_RECORD_VALUE_MACRO(X)		(VALUE_RECORD_VALUE_MASK & X)

// Service Record (SR)
#define SERVICE_RECORD					0x00EF0000
#define SERVICE_RECORD_MASK				0xFFFF0000
#define SERVICE_RECORD_CODE_MASK		0x0000FC00
#define SERVICE_RECORD_COUNTER_MASK		0x000003FF

#define SERVICE_RECORD_MACRO(X)			((SERVICE_RECORD_MASK & X) == SERVICE_RECORD ? true : false)
#define SERVICE_RECORD_CODE_MACRO(X)	((SERVICE_RECORD_CODE_MASK & X) >> 10)
#define SERVICE_RECORD_COUNTER_MACRO(X)	(SERVICE_RECORD_COUNTER_MASK & X)

// Empty Record (ER)
#define EMPTY_RECORD					0x00000000
#define EMPTY_RECORD_MASK				0xFFFFFFFF

#define EMPTY_RECORD_MACRO(X)			((EMPTY_RECORD_MASK & X) == EMPTY_RECORD ? true : false)

/*
 * trigger data
 */

#define TRIGGER_WORD_HEADER_V10			0x00FFFF00
#define TRIGGER_WORD_HEADER_MASK_V10	0xFFFFFF00

#define TRIGGER_WORD_HEADER				0x00F80000 // tolerant to 1-bit flips and not equal to control/comma symbols
#define TRIGGER_WORD_HEADER_MASK		0xFFFF0000
#define TRIGGER_NUMBER_31_24_MASK		0x000000FF
#define TRIGGER_NUMBER_23_0_MASK		0x00FFFFFF

#define TRIGGER_DATA_MASK				0x0000FF00 // trigger error + trigger mode
#define TRIGGER_MODE_MASK				0x0000E000 // trigger mode
#define TRIGGER_ERROR_MASK				0x00001F00 // error code: bit 0: wrong number of dh, bit 1 service record recieved

#define TRIGGER_WORD_MACRO(X)			((((TRIGGER_WORD_HEADER_MASK & X) == TRIGGER_WORD_HEADER)  || ((TRIGGER_WORD_HEADER_MASK_V10 & X) == TRIGGER_WORD_HEADER_V10))? true : false)
#define TRIGGER_NUMBER_MACRO2(X, Y)		(((TRIGGER_NUMBER_31_24_MASK & X) << 24) | (TRIGGER_NUMBER_23_0_MASK & Y)) // returns full trigger number; reference and dereference of following array element

#define TRIGGER_ERROR_OCCURRED_MACRO(X)	(((((TRIGGER_ERROR_MASK & X) >> 8) == 0x00000000) || ((TRIGGER_WORD_HEADER_MASK_V10 & X) == TRIGGER_WORD_HEADER_V10)) ? false : true)
#define TRIGGER_DATA_MACRO(X)			((TRIGGER_DATA_MASK & X) >> 8)
#define TRIGGER_ERROR_MACRO(X)			((TRIGGER_ERROR_MASK & X) >> 8)
#define TRIGGER_MODE_MACRO(X)			((TRIGGER_MODE_MASK & X) >> 13)

#endif //ATLASFE4IINTERPRETER_H
