#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

#include <list>

namespace ss
{
	class CTrail : public sf::Drawable
	{
	public:

		enum class ETextureMode {
			Repeated,
			Stretched
		};

		CTrail();
		virtual ~CTrail();

		void SetPosition(const sf::Vector2f& InPos);
		void SetLifetime(float InLifetime);
		void SetMinDistance(float InMinDistance);
		void SetColor(const sf::Color& InColor);
		void SetWidth(float InMin, float InMax);
		void SetOffset(float InRadius);

		void SetTextureMode(ETextureMode InTextureMode);
		void SetTexture(sf::Texture* InTexture);

		void Update(float InDeltaTime);
		void Reset();
		
	protected:
		// Drawable
		virtual void draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const override;

	private:

		int tilingCount = 0;
		sf::Vector2f position;
		sf::Vector2f lastPoint;
		float textureWidth = 0.f;

		float lifetime = 2.5f;
		float minDistance = 50.f;
		sf::Color color = sf::Color::White;
		sf::Color endColor = sf::Color::White;
		sf::Texture* texture = nullptr;
		ETextureMode textureMode = ETextureMode::Repeated;
		std::pair<float, float> widthOffset;
		float offsetRadius = 0.f;

		struct STrailSegment
		{
			sf::Vector2f position;
			sf::Vector2f offset;
			float timer = 0.f;
			sf::Color color;
			float rotation;
			float yCoord = 0.f;
			float width;
		};
		std::list<STrailSegment> points;

	};
}