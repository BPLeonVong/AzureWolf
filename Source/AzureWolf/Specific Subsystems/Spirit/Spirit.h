#pragma once
/*
class TiXmlElement;
typedef std::string SpiritType;

class Spirit
{
	friend class SpiritFactory;

public:

	typedef std::map<PropertyID, StrongSpiritPropertyPtr> SpiritProperties;

private:

	SpiritID m_ID;
	SpiritProperties m_Properties;
	SpiritType m_SpiritType;

	std::string m_XMLSource;

public:
	explicit Spirit(SpiritID id);
	~Spirit (void);

	bool Init(TiXmlElement *pData);
	void PostInit(void);
	void Destroy(void);
	void Update(int deltaMs);

	std::string Spirit::toXML();

	SpiritID GetID(void) const { return m_ID;}
	SpiritType GeType(void) const {return m_SpiritType;}
	
	template <class PropertyType>
    weak_ptr<PropertyType> GetProperty(PropertyID id)
    {
        SpiritProperties::iterator findIt = m_Properties.find(id);
        if (findIt != m_Properties.end())
        {
            StrongSpiritPropertyPtr pBase(findIt->second);
            shared_ptr<PropertyType> pSub(static_pointer_cast<PropertyType>(pBase));
            weak_ptr<PropertyType> pWeakSub(pSub);
            return pWeakSub;
        }
        else
        {
            return weak_ptr<PropertyType>();
        }
    }	

	template <class PropertyType>
    weak_ptr<PropertyType> GetProperty(const char  *name)
    {
		PropertyID id = SpiritComponent::GetIDFromName(name);
        SpiritProperties::iterator findIt = m_Properties.find(id);
        if (findIt != m_Properties.end())
        {
            StrongSpiritPropertyPtr pBase(findIt->second);
            shared_ptr<PropertyType> pSub(static_pointer_cast<PropertyType>(pBase));
            weak_ptr<PropertyType> pWeakSub(pSub);
            return pWeakSub;
        }
        else
        {
            return weak_ptr<PropertyType>();
        }
    }

	const SpiritProperties* GetProperties() { return &m_Properties; }

    void AddProperty(StrongSpiritPropertyPtr pComponent);
};*/