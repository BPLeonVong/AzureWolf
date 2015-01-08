#include "AzureWolfStd.h"
#include "Spirit.h"
#include "SpiritProperty.h"

Spirit::Spirit(SpiritID id)
{
	m_ID = id;
	m_SpiritType = "???";

	m_XMLSource = "???";
}

Spirit::~Spirit(void)
{
	//prompt to user removing spirit
}

void Spirit::PostInit(void)
{
	for (SpiritProperties::iterator it = m_Properties.begin(); it != m_Properties.end(); ++it)
	{
		it->second->VPostInit();
	}
}

void Spirit::Destroy(void)
{
	m_Properties.clear();
}

void Spirit::Update(int deltaMs)
{
	for(SpiritProperties::iterator it = m_Properties.begin(); it != m_Properties.end();++it)
	{
		it->second->VUpdate(deltaMs);
	}
}

/*
std::string Spirit::toXML()
{
    TiXmlDocument outDoc;

    TiXmlElement* pActorElement = GCC_NEW TiXmlElement("Actor");
    pActorElement->SetAttribute("type", m_type.c_str());
	pActorElement->SetAttribute("resource", m_resource.c_str());

    for (auto it = m_Properties.begin(); it != m_Properties.end(); ++it)
    {
        StrongSpiritPropertyPtr pComponent = it->second;
        TiXmlElement* pComponentElement = pComponent->VGenerateXml();
        pActorElement->LinkEndChild(pComponentElement);
    }

    outDoc.LinkEndChild(pActorElement);
	TiXmlPrinter printer;
	outDoc.Accept(&printer);

	return printer.CStr();
}*/

void Spirit::AddProperty(StrongSpiritPropertyPtr pProperty)
{
    std::pair<SpiritProperties::iterator, bool> success = m_Properties.insert(std::make_pair(pProperty->VGetId(), pProperty));
}