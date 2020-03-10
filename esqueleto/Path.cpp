#include "stdafx.h"
#include "Path.h"

Path::Path(const char* filename)
{
    TiXmlDocument doc(filename);
    if (!doc.LoadFile())
    {
        fprintf(stderr, "Couldn't read params from %s", filename);

    }
    TiXmlHandle hDoc(&doc);
    TiXmlElement* pElem;
    pElem = hDoc.FirstChildElement().Element();
    if (!pElem)
    {
        fprintf(stderr, "Invalid format for %s", filename);

    }
    TiXmlHandle hRoot(pElem);
    TiXmlHandle hPoints = hRoot.FirstChildElement("points");

    TiXmlElement* point = hPoints.FirstChildElement("point").Element();
    while (point)
    {
        USVec2D* pPoint = new USVec2D(0, 0);
        float fX = 0;
        float fY = 0;
        point->Attribute("x", &fX);
        point->Attribute("y", &fY);
        pPoint->mX = fX;
        pPoint->mY = fY;
        m_tPoints.push_back(*pPoint);

       TiXmlNode* pointNode = point->NextSibling();;
       if (pointNode == nullptr)
       {
           point = nullptr;
       }
       else
       {
           point = pointNode->ToElement();
       }
    }

}
void Path::DrawDebug()
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 0.5f);
    USVec2D vPreviousPoint = m_tPoints[0];
    for (int i = 1; i < m_tPoints.size(); i++)
    {
        MOAIDraw::DrawLine(vPreviousPoint, m_tPoints[i]);
        vPreviousPoint = m_tPoints[i];
    }
}