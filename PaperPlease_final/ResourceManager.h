#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include "ImageResource.h"
namespace Gdiplus {
	class Graphics;
	class Image;
}

class ResourceManager
{
public:
	//singleton
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}
	//preloading
	void PreloadingImageJson();
	//lazy loading
	void LazyloadingImageJson(std::string& strkey, std::string& strimg);
	//resource memory clear
	void Clear();
	//initial
	void InitImgJson();
	//get rootsegmention section key (value use)
	std::optional<std::string>GetSectionKey(const std::wstring& name);
	//get image
	ImageResource* GetImageResource(const std::wstring& key);
private:
	//file load
	Gdiplus::Image* LoadImageFromFile(const std::wstring& path); 
private:
	//singleton
	ResourceManager() = default;
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	std::unordered_map<std::wstring, ImageResource> _images;
	nlohmann::json _jsonImgData;
	
};

//�ʱ� �̹��� �ε��� �͵��� ��Ȯ�ϰ� �������ֱ�!
//�׵ڿ� �ǽð����� �ε带 �� ���� ��.... �ǽð� �߰� ���Ϸ� ����� ����ҵ�?
//�׷� �Լ��� 3�������ϴ°Ű�����? 


//1)���ε�
//2)�ε�����
//3)�ǽð��ε�

//4 ���Ͽ���
//5 ���ϴݱ��ʿ�
//6 �ش������� ������ ������ �ʿ�

