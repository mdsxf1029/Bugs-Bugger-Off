#pragma once
#include "AudioEngine.h"
#include "Sets/manager.h"

using namespace cocos2d::experimental;

class AudioManager {
public:
	static AudioManager& getInstance()                               //��ȡʵ�� ��Ƶ
    {
		static AudioManager instance;                               //��̬�ֲ�����
		return instance;                                            //����ʵ��
    }

    void playIntroMusic()                                           //��������
    {
		if (!hasPlayedIntroMusic)								    //���û�в�������
        {
			AudioEngine::play2d("intro.mp3", false, 1.0f);		    //��������
			hasPlayedIntroMusic = true;							    //����Ϊ��������
        }
    }

	void resetIntroMusicFlag()									    //�������ֱ�־
    {
		hasPlayedIntroMusic = false;								 //����Ϊû�в�������
    }

private:
	AudioManager() : hasPlayedIntroMusic(false) {} 			   //���캯��
    bool hasPlayedIntroMusic;
};

