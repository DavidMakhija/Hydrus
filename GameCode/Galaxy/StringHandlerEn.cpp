#include "StringHandlerEn.h"

StringHandlerEn::StringHandlerEn()
{

}

void StringHandlerEn::GenerateStrings()
{
	//FIXME I'm dissatisfied with this. 
	// 1. Programmer can enter duplicates without an error, overwriting previous definitions
	// 2. Enums make you recompile all of the source
	// I think adopting the XML parsing will solve both of these items.
	mStringMap[GAME_NEW_OR_LOAD]            = "Choose an option -\n1 - New game\n2 - Load game\n";
	mStringMap[OPTION_NOT_FOUND]            = "Incorrect option specified, ";
	mStringMap[PICK_VALID_OPTION]           = "Please pick a valid option";
	mStringMap[ENTER_MAIN_CHARACTER_NAME]   = "Hello, what is your name?";
	mStringMap[ENTER_SECOND_CHARACTER_NAME] = "What's you buddies name?";
	mStringMap[WELL]                        = "Well, ";
	mStringMap[KICKASS]                     = "it's time to kick some ass";
	mStringMap[READY_OPTIONS]               = "Attack: a\nPass: p\n";
	mStringMap[ATTACK_DAMAGE]               = "Took attack damage from ";
	mStringMap[COUNTER_ATTACK_DAMAGE]       = "Took counter attack damage from";
	mStringMap[STAT_CHANGE]                 = "Stat change for actor:";
}