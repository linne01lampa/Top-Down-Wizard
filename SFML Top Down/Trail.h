#ifndef TRAIL_HEADER
#define TRAIL_HEADER

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

		int myTilingCount = 0;
		sf::Vector2f myPosition;
		sf::Vector2f myLastPoint;
		float myTextureWidth = 0.f;

		float myLifetime = 2.5f;
		float minDistance = 50.f;
		sf::Color myColor = sf::Color::White;
		sf::Color myEndColor = sf::Color::White;
		sf::Texture* myTexture = nullptr;
		ETextureMode myTextureMode = ETextureMode::Repeated;
		std::pair<float, float> myWidthOffset;
		float myOffsetRadius = 0.f;

		struct STrailSegment
		{
			sf::Vector2f myPosition;
			sf::Vector2f myOffset;
			float myTimer = 0.f;
			sf::Color myColor;
			float myRotation;
			float myYCoord = 0.f;
			float myWidth;
		};
		std::list<STrailSegment> myPoints;

	};
}
#endif
