#include "stdafx.h"
#include "Obstacles.h"

Obstacles::Obstacles(const char* filename)
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
    TiXmlHandle hPoints = hRoot.FirstChildElement("obstacles");

    TiXmlElement* point = hPoints.FirstChildElement("obstacle").Element();
    while (point)
    {
        USVec2D* pPoint = new USVec2D(0, 0);
        float fX = 0;
        float fY = 0;
        float fRadius;
        point->Attribute("x", &fX);
        point->Attribute("y", &fY);
        point->Attribute("r", &fRadius);
        pPoint->mX = fX;
        pPoint->mY = fY;
        Obstacle* pObstacle = new Obstacle(fRadius, *pPoint);
        m_tObstacles.push_back(*pObstacle);

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
void Obstacles::DrawDebug()
{
    MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();

    for (int i = 0; i < m_tObstacles.size(); i++)
    {
        Obstacle obstacle = m_tObstacles[i];
        if (obstacle.m_bColliding)
        {
            gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 0.25f);
        }
        else
        {
            gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 0.25f);
        }
        MOAIDraw::DrawEllipseOutline(obstacle.m_vPosition.mX, obstacle.m_vPosition.mY, obstacle.m_fRadius, obstacle.m_fRadius, 16);
    }
}