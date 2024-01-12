#pragma once

class Config
{
public:
	static inline struct Configuration
	{
		struct
		{
			bool enable = false;
		}client;
		struct
		{
			struct
			{
				bool enable = false;
			}weapon;
			struct
			{
				bool enable = false;
			}cannon;
			struct
			{
				bool enable = false;
			}harpoon;
		}aimbot;
		struct
		{
			struct
			{
				bool enable = false;
			}items;
			struct
			{
				bool enable = false;
			}ship;
			struct
			{
				bool enable = false;
			}other;
		}esp;
	};
};