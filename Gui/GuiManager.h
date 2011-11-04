/*
 *  GuiManager.h
 *  Fish
 *
 *  Created by Todd Vanderlin on 7/14/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#pragma once
#include "GuiGroup.h"

// -------------------------------------
// This is a helper class to manage all
// your gui groups
// -------------------------------------
class GuiManager {
	
public:
	
	GuiManager() {
	}
	
	static void registerEvents() {
		for (int i=0; i<GuiManager::groups.size(); i++) {
			GuiManager::groups[i]->registerEvents();
		}
	}
	
	static void save() {
		for(int i=0; i<GuiManager::groups.size(); i++) {
			GuiManager::groups[i]->save();
		}
	}
	static vector <GuiGroup*> groups;
	
};
