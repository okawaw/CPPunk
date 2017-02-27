//
//  CPP_Input.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 2/26/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_Input_h
#define CPP_Input_h

class CPP_Engine;

class CPP_Input
{
	friend CPP_Engine;
public:
	CPP_Input();
	~CPP_Input() = default;
	CPP_Input(const CPP_Input&) = default;
	CPP_Input(CPP_Input&&) = default;
	CPP_Input& operator=(const CPP_Input&) = default;
	CPP_Input& operator=(CPP_Input&&) = default;
	
	void update();
};

#endif /* CPP_Input_h */
