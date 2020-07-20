#pragma once

#include <string>
#include <unordered_map>
#include "New/Rendering/Shared/Texture/Texture.h"
#include "New/Scene/Shared/Updatable/Updatable.h"

namespace Atlas {
	class TextureManager : public Updatable {
	private:
		struct ImageData {
			int width, height, nrChannels;
			unsigned char* data;
			const std::string& filepath;

			ImageData(int w, int h, int nr, unsigned char* dat, const std::string& path)
				: width(w), height(h), nrChannels(nr), data(dat), filepath(path)
			{

			}
		};

		std::unordered_map<const std::string&, Texture*> loadedTextures;

		ImageData& ReadTexture(const std::string& filepath);
		GLuint LoadTexture(ImageData& data);
	public:
		TextureManager();
		~TextureManager();

		virtual void Update(float deltaTime);

		Texture* LoadTexture(const std::string& filepath);

		Texture* GetTexture(Texture* tex);
		void DeleteReference(Object* obj);
		void AddReference(Object* obj);

		void DeleteTexture(const std::string& name);
		void DeleteTexture(Texture* tex);

		void SetTexture(Texture* newTex);
		void ReplaceTexture(Texture* newTex);
	};
}