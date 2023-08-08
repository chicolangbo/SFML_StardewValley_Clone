#pragma once
#include "Singleton.h"

class ResourceMgr : public Singleton<ResourceMgr>
{
	friend Singleton<ResourceMgr>;

protected:
	ResourceMgr() = default;
	virtual ~ResourceMgr() override;
	
	//씬 적용인지 전체 적용인지 구별하기 위해서 변경
	// 김민지, 230807, 추가
	map<string, sf::IntRect>mapImagePos;
	//
	map<string, tuple<sf::Texture*, bool>>mapTexture;
	map<string, tuple<sf::Font*, bool>>mapFont;
	map<string, tuple<sf::SoundBuffer*, bool>>mapSoundBuffer;
	map<string, tuple<AnimationClip*, bool>>mapAnimationClip;

	/*std::map<std::string, sf::Texture*> mapTexture;
	std::map<std::string, sf::Font*> mapFont;
	std::map<std::string, sf::SoundBuffer*> mapSoundBuffer;
	std::map<std::string, AnimationClip*> mapAnimationClip;*/

public:

	void Init();

	void UnLoadAll();

	void LoadFromCSV(const string path, bool isDefault = false);
	// 김민지, 230807, 함수 수정
	//void Load(ResourceTypes t, const std::string path, bool isDefault = false); 

	void Load(ResourceTypes t, std::string path, std::string name = "N", int left = 0, int top = 0, int width = 0, int height = 0, bool isDefault = false);
	//

	//isDefault가 ture이면 씬이 바뀔 때 빼지 않음
	//void Load(const std::vector<std::tuple<ResourceTypes, std::string>>& array);

	void Unload(ResourceTypes t, const std::string path);
	//void Unload(const std::vector<std::tuple<ResourceTypes, std::string>>& array);


	sf::Texture* GetTexture(const std::string& id);

	// 김민지, 230807, 스프라이트시트 속 단일이미지 사용 가능하게끔 추가
	sf::IntRect GetTextureRect(const std::string& name);
	//

	sf::Font* GetFont(const std::string& id);
	sf::SoundBuffer* GetSoundBuffer(const std::string& id);

	AnimationClip* GetAnimationClip(const string& id);

};

#define RESOURCE_MGR (ResourceMgr::Instance())
