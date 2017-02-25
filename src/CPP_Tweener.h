//
//  CPP_Tweener.h
//  Test
//
//  Created by Wade Okawa-Scannell on 9/29/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Tweener_h
#define CPP_Tweener_h

class CPP_Tweener
{
public:
	CPP_Tweener();
	virtual ~CPP_Tweener() = default;
	// TODO: Other constructors?
	
	// If this object should update.
	bool isActive() const;
	void setActive(bool value);
	
	// If the CPP_Tweener should clear on removal. For CPP_Entities, this is when they are
	// removed from a CPP_World, and for CPP_World this is when the active CPP_World is switched.
	bool isAutoClear() const;
	void setAutoClear(bool value);
	
	virtual void update();
	
private:
	bool active;
	bool autoClear;
};

#endif /* CPP_Tweener_h */
