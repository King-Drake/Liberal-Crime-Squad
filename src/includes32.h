




/*
	File created by Chris Johnson.
	These were previously all in game.cpp.

	This file includes all the the enums, defines, and included headers required globally by all components.

	All code released under GNU GPL.
*/
#include <windows.h>
#include <vector>
#include <map>
#include <deque>
#include "cmarkup/Markup.h"
using namespace std;

#include "includesDeprecated.h"
/* This is declared again lower down, just needed here for this header. */
std::string tostring(long i);
//#include "vehicle/vehicletype.h"
//#include "vehicle/vehicle.h"


//just a float that is initialized to 0
////#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
//#include "activityST.h"

////int get_associated_attribute(int skill_type);

//#include "includesDeprecatedB.h"
//#ifdef	ITEMTYPE_CPP
// itemtype.cpp


#include "../items/itemtype.h"
extern int year;
const string CONST_UNKNOWN_ELEMENT_FOR_ITEM_TYPE_IDNAME = "Unknown element for item type << idname_ << ";
const string CONST_LACKS_IDNAME = "LACKS IDNAME ";
const string CONST_UNDEFINED = "UNDEFINED";

const string tag_fencevalue = "fencevalue";
const string tag_name_future = "name_future";
const string tag_name = "name";
const string tag_idname = "idname";
const string tag_id = "id";
//#endif//ITEMTYPE_CPP
//#endif// INCLUDES_H_INCLUDED
