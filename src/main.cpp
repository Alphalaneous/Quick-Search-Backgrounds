#include <Geode/Geode.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>

using namespace geode::prelude;

class $modify(MyLevelBrowserLayer, LevelBrowserLayer) {

	bool init(GJSearchObject* p0) {
		
		if(!LevelBrowserLayer::init(p0)) return false;

		std::string bgTexture;

		switch (p0->m_searchType)
		{
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

		if (!bgTexture.empty()) {
			CCSprite* bg = CCSprite::create(bgTexture.c_str());
			bg->setUserObject("width", CCFloat::create(bg->getContentSize().width));
			bg->setUserObject("height", CCFloat::create(bg->getContentSize().height));
			bg->setID("bg-overlay"_spr);
			bg->setScale(0.8f);
			bg->setOpacity(25);
			bg->setBlendFunc({ GL_ONE, GL_ONE_MINUS_CONSTANT_ALPHA });
			ccTexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
			bg->getTexture()->setTexParameters(&params);
			
			bg->setZOrder(-1);
			bg->setAnchorPoint({0, 0});
			bg->setRotation(10);
			CCSize winSize = CCDirector::get()->getWinSize();

			bg->setPosition({-winSize.width/2, -winSize.height/2});

			auto rect = bg->getTextureRect();
			rect.size = rect.size * (CCPoint(winSize) / CCPoint(bg->getScaledContentSize()) * 2);
			rect.origin = CCPoint{0, 0};
			bg->setTextureRect(rect);
			addChild(bg);

			animateBG(0);
			schedule(schedule_selector(MyLevelBrowserLayer::animateBG));
		}
		return true;
	}

	void animateBG(float dt){

		CCSprite* bg = typeinfo_cast<CCSprite*>(getChildByID("bg-overlay"_spr));

		auto width = static_cast<CCFloat*>(bg->getUserObject("width"))->getValue();
		auto height = static_cast<CCFloat*>(bg->getUserObject("height"))->getValue();

		auto rect = bg->getTextureRect();

		static float dX;
		static float dY;

		rect.origin.x = dX;
		rect.origin.y = dY;

		dX = rect.origin.x - 2 * dt;
		dY = rect.origin.y + 6 * dt;

		if(dX >= std::abs(width)) {
			dX = 0;
		}

		if(dY >= std::abs(height)) {
			dY = 0;
		}

		rect.origin = CCPoint{dX, dY};

        bg->setTextureRect(rect);
	}
};
