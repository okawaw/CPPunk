//
//  CPP_Mask.h
//  Test
//
//  Created by Wade Okawa-Scannell on 10/10/16.
//  Copyright © 2016 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Mask_h
#define CPP_Mask_h

class CPP_Entity;
class CPP_MaskList;

class CPP_Mask
{
public:
	CPP_Mask();
	virtual ~CPP_Mask() = default;
	// TODO: Other constructors.
	
	
	void assignTo(CPP_Entity* parent);
	
	void update();
	
private:
	CPP_Entity* parent;
	CPP_MaskList* list;
	
};

#endif /* CPP_Mask_h */
