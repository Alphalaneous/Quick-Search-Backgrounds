#include <Geode/Geode.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {

	struct Fields {
		CCSprite* m_background;
		CCSize m_size;
	};

	bool init(GJSearchObject* searchObj) {
		if (!LevelBrowserLayer::init(searchObj)) return false;

		std::string bgTexture;

		switch (searchObj->m_searchType) {
			case SearchType::Downloaded:
				bgTexture = "DownloadsBG.png"_spr;
				break;
			case SearchType::Awarded:
				bgTexture = "AwardedBG.png"_spr;
				break;
			case SearchType::Followed:
				bgTexture = "FollowedBG.png"_spr;
				break;
			case SearchType::Friends:
				bgTexture = "FriendsBG.png"_spr;
				break;
			case SearchType::MostLiked:
				bgTexture = "LikesBG.png"_spr;
				break;
			case SearchType::Magic:
				bgTexture = "MagicBG.png"_spr;
				break;
			case SearchType::Recent:
				bgTexture = "RecentBG.png"_spr;
				break;
			case SearchType::Sent:
				bgTexture = "SentBG.png"_spr;
				break;
			case SearchType::Trending:
				bgTexture = "TrendingBG.png"_spr;
				break;
			default:
				break;
		}


		if (bgTexture.empty()) return true;

		auto fields = m_fields.self();

		fields->m_background = CCSprite::create(bgTexture.c_str());
		fields->m_size = fields->m_background->getContentSize();
		fields->m_background->setID("bg-overlay"_spr);
		fields->m_background->setScale(0.8f);
		fields->m_background->setOpacity(25);
		fields->m_background->setBlendFunc({ GL_ONE, GL_ONE_MINUS_CONSTANT_ALPHA });
		ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
		fields->m_background->getTexture()->setTexParameters(&params);
		
		fields->m_background->setZOrder(-1);
		fields->m_background->setAnchorPoint({0, 0});
		fields->m_background->setRotation(10);
		auto winSize = CCDirector::get()->getWinSize();

		fields->m_background->setPosition({-winSize.width/2, -winSize.height/2});

		auto rect = fields->m_background->getTextureRect();
		rect.size = rect.size * (CCPoint(winSize) / CCPoint(fields->m_background->getScaledContentSize()) * 2);
		rect.origin = CCPoint{0, 0};
		fields->m_background->setTextureRect(rect);
		addChild(fields->m_background);

		animateBG(0);
		schedule(schedule_selector(MyLevelBrowserLayer::animateBG));
		
		return true;
	}

	void animateBG(float dt){
		auto fields = m_fields.self();

		auto rect = fields->m_background->getTextureRect();

		static float dX;
		static float dY;

		rect.origin.x = dX;
		rect.origin.y = dY;

		dX = rect.origin.x - 2 * dt;
		dY = rect.origin.y + 6 * dt;

		if (dX >= std::abs(fields->m_size.width)) {
			dX = 0;
		}

		if (dY >= std::abs(fields->m_size.height)) {
			dY = 0;
		}

		rect.origin = CCPoint{dX, dY};

        fields->m_background->setTextureRect(rect);
	}
};
