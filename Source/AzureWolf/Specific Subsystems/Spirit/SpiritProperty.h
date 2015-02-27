#pragma once

//include string class
/*
class TiXmlElement;

class SpiritProperty
{
	friend class SpiritFactory;

protected:
	StrongSpiritPtr m_pOwner;
public:
	virtual ~SpiritProperty(void){m_pOwner.reset();}

	virtual bool VInit(TiXmlElement* pData) = 0;
	virtual void VPostInit(void){}
	virtual void VUpdate(int deltaMs){}
	virtual void VOnChanged(void){}

	virtual TiXmlElement* VGenerateXml(void) = 0;

	virtual PropertyID VGetId(void) const { return GetIdFromName(VGetName()); }
	virtual const char *VGetName() const = 0;
    static PropertyID GetIdFromName(const char* componentStr)
	{
		//void* rawId = HashedString::hash_name(componentStr);
		//return reinterpret_cast<ComponentId>(rawId);
	}

private:
	void SetOwner(StrongSpiritPtr pOwner){m_pOwner = pOwner;}

};*/