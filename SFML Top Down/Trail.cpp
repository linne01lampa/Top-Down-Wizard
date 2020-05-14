#include "Trail.h"

#include <iostream>

#include "Utilities.h"

#define WIREFRAME_MODE 0

ss::CTrail::CTrail()
{
	myWidthOffset = std::make_pair(10.f, 10.f);
}

ss::CTrail::~CTrail()
{
}

void ss::CTrail::SetPosition(const sf::Vector2f& InPos)
{
	myPosition = InPos;
}

void ss::CTrail::SetLifetime(float InLifetime)
{
	myLifetime = InLifetime;
}

void ss::CTrail::SetMinDistance(float InMinDistance)
{
	minDistance = InMinDistance;
}

void ss::CTrail::SetColor(const sf::Color& InColor)
{
	myColor = InColor;
	myEndColor = myColor;
}

void ss::CTrail::SetWidth(float InMin, float InMax)
{
	myWidthOffset = std::make_pair(InMin, InMax);
}

void ss::CTrail::SetOffset(float InRadius)
{
	myOffsetRadius = InRadius;
}

void ss::CTrail::SetTextureMode(ETextureMode InTextureMode)
{
	myTextureMode = InTextureMode;
}

void ss::CTrail::SetTexture(sf::Texture* InTexture)
{
	myTexture = InTexture;
	myTexture->setRepeated(true);
	myTextureWidth = myTexture->getSize().x;
}

void ss::CTrail::Update(float InDeltaTime)
{
	float distance2 = FLT_MAX;
	if (!myPoints.empty())
	{
		sf::Vector2f diffToLatest = myPosition - myPoints.back().myPosition;
		distance2 = Math::Length2(diffToLatest);
	}

	if (distance2 >= minDistance * minDistance)
	{
		sf::Vector2f direction = myPosition - myLastPoint;
		Math::Normalize(direction);
		myLastPoint = myPosition;
		float angle = atan2f(-direction.x, direction.y);

		if (!myPoints.empty())
		{
			auto& last = myPoints.back();
			last.myPosition = myPosition;
			last.myRotation = angle;
		}

		float segmentWidth = 0.f;
		segmentWidth = Random::GetValue(myWidthOffset.first, myWidthOffset.second);

		float r = Random::GetValue(0, 6.2832f);
		sf::Vector2f offset = Random::GetValue(0.f, myOffsetRadius) * sf::Vector2f(cosf(r), sinf(r));

		myPoints.emplace_back(STrailSegment());
		auto& p = myPoints.back();

		p.myPosition = myPosition;
		p.myOffset = offset;
		p.myTimer = myLifetime;
		p.myColor = myColor;
		p.myRotation = angle;
		p.myYCoord = static_cast<float>(myTilingCount++);
		p.myWidth = segmentWidth;
	}
	
	myPoints.remove_if([&, dt=InDeltaTime](auto& p) {
		p.myTimer -= dt;

		float t = p.myTimer / myLifetime;
		float alpha = t * t;

		p.myColor = myColor;
		p.myColor.a = 255.f * alpha;

		return (p.myTimer <= 0.f);
	});
}

void ss::CTrail::Reset()
{
	myPoints.clear();
	myTilingCount = 0;
}

void ss::CTrail::draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const
{
	sf::VertexArray va;
	size_t index = 0;
	va.resize(2);

	if (!myPoints.empty())
	{
		va.resize(myPoints.size() * 2 + 0);
#if WIREFRAME_MODE
		va.setPrimitiveType(sf::PrimitiveType::LinesStrip);
#else
		va.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
#endif
		sf::Vector2f dimensionAngle;
		for (auto& p : myPoints)
		{
			sf::Vector2f uv;
			uv.x = 0.f;
			//uv.y = (myMinDistance / myWidth) * myTextureWidth * (index/2);//myTextureWidth *  index / static_cast<float>(va.getVertexCount() / 2.f);
			if (myTextureMode == ETextureMode::Repeated)
			{
				uv.y = p.myYCoord * myTextureWidth;
			}
			else
			{
				uv.y = myTextureWidth * static_cast<float>(index / 2) / static_cast<float>(myPoints.size());
			}

			dimensionAngle = 0.5f * p.myWidth * sf::Vector2f(cosf(p.myRotation), sinf(p.myRotation));

			va[index++] = sf::Vertex(p.myOffset + p.myPosition - dimensionAngle, p.myColor, uv);
			uv.x = myTextureWidth;
			va[index++] = sf::Vertex(p.myOffset + p.myPosition + dimensionAngle, p.myColor, uv);
		}

		
		sf::Vector2f fromLast = myPosition - myLastPoint;
		Math::Normalize(fromLast);
		float angle = atan2f(-fromLast.x, fromLast.y);
		sf::Vector2f rotation = 0.5f * myPoints.back().myWidth * sf::Vector2f(cosf(angle), sinf(angle));
		va[index - 2].position = myPoints.back().myOffset + (myPosition - rotation);
		va[index - 1].position = myPoints.back().myOffset + (myPosition + rotation);
		
	}

	sf::RenderStates rs;
	if (myTexture)
	{
		rs.texture = myTexture;
	}

	InTarget.draw(&va[0], va.getVertexCount(), va.getPrimitiveType(), rs);
}

#undef WIREFRAME_MODE