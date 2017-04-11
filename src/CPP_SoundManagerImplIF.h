//
//  CPP_SoundManagerImplIF.h
//  CPPunkDev
//
//  Created by Wade Okawa-Scannell on 4/9/17.
//  Copyright © 2017 Wade Okawa-Scannell. All rights reserved.
//

#ifndef CPP_SoundManagerImplIF_h
#define CPP_SoundManagerImplIF_h

class CPP_SoundManagerImplIF
{
public:
	CPP_SoundManagerImplIF() = default;
	virtual ~CPP_SoundManagerImplIF() = default;
	CPP_SoundManagerImplIF(const CPP_SoundManagerImplIF&) = default;
	CPP_SoundManagerImplIF(CPP_SoundManagerImplIF&&) = default;
	CPP_SoundManagerImplIF& operator=(const CPP_SoundManagerImplIF&) = default;
	CPP_SoundManagerImplIF& operator=(CPP_SoundManagerImplIF&&) = default;
	
	virtual void processSound() const = 0;
	
};

#endif /* CPP_SoundManagerImplIF_h */
