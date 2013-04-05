#include "PhysicsSprite.h"
#include "Settings.h"

USING_NS_CC;
PhysicsSprite::PhysicsSprite()
	:m_pBody(NULL)
{}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}


CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_tAnchorPointInPoints.x;
        y += m_tAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! m_tAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_tAnchorPointInPoints.x + -s*-m_tAnchorPointInPoints.y;
        y += s*-m_tAnchorPointInPoints.x + c*-m_tAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_tTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );
    return m_tTransform;
}