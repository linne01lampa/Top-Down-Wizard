#include "Trail.h"

#include <iostream>

#include "Utilities.h"

#define WIREFRAME_MODE 0

ss::CTrail::CTrail()
{
	widthOffset = std::make_pair(10.f, 10.f);
}

ss::CTrail::~CTrail()
{
}

void ss::CTrail::SetPosition(const sf::Vector2f& InPos)
{
	position = InPos;
}

void ss::CTrail::SetLifetime(float InLifetime)
{
	lifetime = InLifetime;
}

void ss::CTrail::SetMinDistance(float InMinDistance)
{
	minDistance = InMinDistance;
}

void ss::CTrail::SetColor(const sf::Color& InColor)
{
	color = InColor;
	endColor = color;
}

void ss::CTrail::SetWidth(float InMin, float InMax)
{
	widthOffset = std::make_pair(InMin, InMax);
}

void ss::CTrail::SetOffset(float InRadius)
{
	offsetRadius = InRadius;
}

void ss::CTrail::SetTextureMode(ETextureMode InTextureMode)
{
	textureMode = InTextureMode;
}

void ss::CTrail::SetTexture(sf::Texture* InTexture)
{
	texture = InTexture;
	texture->setRepeated(true);
	textureWidth = texture->getSize().x;
}

void ss::CTrail::Update(float InDeltaTime)
{
	float distance2 = FLT_MAX;
	if (!points.empty())
	{
		sf::Vector2f diffToLatest = position - points.back().position;
		distance2 = Math::Length2(diffToLatest);
	}

	if (distance2 >= minDistance * minDistance)
	{
		sf::Vector2f direction = position - lastPoint;
		Math::Normalize(direction);
		lastPoint = position;
		float angle = atan2f(-direction.x, direction.y);

		if (!points.empty())
		{
			auto& last = points.back();
			last.position = position;
			last.rotation = angle;
		}

		float segmentWidth = 0.f;
		segmentWidth = Random::GetValue(widthOffset.first, widthOffset.second);

		float r = Random::GetValue(0, 6.2832f);
		sf::Vector2f offset = Random::GetValue(0.f, offsetRadius) * sf::Vector2f(cosf(r), sinf(r));

		points.emplace_back(STrailSegment());
		auto& p = points.back();

		p.position = position;
		p.offset = offset;
		p.timer = lifetime;
		p.color = color;
		p.rotation = angle;
		p.yCoord = static_cast<float>(tilingCount++);
		p.width = segmentWidth;
	}
	
	points.remove_if([&, dt=InDeltaTime](auto& p) {
		p.timer -= dt;

		float t = p.timer / lifetime;
		float alpha = t * t;

		p.color = color;
		p.color.a = 255.f * alpha;

		return (p.timer <= 0.f);
	});
}

void ss::CTrail::Reset()
{
	points.clear();
	tilingCount = 0;
}

void ss::CTrail::draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const
{
	sf::VertexArray va;
	size_t index = 0;
	va.resize(2);

	if (!points.empty())
	{
		va.resize(points.size() * 2 + 0);
#if WIREFRAME_MODE
		va.setPrimitiveType(sf::PrimitiveType::LinesStrip);
#else
		va.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
#endif
		sf::Vector2f dimensionAngle;
		for (auto& p : points)
		{
			sf::Vector2f uv;
			uv.x = 0.f;
			//uv.y = (minDistance / width) * textureWidth * (index/2);//textureWidth *  index / static_cast<float>(va.getVertexCount() / 2.f);
			if (textureMode == ETextureMode::Repeated)
			{
				uv.y = p.yCoord * textureWidth;
			}
			else
			{
				uv.y = textureWidth * static_cast<float>(index / 2) / static_cast<float>(points.size());
			}

			dimensionAngle = 0.5f * p.width * sf::Vector2f(cosf(p.rotation), sinf(p.rotation));

			va[index++] = sf::Vertex(p.offset + p.position - dimensionAngle, p.color, uv);
			uv.x = textureWidth;
			va[index++] = sf::Vertex(p.offset + p.position + dimensionAngle, p.color, uv);
		}

		
		sf::Vector2f fromLast = position - lastPoint;
		Math::Normalize(fromLast);
		float angle = atan2f(-fromLast.x, fromLast.y);
		sf::Vector2f rotation = 0.5f * points.back().width * sf::Vector2f(cosf(angle), sinf(angle));
		va[index - 2].position = points.back().offset + (position - rotation);
		va[index - 1].position = points.back().offset + (position + rotation);
		
	}

	sf::RenderStates rs;
	if (texture)
	{
		rs.texture = texture;
	}

	InTarget.draw(&va[0], va.getVertexCount(), va.getPrimitiveType(), rs);
}

#undef WIREFRAME_MODE