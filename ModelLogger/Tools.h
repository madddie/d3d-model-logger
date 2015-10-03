#include "Include.h"

class CTools
{
public:
	char Title[64];
	char StartTime[16];

	FILE* File;

	DWORD FindPattern( unsigned char* _Data, unsigned int Length, const unsigned char* _Pattern, const char* _Mask )
	{
		const unsigned char* end = _Data + Length - strlen( _Mask );

		int num_masks = ceil( ( float ) strlen( _Mask ) / ( float ) 16 );
		int masks[ 32 ]; //32*16 = enough masks for 512 bytes

		memset( masks, 0, num_masks*sizeof( int ) );

		for ( int i = 0; i < num_masks; ++i )
			for ( int j = strnlen( _Mask + i * 16, 16 ) - 1; j >= 0; --j )

				if ( _Mask[ i * 16 + j ] == 'x' )
					masks[ i ] |= 1 << j;

		__m128i xmm1 = _mm_loadu_si128( ( const __m128i * ) _Pattern );
		__m128i xmm2, xmm3, mask;

		for ( ; _Data != end; _mm_prefetch( ( const char* ) ( ++_Data + 64 ), _MM_HINT_NTA ) )
		{
			if ( _Pattern[ 0 ] == _Data[ 0 ] )
			{
				xmm2 = _mm_loadu_si128( ( const __m128i * ) _Data );
				mask = _mm_cmpeq_epi8( xmm1, xmm2 );

				if ( ( _mm_movemask_epi8( mask )&masks[ 0 ] ) == masks[ 0 ] )
				{
					for ( int i = 1; i < num_masks; ++i )
					{
						xmm2 = _mm_loadu_si128( ( const __m128i * ) ( _Data + i * 16 ) );
						xmm3 = _mm_loadu_si128( ( const __m128i * ) ( _Pattern + i * 16 ) );
						mask = _mm_cmpeq_epi8( xmm2, xmm3 );

						if ( ( _mm_movemask_epi8( mask )&masks[ i ] ) == masks[ i ] )
						{
							if ( ( i + 1 ) == num_masks )
								return ( DWORD ) _Data;
						}
						else goto cont;
					}
					return ( DWORD ) _Data;
				}
			}cont:;
		}
		return NULL;
	}

	void CreateLog()
	{
		system( "mkdir c:\\ModelLogger" );

		sprintf(Title, "C:\\ModelLogger\\Logs - %d.txt", GetTickCount());

		File = fopen(Title, "w");
	}

	void CreateConsole()
	{
		HANDLE lStdHandle = 0;
		int hConHandle = 0;
		FILE *fp = 0;
		AllocConsole();
		lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		hConHandle = _open_osfhandle(PtrToUlong(lStdHandle), 0x4000);
		SetConsoleTitle("Console");
		SetConsoleTextAttribute(lStdHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		fp = _fdopen(hConHandle, "w");
		*stdout = *fp;
		setvbuf(stdout, NULL, _IONBF, 0);
	}

	void Start()
	{
		GetTimeFormat(NULL, NULL, NULL, NULL, StartTime, 15);

		CreateConsole();
		CreateLog();
	}

	void WriteLog(const char* Text, ...)
	{
		fopen(Title, "a+");

		char Buffer[1024] = { '\0' };
		va_list va_alist;

		va_start(va_alist, Text);
		vsprintf_s(Buffer, Text, va_alist);
		va_end(va_alist);

		fputs(Buffer, File);

		fclose(File);
	}
}; extern CTools* Tools;