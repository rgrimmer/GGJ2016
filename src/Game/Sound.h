#pragma once

class Sound
{
public:
	
	enum ESound
	{
		e_sound_music_menu,
		e_sound_music_game,
		e_sound_max
	};

	//
	// Construction / Destruction
	explicit					Sound					(void);
	virtual						~Sound					(void);

	void						Initialize				(void);
	void						Release					(void);

	void						Update					(float dt);

	void						PlaySound				(ESound eSound);

protected:

private:


public:

protected:

private:

	int									m_aSound				[e_sound_max];
};